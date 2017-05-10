#include "add_from_console.cpp"

int main(int argc, char const *argv[])
{
	std::vector<Point> console_point_vector;
	std::vector<Point*> point_pointer_vector;
	//point_pointer_vector.reserve(10);
	int n = add_from_console(console_point_vector, point_pointer_vector);
	std::cout << n << "points were read" << std::endl;
	for(int i = 0; i < n; i++)
		std::cout << *(point_pointer_vector[i]);
	return 0;
}