
#include <iostream>
#include<string>
#include<cstdint>
#include <limits>
#include <Windows.h>
using namespace std;
string text_or;
string key_or;

string text_t;

string text_en;

string text_de;

uint64_t G0 = 0x5252525252525252;
uint64_t G1 = 0x5252525252525252;
uint64_t H0 = 0x2525252525252525;
uint64_t H1 = 0x2525252525252525;

string line = "=====================================================================================================================\n";

void input_int(int& n, int checkType = 0, int a = 0, int b = 0) {
    while (true) {
        cin >> n;
        if (cin.fail()) {
            cout << "\n[ERROR] Ошибка! Введите целое число: ";
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
            cout << "\n[ERROR] Ошибка! Число должно быть больше 0: ";
            break;
        case 2:
            if (n >= 0) { return; }
            cout << "\n[ERROR] Ошибка! Число не должно быть отрицательным: ";
            break;
        case 3:
            if (n >= a) { return; }
            cout << "\n[ERROR] Ошибка! Число должно быть не меньше " << a << ": ";
            break;
        case 4:
            if (n <= b) { return; }
            cout << "\n[ERROR] Ошибка! Число должно быть не больше " << b << ": ";
            break;
        case 5:
            if (n >= a and n <= b) { return; }
            cout << "\n[ERROR] Ошибка! Число должно быть в диапазоне от " << a << " до " << b << ": ";
            break;
        default:
            cout << "\n[ERROR] Ошибка! Неизвестный тип проверки: ";
            break;
        }
    }
}
int input_ra(int& i, int a)
{
    while (true)
    {
        input_int(i);
        if (i > 0 and i <= a)
        {
            return i;
        }
        cout << endl << "[ERROR] Ошибка! Введите значение от 1 до " << a << ": ";
        cin.clear();
    }
}
void to_uint64(int size_text, uint64_t& r, uint64_t& l, int i,  string text) {
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
void text(int i) {
    if (i == 1 or i == 2) {
        cout << "\n[INPUT] Введите текст для работы ->";
        getline(cin, text_or);
    }
    if (i == 2) {
        while (true) {
            cout << "\n[SYSTEM] Введите значение ключа для работы\n[WARNING] Введенное значение должно соответствовать условиям: весить не больше 16 байт и не ровняться 0, лишняя часть значения будет отрезана!\n[INPUT]Введите значение ->";
            getline(cin, key_or);
            if (key_or.size() == 0) {
                cout << "\n[ERROR] Введенное значение не соответствует условиям, введите значение повторно!";
                key_or.clear();
            }
            else { break; }
        }
    }
}
unsigned char hex(char c) {
    if (c >= '0' && c <= '9') { return c - '0'; }
    if (c >= 'A' && c <= 'F') { return c - 'A' + 10; }
    if (c >= 'a' && c <= 'f') { return c - 'a' + 10; }
    return 0;
}
string hex_str(string& text) {
    string r;
    for (int i = 0; i + 1 < text.size(); i += 2) {
        unsigned char b = (hex(text[i]) << 4) | hex(text[i + 1]);
        r.push_back((char)b);
    }
    return r;
}
string bin_str(string t) {
    static const char* hex = "0123456789ABCDEF";
    for (unsigned char c : t) {
        text_t.push_back(hex[c >> 4]);
        text_t.push_back(hex[c & 0x0F]);
    }
    return text_t;
}
void bit_byte(uint64_t t, string&text_t) {
    for (int i = 7; i >= 0; i--) {
        text_t.push_back(static_cast<char>((t >> (8 * i)) & 0xFF));
    }
}

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
void round_de(uint64_t& t_l, uint64_t& t_r, uint64_t k_r) {
    t_r = t_l ^ t_r;
    shift(t_r, 3, 1);
    t_l = k_r ^ t_l;
    t_l = t_l - t_r;
    shift(t_l, 8, 2);
}
void encryption_speck(uint64_t k_l, uint64_t k_r, uint64_t& t_l, uint64_t& t_r) {
    uint64_t krc = k_r;
    uint64_t klc = k_l;
    for (int i = 0; i < 32; i++) {
        round(klc, krc, i);
        round(t_l, t_r, krc);
    }
}
void decryption_speck(uint64_t k_l, uint64_t k_r, uint64_t& t_l, uint64_t& t_r) {
    uint64_t k[32];
    uint64_t krc, klc;
    krc = k_r;
    klc = k_l;
    for (int i = 0; i < 32; i++) {
        round(klc, krc, i);
        k[i] = krc;
    }
    for (int i = 31; i >= 0; i--) {
        round_de(t_l, t_r, k[i]);
    }
}

void gener(uint64_t k, uint64_t& V) {
    uint64_t f = 0xA3B1C2D3E4F56789;
    for (int i = 0; i < 255; i++) {
        V = k * k;
        V = V + k;
        V = V << 16;
        encryption_speck(k, k, V, f);
        V = V ^ f;
        V = V >> 5;
        V = V ^ (f ^ k);
        f = V;
    }
}
void encryption_cbc(string t, string k) {
    uint64_t v_l = 0;
    string bin_r;
    uint64_t v_r = 0;
    int size_text = t.size();
    int size_key = k.size();
    uint64_t l_k = 0;
    uint64_t r_k = 0;
    to_uint64(size_key, r_k, l_k, 0, k);
    gener(l_k, v_l);
    gener(r_k, v_r);
    for (int i = 0; i < size_text; i = i + 16) {
        uint64_t P_l = 0;
        uint64_t P_r = 0;
        uint64_t C_l = 0;
        uint64_t C_r = 0;
        to_uint64(size_text, P_r, P_l, i, t);
        C_l = P_l ^ v_l;
        C_r = P_r ^ v_r;
        encryption_speck(l_k, r_k, C_l, C_r);
        v_l = C_l;
        v_r = C_r;
        text_t.clear();
        bit_byte(v_l, text_t);
        bit_byte(v_r, text_t);
        bin_r += text_t;
        text_t.clear();
    }
    text_t.clear();
    cout << "[RESULT] Результат шифрования -> " << bin_str(bin_r);
}
void decryption_cbc(string t, string k) {
    t = hex_str(t);
    int size_text = t.size();
    int size_key = k.size();
    uint64_t l_k = 0;
    uint64_t r_k = 0;
    uint64_t v_l = 0;
    uint64_t v_r = 0;
    string bin_r;
    to_uint64(size_key, r_k, l_k, 0, k);
    gener(l_k, v_l);
    gener(r_k, v_r);
    for (int i = 0; i < size_text; i = i + 16) {
        uint64_t P_l = 0;
        uint64_t P_r = 0;
        uint64_t C_l = 0;
        uint64_t C_r = 0;
        to_uint64(size_text, C_r, C_l, i, t);
        uint64_t tmp_l = C_l;
        uint64_t tmp_r = C_r;
        decryption_speck(l_k, r_k, C_l, C_r);
        P_l = C_l ^ v_l;
        P_r = C_r ^ v_r;
        v_l = tmp_l;
        v_r = tmp_r;
        text_t.clear();
        bit_byte(P_l, text_t);
        bit_byte(P_r, text_t);
        text_en += text_t;
        text_t.clear();
    }
    cout << "[RESULT] Результат дешифрования -> ";
    for (unsigned char c : text_en) { cout << c; }

}

void MDC_2(uint64_t& M_l_1, uint64_t& M_l_2) {
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

void main_i5() {
    cout << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ MDC_2\n";
    G0 = 0x5252525252525252;
    G1 = 0x5252525252525252;
    H0 = 0x2525252525252525;
    H1 = 0x2525252525252525;
    int size_text = text_or.size();
    for (int i = 0; i < size_text; i = i + 16) {
        uint64_t r = 0;
        uint64_t l = 0;
        to_uint64(size_text, r, l, i, text_or);
        MDC_2(l, r);
    }
    text_t.clear();
    bit_byte(H0, text_t);
    bit_byte(H1, text_t);
    bit_byte(G0, text_t);
    bit_byte(G1, text_t);
    text_en += text_t;
    text_t.clear();
    cout << endl << "[RESULT] Результат работы MDC_2 до шифрования-> " << bin_str(text_en)<<endl;
    text_t.clear();
    text_en.clear();

    cout << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ ШИФРОВКИ CBC\n";
    encryption_cbc(text_or, key_or);
    string t_cbc = text_t;
    text_t.clear();

    cout << endl << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ ДЕШИФРОВКИ CBC\n";
    decryption_cbc(t_cbc, key_or);
    
    t_cbc = text_en;
    text_en.clear();
    cout << endl << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ MDC_2\n";
    G0 = 0x5252525252525252;
    G1 = 0x5252525252525252;
    H0 = 0x2525252525252525;
    H1 = 0x2525252525252525;
    size_text = t_cbc.size();
    for (int i = 0; i < size_text; i = i + 16) {
        uint64_t r = 0;
        uint64_t l = 0;
        to_uint64(size_text, r, l, i,  t_cbc);
        MDC_2(l, r);
    }
    text_t.clear();
    bit_byte(H0, text_t);
    bit_byte(H1, text_t);
    bit_byte(G0, text_t);
    bit_byte(G1, text_t);
    text_en += text_t;
    text_t.clear();
    cout << "[RESULT] Результат работы MDC_2 после расшифровки -> " << bin_str(text_en) << endl;
    
    text_t.clear();
    text_en.clear();
    text_or.clear();
    key_or.clear();
}
int main()
{
    int i_1, i_2;
    while (true) {
        setlocale(LC_ALL, "Russian");
        SetConsoleOutputCP(CP_UTF8);
        //setlocale(LC_ALL, "ru_RU.UTF-8");
        text_or.clear();
        key_or.clear();
        text_t.clear();
        text_en.clear();
        text_de.clear();
        cout << "\n[SYSTEM] ДОБРО ПОЖАЛОВАТЬ\n" << line << "\n[SYSTEM] ПРОГРАММА ЗАПУЩЕНА\n" << line
            << "[SYSTEM] Выберите режим: \n1)Speck \n2)CBC (chipher Speck) \n3)MDC_2\n4)CBC+MDC_2\n5)Проверка\n[INPUT] Введите ваш ответ ->";
        input_ra(i_1, 5);
        if (i_1 == 1) {
            cout << line << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ SPECK\n" << line
                << "\n[SYSTEM] Что вы хотите сделать\n1)Зашифровать сообщение\n2)Расшифровать сообщение\n[INPUT] Введите ваш ответ ->";
            input_ra(i_2, 2);
            if (i_2 == 1) {
                cout << line << "\n[SYSTEM] ЗАПУЩЕНА ПРОГРАММА ШИФРОВАНИЯ\n" << line;
                text(2);
                int size_text = text_or.size();
                int size_key = key_or.size();
                cout << line << "\n[SYSTEM] Деление по блокам\n" << line;
                int y = 0;
                uint64_t l_k = 0;
                uint64_t r_k = 0;
                to_uint64(size_key, r_k, l_k, 0,  key_or);
                for (int i = 0; i < size_text; i = i + 16) {
                    cout << "\nФормирование блока [" << y + 1 << "]\n";
                    uint64_t l = 0;
                    uint64_t r = 0;
                    to_uint64(size_text, r, l, i,  text_or);
                    encryption_speck(l_k, r_k, l, r);
                    bit_byte(l, text_t);
                    bit_byte(r, text_t);
                    text_en += text_t;
                    text_t.clear();
                    y++;
                }
                bin_str(text_en);
                cout << "[RESULT] Результат шифрования -> " << text_t;
                text_en.clear();
            }
            if (i_2 == 2) {
                cout << line << "\n[SYSTEM] ЗАПУЩЕНА ПРОГРАММА ДЕШИФРОВАНИЯ\n" << line;
                text(2);
                text_or = hex_str(text_or);
                int size_text = text_or.size();
                int size_key = key_or.size();
                int y = 0;
                uint64_t l_k = 0;
                uint64_t r_k = 0;
                to_uint64(size_key, r_k, l_k, 0,  key_or);
                cout << line << "\n[SYSTEM] Деление по блокам\n" << line;
                for (int i = 0; i < size_text; i = i + 16) {
                    cout << "\nФормирование блока [" << y + 1 << "]\n";
                    uint64_t l = 0;
                    uint64_t r = 0;
                    to_uint64(size_text, r, l, i,  text_or);
                    decryption_speck(l_k, r_k, l, r);
                    bit_byte(l, text_t);
                    bit_byte(r, text_t);
                    text_en += text_t;
                    text_t.clear();
                    y++;
                }
                cout << "[RESULT] Результат дешифрования -> ";
                for (unsigned char c : text_en) { cout << c; }
                text_en.clear();
            }
        }
        if (i_1 == 2) {
            cout << line << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ CBC\n" << line
                << "\n[SYSTEM] Что вы хотите сделать\n1)Зашифровать сообщение\n2)Расшифровать сообщение\nВведите ваш ответ -> ";
            input_ra(i_2, 2);
            if (i_2 == 1) {
                cout << line << "\n[SYSTEM] ЗАПУЩЕНА ПРОГРАММА ШИФРОВАНИЯ\n" << line;
                text(2);
                encryption_cbc(text_or, key_or);
            }
            if (i_2 == 2) {
                cout << line << "\n[SYSTEM] ЗАПУЩЕНА ПРОГРАММА ДЕШИФРОВАНИЯ\n" << line;
                text(2);
                decryption_cbc(text_or, key_or);
                text_en.clear();
            }
        }
        if (i_1 == 3) {
            cout << line << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ MDC_2\n" << line;
            text(1);
            int size_text = text_or.size();
            cout << line << "\n[SYSTEM] Деление по блокам\n" << line;
            int y = 0;
            for (int i = 0; i < size_text; i = i + 16) {
                cout << "\n[SYSTEM] Формирование блока [" << y + 1 << "]\n";
                uint64_t r = 0;
                uint64_t l = 0;
                to_uint64(size_text, r, l, i,  text_or);
                MDC_2(l, r);
                y++;
            }
            text_t.clear();
            bit_byte(H0, text_t);
            bit_byte(H1, text_t);
            bit_byte(G0, text_t);
            bit_byte(G1, text_t);
            text_en += text_t;
            text_t.clear();
            bin_str(text_en);
            cout << "[RESULT] Результат работы -> " << text_t;
            text_en.clear();
        }
        if (i_1 == 4) {
            cout << line << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ CBC+MDC_2\n" << line;
            text(2);
            encryption_cbc(text_or, key_or);
            text_de = hex_str(text_en);
            text_en.clear();
            int size_text = text_de.size();
            cout << line << "\n[SYSTEM] Деление по блокам\n" << line;
            int y = 0;
            for (int i = 0; i < size_text; i = i + 16) {
                cout << "\n[SYSTEM] Формирование блока [" << y + 1 << "]\n";
                uint64_t r = 0;
                uint64_t l = 0;
                to_uint64(size_text, r, l, i,  text_de);
                MDC_2(l, r);
                y++;
            }
            text_t.clear();
            bit_byte(H0, text_t);
            bit_byte(H1, text_t);
            bit_byte(G0, text_t);
            bit_byte(G1, text_t);
            text_en += text_t;
            text_t.clear();
            bin_str(text_en);
            cout << "[RESULT] Результат работы -> " << text_t;
            text_en.clear();
        }
        if (i_1 == 5) {
            cout << line << "\n[SYSTEM] ЗАПУЩЕН РЕЖИМ ПРОВЕРКИ\n" << line;
            text_or = "X9@pL2";
            key_or = "A1b2C3d4E5f6G7h8";
            cout << "\n[SYSTEM] РЕЖИМ [1]\n\t\ttext -> " << text_or << " \n\t\tkey -> " << key_or << endl;
            main_i5();

            text_or = "QwErTy1234!@ZxCv";
            key_or = "ZxYwVuTsRqPoNmLk";
            cout << line<<"\n[SYSTEM] РЕЖИМ [2]\n\t\ttext -> " << text_or << " \n\t\tkey -> " << key_or << endl;
            main_i5();

            text_or = "CBC_chain_blocks_test_case_01";
            key_or = "M0n1T0r1nGKey#42";
            cout << line << "\n[SYSTEM] РЕЖИМ [3]\n\t\ttext -> " << text_or << " \n\t\tkey -> " << key_or << endl;
            main_i5();
        }
        cout << "\n[SYSTEM] Вы хотите продолжить работу? \n1)да\n2)нет\n[INPUT] Введите свой выбор ->";
        input_ra(i_2, 2);
        if (i_2 == 2) {
            break;
        }
    }
    return 0;
}
    
