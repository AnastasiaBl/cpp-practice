#include <iostream>
#include <string>
using namespace std;
string сipher ( string text, int changes) {
    string result = "";
    for (int i = 0; i < text.size(); i++) {
        char a = text[i];
        if (a >= 'A' && a <= 'Z') {
            result += (a - 'A' + changes) % 26 + 'A';
        }
        else if (a >= 'a' && a <= 'z') {
            result += (a - 'a' + changes) % 26 + 'a';
        }
        else {
            result += a;
        }
    }
    return result;
}
int main() {
    string text;
    int changes;
    cout << "Enter the text: ";
    cin >> text;
    cout << "Enter the modified: ";
    cin >> changes;
    string encrypted = сipher(text, changes);
    cout << "Encrypted text: " << encrypted << endl;

    return 0;
}
