// RSA.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//ГЕНЕРАЦИЯ КЛЮЧЕЙ
// Вводится сообщение M
//Вводятся простые числа p and q
//Вычисляется n = p * q (n>M)
//Вычисляется F(n) функция Эйлера по формуле: Ф(n) = Ф(p) * Ф(q) = (p - 1) * (q - 1)
//Вычисляется e(открытая экспонента(ключ)) ((1 < е < Ф(n)) и НОД(е, Ф(n)))
//Вычисляется d(закрытая экспонента(ключ)) (d ≡ e ^ -1 mod Ф(n).)
//ШИФРОВАНИЕ
//С = M ^ e mod n
//ДЕШИФРОВАНИЕ
//M = C ^ d mod n
#include <iostream> 
#include <string> 
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;
string line = "\n------------------------------------------------------------------------------------------------------------\n";
string sys_msg = "\n[SYSTEM] ";
string warning = "\n[WARNING] ";
string input = "\n[INPUT] ";
string error = "\n[ERROR] ";
string result = "\n[RESULT] ";
string al =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
"0123456789 .,!?;:-()";
//ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ
//ввод int
void input_int(int& n, int checkType = 0, int a = 0, int b = 0) {
    //n-перменная int
    //checkType-case проверки
    //a-минимальное значение
    //b-максимальное значение
    while (true) {
        cin >> n;
        if (cin.fail()) {
            cout << error << "\nОшибка! Введите целое число: ";
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
            cout << error << "\nОшибка! Число должно быть больше 0: ";
            break;
        case 2:
            if (n >= 0) { return; }
            cout << error << "\nОшибка! Число не должно быть отрицательным: ";
            break;
        case 3:
            if (n >= a) { return; }
            cout << error << "\nОшибка! Число должно быть не меньше " << a << ": ";
            break;

        case 4:
            if (n <= b) { return; }
            cout << error << "\nОшибка! Число должно быть не больше " << b << ": ";
            break;

        case 5:
            if (n >= a && n <= b) { return; }
            cout << error << "\nОшибка! Число должно быть в диапазоне от " << a << " до " << b << ": ";
            break;

        default:
            cout << error << "\nОшибка! Неизвестный тип проверки: ";
            break;
        }
    }
}
//выбор из списка вариантов
int input_ra(int& i, int a)
{
    while (true)
    {
        input_int(i);

        if (i > 0 && i <= a)
        {
            return i;
        }
        cout << endl << error << "Ошибка! Введите значение от 1 до " << a << ": ";
    }
}

