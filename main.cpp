#include "Header.h"

int main()
{
	std::string file_adress;
	file_adress = "C:\\Test.txt";
	std::vector <int> list;
	std::vector<int>* list_ptr = &list;
	read_list(file_adress, list_ptr);
	int res = single_eleme_comp(list);

	if (res == NULL)
	{
		std::cout << "No single results";
	}
	
	return 0;
}