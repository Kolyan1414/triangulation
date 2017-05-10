#include "receive_verified.cpp"
//#define THREAD_NUM 4


int main(int argc, char const *argv[])
{
	std::string file_name = "data.txt";
	std::vector<Point> point_vector;
	std::vector<Point*> point_pointer_vertor;
	receive_verified(file_name, point_vector, point_pointer_vertor);

	/*for (int i = 0; i < 1000000; ++i)
	{	
		std::cout << i << ".	";
		point_pointer_vertor[i]->show();	
	}*/

	return 0;
}
