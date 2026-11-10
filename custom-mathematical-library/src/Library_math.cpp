#include "Self_made.h"
#include "Header1.h"
#include <string>
#include <iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");
	int i, y;
	while (true) {
		cout << "Добро пожаловать!\a\a"
			<< "Что-бы вы хотели сделать?\a"
			<< "1) Возвести в степень по модулю\a"
			<< "2) Вычислить квадратный корень\a"
			<< "3) Вычислить кубический корень\a"
			<< "4) Выполнить обработку строку (строка с перечислением через ';' будет преобразована в массив)\a"
			<< "5) Выполнить сдвиг N массива на N ячеек вправо" << endl;
		check_int(i);
		if (i >= 1 and i <= 5) {
			input(i);
		}
		else {
			cout << "Ошибка! Введите число от 1 до 5.\n";
			continue;
		}
		cout << "Вы хотите продолжить работу? \n1 - Да \n2 - Нет\nУкажите свой выбор: ";
		check_int(y);

		if (y == 2) {
			cout << "Программа завершена.\n";
			break;
		}
		else if (y != 1) {
			cout << "Ошибка! Введите 1-Да 2-Нет\n";
		}
	}
	return 0;
}
