#include "point.h"
#include "point.cpp"
#include "receive_verified_thread.cpp"
#include <thread>
 
#define THREAD_NUM 4


int main(int argc, char const *argv[])
{
	std::string file_name = "data.txt";
	std::vector<Point> point_vector;
	point_vector.reserve(120);

	std::vector<Receive_Navigation> navigation_vector;
	navigation_vector.reserve(THREAD_NUM);
	for (int i = 0; i < THREAD_NUM; ++i)
	{
		navigation_vector[i].point_vector_offset = i*30;
		navigation_vector[i].file_offset = i*210;
		navigation_vector[i].check_file_offset = 0;
	}
	//navigation_vector[1].check_file_offset = 1;

	std::thread zero(receive_verified_thread, &file_name,  &point_vector, &navigation_vector, 0);
	std::thread first(receive_verified_thread, &file_name,  &point_vector,  &navigation_vector, 1);
	std::thread second(receive_verified_thread, &file_name, &point_vector,  &navigation_vector, 2);
	std::thread third(receive_verified_thread, &file_name,  &point_vector, &navigation_vector, 3);

	zero.join();
	first.join();
	second.join();
	third.join();

	for (int i = 0; i < 120; ++i)
	{	
		std::cout << i << ".	";
		point_vector[i].show();
	}
	return 0;
}
