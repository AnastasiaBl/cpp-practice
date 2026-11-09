#include <iostream>
#include <string>

using namespace std;
// 5 задание(1 часть) (Создать функции (int, char, void), которые будут прибавлять к переменной +20)
int s (int a)
{
    return a + 20;
}
char u (char b)
{
    return b + 20;
}
void m (int &c)
{
    c += 20;
}
int main() {
    // 1 задание (Создать переменные (int, char, string))
    int x;
    int t = 2;
    char r = 'b';
    string g = "Hello, good day!";
    // 2 задание (Вывести переменные(перемнную string вывести как переменную и как массив))
    cout << "Variable int = " << t << "\n" << "Variable char = " << r << "\n" << "Variable string = " << g << "\n";
    cout << "Array string = ";
    for (int i = 0; i < g.size(); i++)
    {
        cout << g[i] << " ";
    }
    cout << endl;
    // 3 задание (Создать массивы (int, char))
    int numbers[4] = { 1,2,3,4 };
    char name[9] = { 'A','N','A','S', 'T','A','S','I','A' };
    // 4 задание (Вывести массивы (Вывести отдельно по индексу, вывести весь массив))
    cout << "Element: 1" << " | id: 0" << " | " << numbers[0] << "\n";
    cout << "Element: 2" << " | id: 1" << " | " << numbers[1] << "\n";
    cout << "Element: 3" << " | id: 2" << " | " << numbers[2] << "\n";
    cout << "Element: 4" << " | id: 3" << " | " << numbers[3] << "\n";
    for (int a = 0; a < 4; a++)
    {
        cout << "Element: " << a + 1 << " | id: " << a << " | " << numbers[a] << endl;
    }
    int id;
    cout << "Enter a id: ";
    cin >> id;
    if (id <= 8 and id >= -1)
    {
        cout << "Name element: " << id + 1 << " | id: " << id << " | letter: " << name[id] << endl;
    }
    else
    {
        cout << "False" << "\n";
    }
    cout << "Name :";
    for (int n = 0; n < 9; n++) {
        cout << name[n];
    }
    //5 задание(2 часть)
    cout << "\n" << "Enter a number: " << endl;
    cin >> x;

    cout << "The result of the function s(x): " << s(x) << endl;
    int x2 = u(x);
    cout << "The result of the function u(x): " << x2 << endl;
    m(x);
    cout << "The result of the function m(x): " << x << endl;


    return 0;

}
