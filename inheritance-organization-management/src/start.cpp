// Создайте базовый класс `Organization` с полями для названия и адреса, а также производные классы `School`, `University`, `Company` у произвольных.
#include<iostream>
#include<string>
#include"tools.h"
#include<stdio.h>
#include<windows.h>
using namespace std;
//people
class People {
private:
	static People** people_n;
	static int size;
	string _name, _surname, _patronymic, _phone, _email;
	int _years, _id;
public:
	People() : _name(""), _surname(""), _patronymic(""), _years(0), _phone(""), _id(size), _email("") {}
	People(string name, string surname, string patronymic, int years, string phone, string email, int id) {
		_name = name;
		_surname = surname;
		_patronymic = patronymic;
		_years = years;
		_phone = phone;
		_id = id;
		_email = email;
		cout << "The entry was successfully entered! " << endl;
	}
	int get_size() { return size; }
	//Просмотр информации о человеке
	void all_info() {
		cout << "Id: " << _id << " | "
			<< "Имя: " << _name << " | "
			<< "Фамилия: " << _surname << " | "
			<< "Отчество: " << _patronymic << " | \n"
			<< "Возраст: " << _years << " | "
			<< "Телефон: " << _phone << " | "
			<< "Адрес электронной почты: " << _email << endl;
	}
	//Добавление информации о человеке
	void add_info(string name, string surname, string patronymic, int years, string phone, string email) {
		People** t = new People * [size + 1];
		for (int i = 0; i < size; i++)
			t[i] = people_n[i];
		t[size] = new People(name, surname, patronymic, years, phone, email, size);
		delete[] people_n;
		people_n = t;
		size++;
	}
	//Просмотр всех людей
	void people() {
		if (size == 0) {
			cout << "информация о людях не внесена!" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			people_n[i]->all_info();
		}
	}
	//Просмотр инф о человеке по номеру
	void people_id(int id) {
		if (id < 0 or id >= size) {
			cout << "Некорректный индекс человека!" << endl;
			return;
		}
		cout << "Человек под номером " << id + 1 << ":\n";
		people_n[id]->all_info();
	}
	//Удаление инф o человеке по номеру
	void delete_people(int id) {
		if (id < 0 or id >= size) {
			cout << "Некорректный индекс человека!" << endl;
			return;
		}
		People** t = new People * [size - 1];
		for (int i = 0, j = 0; i < size; i++) {
			if (i != id) t[j++] = people_n[i];
			else delete people_n[i];
		}
		delete[] people_n;
		people_n = t;
		size--;
		cout << "Информация о человеке удалена!\n";
	}
	//Удаление инф о всех людях
	void delete_all() {
		for (int i = 0; i < size; i++)
			delete people_n[i];
		delete[] people_n;
		people_n = nullptr;
		size = 0;
		cout << "Информация о всех людях удалена!\n";
	}
	~People() {
		if (people_n) {
			for (int i = 0; i < size; i++)
				delete people_n[i];
			delete[] people_n;
		}
	}
};
People** People::people_n = nullptr;
int People::size = 0;
//organization
class Organization {
protected:
	static Organization** org_n;
	static int size;
	string _name_org, _address, _phone_org, _email;
	int _id_org, _org_type;
public:
	Organization() : _name_org(""), _address(""), _phone_org(""), _email(""), _org_type(0), _id_org(size) {}
	Organization(const string& name, const string& address, const string& phone, const string& email, int org_type, int id_o) {
		_name_org = name;
		_address = address;
		_phone_org = phone;
		_email = email;
		_org_type = org_type;
		_id_org = id_o;
		cout << "The entry was successfully entered! " << endl;
	};
	//Добавление информации про организацию
	virtual void add_info_org(string name, string address, string phone, string email, int status) {
		Organization** t = new Organization * [size + 1];
		for (int i = 0; i < size; i++)
			t[i] = org_n[i];
		t[size] = new Organization(name, address, phone, email, status, size);
		delete[] org_n;
		org_n = t;
		size++;
	}
	//Просмотр информации про организацию
	virtual void all_info_org(int i) {
		cout << "Id: " << _id_org << " | "
			<< "Имя: " << _name_org << " | "
			<< "Адрес: " << _address << " | "
			<< "Телефон: " << _phone_org << " | "
			<< "Адрес электронной почты: " << _email << endl;
	}
	static int get_size_org() { return size; }
	//Просмотр всех организаций
	virtual void org() {
		if (size == 0) {
			cout << "информация о организациях не внесена!" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			org_n[i]->all_info_org(i);
		}
	}
	//Просмотр инф про организацию по id
	virtual void org_id(int id) {
		if (id < 0 or id >= size) {
			cout << "Некорректный индекс организации!" << endl;
			return;
		}
		cout << "Организация под номером " << id + 1 << ":\n";
		org_n[id]->all_info_org(id);
	}
	//Удаление инф про организацию по id
	virtual void delete_org(int id) {
		if (id < 0 or id >= size) {
			cout << "Некорректный индекс организации!" << endl;
			return;
		}
		Organization** t = new Organization * [size - 1];
		for (int i = 0, j = 0; i < size; i++) {
			if (i != id) { t[j++] = org_n[i]; }
			else { delete org_n[i]; }
		}
		delete[] org_n;
		org_n = t;
		size--;
		cout << "Информация о организации удалена!\n";
	}
	//Удаление инф о всех организациях
	virtual void delete_all_org() {
		for (int i = 0; i < size; i++) {
			delete org_n[i];
		}
		delete[] org_n;
		org_n = nullptr;
		size = 0;
		cout << "Информация о всех организациях удалена!\n";
	}
	//Просмотр всех компаний
	void org_com() {
		if (size == 0) {
			cout << "информация о компаниях не внесена!" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			if (org_n[i]->_org_type == 3) {
				org_n[i]->all_info_org(i);
			}
		}
	}
	//Удаление инф о всех компаниях
	void delete_all_com() {
		int ns = 0;
		Organization** t = new Organization * [size];
		for (int i = 0, j = 0; i < size; i++) {
			if (org_n[i]->_org_type == 3) {
				t[j++] = org_n[i];
			}
			else { delete org_n[i]; }
		}
		delete[] org_n;
		org_n = t;
		size = ns;
		cout << "Информация о всех компаниях удалена!\n";
	}
	//Просмотр всех университетов
	void org_uni() {
		if (size == 0) {
			cout << "информация о университетах не внесена!" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			if (org_n[i]->_org_type == 2) {
				org_n[i]->all_info_org(i);
			}
		}
	}
	//Удаление инф о всех университетах
	void delete_all_uni() {
		int ns = 0;
		Organization** t = new Organization * [size];
		for (int i = 0, j = 0; i < size; i++) {
			if (org_n[i]->_org_type == 2) {
				t[j++] = org_n[i];
			}
			else { delete org_n[i]; }
		}
		delete[] org_n;
		org_n = t;
		size = ns;
		cout << "Информация о всех университетах удалена!\n";
	}
	//Просмотр всех школ
	void org_sch() {
		if (size == 0) {
			cout << "информация о школах не внесена!" << endl;
			return;
		}
		for (int i = 0; i < size; i++) {
			if (org_n[i]->_org_type == 1) {
				org_n[i]->all_info_org(i);
			}
		}
	}
	//Удаление инф о всех школах
	void delete_all_sch() {
		int ns = 0;
		Organization** t = new Organization * [size];
		for (int i = 0, j = 0; i < size; i++) {
			if (org_n[i]->_org_type == 1) {
				t[j++] = org_n[i];
			}
			else { delete org_n[i]; }
		}
		delete[] org_n;
		org_n = t;
		size = ns;
		cout << "Информация о всех школах удалена!\n";
	}
	virtual ~Organization() {
		if (org_n) {
			for (int i = 0; i < size; i++) {
				delete org_n[i];
			}
			delete[] org_n;
		}
	}
};
Organization** Organization::org_n = nullptr;
int Organization::size = 0;
//connection
class Connection {
private:
	static Connection** con_n;
	static int size_c;
	string _role;
	int _id_org, _id, _id_c;
	People* p;
	Organization* orgs;
	int org_count;
public:
	Connection() : _role(""), _id_org(0), _id(0), _id_c(size_c) {}
	Connection(const string& role, int org_type, int id, int id_c) {
		_role = role;
		_id_org = org_type;
		_id = id;
		_id_c = id_c;
		cout << "The entry was successfully entered! " << endl;
	}
	//Добавление информации про связь
	void add_info_con(string role, int org_type, int id) {
		Connection** s = new Connection * [size_c + 1];
		for (int i = 0; i < size_c; i++)
			s[i] = con_n[i];
		s[size_c] = new Connection(role, org_type, id, size_c);
		delete[] con_n;
		con_n = s;
		size_c++;
	}
	int get_size_c() { return size_c; }
	//Просмотр информации про связь
	void all_info_c() {
		cout << "Id: " << _id_c << " | "
			<< "Должность: " << _role << " | "
			<< "Id человека: " << _id << " | "
			<< "Id организации: " << _id_org << " | "
			<< "ПОДРОБНЕЕ ПРО ЧЕЛОВЕКА: "<<endl;
		p->people_id(_id);
	}
	//Просмотр всех связей
	void connect() {
		if (size_c == 0) {
			cout << "информация о людях не внесена!" << endl;
			return;
		}
		for (int i = 0; i < size_c; i++) {
			con_n[i]->all_info_c();
		}
	}
	//Просмотр инф о связи по номеру
	void connect_id(int id) {
		if (id < 0 or id >= size_c) {
			cout << "Некорректный индекс человека!" << endl;
			return;
		}
		cout << "Человек под номером " << id + 1 << ":\n";
		con_n[id]->all_info_c();
	}
	//Удаление инф o связи по номеру
	void delete_connect(int id) {
		if (id < 0 or id >= size_c) {
			cout << "Некорректный индекс человека!" << endl;
			return;
		}
		Connection** t = new Connection * [size_c - 1];
		for (int i = 0, j = 0; i < size_c; i++) {
			if (i != id) t[j++] = con_n[i];
			else delete con_n[i];
		}
		delete[] con_n;
		con_n = t;
		size_c--;
		cout << "Информация о человеке удалена!\n";
	}
	//Удаление инф о всех связях
	void delete_all_c() {
		for (int i = 0; i < size_c; i++)
			delete con_n[i];
		delete[] con_n;
		con_n = nullptr;
		size_c = 0;
		cout << "Информация о всех людях удалена!\n";
	}
	~Connection() {
		if (con_n) {
			for (int i = 0; i < size_c; i++)
				delete con_n[i];
			delete[] con_n;
		}
	}
};
Connection** Connection::con_n = nullptr;
int Connection::size_c = 0;
//company
class Company : public Organization {
public:
	string _industry, _stats;
	int _q_staff;
	Company()
	{
		_name_org = "";
		_address = "";
		_phone_org = "";
		_email = "";
		_org_type = 3;
		_industry = "";
		_stats = "";
		_q_staff = 0;
	}
	Company(const string& name, const string& address, const string& phone, const string& email, int id_o, int org_type, int q_staff, const string& industry, const string& stat) : Organization(name, address, phone, email, 3, size)
	{
		_name_org = name;
		_address = address;
		_phone_org = phone;
		_email = email;
		_org_type = 3;
		_industry = industry;
		_stats = stat;
		_q_staff = q_staff;
		cout << "The entry was successfully entered! " << endl;
	}
	void add_info_org(string name, string address, string phone, string email, int status, int q_staff, string industry, string stat) {
		Organization** t = new Organization * [size + 1];
		for (int i = 0; i < size; i++)
			t[i] = org_n[i];
		t[size] = new Company(name, address, phone, email, size, 3, q_staff, industry, stat);
		delete[] org_n;
		org_n = t;
		size++;
	}
	//Просмотр информации про организацию
	void all_info_org(int i) override {
		cout << "--КОМПАНИЯ" << " | " << endl;
		cout << "Id: " << _id_org << " | "
			<< "Имя: " << _name_org << " | "
			<< "Адрес: " << _address << " | "
			<< "Телефон: " << _phone_org << " | "
			<< "Адрес электронной почты: " << _email << " | "
			<< "Отрасль: " << _industry << " | "
			<< "Количество сотрудников: " << _q_staff << " | "
			<< "Статус(ООО,ЗАО,ТП): " << _stats << endl;
	}
};
//university
class University : public Organization {
private:
	string _faculty;
	int _q_stud;
	float _rat;

public:
	University()
	{
		_name_org = "";
		_address = "";
		_phone_org = "";
		_email = "";
		_org_type = 2;
		_q_stud = 0;
		_faculty = "";
		_rat = 0;
	}
	University(const string& name, const string& address, const string& phone, const string& email, int id_o, int org_type, const string& faculty, int q_stud, float _rat) : Organization(name, address, phone, email, 2, size)
	{
		_name_org = name;
		_address = address;
		_phone_org = phone;
		_email = email;
		_org_type = 2;
		_q_stud = q_stud;
		_faculty = faculty;
		_rat = _rat;
		cout << "The entry was successfully entered! " << endl;
	}
	void add_info_org(string name, string address, string phone, string email, int status, int q_stud, string faculty, float rat) {
		Organization** t = new Organization * [size + 1];
		for (int i = 0; i < size; i++)
			t[i] = org_n[i];
		t[size] = new University(name, address, phone, email, size, 2, faculty, q_stud, _rat);
		delete[] org_n;
		org_n = t;
		size++;
	}
	//Просмотр информации про организацию
	void all_info_org(int i) override {
		cout << "--УНИВЕРСИТЕТ" << " | " << endl;
		cout << "Id: " << _id_org << " | "
			<< "Имя: " << _name_org << " | "
			<< "Адрес: " << _address << " | "
			<< "Телефон: " << _phone_org << " | "
			<< "Адрес электронной почты: " << _email << " | "
			<< "Количество студентов: " << _q_stud << " | "
			<< "Факультет: " << _faculty << " | "
			<< "Рейтинг: " << _rat << endl;
	}
};
//school
class School : public Organization {
private:
	int _q_peop;
	string _type_sch;

public:
	School()
	{
		_name_org = "";
		_address = "";
		_phone_org = "";
		_email = "";
		_org_type = 1;
		_q_peop = 0;
		_type_sch = "";
	}
	School(const string& name, const string& address, const string& phone, const string& email, int id_o, int org_type, int q_peop, const string& type_sch) : Organization(name, address, phone, email, 1, size)
	{
		_name_org = name;
		_address = address;
		_phone_org = phone;
		_email = email;
		_org_type = 1;
		_q_peop = q_peop;
		_type_sch = type_sch;
		cout << "The entry was successfully entered! " << endl;
	}
	//Добавление информации про школу
	void add_info_org(string name, string address, string phone, string email, int status, int q_peop, string type_sch) {
		Organization** t = new Organization * [size + 1];
		for (int i = 0; i < size; i++)
			t[i] = org_n[i];
		t[size] = new School(name, address, phone, email, size, 1, q_peop, type_sch);
		delete[] org_n;
		org_n = t;
		size++;
	}
	//Просмотр информации про организацию
	void all_info_org(int i) override {
		cout << "--ШКОЛА" << " | " << endl;
		cout << "Id: " << _id_org << " | "
			<< "Имя: " << _name_org << " | "
			<< "Адрес: " << _address << " | "
			<< "Телефон: " << _phone_org << " | "
			<< "Адрес электронной почты: " << _email << " | "
			<< "Количество учеников: " << _q_peop << " | "
			<< "Наличие школы[1-начальной, 2-средней,3-старшей]: " << _type_sch << endl;
	}
};

