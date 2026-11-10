#include <iostream>
#include <sstream>
#include <locale>
using namespace std;

//General list
class Check;
//int clos();
class Task_1;
//int factorial(int n);
//int task_1();
class Task_2;
//int tribonacci(int n);
//int task_2();
class Task_3;
//int gcd(int a, int b);
//int task_3();
class Task_4;
//int extended_Euc(int a, int b, int gcd);
//int task_4();
class ADD;
//int check(int nu);
//int start();
int main();

//Global variables
int num = 0;
int i = -1;

class Check {
public:
    int check(int& nu, int& i) {
        char fail;
        string in;
        cin >> in;
        istringstream str(in);
        if (str >> nu and !(str >> fail)) {
            i = 1;
            return nu;
        }
        else {
            cout << "\nОшибка при вводе! Введено некорректное значение.\n\n";
            i = 0;
            return i;
        }
    }
};
class Task_1 {
public:
    int factorial(int n) {
        if (n == 1 or n == 0) {
            return 1;
        }
        return n * factorial(n - 1);
    }
    int task_1() {
        cout << "\nВведите положительное целое число: ";
        Check t;
        t.check(num, i);
        if (i == 1) {
            if (num > 0) {
                cout << "\n" << num << "!=" << factorial(num) << endl;
                return 0;
            }
            else
            {
                cout << "\nОшибка при вводе! Вы ввели отрицательное число!\n\n";
                return task_1();
            }
        }
        return task_1();
    }
};
class Task_2 {
public:
    int tribonacci(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1 or n == 2) {
            return 1;
        }
        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
    }
    int task_2() {
        cout << "\nВведите целое число: ";
        Check t;
        t.check(num, i);
        if (i == 1) {
            if (num > 0) {
                cout << "T(" << num << ")=" << tribonacci(num) << endl;
                return 0;
            }
            else
            {
                cout << "Ошибка при вводе! Вы ввели отрицательное число!\n\n";
                return task_2();
            }
        }
        return task_2();
    }
};
class Task_3 {
public:
    int gcd(int a, int b) {
        if (b == 0) {
            return a;
        }
        if (a == 0) {
            return b;
        }
        return gcd(b, a % b);

    }
    int task_3() {
        cout << "Введите 2 числа (1(a) больше, чем 2(b)): \na=";
        int i1, i2, gcd_r, nu1, nu2;
        Check t;
        t.check(num, i);
        nu1 = num;
        i1 = i;
        cout << "b=";
        t.check(num, i);
        nu2 = num;
        i2 = i;
        if (i1 == 1 and i2 == 1) {
            gcd_r = gcd(nu1, nu2);
            cout << "НОД(a=" << nu1 << ";" << "b=" << nu2 << ") = " << gcd_r << endl;
            return 0;
        }
        return task_3();
    }
};
class Task_4 {
private:
    int extended_Euc(int a, int b, int& x) {
        if (b == 0) {
            x = 1;
            return a;
        }
        int x0 = 1, x1 = 0;
        int r, P, res,q;
        P = b;
        while (b > 0) {
            r = a % b;
            q = a / b;
            a = b;
            b = r;
            res = x0 - q * x1;
            x0 = x1;
            x1 = res;
        }
        x = x0;
        return a;
    }
public:
    int task_4() {
        cout << "Введите 2 числа (1(a) больше, чем 2(b)): \na=";
        int i1, i2, a, b, x;
        Check t;
        t.check(a, i1);
        cout << "b=";
        t.check(b, i2);
        if (i1 == 1 and i2 == 1) {
            if (a < 0 or b < 0) {
                cout << "Ошибка! Числа должны быть положительными.\n";
                return task_4();
            }
            int res = extended_Euc(a, b, x);
            cout << "НОД(a=" << a << ";" << "b=" << b << ") = " << res << endl
                << "Коэффициент x = " << x << endl;
            if (res == 1) {
                int rev = (x % b + b) % b;
                cout << "Обратный элемент " << a << " по модулю " << b << " = " << rev << endl;
                return 0;
            }
            else {
                cout << "Обратного элемента не существует, так как НОД не равен 1.\n";
                return 0;
            }
        }
        return task_4();
    }
};
class ADD {
public:
    int clos() {
        cout << "\nВы хотите продолжить работу? \n1-да \n2-нет\n\nУкажите свой выбор:";
        Check t;
        t.check(num, i);
        cout << "\n\n";
        if (i == 1) {
            if (num == 1) {
                start();
            }
            if (num == 2) {
                return 0;
            }
            else {
                cout << "\nОшибка при вводе! Введите число от 1 до 2.\n";
                clos();
            }
        }
        else {
            clos();
        }
    }
    int start() {
        while (true) {
            cout << "Здравствуйте! Выберите, какую программу вы хотите запустить: "
                << "\n1 - Вычислить n!."
                << "\n2 - Числа Трибоначчи."
                << "\n3 - Алгоритм Евклида для вычисления наибольшего общего делителя."
                << "\n4 - Расширенный алгоритм Евклида (вычисляет НОД, коэффициент соотношения x)"
                << "\nВведите номер выбранной программы : ";
            Check t;
            t.check(num, i);
            if (i == 1) {
                if (num == 1) {
                    Task_1 t;
                    t.task_1();
                    clos();
                    break;
                }
                if (num == 2) {
                    Task_2 k;
                    k.task_2();
                    clos();
                    break;
                }
                if (num == 3) {
                    Task_3 n;
                    n.task_3();
                    clos();
                    break;
                }
                if (num == 4) {
                    Task_4 l;
                    l.task_4();
                    clos();
                    break;
                }
                else {
                    cout << "\nОшибка при вводе! Пожалуйста, введите число от 1 до 3.\n\n";
                    continue;
                }
            }
        }
        return 0;
    }
};
int main()
{
    setlocale(LC_ALL, "Russian");
    ADD t;
    t.start();
    return 0;
}
