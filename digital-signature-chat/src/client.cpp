//client.cpp
//Клиент
/*
Подключается к серверу
Подключается к серверу
Отправляет/получает сообщения
*/
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include "hash.h"
#include "rsa.h"
#include "elgamal.h"
#include "network.h"
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
using namespace std;
//Отправка сообщения
void send_msg(int s, const string& msg) {
    uint32_t size = msg.size();
    send(s, (char*)&size, sizeof(size), 0);
    send(s, msg.data(), size, 0);
}
//Получение сообщения
string recv_msg(int s) {
    uint32_t size;
    int r = recv(s, (char*)&size, sizeof(size), 0);
    if (r <= 0){
        return "";
    }
    string msg(size, '\0');
    int t = 0;
    while (t < size) {
        r = recv(s,&msg[0] + t,size - t,0);
        if (r <= 0){
            return "";
        }
        t += r;
    }
    return msg;
}
//Поток отправки (ввод пользователя)
void send_l(int s, string name,string alg) {
   string msg;
    while (true) {
        cout<<sys_msg<<"Enter your message ->";
        getline(cin, msg);
    if (msg.empty()) {continue;}
        Signature v;
        if(alg == "RSA") {
            v=rsa_t(msg);
        }
        else if(alg == "ELGAMAL"){
            v=elgamal_t(msg);
        }
        Packet p;
        p.type = "MSG";
        p.name = name;
        p.text = msg;
        p.alg = alg;
        p.r_m = v.r_m;
        p.s = v.s;
        p.e_p=v.e_p;
        p.n_g=v.n_g;
        p.y=v.y;
        send_msg(s, serialize(p));
    }
}
//Поток получения (вывод сообщений)
void recv_l(int s) {
    while (true) {
        string t = recv_msg(s);
        if (t.empty()) {
            cout << "\n[SYSTEM] Disconnected from server.\n";
            break;
        }
        Packet p = deserialize(t);
        cout << "\n[" << p.name << "] " << p.text << "\n"<< sys_msg << "Enter your message -> ";
        cout.flush();
    }
}
int main() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    srand(time(0));
    Socket s = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in ser{};
    ser.sin_family = AF_INET;
    ser.sin_port = htons(1111);
    inet_pton(AF_INET, "127.0.0.1", &ser.sin_addr);
    if (connect(s, (sockaddr*)&ser, sizeof(ser)) < 0) {
        cout << error << "Cannot connect to server!\n";
        return 1;
    }    
    string name;
    cout<<sys_msg<<"WELCOME!"<<line<<"What is your name?"<<input<<"enter your answer ->";
    cin >> name;
    cin.ignore();
    Packet p;
    p.type = "LOGIN";
    p.name = name;
    p.text = "";
    p.alg = "";
    p.r_m = 0;
    p.s = 0;
    p.e_p=0;
    p.n_g=0;
    p.y=0;
    send_msg(s, serialize(p));
    cout << "Connected to server\n";
    string alg;
    int c;
    cout << sys_msg << "Choose signature algorithm:\n1) RSA\n2) ElGamal\n" << input << "-> ";
    input_ra(c, 2);
    if(c == 1){
        alg = "RSA";
    }
    else{
        alg = "ELGAMAL";
    }
    cout << sys_msg << "Connected! Algorithm: " << alg << "\n";
    thread t(send_l, s, name, alg);
    t.detach();
    recv_l(s);
    closeSocket(s);
    return 0;
}
