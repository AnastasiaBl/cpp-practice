// Caesar.cpp 
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

string al_ru = "абвгдеёжзийклмнопрстуфхчшщъыьэюя";
string AL_ru = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЧШЩЪЫЬЭЮЯ";
string al_en = "";
string AL_en = "";
//Шифрование
string en(string text, int key) {
    string text_n = text;
    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < al_ru.size(); j++) {
            if (text[i] == al_ru[j]) {
                text_n[i] = al_ru[(j + key + al_ru.size()) % al_ru.size()];
                break;
            }
        }
        for (int j = 0; j < AL_ru.size(); j++) {
            if (text[i] == AL_ru[j]) {
                text_n[i] = AL_ru[(j + key + AL_ru.size()) % AL_ru.size()];
                break;
            }
        }
    }
    return text_n;
};
//Дешифрование
string de(string text, int key) {
    string text_n = text;
    for (int i = 0; i < text.size(); i++) {
        for (int j = 0; j < al_ru.size(); j++) {
            if (text[i] == al_ru[j]) {
                text_n[i] = al_ru[(j - key - al_ru.size()) % al_ru.size()];
                break;
            }
        }
        for (int j = 0; j < AL_ru.size(); j++) {
            if (text[i] == AL_ru[j]) {
                text_n[i] = AL_ru[(j - key - AL_ru.size()) % AL_ru.size()];
                break;
            }
        }
    }
    return text_n;
};
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    string text;
    int key = 0;
    cout << "Выберите -> 1)шифрование 2)дешифрование :\n";
    int a = 0;
    cin >> a;
    if (a == 1) {
        cout << "Введите текст для шифрования: \n";
        getline(cin, text);
        getline(cin, text);
        cout << "Введите ключ: \n";
        cin >> key;
        string text_n;
        text_n = en(text, key);

        cout << "Результат: " << text_n;
    }
    else if(a==2) {
        cout << "Введите текст для дешифрования: \n";
        getline(cin, text);
        getline(cin, text);
        cout << "Введите ключ: \n";
        cin >> key;
        string text_n;
        text_n = de(text, key);
        cout << "Результат: " << text_n;
    }
}
