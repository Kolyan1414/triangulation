#include "point.cpp"
#include <vector>

int add_from_console(std::vector<Point> &console_point_vector, std::vector<Point*> &point_pointer_vector)
{	
	//set return value the number of concole point
	int number = 0;
	std::cout << "Enter the points in the format: x y z" << std::endl;
	std::cout << "\tx - first coordinate" << std::endl;
	std::cout << "\ty - second coordinate" << std::endl;
	std::cout << "\tz - value" << std::endl;
	std::cout << "press 'q' to complete input" << std::endl;


	Point tmp_point;
	//Input proсess
	while(std::cin.peek() != (int)'q')
	{	
		//if console_point_vector memory is not enough, then increase it
		if(number == console_point_vector.capacity())
			console_point_vector.reserve(number+10);

		std::cin >> tmp_point;
		//incorrect input
		while(std::cin.fail() && (std::cin.peek() != (int)'q'))
		{	
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cout << "ERROR: Incorrect data\nTry again" << std::endl;
			//if user  decided to complete the input
			if(std::cin.peek() == (int)'q')
				break;
			std::cin >> tmp_point; 
		}
		if(std::cin.peek() == (int)'q')
				break;
		console_point_vector[number] = tmp_point;
		number++;
		std::cin.ignore(256, '\n');   // ignore until \n
	}
	//Add values ​​to the general point_pointer_vector
	for (int i = 0; i < number; ++i)
	{
		point_pointer_vector.push_back(&console_point_vector[i]);
	}
	return number;
}