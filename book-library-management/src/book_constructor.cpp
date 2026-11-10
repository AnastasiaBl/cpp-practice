//Книга (жанр, автор, название, год издания, цена)
#include <iostream>
#include<string>
#include"FileName.h"
using namespace std;
int id;
class Book {
private:
	string _genre, _author, _title;
	int _year_of_publication, _price;
public:
	Book(string author, string title, string genre, int year_of_publication, int price) {
		_genre = genre;
		_author = author;
		_title = title;
		_year_of_publication = year_of_publication;
		_price = price;
		cout << "The entry was successfully entered! " << endl;
	}
	void set_author(const string& new_author) {
		_author = new_author; 
	}
	void set_title(const string& new_title) {
		_title = new_title; 
	}
	void set_genre(const string& new_genre) {
		_genre = new_genre; 
	}
	void set_year(int new_year) {
		_year_of_publication = new_year; 
	}
	void set_price(int new_price) {
		_price = new_price; 
	}
	//Просмотр книги
	void all_book() {
		cout << "Author: " << _author << " | " 
			<< "Title: " << _title << " | " 
			<< "Genre: " << _genre << " | " 
			<< "Year of publication: " << _year_of_publication << " | " 
			<< "Price: " << _price << endl;
	}
};
class Library {
private:
	Book** book_n;
	int size;
public:
	int get_size() { return size; }
	Library() {
		size = 0;
		book_n = nullptr;
	}
	void add_book(string author, string title, string genre, int year_of_publication, int price) {
		Book** t = new Book * [size + 1];
		for (int i = 0; i < size; i++) {
			t[i] = book_n[i];
		}
		t[size] = new Book(author, title, genre, year_of_publication, price);
		delete[] book_n;
		book_n = t;
		size++;
	}
	//Просмотр всех книг
	void book() {
		if (size == 0) {
			cout << "Библиотека пуста!" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			book_n[i]->all_book();
		}
	}
	//Просмотр книги по номеру
	void book_id(int id) {
		if (id < 0 or id >= size) {
			cout << "Некорректный индекс книги!" << endl;
			return;
		}
		cout << "Книга под номером " << id + 1 << ":\n";
		book_n[id]->all_book();
	}
	//Удаление книги
	void delete_book(int id) {
		if (id < 0 or id >= size) {
			cout << "Некорректный индекс книги!" << endl;
			return;
		}
		Book** t = new Book * [size - 1];
		for (int i = 0, j = 0; i < size; i++) {
			if (i != id) t[j++] = book_n[i];
			else delete book_n[i];
		}
		delete[] book_n;
		book_n = t;
		size--;
		cout << "Книга удалена!\n";
	}
	//Удаление всех книг
	void delete_all() {
		for (int i = 0; i < size; i++) {
			delete book_n[i];
		}
		delete[] book_n;
		book_n = nullptr;
		size = 0;
		cout << "Все книги удалены!\n";
	}
	~Library() {
		if (book_n) {
			for (int i = 0; i < size; i++) {
				delete book_n[i];
			}
			delete[] book_n;
		}
	}
};

int choice_1(int choice, Library& lib) {
	switch (choice) {
	case 1: {
		string author, title, genre;
		int year_of_publication, price;

		cin.ignore();
		cout << "Введите автора: ";
		input_string(author);
		cout << "Введите название: ";
		input_string(title);
		cout << "Введите жанр: ";
		input_string(genre);
		cout << "Введите год издания: ";
		input_int(year_of_publication);
		cout << "Введите цену: ";
		input_int(price);

		lib.add_book(author, title, genre, year_of_publication, price);
		cout << "Книга добавлена!\n";
		break;
	}
	case 2: {
		lib.book();
		break;
	}
	case 3: {
		cout << "Введите номер книги: ";
		check_int(id);
		lib.book_id(id - 1);
		break;
	}
	case 4: {
		cout << "Введите номер книги для удаления: ";
		check_int(id);
		lib.delete_book(id - 1);
		break;
	}
	case 5: {
		lib.delete_all();
		break;
	}
	default:
		cout << "Ошибка! Введите число от 1 до 5.\n";
		break;
	}
	return 1;
}


int main() {
	setlocale(LC_ALL, "Russian");
	Library lib;
	int choice;
	while (true) {
		cout << "Меню:"<< endl
			<<"\a1) Добавить книгу"<< endl
			<<"\a2) Показать все книги"<<endl
			<<"\a3) Показать книгу по номеру"<< endl
			<<"\a4) Удалить книгу по номеру"<< endl
			<<"\a5) Удалить все книги"<< endl
			<<"\aВыберите действие : "<< endl;
		check_int(choice);
		if (choice >= 1 and choice <= 6) {
			choice_1(choice, lib);
		}
		else {
			cout << "Ошибка! Введите число от 1 до 6.\n";
			continue;
		}
		cout << "Вы хотите продолжить работу? \n1 - Да \n2 - Нет\nУкажите свой выбор: ";
		int y;
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
