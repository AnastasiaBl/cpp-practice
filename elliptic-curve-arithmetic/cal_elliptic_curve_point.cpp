// cal_elliptic_curve_point.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//1)вычисляются параметры:a,b,p ;p-простое число
//2)проверяется условие: 4*a^3+27*b^2 != 0 (условие для a и b)
// 3)вычисляется левая часть с точками и правая y^2 mod P == x^3+a*x+b mod P
//4)создается координатная плоскость
// y/x ПЧ/ЛЧ; 
//5)выставляем точки в месте пересечений одинаковых сторон координат(ЛЧ, ПЧ)
//6)выписываются координаты точек по {x,y} (начиная с O{∞,∞},A{,} и тд)
//7)сложение точек
//7-1)разные
//λ=y(1)-y(2)*(x(1)-x(2))^-1, если (y(1)-y(2))==0 то λ=0
// x3=λ^2-(x(1)+y(2))
// y3=λ(x(1)-x(3))-y(2)
// !ошибочные координаты, если у нас получились координаты точки, 
// которой не существует, то такая точка будет обозначаться как точка бесконечности - O{∞,∞}.
//7-2)одинаковых
//λ=3*x(1)^2+a
//x(3)=λ^2-2*x(1)
//y(3)=λ*(x(1)-x(3))-y(1)
//8)скалярное умножение
//2P=P+P; 3P=2P+P

//Задание:
//A + B;
//F + C;
//D + D;
//A + A;
//3E;

