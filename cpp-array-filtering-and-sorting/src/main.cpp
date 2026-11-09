
#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <limits>


using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите кол-во элементов массива:";
    cin >> n;
    vector<variant<int, char, double, string, bool>> arr;
    for (int i = 0; i < n; i++) {

        cout << "Выберите тип данных для элемента " << i + 1 << ": \n 1-int \n 2-char \n 3-double \n 4-string \n 5-bool \n";
        int type;
        cin >> type;
        switch (type)
        {
        case 1: {
            int data;
            cout << "Введите значение:";
            cin >> data;
            while (!(cin >> data)) {
                cout << "Неверное значение! Введите снова: \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            arr.push_back(data);
            break;
        }
        case 2: {
            char data;
            cout << "Введите значение:";
            cin >> data;
            while (!(cin >> data)) {
                cout << "Неверное значение! Введите снова: \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            arr.push_back(data);
            break;
        }
        case 3: {
            double data;
            cout << "Введите значение:";
            cin >> data;
            while (!(cin >> data)) {
                cout << "Неверное значение! Введите снова: \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            arr.push_back(data);
            break;
        }
        case 4: {
            string data;
            cout << "Введите значение:";
            cin >> data;
            while (!(cin >> data)) {
                cout << "Неверное значение! Введите снова: \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            arr.push_back(data);
            break;
        }
        case 5: {
            bool data;
            cout << "Введите значение:";
            cin >> data;
            while (!(cin >> data)) {
                cout << "Неверное значение! Введите снова: \n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            arr.push_back(data);
            break;
        }
        default:
            cout << "Неверный выбор типа данных!" << endl;
            i--;
            break;
        }
    }
    cout << "\nМассив: \n";
    for (auto& e : arr) {
        visit([](auto&& a) 
            {
            cout << a << "\n";
            }, e);
    }
    return 0;
}
