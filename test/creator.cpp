#include <fstream>
#include <iostream>
#include <time.h> 
#include <stdlib.h> 
#include <iostream>    
#include <fstream> 

using namespace std;
 
int main(int argc, char* argv[])
{
    ofstream data_out;
     // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
    data_out.open("data.txt");
    if (!data_out.is_open())
    { // если файл не открыт
        cout << "Файл не может быть открыт!\n"; // сообщить об этом
        exit(-1);
    }
    
    srand( time( 0 ) ); // автоматическая рандомизация
    for(int i = 1000000; i; i--)
    {
        data_out << static_cast<double>((-RAND_MAX/2.0 + rand())/200000000.0) << " "
                 << static_cast<double>((-RAND_MAX/2.0 + rand())/200000000.0) << " "
                 << static_cast<double>((-RAND_MAX/2.0 + rand())/2000000000.0) << endl;
    }
    data_out.close(); // закрываем файл

    ifstream data ("data.txt");
    // get length of file:

    data.seekg (0, data_out.end);
    int length = data.tellg();
    cout << length << "bite" << endl;
 
    data.close(); // закрываем файл
    return 0;
}