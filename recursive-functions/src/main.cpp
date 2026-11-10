#include <iostream>
#include <sstream>
#include <locale>
using namespace std;

//Вычисляет n!
int task_1(int y);
int factorial(int n);
//Числа Трибоначи 
int task_2(int y);
int tribonacci(int n);
//Алгоритм Евклида
int task_3(int y);
int gcd(int a, int b);
//Общие
int main();
int close(int y);

int task_1(int y) {
    cout << "Введите положительное целое число: ";
    char fail;
    string number;
    int nu;
    cin >> number;
    istringstream stream(number);
    if (stream >> nu and !(stream >> fail)) {
        if (nu > 0) {
            cout << nu << "!=" << factorial(nu) << endl;
            return 0;
        }
        else
        {
            cout << "Ошибка при вводе! Вы ввели отрицательное число!\n\n";
            return task_1(y);
        }
    }
    else {
        cout << "Ошибка при вводе! Введено некорректное число.\n\n";
        return task_1(y);
    }
}
int factorial(int n) {
    if (n == 1 or n==0) {
        return 1;
    }
    return n * factorial(n - 1);
}
int tribonacci(int n) {
    if ( n==0) {
        return 0;
    }
    if (n == 1 or n == 2) {
        return 1;
    }
        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
} 
int task_2(int y) {
    cout << "Введите целое число: ";
    char fail;
    string number;
    int nu;
    cin >> number;
    istringstream stream(number);
    if (stream >> nu and !(stream >> fail)) {
        if (nu > 0) {
            cout << "T(" << nu << ")=" << tribonacci(nu) << endl;
            return 0;
        }
        else
        {
            cout << "Ошибка при вводе! Вы ввели отрицательное число!\n\n";
            return task_2(y);
        }
    }
    else {
        cout << "Ошибка при вводе! Введено некорректное число.\n\n";
        return task_2(y);
    }
}
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    if (a == 0) {
        return b;
    }
    return gcd(b, a % b);
}
int task_3(int y) {
    cout << "Введите 2 числа (1(a) больше, чем 2(b)): \na=";
    char fail1, fail2;
    string number_1, number_2;
    cin >> number_1;
    int nu1, nu2;
    cout << "b=";
    cin >> number_2;
    istringstream stream_1(number_1);
    istringstream stream_2(number_2);
    if ((stream_1 >> nu1 and !(stream_1 >> fail1)) and (stream_2 >> nu2 and !(stream_2 >> fail2))){
        if (nu1 != 0 and nu2 != 0) {
            if (nu1 < nu2) {
                cout << "Ошибка при вводе! Введите еще раз (1(a) больше, чем 2(b))!\n\n";
                return task_3(y);
            }
        }        
        cout << "НОД(a=" << nu1 << ";" << "b=" << nu2 << ") = " << gcd(nu1, nu2) << endl;
        return 0;
    }
    else {
        cout << "Ошибка при вводе! Введено некорректное число.\n\n";
        return task_3(y);
    }
}
int close(int y) {
    int v;
    char fail;
    string choice;
    cout << "Вы хотите продолжить работу? \n1-да \n2-нет\n\nУкажите свой выбор:";
    cin >> choice;
    cout << "\n\n";
    istringstream stream(choice);
    if (stream >> v and !(stream >> fail)) {
        if (v == 1) {
            main();
        }
        if (v == 2) {
            return 0;
        }
        else {
            cout << "Ошибка при вводе! Введите число от 1 до 2.\n";
            close(v);
        }
    }
    else {
        cout << "Ошибка при вводе! Введите число от 1 до 2.\n\n";
        close(v);
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    string program;
    while (true) {
        cout << "Здравствуйте! Выберите, какую программу вы хотите запустить: \n1 - Вычислить n!.\n2 - Числа Трибоначчи.\n3 - Алгоритм Евклида для вычисления наибольшего общего делителя.\nВведите номер выбранной программы:";
        cin >> program;
        istringstream stream(program);
        int y;
        char fail;
        if (stream >> y and !(stream >> fail)) {
            if (y == 1) {
                task_1(y);
                close(y);
                break;
            }
            if (y == 2) {
                task_2(y);
                close(y);
                break;
            }
            if (y == 3) {
                task_3(y);
                close(y);
                break;
            }
            else {
                cout << "Ошибка: введите число от 1 до 3.\n\n";
            }
        }
        else {
            cout << "Ошибка при вводе! Пожалуйста, введите число от 1 до 3.\n\n";
            continue;
        }
    }
}


