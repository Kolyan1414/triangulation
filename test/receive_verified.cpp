#include "point.cpp"
#include "receive_verified_thread.cpp"
#include <thread>
#include <fstream>
 
//#define THREAD_NUM 4


void receive_verified(std::string &file_name,std::vector<Point> &point_vector,
					 std::vector<Point*> &point_pointer_vector)
{	
	//Get length of file:
	std::ifstream data (file_name);
    data.seekg (0, data.end);
    int length = data.tellg();
    data.close();

   	//Reserve space po puch pioin from file
   	int reserve_size = length + THREAD_NUM*10;
	point_vector.reserve(reserve_size);
	std::vector<Receive_Navigation> navigation_vector;
	navigation_vector.reserve(THREAD_NUM);

	//If file length is reasonabe to make thread
	if(length > 100000)
	{	
		//navigation_vector initialisation

		int iter_reserve = reserve_size/THREAD_NUM;
		int iter_length = length/THREAD_NUM;

		for (int i = 0; i < THREAD_NUM; ++i)
		{
			navigation_vector[i].point_vector_offset = i*iter_reserve;
			navigation_vector[i].file_offset = i*iter_length;
			navigation_vector[i].check_file_offset = 0;
		}
		//Run threads
		std::thread zero(receive_verified_thread, &file_name,  &point_vector, &navigation_vector, 0);
		std::thread first(receive_verified_thread, &file_name,  &point_vector,  &navigation_vector, 1);
		std::thread second(receive_verified_thread, &file_name, &point_vector,  &navigation_vector, 2);
		std::thread third(receive_verified_thread, &file_name,  &point_vector, &navigation_vector, 3);
		//join threads
		zero.join();
		first.join();
		second.join();
		third.join();
	}else
	//If one thread is faster
	{	
		//navigation_vector initialisation
		navigation_vector[0].point_vector_offset = 0;
		navigation_vector[0].file_offset = 0;
		navigation_vector[0].check_file_offset = 1;

		//Run threads
		std::thread zero(receive_verified_thread, &file_name,  &point_vector, &navigation_vector, 0);
		
		//join threads
		zero.join();
	}
	//Initialase point_pointer_vector <Point*>
	if(navigation_vector[0].check_file_offset)
	{	
		std::cout << "error" << std::endl;
		length = navigation_vector[0].point_vector_end;
		point_pointer_vector.reserve(length);
		for (int i = 0; i < length; ++i)
		{
			point_pointer_vector[i] = &point_vector[i];
		}
	}else
	{	
		for (int i = 0; i < THREAD_NUM; ++i)
		{
			length += navigation_vector[i].point_vector_end - navigation_vector[i].point_vector_offset;
		}
		point_pointer_vector.reserve(length);
		int j = 0;
		for (int k = 0; k < THREAD_NUM; ++k)
		{
			for (int i = navigation_vector[k].point_vector_offset; i < navigation_vector[k].point_vector_end; ++i)
			{
				point_pointer_vector[j] = &point_vector[i];
				j++;
			}
		}
	}
}