#include <string> 
#include <iostream> 
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
string line = "\n------------------------------------------------------------------------------------------------------------\n";
string sys_msg = "\n[SYSTEM] ";
string warning = "\n[WARNING] ";
string input = "\n[INPUT] ";
string error = "\n[ERROR] ";
string result = "\n[RESULT] ";
struct Point {
    int x;
    int y;
    char n;
};
vector<Point> c;
int a, b, P;
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
//возведение в степень
int m(int a, int i) {
    int u = 1;
    while (i > 0) {
        u = u * a;
        i--;
    }
    return u;
}
//проверка на простое число
int pr(int a) {
    if (a < 2) { return 0; }
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) { return 0; }
    }
    return 1;
}
//определение P простое число и a,b<P
void input_P(int& P, int a,int b) {
    int u;
    cout << sys_msg << "Выберите способ ввода модуля <P> :" << "\n1 - Ввести параметр вручную"
        << "\n2 - Сгенерировать параметр автоматически" << input << "Введите ваш ответ ->";
    input_ra(u, 2);
    if (u == 1) {
        while (true) {
            cout << warning << "P <модуль> должен соответствовать условиям: \n1 - простое число \n2 - P>"<<a<<" и P>"<<b << input << "Введите значение[P] ->";
            input_int(P, 1);
            if (pr(P) == 1 and P > a and P>b) {
                return;
            }
            cout << error << "Введенное значение не соответствует условиям!";
        }
    }
    else {
        while (true) {
            P = 2 + rand() % 29;
            if (pr(P) == 1 and P > a and P > b) {
                return;
            }
        }
        cout << result << "Сгенерированное число <P> ->" << P;
    }
}
void coordinate_plane(int P, int a, int b) {
    vector<vector<char>> grid(P, vector<char>(P, '.'));
    char p = 'A';
    vector<int> left(P);
    vector<int> right(P);
    int r, l;
    c.push_back({0, 0,'O'});
    for (int x = 0; x < P; x++) {
        r = 1;
        r = ((x*x*x) + a * x + b) % P;
        right[x] = r;
        for (int y = 0; y < P; y++) {
            l = 1;
            l = (y*y) % P;
            left[y] = l;
            if (l == r) {
                c.push_back({x,y,p});
                grid[y][x] = '*';
                p++;
            }
        }
    }
    cout<<sys_msg << "Координатная плоскость:\n\n";
    cout << "y\\x ";
    for (int x = 0; x < P; x++) {
        cout << x << " ";
    }
    cout << "| ЛЧ(y)"<<endl;
    for (int i = 0; i < P * 2 + 12; i++) {
        cout << "-";
    }
    cout << endl;
    for (int y = 0; y < P; y++) {
        cout << y << " | ";
        for (int x = 0; x < P; x++) {
            cout << grid[y][x] << " ";
        }
        cout << "| " << left[y];
        cout << endl;
    }
    for (int i = 0; i < P * 2 + 12; i++) {
        cout << "-";
    }
    cout << endl<<"ПЧ  ";
    for (int x = 0; x < P; x++) {
        cout << right[x] << " ";
    }
    cout << sys_msg << "Множество точек:\n";
    cout << c[0].n<<"{∞,∞}" << endl;
    for (int i = 1; i < c.size(); i++) {
        cout << c[i].n << "{" << c[i].x << "," << c[i].y << "}" << endl;
    }
    cout<<result<<"Общее количество: "<< c.size()-1;
}
int input_d( int x,int p) {
    for (int i = 1; i < p; i++) {
        if ((x * i) % p == 1) {
            return i;
        }
    }
   return -1;
}
void addition(int x1,int y1,int x2,int y2,int p) {
    int x3, y3, d,l;
    if (x1 != x2) {
        int dx = ((x1 - x2) % p + p) % p;
        int dy = ((y1 - y2) % p + p) % p;
        d = input_d(dx, p);
        if (d == -1) {
            cout << error << "Обратный элемент не существует. Получена точка O{∞,∞}\n";
            return;
        }
        l = (dy * d) % p;
        x3 = (l * l) - (x1 +x2);
        y3 = l * (x1 - x3) - y1;
        x3 = (x3%p + p) % p;
        y3 = (y3%p + p) % p;
    }
    else {
        int dx = (3 * x1 * x1 + a) % p;
        int dy = (2 * y1) % p;
        d = input_d(dy, p);
        if (d == -1) {
            cout << error << "Обратный элемент не существует. Получена точка O{∞,∞}\n";
            return;
        }
        l= (dx * d) % p;
        x3 = (l * l) - (2 * x1);
        y3 = l * (x1 - x3) - y1;
        x3 = (x3 % p + p) % p;
        y3 = (y3 % p + p) % p;
    }
    
    bool found = false;
    for (int i = 1; i < c.size(); i++) {
        if (c[i].x ==x3 && y3== c[i].y) {
            cout<<result<<"Совпадение с точкой ->"<< c[i].n << "{" << c[i].x << "," << c[i].y << "}" << endl;
            cout << result << "λ = " << l;
            cout << result << "Результат сложения = {" << x3 << "," << y3 << "}\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << result<< "Получена точка бесконечности O{∞,∞}\n";
    }
}
void multiplication(int x1,int y1,int p,int i) {
    int  d,l,x3,y3,l2;
    bool found = false;
    int x2 = x1;
    int y2 = y1;
    int dx = (3 * x1 * x1 + a) % p;
    int dy = (2 * y1) % p;
    d = input_d(dy, p);
    if (d == -1) {
        cout << error << "Обратный элемент не существует. Получена точка O{∞,∞}\n";
        return;
    }
    l = (dx * d) % p;
    x3 = (l * l) - (2 * x1);
    y3 = l * (x1 - x3) - y1;
    x3 = (x3 % p + p) % p;
    y3 = (y3 % p + p) % p;
    if (i == 2) {
        cout << result << "Результат умножения: " << i << "P = " << "{" << x3 << "," << y3 << "}\n";
        for (int i = 1; i < c.size(); i++) {
            if (c[i].x == x3 && y3 == c[i].y) {
                cout << result << "Совпадение с точкой ->" << c[i].n << "{" << c[i].x << "," << c[i].y << "}" << endl;
                cout << result << "λ = " << l;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << result << "Получена точка бесконечности O{∞,∞}\n";
        }
        return;
    }
    for (int j = 3; j <= i; j++) {
        int dx2 = ((x3 - x1) % p + p) % p;
        int dy2 = ((y3 - y1) % p + p) % p;
        int d2 = input_d(dx2, p);
        if (d2 == -1) {
            cout << result << "λ = " << l;
            cout << error<< "Получена точка O{∞,∞}\n";
            return;
        }
        l2 = (dy2 * d2) % p;
        int x4 = (l2 * l2) - (x3 + x1);
        int y4 = l2 * (x3 - x4) - y3;
        x4 = (x4 % p + p) % p;
        y4 = (y4 % p + p) % p;
        x3 = x4;
        y3 = y4;
    }
    cout<<result<<"Результат умножения: "<<i<<"P = "<<"{" << x3 << "," << y3 << "}\n";
    for (int i = 1; i < c.size(); i++) {
        if (c[i].x ==x3 && y3== c[i].y) {
            cout<<result<<"Совпадение с точкой ->"<< c[i].n << "{" << c[i].x << "," << c[i].y << "}" << endl;
            cout << result << "λ = " << l2;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << result<< "Получена точка бесконечности O{∞,∞}\n";
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    cout <<sys_msg<< "ДОБРО ПОЖАЛОВАТЬ!\n"<<line;
    while (true) {
        int i1,i2,i3,i4;
        while (true) {
            cout << sys_msg << "Выберите способ ввода параметра <a> :" << "\n1 - Ввести параметр вручную"
                << "\n2 - Сгенерировать параметр автоматически"<<input<<"Введите ваш ответ ->";
            input_ra(i1, 2);
            if (i1 == 1) {
                cout << warning << "Введенные параметры должны соответствовать условию: 4*a^3 + 27*b^2 mod p != 0";
                cout << input << "Введите параметр <a> ->";
                input_int(a);
            }
            else {
                a = rand() % 30;
                cout << sys_msg << "Сгенерированный параметр <a> ->"<<a;
            }
            cout << sys_msg << "Выберите способ ввода параметра [b]:" << "\n1 - Ввести параметр вручную"
                << "\n2 - Сгенерировать параметр автоматически" << input << "Введите ваш ответ ->";
            input_ra(i2, 2);
            if (i2 == 1) {
                cout << warning << "Введенные параметры должны соответствовать условию: 4*a^3 + 27*b^2 mod p != 0";
                cout << input << "Введите параметр <b> ->";
                input_int(b);
            }
            else {
                b = rand() % 30;
                cout <<sys_msg<< "Сгенерированный параметр <b> ->" << b;
            }
            cout << sys_msg << "Проверка условия: 4*a^3 + 27*b^2 mod p != 0";
            int a1 = m(a, 3);
            int b1 = m(b, 2);
            input_P(P, a, b);
            if (((4 * a1) + (27 * b1))%P != 0) {
                cout << sys_msg << "Условие выполнено. Кривая корректна.";
                break;
            }
            else {
                cout << error << "Кривая вырожденная. Необходимо изменить параметры a и b.";
            }
        }
        coordinate_plane(P, a, b);
        char s1,s2;
        while(true){
            cout<<sys_msg<<"Выберите операцию: \n1 - Сложение двух точек\n2 - Скалярное умножение точки\n3 - Завершить программу\n4 - Задать новые параметры"<<input<<"Введите номер операции ->";
            input_ra(i4,4);
            if(i4==1){
                int x1, x2, y1, y2;
                while (true) {
                    bool found = false;
                    bool f2 = false;
                    cout << input << "Введите букву первой точки -> ";
                    cin >> s1;
                    cout << input << "Введите букву второй точки -> ";
                    cin >> s2;
                    for (int i = 1; i < c.size(); i++) {
                        if (c[i].n == s1) {
                            x1 = c[i].x;
                            y1 = c[i].y;
                            found = true;
                        }
                        if (c[i].n == s2) {
                            x2 = c[i].x;
                            y2 = c[i].y;
                            f2 = true;
                        }
                    }
                    if (found && f2) {
                        break; 
                    }
                    cout << error << "Введенной точки не существует, повторите ввод!";
                }
                addition(x1,y1,x2,y2,P);
            }
            if(i4==2){
                int x1, x2, y1, y2,h;
                char s1;
                while (true) {
                    bool f1 = false;
                    cout << input << "Введите букву точки -> ";
                    cin >> s1;
                    for (int i = 1; i < c.size(); i++) {
                        if (c[i].n == s1) {
                            x1 = c[i].x;
                            y1 = c[i].y;
                            f1 = true;
                            break;
                        }
                    }
                    if (f1) {
                        break;
                    }
                    cout << error << "Введенной точки не существует, повторите ввод!\n";
                }
                cout<<input<<"Введите коэффициент скалярного умножения -> ";
                input_int(h,1);
                multiplication(x1,y1,P,h);
            }
            if(i4==3){
                cout << endl << "Вы хотите продолжить работу? \n1)да\n2)нет" << input << "Введите свой выбор ->";
                input_ra(i3, 2);
                if (i3 == 2) {
                    break;
                }
            }
            if(i4==4){
                break;
            }
        }
        //Задание:
        //A + B;
        //F + C;
        //D + D;
        //A + A;
        //3E;
        if (i4 == 3) {
            break;
        }
    }
}