//start
int id;
int status_t(int& i) {
	int y;
	input_int(y);
	switch (y) {
	case 1: { i = 1; break;	}
	case 2: { i = 2; break;	}
	case 3: { i = 3; break;	}
	default:
		cout << "Ошибка! Введите число от 1 до 3.\n";
		break;
	}
	return 1;
}
string type_sc(string& y) {
	while (true) {
		input_string(y); 
		bool valid = true;
		for (char c : y) {
			if (c != '1' && c != '2' && c != '3') {
				valid = false;
				break;
			}
		}
		if (valid && y.size() < 4 && !y.empty()) {
			return y;
		}
		else {
			cout << "Ошибка! Введите строку, содержащую только числа 1, 2 или 3, длиной до 3 символов.\n";
		}
	}
}
int choice_1(int choice, People& pe, Organization& organ, Connection& con, Company& com,School& sch, University& univ) {
	string name_org, address, phone_org, email_org;
	int status, id_people;
	string name, surname, patronymic, phone, email;
	int years;
	int q_peop, q_stud;
	string faculty, type_sch;
	float rat;
	string industry, stats;
	int q_staff;
	string role;
	int id_org, id;
	switch (choice) {
	case 1: {
		cout << "Введите имя: ";
		input_string(name);
		cout << "Введите фамилию: ";
		input_string(surname);
		cout << "Введите отчество(если нет введите [-]): ";
		input_string(patronymic);
		cout << "Введите возраст: ";
		input_int(years);
		cout << "Введите номер телефона: ";
		input_string(phone);
		cout << "Введите адрес электронной почты: ";
		input_string(email);
		pe.add_info(name, surname, patronymic, years, phone, email);
		cout << "Информация добавлена!\n";
		break;
	}
	case 2: {pe.people(); break; }
	case 3: {
		cout << "Введите id человека: ";
		check_int(id);
		pe.people_id(id - 1);
		break;
	}
	case 4: {
		cout << "Введите номер человека для удаления: ";
		check_int(id);
		pe.delete_people(id - 1);
		break;
	}
	case 5: { pe.delete_all(); break; }
	case 6: {
		cout << "Введите название: ";
		input_string(name_org);
		cout << "Введите адрес: ";
		input_string(address);
		cout << "Введите номер телефона: ";
		input_string(phone_org);
		cout << "Введите адрес электронной почты: ";
		input_string(email_org);
		cout << "Выберите:\n \a1)Школа\n \a2)Университет\n \a3)Компания\n Введите ваш выбор: ";
		status_t(status);
		if (status == 1) {
			cout << "Введите количество учеников: ";
			input_int(q_peop);
			cout << "Введите наличие школы [1-начальной, 2-средней,3-старшей](Формат ввода 123):";
			type_sc(type_sch);
			sch.add_info_org(name_org, address, phone_org, email_org, status, q_peop, type_sch);
			break;
		}
		else if (status == 2) {
			cout << "Введите факультет: ";
			input_string(faculty);
			cout << "Введите количество студентов: ";
			input_int(q_stud);
			cout << "Введите рейтинг: ";
			input_float(rat);
			univ.add_info_org(name_org, address, phone_org, email_org, status, q_stud, faculty, rat);
			break;
		}
		else if (status == 3) {
			cout << "Введите отрасль: ";
			input_string(industry);
			cout << "Введите количество сотрудников: ";
			input_int(q_staff);
			cout << "Введите статус[например: ООО,ЗАО,ТП]: ";
			input_string(stats);
			com.add_info_org(name_org, address, phone_org, email_org, status, q_staff, industry, stats);
			break;
		}
		else {
			organ.add_info_org(name_org, address, phone_org, email_org, status);
			cout << "Организация добавлена!\n";
			break;
		}
	}
	case 7: { organ.org(); break; }
	case 8: { organ.org_sch(); break; }
	case 9: { organ.org_uni(); break; }
	case 10: { organ.org_com();	break; }
	case 11: {
		cout << "Введите номер организации: ";
		check_int(id);
		organ.org_id(id - 1);
		break;
	}
	case 12: {
		cout << "Введите номер организации: ";
		check_int(id);
		organ.delete_org(id - 1);
		break;
	}
	case 13: { organ.delete_all_org(); break; }
	case 14: { organ.delete_all_sch(); break; }
	case 15: { organ.delete_all_uni(); break; }
	case 16: { organ.delete_all_com(); break; }
	case 17: {
		cout << "Введите должность: ";
		input_string(role);
		cout << "Введите id человека: ";
		input_int(id);
		cout << "Введите id организации: ";
		input_int(id_org);
		con.add_info_con(role,id_org,id);
		cout << "Связь добавлена!\n";
		break;
	}
	case 18: {
		cout << "Введите номер связи: ";
		check_int(id);
		con.delete_connect(id - 1);
		break;
	}
	case 19: {
		con.connect();
		break;
	}
	case 20: {
		cout << "Введите номер связи: ";
		check_int(id);
		con.connect_id(id - 1);
		break;
	}
	case 21: {
		con.delete_all_c();
		break;
	}
	default:
		cout << "Ошибка! Введите число от 1 до 23.\n";
		break;
	}
	return 1;
}
int main() {
	setlocale(LC_ALL, "ru");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	People pe;
	Organization organ;
	Connection con;
	Company com;
	School sch;
	University univ;
	int choice;
	while (true) {
		cout << "Меню:" << endl
			<< "\a1) Добавить информацию о человеке" << endl
			<< "\a2) Показать всех людей" << endl
			<< "\a3) Показать информацию о человеке по номеру" << endl
			<< "\a4) Удалить информацию о человеке по номеру" << endl
			<< "\a5) Удалить информацию о всех людей" << endl
			<< "\a6) Добавить информацию про организацию" << endl
			<< "\a7) Показать все организации" << endl
			<< "\a8) Показать все школы" << endl
			<< "\a9) Показать все университеты" << endl
			<< "\a10) Показать все компании" << endl
			<< "\a11) Показать информацию про организацию по номеру" << endl
			<< "\a12) Удалить информацию про организацию по номеру" << endl
			<< "\a13) Удалить информацию про все организации" << endl
			<< "\a14) Удалить информацию про все школы" << endl
			<< "\a15) Удалить информацию про все университеты" << endl
			<< "\a16) Удалить информацию про все компании" << endl
			<< "\a17) Добавить человека в организацию" << endl
			<< "\a18) Удалить человека из организации" << endl
			<< "\a19) Показать все связи" << endl 
			<< "\a20) Показать информацию про связь" << endl 
			<< "\a21) Удалить информацию про все связи" << endl
			<< "\aВыберите действие : " << endl;
		check_int(choice);
		if (choice >= 1 and choice <= 21) {
			choice_1(choice, pe, organ,con,com,sch,univ);
		}
		else {
			cout << "Ошибка! Введите число от 1 до 21.\n";
			continue;
		}
		while (true) {
			cout << "Вы хотите продолжить работу? \n1 - Да \n2 - Нет\nУкажите свой выбор: ";
			int y;
			check_int(y);
			if (y == 1) {
				break;
			}
			else if (y != 2) {
				cout << "Ошибка! Введите 1 - Да, 2 - Нет: ";
			}
			else if (y == 2) {
				cout << "Программа завершена.\n";
				return 0;
			}
		}
	}
	return 0;
}
