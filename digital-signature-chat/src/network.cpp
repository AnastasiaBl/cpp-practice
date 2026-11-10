//network.cpp


#include <vector>
#include <string> 
#include <iostream> 
#include <limits>
#include <cstdlib>
using namespace std;
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef SOCKET Socket;
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
typedef int Socket;
#endif
string line = "\n------------------------------------------------------------------------------------------------------------\n";
string sys_msg = "\n[SYSTEM] ";
string warning = "\n[WARNING] ";
string input = "\n[INPUT] ";
string error = "\n[ERROR] ";
string result = "\n[RESULT] ";
void closeSocket(Socket sock)
{
#ifdef _WIN32
    closesocket(sock);
#else
    close(sock);
#endif
}
void initSockets()
{
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
}
void cleanupSockets()
{
#ifdef _WIN32
    WSACleanup();
#endif
}
struct Packet {
    string type;     // MSG
    string name;   
    string text;     
    string alg;
    int r_m;
    int s;
    int e_p;
    int n_g;
    int y;
};
struct Signature {
    int r_m;
    int s;
    int e_p;
    int n_g;
    int y;
};
vector<string> split(const string& s, char delim) {
    vector<string> parts;
    string temp;
    for (char c : s) {
        if (c == delim) {
            parts.push_back(temp);
            temp.clear();
        } else {
            temp += c;
        }
    }
    parts.push_back(temp);
    return parts;
}
string serialize(const Packet& p) {
    return p.type + "|" + p.name + "|" + p.text + "|" + p.alg + "|" + to_string(p.r_m)+"|"+to_string(p.s)+"|"+to_string(p.e_p)+"|"+to_string(p.n_g)+"|"+to_string(p.y);
}
Packet deserialize(const string& s) {
    vector<string> v = split(s, '|');
    Packet p;
    if (v.size() >= 9) {
        p.type = v[0];
        p.name = v[1];
        p.text = v[2];
        p.alg = v[3];
        p.r_m = stoll(v[4]);
        p.s = stoll(v[5]);
        p.e_p = stoll(v[6]);
        p.n_g = stoll(v[7]);
        p.y = stoll(v[8]);
    }
    return p;
}

//ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ
//ввод int
void input_int(int& n, int checkType = 0, int a = 0, int b = 0) {
    //n-перменная int
    //checkType-case проверки
    //a-минимальное значение
    //b-максимальное значение
    while (true) {
        cin >> n;
        if (cin.fail()) {
            cout << error << "\nError! Please enter an integer: ";
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            continue;
        }
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        switch (checkType) {
        case 0:
            return;

        case 1:
            if (n > 0) { return; }
            cout << error << "\nThe number must be greater than 0: ";
            break;
        case 2:
            if (n >= 0) { return; }
            cout << error << "\nThe number must not be negative: ";
            break;
        case 3:
            if (n >= a) { return; }
            cout << error << "\nThe number must be at least " << a << ": ";
            break;

        case 4:
            if (n <= b) { return; }
            cout << error << "\n The number must not exceed " << b << ": ";
            break;

        case 5:
            if (n >= a && n <= b) { return; }
            cout << error << "\nThe number must be between " << a << " and " << b << ": ";
            break;

        default:
            cout << error << "\nUnknown check type: ";
            break;
        }
    }
}
//выбор из списка вариантов
int input_ra(int& i, int a)
{
    while (true)
    {
        input_int(i);

        if (i > 0 && i <= a)
        {
            return i;
        }
        cout << endl << error << "Error! Please enter a value between 1 and " << a << ": ";
    }
}
