#include <string>
#include <vector>
#include <ios>

#define THREAD_NUM 4

struct Receive_Navigation
{
	int point_vector_offset;
	std::streampos file_offset;
	bool check_file_offset;
	int point_vector_end;
};
	
void receive_verified_thread(std::string *file_name, std::vector<Point> *point_vector,
							 std::vector<Receive_Navigation> *navigation_vector, short thread_num = 0)
{	
	//Open file for receiving Point
	std::ifstream file(*file_name, std::ifstream::in);
	if(!file.is_open())
	{
		std::cout << "Cann't open file :" << file_name << std::endl;
		exit(-1);
	}

	//Set the marcer to the last thread
	file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg (0, file.beg);

	//Set the right file offset
	//Check that position points on the begginning of new string(in the case of non 0thread)
	if(thread_num >0)
	{
		//Sets the position of the next character to be extracted from the file
		file.seekg((*navigation_vector)[thread_num].file_offset);
		
		//Sets the position of the next Point to be extracted from the file		
		while(!(file.peek() == int('\n')))
		{
			file.seekg((*navigation_vector)[thread_num].file_offset -= 1);
		}
		file.seekg((*navigation_vector)[thread_num].file_offset += 1);
		(*navigation_vector)[thread_num].check_file_offset++;
	}

	//Check that every thread set its file_offset
	//If there is only one thread(small file)
	if((*navigation_vector)[0].check_file_offset == 0){
		while(1)
		{	
			char check_set = 0;
			for (char i = 1; i < THREAD_NUM; ++i)
			{
				if((*navigation_vector)[i].check_file_offset > 0)
					check_set++;
			}
			if(check_set == THREAD_NUM -1)	
				break;
		}
	}
	//Assign Point from file segment to vector segment
	int i = (*navigation_vector)[thread_num].point_vector_offset;

	if((thread_num == THREAD_NUM - 1) || ((*navigation_vector)[0].check_file_offset == 1))
	{
		while(file.tellg() < length)
		{	
			file >> (*point_vector)[i];
			//std::cout << thread_num << ":\t" << i << ".	";
			//(*point_vector)[i].show();
			i++;
			file.ignore(1, '\n');
			if(file.eof())
				break;
		}
	}else
	{
		while(file.tellg() <  (*navigation_vector)[thread_num+1].file_offset)
		{	
			file >> (*point_vector)[i];
			//std::cout << thread_num << ":\t" << i << ".	";
			//(*point_vector)[i].show();
			i++;
			file.ignore(1, '\n');
		}
	}
	//Set the positions of the the element thet followed by last. 
	(*navigation_vector)[thread_num].point_vector_end = i;
	file.close();
}
