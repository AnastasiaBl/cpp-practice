//elgamal.cpp


//вычисляется хэш-сумма сообщения
//вычисляется Р - модуль,g
//генерируется\выбирается сеансовый ключ k
//вычисляется r
//вычисляется s
//подписью сообщения M является пара (r, s)

//ПРОВЕРКА ПОДПИСИ на Эль-Гамаля
//!Открытым ключом является y, g, p, закрытым ключом — число x
//!Подпись (r,s) сообщения M
//Проверяется выполнимость условия: 0 < r < p и 0 < s < p – 1.
//Вычисляется хэш-сумма m = h(M)
//Проверяем сравнение: y^r * r^s (mod p) ≡ g^m (mod p).
//!Подпись считается верной, если выполняется сравнение: y^r*r^s ≡ g^m(mod p).
//Вычисляем левую часть по модулю
//Вычисляем правую часть по модулю
//Так как правая и левая часть равны, то это означат что подпись верна.

#include <iostream> 
#include <string> 
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include "network.h"
#include "hash.h"
using namespace std;
//НОД((P-1), k), для взаимно простого числа с (P-1)
int gcd(int p, int k) {
    while (k != 0) {
        int t = p % k;
        p = k;
        k = t;
    }
    return p;
}
//проверка на простое число для P
int pr(int a) {
    if (a < 2) { return 0; }
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) { return 0; }
    }
    return 1;
}
//определение P-модуль простое число
void input_P(int& P, int min) {
    int u;
    cout << sys_msg << "Would you like to enter P <module> manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";
    input_ra(u, 2);
    if (u == 1) {
        while (true) {
            cout << warning << "P <module> must satisfy the following conditions: \n1) it must be a prime number \n2) P > M" << input << "Enter a value for [P] ->";
            input_int(P, 1);
            if (pr(P) == 1) {
                return;
            }
            cout << error << "The value entered does not meet the criteria!";
        }
    }
    else {
        while (true) {
            P = rand() % 500 + 100;
            if (pr(P) == 1) {
                return;
            }
        }
        cout << result << "Generated number [P] ->" << P;
    }
}
//определение g (целое число)
void input_g(int& g, int P) {
    int u;
    cout << sys_msg << "Would you like to enter g <primitive root> manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";
    input_ra(u, 2);
    if (u == 1) {
        cout << sys_msg << "Enter a value [g] ->";
        input_int(g);
    }
    else {
        g = rand() % (P - 2) + 2;
        cout << result << "Generated number [g] ->" << g;
    }
}
//определение x целое число (1<x<p)
void input_x(int& x, int P) {
    int u;
    cout << sys_msg << "Would you like to enter x <private key> manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";
    input_ra(u, 2);
    if (u == 1) {
        cout << input << "Enter a value for [x] ->";
        input_int(x, 5, 1, P - 1);
    }
    else {
        x = rand() % (P - 3) + 2;
        cout << result << "Generated number [x] ->" << x;
    }
}
///определение y (y = g^x mod p)
void input_y(int& y, int g, int x, int P) {
    int g1 = 1;
    while (x > 0) {
        g1 = (g1 * g) % P;
        x--;
    }
    y = g1;
    cout << sys_msg << "Value [r] ->" << y;
}
//определяется k; k целое число; взаимно простое с (P-1); 1 < k < p - 1
void input_k(int& k, int P) {
    int u;
    cout << sys_msg << "Would you like to enter the session key manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";
    input_ra(u, 2);
    if (u == 1) {
        while (true) {
           cout << warning << "The session key <k> must satisfy the following conditions: \n1) 1 < k < (p-1)!\n2) an integer \n3) relatively prime to (P-1) [" << P - 1 << "]";
            cout << input << "Enter the value of <k> ->";
            input_int(k, 5, 1, P - 1);
            if (gcd(k, P - 1) == 1) { return; }
            cout << error << "The value entered does not meet the criteria!";
        }
    }
    else {
        while (true) {
            k = rand() % (P - 3) + 2;
            if (gcd(k, P - 1) == 1) { 
                cout << result << "Generated number [k] ->" << k;
                return; 
            }            
        }
    }
}
int mod_inv(int k, int P) {
    k %= P;
    for (int i = 1; i < P; i++) {
        if ((k * i) % P == 1) {
            return i;
        }
    }
    return -1;
}
//s = (m – x*r)*k^-1 mod p – 1
void input_s(int m, int x,int r,int k,int P, int& s){
    int m1 = mod_inv(k,P-1);
    s = ((m - x * r) * m1) % (P - 1);
    if (s < 0) {
        s =s+ (P - 1);
    }
}
Signature elgamal_t(string text_r) {
    string text;
    int P, g, x, y, k, r, s;
    int M;
    int i_3;
    hash_t(text_r,text);
    int m = 0;
    for (char c : text) {
        m += c;
    }
    input_P(P, m);
    input_g(g, P);
    input_x(x, P);
    input_y(y, g, x, P);
    input_k(k, P);
    input_y(r, g, k, P);
    input_s(m,x,r,k,P,s);
    Signature sign;
    sign.r_m = r;
    sign.e_p=P;
    sign.s = s;
    sign.n_g=g;
    sign.y=y;
    return sign;
}
int ver_el(string t_or,int r,int s,int p,int g,int y){
    string text;
    int y1,r1,g1,v;
    hash_t(t_or,text);
    int m = 0;
    for (char c : text) {
        m += c;
    }
    if((0<r && r<p) && (0<s && s<(p-1))){
        y1=1;
        for(int i=0;i<r;i++){
            y1=(y1*y)%p;
        }
        r1=1;
        for(int i=0;i<s;i++){
            r1=(r1*r)%p;
        }
        g1=1;
        for(int i=0;i<m;i++){
            g1=(g1*g)%p;
        }
        if((y1*r1)%p==g1){
            v=1;
        }
        else{
            v=0;
        }
    }
    else{
        v=0;
    }
    return v;
}
