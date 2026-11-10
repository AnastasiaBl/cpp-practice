// Магический квадрат.cpp 
#include <iostream>
#include<string>
#define NOMINMAX
#include<Windows.h> //SetConsole...
#include <algorithm> //shuffle
#include <random> //random_device, mt19937

using namespace std;

int size_row, size_column, max_num, size_text,ro;
string text;

void encryption(string text, int** m,char** arr_let) {
    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < size_column; j++) {
            if (m[i][j] < size_text)
                arr_let[i][j] = text[m[i][j]];
            else
                arr_let[i][j] = '-';
        }
    }
    cout << "Сгенерированный массив(ключ):" << endl;
    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < size_column; j++) {
            cout << arr_let[i][j] << "("<< m[i][j]<<")"<<"\t";
        }
        cout << endl;
    }
    cout << "Зашифрованный текст:" << endl;
    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < size_column; j++) {
            if (arr_let[i][j] != '-') {
                cout << arr_let[i][j];
            }
        }
    }
}
void decryption(string text, int** m, char** arr_let) {
    string text_or;
    text_or = text;
    cout << "Введите сгенерированный массив(ключ):" << endl;
    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < size_column; j++) {
            cout<<"id = "<<m[i][j]<<"\nВведите символ соответствующий id в ключе >> ";
            cin >> arr_let[i][j];
            cout << endl;
        }
    }
    int y = 0;
    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < size_column; j++) {
            if (arr_let[i][j] != '-') {
                text_or[y] = arr_let[i][j];
                y++;
            }
        }
    }
    cout << "Расшифрованный текст: " << text_or<<endl;
}
int main()
{    
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    while (true) {
        int f;
        cout << "Здравствуйте! Вы хотите зашифровать текст(1) или расшифровать(2)? \nВведите ваш выбор >> ";
        cin >> f;
        if (f == 1) {
            cout << "Введите текст, который необходимо зашифровать: \n";
            getline(cin, text);
            getline(cin, text);
            size_text = text.size();
            if (size_text % 2 == 0) {
                size_row = size_text / 2;
                size_column = size_text / 2;
            }
            else {
                size_row = (size_text + 1) / 2;
                size_column = (size_text + 1) / 2;
            }
            max_num = size_row * size_column;
            int* num = new int[max_num];
            for (int i = 0; i < max_num; i++) {
                num[i] = i;
            }
            random_device rd;
            mt19937 g(rd());
            shuffle(num, num + max_num, g);
            int** m = new int* [size_row];
            for (int i = 0; i < size_row; i++) {
                m[i] = new int[size_column];
            }
            char** arr_let = new char* [size_row];
            for (int i = 0; i < size_row; i++) {
                arr_let[i] = new char[size_column];
            }

            int in = 0;
            for (int i = 0; i < size_row; i++) {
                for (int j = 0; j < size_column; j++) {
                    m[i][j] = num[in++];
                }
            }
            encryption(text, m, arr_let);
            delete[] num;
            for (int i = 0; i < size_row; i++) {
                delete[] m[i];
                delete[] arr_let[i];
            }
            delete[] m;
            delete[] arr_let;
        }
        else if (f == 2) {
            cout << "Введите текст, который необходимо расшифровать: \n";
            getline(cin, text);
            getline(cin, text);
            size_text = text.size();
            if (size_text % 2 == 0) {
                size_row = size_text / 2;
                size_column = size_text / 2;
            }
            else {
                size_row = (size_text + 1) / 2;
                size_column = (size_text + 1) / 2;
            }
            max_num = size_row * size_column;
            int* num = new int[max_num];
            for (int i = 0; i < max_num; i++) {
                num[i] = i;
            }
            int** m = new int* [size_row];
            for (int i = 0; i < size_row; i++) {
                m[i] = new int[size_column];
            }
            int in = 0;
            for (int i = 0; i < size_row; i++) {
                for (int j = 0; j < size_column; j++) {
                    m[i][j] = num[in++];
                }
            }
            char** arr_let = new char* [size_row];
            for (int i = 0; i < size_row; i++) {
                arr_let[i] = new char[size_column];
            }
            decryption(text, m, arr_let);
            for (int i = 0; i < size_row; i++) {
                delete[] m[i];
                delete[] arr_let[i];
            }
            delete[] m;
            delete[] arr_let;
        }
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите число 1 или 2!\n";
            continue;
        }
        cout << "\nВы хотите продолжить работу? \n1 - Да \n2 - Нет\nУкажите свой выбор: ";
        int y;
        cin >> y;
        if (y == 2) {
            cout << "Программа завершена.\n";
            break;
        }
        else if (y != 1) {
            cout << "Ошибка! Введите 1-Да 2-Нет\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    

    return 0;
}
