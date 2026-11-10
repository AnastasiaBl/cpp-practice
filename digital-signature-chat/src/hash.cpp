//hash.cpp

#include <iostream> 
#include <string> 
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <limits>
using namespace std;

void shift(uint64_t& t, int bit, int i) {
    if (i == 1) {
        t = (t >> bit) | (t << (64 - bit));
    }
    if (i == 2) {
        t = (t << bit) | (t >> (64 - bit));
    }
}
void round(uint64_t& l, uint64_t& r, uint64_t vr) {
    shift(l, 8, 1);
    l = l + r;
    shift(r, 3, 2);
    l = vr ^ l;
    r = l ^ r;
}
void encryption_speck(uint64_t k_l, uint64_t k_r, uint64_t& t_l, uint64_t& t_r) {
    uint64_t krc = k_r;
    uint64_t klc = k_l;
    for (int i = 0; i < 32; i++) {
        round(klc, krc, i);
        round(t_l, t_r, krc);
    }
}
void MDC_2(uint64_t& M_l_1, uint64_t& M_l_2,uint64_t &G0,uint64_t &G1,uint64_t &H0,uint64_t &H1) {
    uint64_t M_r_1 = 0;
    uint64_t M_r_2 = 0;
    uint64_t t_1_l = 0;
    uint64_t t_1_r = 0;
    uint64_t t_2_l = 0;
    uint64_t t_2_r = 0;
    M_r_1 = M_l_1;
    t_1_l = M_l_1;
    t_1_r = M_r_1;
    encryption_speck(H0, H1, M_l_1, M_r_1);
    H0 = M_l_1 ^ t_1_l;
    H1 = M_r_1 ^ t_1_r;
    M_r_2 = M_l_2;
    t_2_l = M_l_2;
    t_2_r = M_r_2;
    encryption_speck(G0, G1, M_l_2, M_r_2);
    G0 = M_l_2 ^ t_2_l;
    G1 = M_r_2 ^ t_2_r;
    
}
void to_uint64(size_t size_text, uint64_t& r, uint64_t& l, int i,  string text) {
    l = 0;
    r = 0;
    for (int j = 0; j < 8; j++) {
        l <<= 8;
        if (i + j < size_text) {
            l |= (uint8_t)text[i + j];
        }
    }
    for (int j = 0; j < 8; j++) {
        r <<= 8;
        if (i + 8 + j < size_text) {
            r |= (uint8_t)text[i + 8 + j];
        }
    }
}
void bit_byte(uint64_t t, string&text_t) {
    for (int i = 7; i >= 0; i--) {
        text_t.push_back(static_cast<char>((t >> (8 * i)) & 0xFF));
    }
}
string hash_t(const string& msg,string &text_en){
    uint64_t G0 = 0x5252525252525252;
    uint64_t G1 = 0x5252525252525252;
    uint64_t H0 = 0x2525252525252525;
    uint64_t H1 = 0x2525252525252525;
    string text_t;
    size_t size_text = msg.size();
    for (int i = 0; i < size_text; i = i + 16) {
        uint64_t r = 0;
        uint64_t l = 0;
        to_uint64(size_text, r, l, i,  msg);
        MDC_2(l, r,G0,G1,H0,H1);
    }
    text_t.clear();
    bit_byte(H0, text_t);
    bit_byte(H1, text_t);
    bit_byte(G0, text_t);
    bit_byte(G1, text_t);
    text_en += text_t;
    text_t.clear();
    return text_en;
}
