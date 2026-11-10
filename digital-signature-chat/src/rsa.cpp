//rsa.cpp

//вычисляется хэш-сумма сообщения
//вычисляется d,n
//генерируется\выбирается сеансовый ключ k
//вычисляется r
//вычисляется s
//подписью сообщения M является пара (r, s)

//ПРОВЕРКА ПОДПИСИ на RSA
//Вводятся простые числа p and q
//Вычисляется n = p * q (n>M)
//Вычисляется F(n) функция Эйлера по формуле: Ф(n) = Ф(p) * Ф(q) = (p - 1) * (q - 1)
//Вычисляется e(открытая экспонента(ключ)) ((1 < е < Ф(n)) и НОД(е, Ф(n)))
//Вычисляется d(закрытая экспонента(ключ)) (d ≡ e ^ -1 mod Ф(n).)
//Создать цифровую подпись s с помощью своего секретного ключа {d, n}: S = m^d mod n
//Передать пару {m, s}, состоящую из сообщения и подписи
//Взять открытый ключ {e, n}
//Вычислить прообраз сообщения: m1 = s^e mod n
//Проверить подлинность: m ≡ m1
#include <iostream> 
#include <string> 
#include <cstdlib>
#include <ctime>
#include <limits>
#include "network.h"
#include "hash.h"

using namespace std;

//определение g (целое число)
void input_g_r(int& g, int P) {
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
void input_x_r(int& x, int P) {
    int u;
    cout << sys_msg << "Would you like to enter x <private key> manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";    input_ra(u, 2);
    if (u == 1) {
        cout << input << "Enter a value [x] ->";
        input_int(x, 5, 1, P - 1);
    }
    else {
        x = rand() % (P - 3) + 2;
        cout << result << "Generated number [x] ->" << x;
    }
}
//НОД(е, Ф(n)), для взаимно простого числа с Ф(n)
int gcd_r(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}
//Проверка на простое число для q and p
int pr_r(int a) {
    if (a < 2) { return 0; }
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) { return 0; }
    }
    return 1;
}
//Определение p
void input_p(int& p, int M) {
    int i_1;
    cout << sys_msg << "Would you like to enter <p> manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";
    input_ra(i_1, 2);
    if (i_1 == 1) {
        while (true) {
            cout << warning << "<p> must satisfy the following condition: \n1) prime number" << input << "Enter a value [p] ->";
            input_int(p, 1);
            if (pr_r(p) == 1) {
                return;
            }
            cout << error << "The value entered does not meet the criteria!";
        }
    }
    if (i_1 == 2) {
        while (true) {
            p = rand() % 500 + 100;
            if (pr_r(p) == 1) {
                return;
            }
        }
        cout << result << "Generated number [p] ->" << p;
    }
}
//Определение q
void input_q(int& q, int M) {
    int i_1;
    cout << sys_msg << "Would you like to enter <q> manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";
    input_ra(i_1, 2);
    if (i_1 == 1) {
        while (true) {
            cout << warning << "<q> must satisfy the following condition: \n1) prime number" << input << "Enter a value [q] ->";
            input_int(q, 1);
            if (pr_r(q) == 1) {
                return;
            }
            cout << error << "The value entered does not meet the criteria!";
        }
    }
    if (i_1 == 2) {
        while (true) {
            q = rand() % 500 + 100;
            if (pr_r(q) == 1) {
                return;
            }
        }
        cout << result << "Generated number [q] ->" << q;
    }
}
//Определение e; (1 < е < Ф(n)) and НОД(е, Ф(n))
void input_e(int& e, int f) {
    int i_1;
    cout << sys_msg << "Would you like to enter <e> manually or generate it automatically?\n1) Enter manually\n2) Generate" << input << "Enter your answer ->";    
    input_ra(i_1, 2);
    if (i_1 == 1) {
        while (true) {
            cout << warning << "The given exponent <e> must satisfy the following conditions:\n1) 1 < e < F(n) \n2) be relatively prime to F(n) [" << f << "]";
            cout << input << "Enter <e> ->";
            input_int(e, 5, 1, f);
            if (gcd_r(e, f) == 1) { return; }
            cout << error << "Введенное значение не соответствует условиям!";
        }
    }
    else {
        while (true) {
            e = rand() % f;
            if (gcd_r(e, f) == 1) { return; }
        }
        cout << result << "Generated number ->" << e;
    }
}
//Определение d; d ≡ e ^ -1 mod Ф(n)
void input_d(int& d, int e, int f) {
    int m1 = 0;
    for (int i = 1; i < f; i++) {
        if ((e * i) % f == 1) {
            m1 = i;
            break;
        }
    }
    d = m1;
}
//вычисляется s; s = m ^ d mod n
void input_s(int m,int d,int n,int &s){
    int m1 = 1;
    while (d > 0) {
        m1 = (m1 * m) % n;
        d--;
    }
    s = m1;
}
Signature rsa_t(string text_or) {
    string text;
    int p, q,s, n, f, e, d, i_3;
    hash_t(text_or,text);
    int m = 0;
    for (char c : text) {
        m += c;
    }
    while (true) {
        input_p(p, m);
        input_q(q, m);
        if (p * q > m) { break; }
        cout << error << "The value entered does not meet the condition!";
    }
    n = p * q;
    f = (p - 1) * (q - 1);
    input_e(e, f);
    input_d(d, e, f);
    input_s(m,d,n,s);
    Signature sign;
    sign.r_m = m;
    sign.s = s;
    sign.e_p=e;
    sign.n_g=n;
    return sign;
}
int ver_rsa(string t_or,int m,int s,int e,int n){
    int m1, v,j;
    string text;
    input_s(s,e,n,m1);
    if(m==m1){
        v=1;
    }
    else{
        v=0;
    }
    return v;
}
