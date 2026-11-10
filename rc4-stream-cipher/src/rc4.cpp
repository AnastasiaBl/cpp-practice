// Rc4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include<string>
#include"FileName.cpp"
#include <iostream>
using namespace std;
const int N = 256;
int S[N];


void x(const string& t, const string& k, string& new_t) {
	new_t.clear();
	for (size_t i = 0; i < t.length(); i++) {
		new_t += t[i] ^ k[i % k.length()];
	}
}
void KSA(const string& key_bytes) {
	for (int i = 0; i < N; i++) S[i] = i;
	int j = 0;
	for (int i = 0; i < N; i++) {
		j = (j + S[i] + static_cast<unsigned char>(key_bytes[i % key_bytes.size()])) % N;
		swap(S[i], S[j]);
	}
}
int PRGA(int&i,int&j ) {
		i = (i + 1) % N;
		j = (j + S[i]) % N;
		swap(S[i], S[j]);
		return S[(S[i] + S[j]) % N];
}
string enc_RC4(const string& text, const string& key){
	string t;
	KSA(key);
	int j = 0, i = 0;	
	for (size_t k = 0; k < text.length(); k++) {
		int ks_bit = PRGA(i, j);
		int bit = (ks_bit >> (7 - (k % 8))) & 1;
		int text_bit = text[k] - '0';
		t += (text_bit ^ bit) + '0';
	}
	return t;
}

int choice_1(int choice, BinaryConverter& conv) {
	string open_text, open_key, bin_text, bin_key, enc_text, enc_t_text;
	switch (choice) {
	case 1: {
		cout << "\nВедите текст для шифрования: "<<endl;
		input_string(open_text);
		cout << "\nВведите ключ для шифрования: " << endl;
		input_string(open_key);
		bin_text = conv.textToBits(open_text);
		bin_key = conv.textToBits(open_key);
		cout << "\nБинарный вид текста: " << bin_text;
		cout << "\nБинарный вид ключа: " << bin_key;
		enc_text = enc_RC4(bin_text, bin_key);
		cout << "\nЗашифрованный текст: " << enc_text << endl;
		cout << "\nЗашифрованный текст: " << conv.b_hex(enc_text) << endl;
		break;
	}
	case 2: {
		cout << "\nВедите текст для расшифровки: "<<endl;
		input_string(open_text);
		cout << "\nВведите ключ для расшифровки: " << endl;
		input_string(open_key);
		bin_text = conv.hex_b(open_text);
		bin_key = conv.textToBits(open_key);
		cout << "\nБинарный вид текста: " << bin_text;
		cout << "\nБинарный вид ключа: " << bin_key;
		enc_text = enc_RC4(bin_text, bin_key);
		cout << "\n(Бинар расшифрованного текста): " << enc_text << endl;
		enc_t_text = conv.bitsToText(enc_text);
		cout << "\nРасшифрованный текст: " << enc_t_text;
		break;

	}
	default:
		cout << "\nОшибка! Введите число от 1 до 2.\n";
		break;
	}
	return 1;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    BinaryConverter conv;
    int choice;
	
    while (true) {
		cout << "\nВыберите действие:" << endl
			<< "\n1)Зашифровать текст" << endl
			<< "\n2)Расшифровать текст\nВведите значение: " << endl;
			
		check_int(choice);
		if (choice >= 1 and choice <= 2) {
			choice_1(choice, conv);
		}
		else {
			cout << "\nОшибка! Введите число от 1 до 2.\n";
			continue;
		}
		cout << "\nВы хотите продолжить работу? \n1 - Да \n2 - Нет\nУкажите свой выбор: ";
		int y;
		check_int(y);
		if (y == 2) {
			cout << "\nПрограмма завершена.\n";
			break;
		}
		else if (y != 1) {
			cout << "\nОшибка! Введите 1-Да 2-Нет\n";
		}

    }
}
