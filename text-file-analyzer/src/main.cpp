#include <iostream>
#include<fstream>
#include <string>
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream output("output.txt");
    string line;
    int count=0;
    string maxline="";
    while (getline(in, line))
    {
        count++;
        //Удалить все пустые строки(если они есть).
       if(line.length()==1){
           continue;
       }
        //Заменить все цифры(если они есть) на символ* .
        for (int i = 0; i < line.length(); i++) {
            if (line[i] >= '0' and line[i] <= '9') {
                line[i] = '*';
            }
        }
        //Найти самое длинное слово в тексте и вывести его.
        string s1="";
        for (int i = 0; i <= line.length(); i++) {
            if (i<line.length() and line[i] != ' ') {
                s1 += line[i] ;
            }
            else {
                if(s1.length()>maxline.length()){
                    maxline=s1;
                }
                s1="";
            }
        }
        output << line << endl;
    }
    //В конце файла добавить статистику в формате :
    output <<  endl;
    in.close();
    //16
    output << "Количество строк :" << count<<endl;
    //предрассудокh
    output << "Самое длинное слово :" << maxline << endl;
    output.close();
    return 0;
}
