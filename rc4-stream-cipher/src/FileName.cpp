#include <string>
#include <iostream>
#include <bitset>
#include <sstream>
#include <iomanip>
using namespace std;

void check_int(int& n) {
    while (true) {
        cin >> n;
        if (cin.good()) break;
        cout << "\nОшибка! Введите целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void check_float(float& n) {
    while (true) {
        cin >> n;
        if (cin.good()) break;
        cout << "\nОшибка! Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void input_int(int& a) {
    cout << "\nВведите целое число: ";
    check_int(a);
}
void input_float(float& a) {
    cout << "\nВведите число: ";
    check_float(a);
}
void input_string(std::string& a) {
    cout << "\nВведите строку значений: ";
    cin.ignore();
    getline(cin, a);
}
void filling_num(int a[], int size) {
    for (int i = 0; i < size; i++) {
        a[i] = i;
    }
}
class BinaryConverter {
public:

    string textToBits(const string& text) {
        string bits;
        for (unsigned char c : text) {
            bits += bitset<8>(c).to_string();
        }
        return bits;
    }
    string bitsToText(const string& bits) {
        string text;
        for (size_t i = 0; i + 8 <= bits.size(); i += 8) {
            bitset<8> b(bits.substr(i, 8));
            text += static_cast<char>(b.to_ulong());
        }
        return text;
    }
    string b_hex(const string& bits) {
        string hexs;
        for (size_t i = 0; i + 8 <= bits.size(); i += 8) {
            bitset<8> b(bits.substr(i, 8));
            stringstream ss;
            ss << hex << setw(2) << setfill('0') << b.to_ulong();
            hexs += ss.str();
        }
        return hexs;
    }
    string hex_b(const string& hexs) {
        string bits;
        for (size_t i = 0; i + 2 <= hexs.size(); i += 2) {
            string b = hexs.substr(i, 2);
            unsigned char val = static_cast<unsigned char>(stoi(b, nullptr, 16));
            bits += bitset<8>(val).to_string();
        }
        return bits;
    }
};
