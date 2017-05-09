#include <iostream>
#include <fstream>
using namespace std;

 int main(int argc, char const *argv[])
 {
 	ifstream data ("data.txt");
    // get length of file:

    data.seekg (0, data.end);
    int length = data.tellg();
    cout << length << "bite" << endl;
    cout << sizeof(int) << "int" << endl;
    cout << sizeof(short) << "short" << endl;
    cout << sizeof(float) << "float" << endl;
    cout << sizeof(double) << "double" << endl;
 
    data.close(); // закрываем файл
    return 0;
 }	