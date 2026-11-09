#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
// Функция для зполнения массива случайными числами
void randomint(int two[5][5]) {
    cout << "Массив 5*5:" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            two[i][j] = rand() % 100;
        }
    }
}
// Функция для заполнения массива случайными числами
void randomints(int array1[], int array2[]) {
    for (int i = 0; i < 5; i++) {
        array1[i] = i;  //для строк
        array2[i] = i;  //для столбцов
    }
    random_shuffle(array1, array1 + 5);
    random_shuffle(array2, array2 + 5);
}
// Функция для заполнения двумерного массива символами из строки
void arraystr(char array[5][5], string& str) {
    int id = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            array[i][j] = str[id++];
        }
    }
}
// Функция для заполнения двумерного массива символами из одномерных массивов
void five(int array[5][5],int array2[5],int array3[5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            array[i][j] = 0;
        }
    }
    int id = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            array[array2[i]][array3[j]]=id++;
        }
    }
}
// Функция для генерации случайной буквы от 'A' до 'Z'
void randomchar(char array[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            array[i][j] = 'a' + rand() % 26;  
        }
    }
}
// Функция для вывода двумерного массива символов
void printchar(char array[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << array[i][j] << "\t";
        }
        cout << endl;
    }
}
// Функция для вывода двумерного массива целых чисел
void printint(int array[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << array[i][j] << "\t";
        }
        cout << endl;
    }
}
// Функция для поиска максимального четного числа в строке и его размещения на диагонали
void even(int array[5][5], int res[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            res[i][j] = array[i][j];
        }
    }
    for (int i = 0; i < 5; i++) {
        int maxi = -1;
        for (int j = 0; j < 5; j++) {
            int e = array[i][j];
            if (e % 2 == 0 and e > maxi) {
                maxi = e;
            }
        }
        if (maxi != -1) {
            res[i][i] = maxi;
        }
        else {
            res[i][i] = 0;
        }
    }
}
//Функция для поиска гласных букв
void vowels(char array[5][5]) {
    char vowels[5] = { 'a', 'e', 'i', 'o', 'u'};
    for (int i = 0;i < 5;i++) {
        for (int j = 0;j < 5;j++) {
           char b = array[i][j];
            for (int a = 0;a < 5;a++) {
                if (b == vowels[a]) {
                    cout << "Гласная буква: " << b << " на позиции [ " << i+1 << " ][ " << j+1 << " ]" << "\n";
                }
            }
        }
    }
}
int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    string one;
    cout << "Введите значение : \n";
    cin >> one;
    if (one.size() != 25) {
        cout << "Ошибка, попробуйте снова!\n";
        return 1;
    }
    char arr[5][5];
    arraystr(arr, one);
    cout << "Char array:" << endl;
    printchar(arr);
    int two[5][5];
    randomint(two);
    printint(two);
    int three[5][5] = { 0 };
    even(two, three);
    cout << "Массив после изменений (максимальные четные числа на диагонали):" << endl;
    printint(three);
    char letter[5][5];
    randomchar(letter);
    cout << "Массив заполненный рандомными значениями: \n";
    printchar(letter);
    cout << "ШАБЛОН: \nГласная буква: " << "БУКВА  на позиции [ СТРОКА ][ СТОЛБЕЦ ] \n";
    vowels(letter);
    int array1[5][5];
    int array2[5];
    int array3[5];
    randomints(array2, array3);
    sort(array2, array2 + 5);
    sort(array3, array3 + 5);
    five(array1, array2, array3);
    cout << "Двумерный массив на основе двух одномерных массивов:" << endl;
    printint(array1);
}
