#pragma once
#include <iostream> 
#include <string> 
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

void shift(uint64_t& t, int bit, int i) ;
void round(uint64_t& l, uint64_t& r, uint64_t vr) ;
void encryption_speck(uint64_t k_l, uint64_t k_r, uint64_t& t_l, uint64_t& t_r) ;
void to_uint64(size_t size_text, uint64_t& r, uint64_t& l, int i,  string text) ;
void bit_byte(uint64_t t, string&text_t) ;
string hash_t(const string& msg,string &text_en);
