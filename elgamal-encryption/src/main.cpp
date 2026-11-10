// Алгоритм_Эль-Гамаля_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

//ГЕНЕРАЦИЯ КЛЮЧЕЙ
//  Генерируется\выбирается P,g,x
//  Вычисляется y
//  !Открытым ключом является y, g, p, закрытым ключом — число x
//ШИФРОВАНИЕ
//  Вводится сообщение M
//  Генерируется\выбирается сеансовый ключ k
//  Вычисляются a and b
//  Шифротекст (a,b)
//ДЕШИФРОВАНИЕ
//  Вводится x
// Вводится зашифрованный текст (a,b)
//  Вычисляется M

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
//НОД((P-1), k), для взаимно простого числа с (P-1)
int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}
//проверка на простое число для P
int pr(int a) {
    if (a < 2) { return 0; }
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) { return 0; }
    }
    return 1;
}
//определение P простое число и M<P
void input_P(int& P, int min) {
    int u;
    cout << sys_msg << "Вы хотите ввести P <модуль> вручную или сгенерировать его автоматически?\n1)ввести вручную\n2)сгенерирвать" << input << "Введите свой ответ ->";
    input_ra(u, 2);
    if (u == 1) {
        while (true) {
            cout << warning << "P <модуль> должен соответствовать условиям: \n1) простое число \n2) P>M" << input << "Введите значение [P] ->";
            input_int(P, 1);
            if (pr(P) == 1 and P > min) {
                return;
            }
            cout << error << "Введенное значение не соответствует условиям!";
        }
    }
    else {
        while (true) {
            P = rand() % 500 + 100;
            if (pr(P) == 1 and P > min) {
                return;
            }
        }
        cout << result << "Сгенерированное число [P] ->" << P;
    }
}
//определение g (целое число)
void input_g(int& g, int P) {
    int u;
    cout << sys_msg << "Вы хотите ввести g <первообразный корень> вручную или сгенерировать его автоматически?\n1)ввести вручную\n2)сгенерирвать" << input << "Введите свой ответ ->";
    input_ra(u, 2);
    if (u == 1) {
        cout << sys_msg << "Введите значение [g] ->";
        input_int(g);
    }
    else {
        g = rand() % (P - 2) + 2;
        cout << result << "Сгенерированное число [g] ->" << g;
    }
}
//определение x целое число (1<x<p-1)
void input_x(int& x, int P) {
    int u;
    cout << sys_msg << "Вы хотите ввести x <закрытый ключ> вручную или сгенерировать его автоматически?\n1)ввести вручную\n2)сгенерирвать" << input << "Введите свой ответ ->";
    input_ra(u, 2);
    if (u == 1) {
        cout << input << "Введите значение [x] ->";
        input_int(x, 5, 1, P - 1);
    }
    else {
        x = rand() % (P - 3) + 2;
        cout << result << "Сгенерированное число [x] ->" << x;
    }
}
//определение y (y = g^x mod p)
void input_y(int& y, int g, int x, int P) {
    int g1 = 1;
    while (x > 0) {
        g1 = (g1 * g) % P;
        x--;
    }
    y = g1;
    cout << sys_msg << "Значение [y] ->" << y;
}
//определение k цулое число; взаимно простое с (P-1); 1 < k < p - 1
void input_k(int& k, int P) {
    int u;
    cout << sys_msg<<"Вы хотите ввести k <сеансовый ключ> вручную или сгенерировать его автоматически?\n1)ввести вручную\n2)сгенерирвать" << input<< "Введите свой ответ ->";
    input_ra(u, 2);
    if (u == 1) {
        while (true) {
            cout << warning << "Сеансовый ключ <k> должен соответствовать условиям: \n1) 1<k<(p-1)!\n2) целое число \n3) взаимно простое с (P-1) [" << P - 1 << "]";
            cout << input << "Введите значение <k> ->";
            input_int(k, 5, 1, P - 1);
            if (gcd(k, P - 1) == 1) { return; }
            cout << error << "Введенное значение не соответствует условиям!";
        }
    }
    else {
        while (true) {
            k = rand() % (P - 3) + 2;
            if (gcd(k, P - 1) == 1) { return; }
            cout << result<<"Сгенерированное число [k] ->" << k;
        }
    }
}
//шифрование
void encryption() {
    cout << sys_msg << "ЗАПУЩЕНА ПРОГРАММА ШИФРОВАНИЯ\n" << line;
    string text;
    int P, g, x, y,m,M,k,a,b,k1, a1,k2,b1,i_3, s_text;
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
    int** arr_en = new int* [s_text];
    for (int a = 0; a < s_text; a++) {
        arr_en[a] = new int[2];
    }
    if(i_3==1){
        cout << sys_msg << "Подготовка текста для шифрования ->\n";
        for (int i = 0; i < s_text; i++) {
            char c = text[i];
            int n = c;
            cout << "[" << text[i] << "] - <" << n << ">\n";
            arr[i] = n;
        }
    }
    if(i_3==2){
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
    input_P(P, m);
    input_g(g, P);
    input_x(x, P);
    input_y(y, g, x, P);
    for (int i = 0; i < s_text; i++) {
        input_k(k, P);
        for (int j = 0; j < 2; j++) {
            M = arr[i];
            if (j == 0) {
                k1 = k;
                a1 = 1;
                //a = g^k mod p 
                for (int f = 0; f < k1; f++) {
                    a1 = (a1 * g) % P;
                }
                a = a1;
                arr_en[i][j] = a;
            }
            else if (j == 1) {
                k2 = k;
                b1 = 1;
                //b = y^k * M mod p
                for (int h = 0; h < k2; h++) {
                    b1 = (b1 * y) % P;
                }
                b1 = (b1 * M) % P;
                b = b1;
                arr_en[i][j] = b;
            }
        }
    }
    cout << endl << line << result << "РЕЗУЛЬТАТ ШИФРОВАНИЯ\n" << sys_msg << "x = [" << x << "]\n" << sys_msg << "P = [" << P << "]\n" <<warning<<"(a,b) = 1 символ!"<< result << "\n|  a  |  b  |\n";
    for (int i = 0; i < s_text; i++) {
        for (int j = 0; j < 2; j++) {
            if (j == 0) {
                cout << "| " << arr_en[i][j];
            }
            if (j == 1) {
                cout << " | " << arr_en[i][j] << " |";
            }
        }
    }
    for (int a = 0; a < s_text; a++) {
        delete[] arr_en[a];
    }
    delete[] arr;
    delete[] arr_en;
}
//определение M (b * (a^x)^-1 mod p)
void M_text(int a, int b, int x, int P, int& M) {
    int g1 = 1;
    int m1 = 0;
    while (x > 0) {
        g1 = (g1 * a) % P;
        x--;
    }
    for (int i = 1; i < P; i++) {
        if ((g1 * i) % P == 1) {
            m1 = i;
            break;
        }
    }
    M = (b * m1) % P;
}
void decryption() {
    cout << sys_msg << "ЗАПУЩЕНА ПРОГРАММА ДЕШИФРОВАНИЯ\n" << line;
    cout << sys_msg << "Введите элементы сообщения ->"<<warning<<"1 символ равен (a,b)!"
        << warning<<"Для завершения ввода используйте значение 0 в поле a!";
    int s_text = 0;
    int a, b,s,P,x,i_2,i_3,m;
    string text_res = "";
    int** j = new int* [s_text];
    for (int i = 0; i < s_text; i++) {
        j[i] = new int[2];
    }
    while (true) {
        int new_s = s_text + 1;
        cout << sys_msg << "Ввод элемента <" << s_text + 1<<">";
        cout << input << "Введите элемент <a> ->";
        input_int(a, 0);
        if (a == 0) {
            break;
        }
        cout << input << "Введите элемент <b> ->";
        input_int(b, 0);
        int** arr_en = new int* [new_s];
        for (int i = 0; i < s_text; i++) {
            arr_en[i] = j[i];
        }
        arr_en[new_s - 1] = new int[2];
        arr_en[new_s - 1][0] = a;
        arr_en[new_s - 1][1] = b;
        delete[] j;
        j = arr_en;
        s_text = new_s;
    }
    cout<< input << "Введите значение [P] ->";
    input_int(P, 1);
    cout << input << "Введите значение [x] ->";
    input_int(x, 5, 1, P - 1);
    int* arr_de = new int[s_text];
    for (int i = 0; i < s_text; i++) {
        for (int h = 0; h < 2; h++) {
            if (h == 0) {
                a = j[i][h];
            }
            if (h == 1) {
                b = j[i][h];
            }
        }
        M_text(a, b, x, P, arr_de[i]);
    }
    cout << endl << line << sys_msg << "РЕЗУЛЬТАТ ДЕШИФРОВАНИЯ" << sys_msg << "x = [" << x << "]" << sys_msg << "P = [" << P << "]" << result << "Результат дешифрования ->";
    for (int i = 0; i < s_text; i++) {
        cout << arr_de[i] << "; ";
    }
    cout << sys_msg << "Хотите перевести полученный набор элементов в символы?\n1)да\n2)нет" << input << "Введите свой ответ ->";
    input_ra(i_2, 2);
    cout << sys_msg << "Выберите способ перевода:\n1)ASCII\n2)Пользовательский алфавит(введите <3> если хотите посмотреть пользовательский алфавит, после этого выбор будет продублирован)" << input << "Введите свой ответ ->";
    input_ra(i_3, 3);
    if (i_3 == 3) {
        for (int i = 0; i < al.size(); i++) {
            cout << i << " -> " << al[i] << endl;
        }
    }
    cout << sys_msg << "Выберите способ перевода:\n1)ASCII\n2)Пользовательский алфавит" << input << "Введите свой ответ ->";
    input_ra(i_3, 2);
    if (i_3 == 1) {
        for (int i = 0; i < s_text; i++) {
            text_res += (char)arr_de[i];
        }
    }
    if(i_3==2){
        for (int i = 0; i < s_text; i++) {
            text_res += al[arr_de[i] - 1];
        }
    }
    cout << result << "Результат перевода -> "<<text_res;
    for (int a = 0; a < s_text; a++) {
        delete[] j[a];
    }
    delete[] j;
    delete[] arr_de;
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
            decryption();
        }
        cout << endl << "Вы хотите продолжить работу? \n1)да\n2)нет" << input << "Введите свой выбор ->";
        input_ra(i_2, 2);
        if (i_2 == 2) {
            break;
        }
    }
    return 0;
}
