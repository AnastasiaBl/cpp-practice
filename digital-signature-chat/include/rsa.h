
#include <iostream> 
#include <string> 
#include <cstdlib>
#include <ctime>
#include "network.h"
#include "hash.h"



using namespace std;


//определение g (целое число)
void input_g_r(int& g, int P);
//определение x целое число (1<x<p)
void input_x_r(int& x, int P) ;
//НОД(е, Ф(n)), для взаимно простого числа с Ф(n)
int gcd_r(int a, int b) ;
//Проверка на простое число для q and p
int pr_r(int a) ;
//Определение p
void input_p(int& p, int M) ;
//Определение q
void input_q(int& q, int M) ;
//Определение e; (1 < е < Ф(n)) and НОД(е, Ф(n))
void input_e(int& e, int f) ;
//Определение d; d ≡ e ^ -1 mod Ф(n)
void input_d(int& d, int e, int f) ;
void input_s(long long m,int d,int n,int s);
Signature rsa_t(string text_or) ;
int ver_rsa(string t_or,int m,int s,int e,int n);

