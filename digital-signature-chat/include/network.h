#pragma once
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
extern string line;
extern string sys_msg;
extern string warning;
extern string input;
extern string error;
extern string result;
void closeSocket(Socket sock);
void initSockets();
void cleanupSockets();

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
string serialize(const Packet& p);
Packet deserialize(const string& s);
vector<string> split(const string& s, char delim);
void input_int(int& n, int checkType = 0, int a = 0, int b = 0);
int input_ra(int& i, int a);
