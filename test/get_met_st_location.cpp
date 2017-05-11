#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <istream>
#include <cmath>

#define PI 3.14159265

int main(int argc, char const *argv[])
{	
	std::ofstream data_out;
     // (ВВЕЛИ НЕ КОРРЕКТНОЕ ИМЯ ФАЙЛА)
    data_out.open("data.txt");
    if (!data_out.is_open())
    { // если файл не открыт
        std::cout << "Файл не может быть открыт!\n"; // сообщить об этом
        exit(-1);
    }

    std::ifstream data_in ("raw_data.txt");   
	
	double tmp_angle_t;
	double tmp_angle_f;

	while(!data_in.eof())
	{
		data_in.ignore(256,' ');
		data_in.ignore(256,' ');
		data_in.ignore(256,' ');

		data_in >> tmp_angle_t;
		data_in >> tmp_angle_f;

		//std::cout << tmp_angle_t << "\t" << tmp_angle_f << std::endl;

		data_out << 3*cos(tmp_angle_t*PI/1800)*cos(tmp_angle_f*PI/1800) << " "
                 << 3*sin(tmp_angle_f*PI/1800)*cos(tmp_angle_t*PI/1800) << " "
                 << 3*sin(tmp_angle_t*PI/1800) << std::endl;
        data_in.ignore(256, '\n');
	}
	data_in.close();
	data_out.close();
	return 0;
}