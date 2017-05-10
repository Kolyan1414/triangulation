#include "Graphics.h"
#include "receive_verified.cpp"
#include "add_from_console.cpp"
#include "point.cpp"

int main(int argc, char const *argv[])
{
	std::std::vector<Point> point_vector;
	std::std::vector<Point*> point_pointer_vector;
	std::std::vector<Point> point_from_console_vector;

	std::string file_name = "data.txt";
	receive_verified(file_name, point_vector, point_pointer_vector);
	add_from_console(point_from_console_vector, point_pointer_vector);

	InitializationGLUT(&argc, argv, LFK, FULL_SCREEN, &point_pointer_vector);


	return 0;
}