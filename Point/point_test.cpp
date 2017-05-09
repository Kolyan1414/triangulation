#include "point.cpp"
#include <iostream>
#include <ios>

int main(int argc, char const *argv[])
{
	std::ifstream if_s ("data.txt");
	//std::ofstream of_s ("data.txt");

	//function show()
	Point point;
	point.set(1,1,1);
	point.show();
	/*
	//Operator <<
	std::cout << point;
	//Operator >>
	std::cin >> point;
	point.show();
	*/
	//Operator >> (file)
	if_s >> point;
	point.show();
	//Operator << (file)
	//of_s << point;
	if_s.close();
	return 0;
}