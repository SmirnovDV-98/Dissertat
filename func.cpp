#include "Header.h"

void read_list(std::string adress, std::vector <int>*list)
{

	std::string s;
	std::ifstream file(adress);
	while (std::getline(file, s))
	{
		int i = std::stoi(s, nullptr, 10);
		//	std::cout << i;
		list->push_back(i);
	}
	file.close();
}
std::vector<int> compare_first_come_par(const std::vector<int>& list)
{
	std::vector<int> res;
	return res;

}
std::vector<int> compare_min_par(std::vector<int>*& list)
{
	std::vector<int> res;
	return res;
}
int single_eleme_comp(std::vector<int>& list)  //checked
{
	int size = list.size();
	for (int i = 0; i < size; i++)
	{
		int check = list[i];
		bool flag = true;
		for (int j = 0; j < size; j++)
		{
			if (j == i)
			{

			}
			else
			{
				if (check == list[j])
				{
					flag = false;
				}
			}
		}
		if (flag == true)
		{
			return check;
		}
	}
	return NULL;
}
