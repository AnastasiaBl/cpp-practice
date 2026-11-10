#include "Header1.h"
#include <iostream>
#include <string>
using namespace std;
//1) Возведение в степень по модулю
int degree_modu() {
    int a, n, m;
    input_int(a);
    input_int(n);
    input_int(m);
    int c = 1;
    a = a % m;
    while (n > 0) {
        if (n % 2 == 1) {
            c = (c * a) % m;
        }
        n = n / 2;
        a = (a * a) % m;
    }
    cout << "Результат вычислений: " << c;
    return c;
}
//2) Квадратный корень
float square_root() {
    float x;
    input_float(x);
    if (x < 0) {
        cout << "Решение невозможно" << endl;
        return -1;
    }
    if (x == 0 or x == 1) {
        cout << "Результат вычислений: " << x;
        return x;
    }
    float a = x / 2.0f;
    float b = 0.00001f;
    while (abs(a * a - x) > b) {
        a = (a + x / a) / 2.0f;
    }
    cout << "Результат вычислений: " << a << endl;
    return a;
}
//3)Кубический корень
float cube_root(float x) {
    if (x < 0) return -cube_root(-x);
    if (x == 0 or x == 1) {
        cout << "Результат вычислений: " << x;
        return x;
    }
    float a = x / 3.0f;
    float b = 0.0001f;
    while (abs(a * a * a - x) > b) {
        a = a - (a * a * a - x) / (3 * a * a);
    }
    return a;
}
float square_3() {
    float x;
    input_float(x);
    float res = cube_root(x);
    cout << "Результат вычислений: " << res << endl;
    return res;
}
//4) Обработка string.Дана строка, в ней слова разделены ";", каждое слово переписать собственную ячейку массива
int string_processing() {
    string input;
    input_string(input);
    const int ma = 1000;
    string e[ma];
    int i = 0;
    string t = "";
    for (char c : input) {
        if (c == ';') {
            e[i++] = t;
            t = "";
        }
        else {
            t += c;
        }
    }
    e[i++] = t;
    cout << "Результат вычислений: ";
    for (int g = 0; g < i; g++) {
        cout << e[g] << "\t";
    }
    cout << endl;
    return 0;
}
//5) Дан массив из N элементов, произвести сдвиг массива на N ячеек вправо.Примечание: разрешается использовать вспомогательный массив из 4 ячеек.
void array_of_n_elements() {
    string str;
    input_string(str);
    int m = str.size();
    char* a = new char[m + 1];
    char u[1];
    for (int i = 0; i < m; i++) {
        a[i] = str[i];
    }
    cout << "Результат вычислений: " << endl;
    for (int t = 0; t < m; t++) {
        for (int i = 0; i < m; i++) {
            cout << a[i];
        }
        cout << endl;
        u[0] = a[m - 1];
        for (int i = m - 1; i > 0; i--) {
            a[i] = a[i - 1];
        }
        a[0] = u[0];
    }
    delete[] a;
}