//ОСНОВНЫЕ ФУНКЦИИ
// 
//НОД(е, Ф(n)), для взаимно простого числа с Ф(n)
int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}
//Проверка на простое число для q and p
int pr(int a) {
    if (a < 2) { return 0; }
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) { return 0; }
    }
    return 1;
}
//Определение p
void input_p(int& p, int M) {
    int i_1;
    cout <<sys_msg<< "Вы хотите ввести <p> вручную или сгенерировать его автоматически?\n1)ввести вручную\n2)сгенерировать"<<input<<"Введите свой ответ ->";
    input_ra(i_1, 2);
    if (i_1 == 1) {
        while (true) {
            cout << warning << "<p> должен соответствовать услови.: \n1) простое число" << input << "Введите значение [p] ->";
            input_int(p, 1);
            if (pr(p) == 1) {
                return;
            }
            cout << error << "Введенное значение не соответствует условиям!";
        }
    }
    if (i_1 == 2) {
        while (true) {
            p = rand() % 500 + 100;
            if (pr(p) == 1) {
                return;
            }
        }
        cout << result<<"Сгенерированное [p] ->" << p;
    }
}
//Определение q
void input_q(int& q, int M) {
    int i_1;
    cout << sys_msg << "Вы хотите ввести <q> вручную или сгенерировать его автоматически?\n1)ввести вручную\n2)сгенерировать" << input << "Введите свой ответ ->";
    input_ra(i_1, 2);
    if (i_1 == 1) {
        while (true) {
            cout << warning << "<q> должен соответствовать услови.: \n1) простое число" << input << "Введите значение [q] ->";
            input_int(q, 1);
            if (pr(q) == 1) {
                return;
            }
            cout << error << "Введенное значение не соответствует условиям!";
        }
    }
    if (i_1 == 2) {
        while (true) {
            q = rand() % 500 + 100;
            if (pr(q) == 1) {
                return;
            }
        }
        cout << result << "Сгенерированное [q] ->" << q;
    }
}
//Определение e; (1 < е < Ф(n)) and НОД(е, Ф(n))
void input_e(int& e, int f) {
    int i_1;
    cout <<sys_msg<< "Вы хотите ввести <e> вручную или сгенерировать его автоматически?\n1)ввести вручную\n2)сгенерировать"<<input<<"Введите свой ответ ->";
    input_ra(i_1, 2);
    if (i_1 == 1) {
        while (true) {
            cout << warning << "Открытая экспонента <e> должна сответствовать условиям:\n1) 1<е<Ф(n) \n2)взаимно простое с F(n) [" << f << "]";
            cout << input<<"Введите <e> ->";
            input_int(e, 5, 1, f);
            if (gcd(e, f) == 1) { return; }
            cout << error << "Введенное значение не соответствует условиям!";
        }
    }
    else {
        while (true) {
            e = rand() % f;
            if (gcd(e, f) == 1) { return; }
        }
        cout << result << "Сгенерированное число ->" << e;
    }
}
//Определение d; d ≡ e ^ -1 mod Ф(n)
void input_d(int& d, int e,int f) {
    int m1 = 0;
    for (int i = 1; i < f; i++) {
        if ((e * i) % f == 1) {
            m1 = i;
            break;
        }
    }
    d = m1;
}
//шифрование
void encryption() {
    cout << sys_msg << "ЗАПУЩЕНА ПРОГРАММА ШИФРОВАНИЯ\n" << line;
    string text;
    int p, q, n, f, e,m, d, i_3, s_text,C,M;
    cout << sys_msg << "Выберите режим шифрования:\n1)ASCII\n2)Пользовательский алфавит(введите <3> если хотите посмотреть пользовательский алфавит, после этого выбор будет продублирован)" << input << "Введите свой ответ ->";
    input_ra(i_3, 3);
    if (i_3 == 3) {
        for (int i = 0; i < al.size(); i++) {
            cout << i << " -> " << al[i] << endl;
        }
    }
    cout << sys_msg << "Выберите режим шифрования:\n1)ASCII\n2)Пользовательский алфавит" << input << "Введите свой ответ ->";
    input_ra(i_3, 2);
    if (i_3 == 1) {
        cout << sys_msg << "Ведите сообщение для шифрования" << input << "Введите текст -> ";
        getline(cin, text);
        s_text = text.size();
    }
    if (i_3 == 2) {
        cout << sys_msg << "Ведите сообщение для шифрования" << input << "Введите текст -> ";
        getline(cin, text);
        s_text = text.size();
    }
    int* arr = new int[s_text];
    int* arr_en = new int[s_text];
    if (i_3 == 1) {
        cout << sys_msg << "Подготовка текста для шифрования ->\n";
        for (int i = 0; i < s_text; i++) {
            char c = text[i];
            int n = c;
            cout << "[" << text[i] << "] - <" << n << ">\n";
            arr[i] = n;
        }
    }
    if (i_3 == 2) {
        for (int i = 0; i < s_text; i++) {
            for (int j = 0; j < al.size(); j++) {
                if (al[j] == text[i]) {
                    arr[i] = j;
                    cout << "[" << text[i] << "] - <" << j << ">\n";
                    break;
                }
            }
        }
    }
    m = -1;
    for (int i = 0; i < s_text; i++) {
        if (arr[i] > m) {
            m = arr[i];
        }
    }
    while (true) {
        input_p(p, m);
        input_q(q, m);
        if (p * q > m) { break; }
        cout << error << "Введенное значение не соответствует условию!";
    }
    n = p * q;
    f = (p - 1) * (q - 1);
    input_e(e, f);
    input_d(d,e, f);
    for (int i = 0; i < s_text; i++) {
        M = arr[i];
        C = 1;
        for (int f = 0; f < e; f++) {
            C = (C * M) % n;
        }
        arr_en[i] = C;
    }
    cout << endl << line << result << "РЕЗУЛЬТАТ ШИФРОВАНИЯ\n" << sys_msg << "p = [" << p << "]\n" << sys_msg << "q = [" << q << "]\n" << sys_msg << "d = [" << d << "]\n";
    cout << result << "Резкультат шифрования ->";
    for (int i = 0; i < s_text; i++) {
        cout << " ["<< arr_en[i] << "] ";
    }
    delete[] arr;
    delete[] arr_en;
}
int main()
{
    while (true) {
        srand(time(0));
        setlocale(LC_ALL, "Russian");
        cout << sys_msg << "ДОБРО ПОЖАЛОВАТЬ\n"
            << line
            << sys_msg << "Что вы хотите сделать\n1)Зашифровать сообщение\n2)Расшифровать сообщение\n"
            << input << "Введите ваш ответ ->";
        int i_1, i_2;
        input_ra(i_1, 2);
        if (i_1 == 1) {
            encryption();
        }
        else if (i_1 == 2) {
            //decryption();
        }
        cout << endl << "Вы хотите продолжить работу? \n1)да\n2)нет" << input << "Введите свой выбор ->";
        input_ra(i_2, 2);
        if (i_2 == 2) {
            break;
        }
    }
    return 0;
}
