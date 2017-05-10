#include "point.h"

//Inpurt and output operators
std::ostream & operator<<(std::ostream & os, const Point & arg)
{
	os << arg.x << " " << arg.y << " " << arg.z << std::endl;
	return os;
}

std::istream & operator>>(std::istream & is, Point & arg)
{
	is >> arg.x >> arg.y >> arg.z;
	return is; 
}

std::ifstream & operator>>(std::ifstream & if_s, Point & arg)
{
	if_s >> arg.x >> arg.y >> arg.z;
	return if_s; 
}

void Point::show()
{
	std::cout << "x = " << this->x << "\t";
	std::cout << "y = " << this->y << "\t";
	std::cout << "z = " << this->z << "\t" << std::endl;
}

Point::Point(double arg_x, double arg_y, double arg_z)
{
	x = arg_x;
	y = arg_y;
	z = arg_z;
}

Point::Point(const Point & prot)
{
	x = prot.x;
	y = prot.y;
	z = prot.z;
}

void Point::set(double tmp_x, double tmp_y, double tmp_z)
{	
	this->x = tmp_x;
	this->y = tmp_y;
	this->z = tmp_z;
}

void Point::set()
{	
	std::cout << "Enter the point:\n\tx = ";
	std::cin >> this->x;
	std::cout << "\ty = ";
	std::cin >> this->y;
	std::cout << "\tz = ";
	std::cin >> this->z;
}

void Point::get_f(std::ifstream & ifs)
{
	double tmp_x, tmp_y, tmp_z;
	ifs >> tmp_x >> tmp_y >> tmp_z;
	this->x = tmp_x;
	this->y = tmp_y;
	this->z = tmp_z;
}

void Point::put_f(std::ofstream & ofs)
{
	ofs << this->x << " " << this->y<< " " << this->z << "\n";
}