#include <iostream> 
#include <string> 
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include "network.h"
#include "hash.h"

using namespace std;


//проверка на простое число для P
int pr(int a) ;
//определение P-модуль простое число
void input_P(int& P, int min) ;
//определение g (целое число)
void input_g(int& g, int P) ;
//определение x целое число (1<x<p)
void input_x(int& x, int P) ;
//НОД(е, Ф(n)), для взаимно простого числа с Ф(n)
int gcd(int p, int k) ;
void input_y(int& y, int g, int x, int P);
void input_k(int& k, int P);
int mod_inv(int k, int P);
void input_s(int m, int x,int r,int k,int P, int& s);
//Шифрование
Signature elgamal_t(string text) ;
int ver_el(string t_or,int r,int s,int p,int g,int y);
