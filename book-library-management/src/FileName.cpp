#include <string>
#include <iostream>
#include <limits>
using namespace std;

void check_int(int& n) {
    while (true) {
        cin >> n;
        if (cin.good()) break;
        cout << "Ошибка! Введите целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
void check_float(float& n) {
    while (true) {
        cin >> n;
        if (cin.good()) break;
        cout << "Ошибка! Введите число: ";
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
