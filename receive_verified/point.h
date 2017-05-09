#ifndef POINT_H_	
#define POINT_H_
#include <iostream>
#include <fstream>


class Point
{
	double x;
	double y;
	double z;
public:
	//Inpurt and output operators
	friend std::ostream & operator<<(std::ostream & os, const Point & arg);	
	friend std::istream & operator>>(std::istream & is, Point & arg);
	friend std::ifstream & operator>>(std::ifstream & if_s, Point & arg);

	void show();
	//Constructors
	Point(double tmp_x = 0, double tmp_y = 0, double tmp_z = 0); 
	Point(const Point & prot);
	
	//Initialization
	void set(); //Set from concole
	void set(double tmp_x, double tmp_y, double tmp_z);
	
	//Function for file inpun and file output
	void get_f(std::ifstream & ifs);
	void put_f(std::ofstream & ofs);

};

#endif
