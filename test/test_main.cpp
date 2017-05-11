#include "Graphics.h"
#include "Graphics.cpp"
#include "receive_verified.cpp"
#include "add_from_console.cpp"

int main(int argc, char *argv[])
{
	std::vector<Point> point_vector;
	std::vector<Point*> point_pointer_vector;
	std::vector<Point> point_from_console_vector;

	std::string file_name = "data.txt";
	receive_verified(file_name, point_vector, point_pointer_vector);
	add_from_console(point_from_console_vector, point_pointer_vector);

	InitializationGLUT(&argc, argv, LFK, FULL_SCREEN, &point_pointer_vector);


	return 0;
}