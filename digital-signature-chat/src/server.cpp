//server.cpp
//Сервер
/*
Слушает порт
Принимает клиентов
Пересылает сообщения
*/
#include <iostream>
#include <vector>
#include <thread> //многопоточность
#include <mutex> //синхронизация потоков
#include <algorithm> //алгоритмы STL
#include "network.h"
#include "hash.h"
#include "rsa.h"
#include "elgamal.h"


#ifdef _WIN32
#include <winsock2.h> //основной API сокетов Windows
#pragma comment(lib, "ws2_32.lib")  //подключение сетевой библиотеки Windows, для создания TCP-соединений и работы с сокетами
#define CLOSE_SOCKET closesocket //функция закрытия
#else
#include <sys/socket.h> //базовый API сокетов, создания и управления сокетами
#include <netinet/in.h> //структуры для IP-адресов, настройки IP-адреса и порта
#include <arpa/inet.h> //преобразования IP
#include <unistd.h> //системные вызовы, для закрытия сокетов
#define CLOSE_SOCKET close //функция закрытия
#endif

using namespace std;

struct Client {
    Socket s;
    string name;
};

vector<Client> clients; 
mutex mtx; 
mutex clients_mtx;

int recv_all(Socket sock, char* buffer, int size)
{
    int t = 0,v;
    while (t < size)
    {
        int r = recv(sock,buffer + t,size - t,0);
        if (r <= 0)
        {
            return v=0;
        }
        t += r;
    }
    return v=1;
}
//Отправка сообщения клиенту
int send_msg(Socket sock, const string& msg) {
    uint32_t size = msg.size(); 
    int v;
    int r = send(sock,(char*)&size,sizeof(size),0);
    if (r <= 0)
    {
        return v=0;
    }
    int total = 0;
    while (total < size)
    {
        r = send(sock,msg.data() + total,size - total,0);
        if (r <= 0)
        {
            return v=0;
        }
        total += r;
    }
    return v=1;
}
//Получение сообщения из сокета
string recv_msg(Socket sock) {
    uint32_t size;
     if (!recv_all(sock,(char*)&size,sizeof(size)))
    {
        return "";
    }
    string msg(size, '\0');
    if (!recv_all(sock,&msg[0],size))
    {
        return "";
    }
    return msg;
}
//Рассылка всем клиентам
void broadcast(const string& msg, Socket sender) {
    vector<Client> copy;
    {
        lock_guard<mutex> lock(clients_mtx); 
        copy = clients;
    }
    for (auto& c : copy) {
        if (c.s != sender) {
            send_msg(c.s, msg);
        }
    }
}
//Удаление клиента
void remove_c(Socket sock) {
    lock_guard<mutex> lock(clients_mtx);
    clients.erase( remove_if(clients.begin(), clients.end(), [sock](const Client& c){ return c.s == sock; }), clients.end() );
}
int ver_p(const Packet& p)
{
    int v;
    if (p.alg == "RSA")
    {
        v=ver_rsa(p.text,p.r_m,p.s,p.e_p,p.n_g);
        return v;
    }
    if (p.alg == "ELGAMAL")
    {
        v=ver_el(p.text,p.r_m,p.s,p.e_p,p.n_g,p.y);
        return v;
    }
    return v=0;
}
//Обработка клиента
void handle(Socket c_sock) {
    string name;
    while (true) {
        string msg = recv_msg(c_sock); 
        if (msg.empty()){
            {
                lock_guard<mutex> lock(mtx);
                cout<< name<< " disconnected\n";
            }
            break;
        }
        Packet p = deserialize(msg);
        if (p.type== "LOGIN") {
            name = p.name;
            {
                lock_guard<mutex> lock(clients_mtx);
                clients.push_back({c_sock, name});
            }
            {
                lock_guard<mutex> lock(mtx);
                cout<< name<< " connected\n";
            }
            continue;
        }
        if(p.type=="MSG") {
            int v = ver_p(p);
            {
                lock_guard<mutex> lock(mtx);
                cout << (v ? "[VERIFIED]" : "[FAKE SIGNATURE] ");
                cout << p.name << ": " << p.text << "\n";
            }

            if (v == 1) {
                broadcast(msg, c_sock);
            } else {
                send_msg(c_sock, "SIGNATURE_INVALID");
            }
        }
    }
    remove_c(c_sock);
    CLOSE_SOCKET(c_sock);
}
int main() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    srand(time(0));
    initSockets();
    Socket ser = socket(AF_INET, SOCK_STREAM, 0); 
    if (ser < 0)
    {
        cout << sys_msg<< "Socket creation error\n";
        return 1;
    }
    sockaddr_in ad{};
    ad.sin_family = AF_INET;
    ad.sin_port = htons(1111);        
    ad.sin_addr.s_addr = INADDR_ANY;  
    if (bind(ser, (sockaddr*)&ad, sizeof(ad)) < 0)
    {
        cout << sys_msg<< "Bind error\n";
        return 1;
    }
    //привязка сокета к порту
    if (listen(ser, 5) < 0)
    {
        cout << "Listen error\n";
        return 1;
    }
    cout << sys_msg<<"Server started...\n";
    while (true) {
        Socket cl = accept(ser, nullptr, nullptr);
        if (cl < 0) {continue;}
        thread(handle, cl).detach();
    }
    closeSocket(ser);
    cleanupSockets();
    return 0;
}
