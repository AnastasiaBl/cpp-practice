
#include <iostream>
#include <ctime>
using namespace std;
int line;// строка
int column;// столбец
int Sblock;// S-блок
static const uint8_t __EP[48] = {
    32, 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 ,
    8 , 9 , 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 ,
};

static const uint8_t __P[32] = {
    16, 7 , 20, 21, 29, 12, 28, 17, 1 , 15, 23, 26, 5 , 18, 31, 10,
    2 , 8 , 24, 14, 32, 27, 3 , 9 , 19, 13, 30, 6 , 22, 11, 4 , 25,
};
static const uint8_t __Sbox[8][4][16] = {
    { // 0
        {14, 4 , 13, 1 , 2 , 15, 11, 8 , 3 , 10, 6 , 12, 5 , 9 , 0 , 7 },
        {0 , 15, 7 , 4 , 14, 2 , 13, 1 , 10, 6 , 12, 11, 9 , 5 , 3 , 8 },
        {4 , 1 , 14, 8 , 13, 6 , 2 , 11, 15, 12, 9 , 7 , 3 , 10, 5 , 0 },
        {15, 12, 8 , 2 , 4 , 9 , 1 , 7 , 5 , 11, 3 , 14, 10, 0 , 6 , 13},
    },
    { // 1
        {15, 1 , 8 , 14, 6 , 11, 3 , 4 , 9 , 7 , 2 , 13, 12, 0 , 5 , 10},
        {3 , 13, 4 , 7 , 15, 2 , 8 , 14, 12, 0 , 1 , 10, 6 , 9 , 11, 5 },
        {0 , 14, 7 , 11, 10, 4 , 13, 1 , 5 , 8 , 12, 6 , 9 , 3 , 2 , 15},
        {13, 8 , 10, 1 , 3 , 15, 4 , 2 , 11, 6 , 7 , 12, 0 , 5 , 14, 9 },
    },
    { // 2
        {10, 0 , 9 , 14, 6 , 3 , 15, 5 , 1 , 13, 12, 7 , 11, 4 , 2 , 8 },
        {13, 7 , 0 , 9 , 3 , 4 , 6 , 10, 2 , 8 , 5 , 14, 12, 11, 15, 1 },
        {13, 6 , 4 , 9 , 8 , 15, 3 , 0 , 11, 1 , 2 , 12, 5 , 10, 14, 7 },
        {1 , 10, 13, 0 , 6 , 9 , 8 , 7 , 4 , 15, 14, 3 , 11, 5 , 2 , 12},
    },
    { // 3
        {7 , 13, 14, 3 , 0 , 6 , 9 , 10, 1 , 2 , 8 , 5 , 11, 12, 4 , 15},
        {13, 8 , 11, 5 , 6 , 15, 0 , 3 , 4 , 7 , 2 , 12, 1 , 10, 14, 9 },
        {10, 6 , 9 , 0 , 12, 11, 7 , 13, 15, 1 , 3 , 14, 5 , 2 , 8 , 4 },
        {3 , 15, 0 , 6 , 10, 1 , 13, 8 , 9 , 4 , 5 , 11, 12, 7 , 2 , 14},
    },
    { // 4
        {2 , 12, 4 , 1 , 7 , 10, 11, 6 , 8 , 5 , 3 , 15, 13, 0 , 14, 9 },
        {14, 11, 2 , 12, 4 , 7 , 13, 1 , 5 , 0 , 15, 10, 3 , 9 , 8 , 6 },
        {4 , 2 , 1 , 11, 10, 13, 7 , 8 , 15, 9 , 12, 5 , 6 , 3 , 0 , 14},
        {11, 8 , 12, 7 , 1 , 14, 2 , 13, 6 , 15, 0 , 9 , 10, 4 , 5 , 3 },
    },
    { // 5
        {12, 1 , 10, 15, 9 , 2 , 6 , 8 , 0 , 13, 3 , 4 , 14, 7 , 5 , 11},
        {10, 15, 4 , 2 , 7 , 12, 9 , 5 , 6 , 1 , 13, 14, 0 , 11, 3 , 8 },
        {9 , 14, 15, 5 , 2 , 8 , 12, 3 , 7 , 0 , 4 , 10, 1 , 13, 11, 6 },
        {4 , 3 , 2 , 12, 9 , 5 , 15, 10, 11, 14, 1 , 7 , 6 , 0 , 8 , 13},
    },
    { // 6
        {4 , 11, 2 , 14, 15, 0 , 8 , 13, 3 , 12, 9 , 7 , 5 , 10, 6 , 1 },
        {13, 0 , 11, 7 , 4 , 9 , 1 , 10, 14, 3 , 5 , 12, 2 , 15, 8 , 6 },
        {1 , 4 , 11, 13, 12, 3 , 7 , 14, 10, 15, 6 , 8 , 0 , 5 , 9 , 2 },
        {6 , 11, 13, 8 , 1 , 4 , 10, 7 , 9 , 5 , 0 , 15, 14, 2 , 3 , 12},
    },
    { // 7
        {13, 2 , 8 , 4 , 6 , 15, 11, 1 , 10, 9 , 3 , 14, 5 , 0 , 12, 7 },
        {1 , 15, 13, 8 , 10, 3 , 7 , 4 , 12, 5 , 6 , 11, 0 , 14, 9 , 2 },
        {7 , 11, 4 , 1 , 9 , 12, 14, 2 , 0 , 6 , 10, 13, 15, 3 , 5 , 8 },
        {2 , 1 , 14, 7 , 4 , 10, 8 , 13, 15, 12, 9 , 0 , 3 , 5 , 6 , 11},
    },
};
// Заполнение массива рандомными числами
void rands(int arr[32]) {
    for (int i = 0;i < 32;i++) {
        arr[i] = rand() % 2;
        cout << arr[i];
    }
    
}
// Вывод массива
void printint(int arr[], int size) {
    for (int i = 0;i < size;i++) {
        cout << arr[i];
    }
    cout << endl;
}
// Перевод в 10-тичную систему счисления
int binary(int arr1[2], int arr2[4]) {
    int bit2[] = { 2, 1 };
    int bit4[] = { 8,4,2,1 };
    int size;
    line = 0;
    column = 0;
    
    for (int i = 0; i < 2;i++) {
        if (arr1[i] == 1) {
            line += bit2[i];
        }
    }
    for (int j = 0; j < 4;j++) {
        if (arr2[j] == 1) {
            column += bit4[j];
        }
    }
    if (Sblock < 0 or Sblock > 7 or line < 0 or line > 3 or column < 0 or column > 15) {
        cout << "Ошибка: индекс выходит за пределы массива!"<<"\nS-блок(Sblock) = " << Sblock << ", строка(line)  = " << line << ", столбец(column) = " << column << endl;
        return -1;
    }
    cout << "S-блок: " << Sblock+1 << " Линия: " << line+1 << " Строка: " << column+1<<"\n";
    int result = __Sbox[Sblock][line][column];
    cout<<"Значение, возвращаемое S-блоком: " << result << endl;
    return result;
}
// Перевод в 2-ичную систему счисления
void reversebinary(int res) {
    int bit[4] = { 0 };
    for (int i = 3;i >= 0;i--) {
        bit[i] = res % 2;
        res = res / 2;
    }
    int size = 4;
    printint(bit, size);
}
// Функция обработки S-блоков
void processing(int arr[6],int boxnum) {
    cout << "Группа: " << boxnum+1 << " элементы: ";
    int size;
    size = 6;
    printint(arr,size);
    int arr1[2] = { arr[0], arr[5] };
    int arr2[4] = { arr[1], arr[2], arr[3], arr[4] };
    cout << "Линия: ";
    size = 2;
    printint(arr1, size);
    size = 4;
    cout << "Строка: ";
    printint(arr2, size);
    Sblock = boxnum;
    int result = binary(arr1, arr2);
    cout << "4-битный результат S-блока: ";
    reversebinary(result);
    cout << endl;
}
// Функция обработки 8 блоков
void grouping(int array[48]) {
    for (int i = 0; i < 8; i++) {
        int arr[6];
        for (int j = 0; j < 6; j++) {
            arr[j] = array[i * 6 + j];
        }
        processing(arr, i);
    }
}
// Функция расширения(E) до 48 бит
void expansionE(int arr[48],int array[32]) {
    cout << "Расширение до 48 бит:\n";
    for (int i = 0;i < 48;i++) {
        arr[i] = array[__EP[i] - 1];
        cout << arr[i];
    }
    cout << endl;
}
// Функция перестановки
void permutation(int arr[48], int array[32]) {
    for (int i = 0;i < 32;i++) {
        arr[i] = array[__P[i] - 1];
        cout << arr[i];
    }
}
int main()
{
    srand(time(0));
    setlocale(LC_ALL, "Russian");
    int choice;
    int plaintext[32];
    int temporary[32] = { 1,0,1,0,1,0,1,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 };
    cout << "Вам нужно выбрать, каким будет начальный текст для шифрования:\n1-уже набраный текст\n2-сгенерировать текст случайным образом\n3-ввести текст самостоятельно\n";
    cin >> choice;
    if (choice == 1) {
        for (int i = 0; i < 32; i++) {
            plaintext[i] = temporary[i];
        }
        cout << "\nВы выбрали предустановленный текст:";
        cout << endl;
    }
    else if(choice == 2) {
        cout << "\nСлучайно сгенерированный текст:";
        rands(plaintext);
        cout << endl;
    }
    else if (choice == 3) {
        for (int i = 0;i < 32;i++) {
            int a;
            cout << "Введите 0 или 1 для элемента " << i + 1 << ": ";
            cin >> a;
            if (a==1 or a==0) {
                plaintext[i]=a;
            }
            else {
                cout << "Ошибка, попробуйте снова!\n";
                i--;
            }            
        }
        cout << "\nВы ввели следующий текст:";
        cout << endl;
    }
    else {
        choice = 0;
    }
    if (choice != 0) {
        cout << "\nВаш выбор: " << choice << "\n" << endl;
        cout << "Блок открытого текста:\n";
        int size = 32;
        printint(plaintext, size);
        cout << endl;
        int expansion[48];
        expansionE(expansion, plaintext);
        cout << endl;
        grouping(expansion);
        cout << "Результат работы с S-блоками: \n";
        printint(expansion, size);
        cout << "\nРезультат перестановки: \n";
        permutation(expansion, plaintext);
        cout << endl;
    }
    else {
        cout << "\nОшибка: некорректный выбор. Пожалуйста, запустите программу снова и выберите правильный вариант.\n";
    }
    
    return 0;
}


