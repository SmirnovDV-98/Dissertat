#include "Header.h"

void read_list(std::string adress, std::vector <int>*list,std::string for_save_adress)
{

	std::string s,r;
	std::ifstream sfile(for_save_adress);
	int l = 0;
	while (std::getline(sfile, r))
	{
		if (r != "//")
		{
			l++;
		}
		else
		{

		}
	}
	sfile.close();
	std::ifstream file(adress);
	int j = 0;
	while (std::getline(file, s))
	{
		j++;
		std::cout << j<<std::endl;
		if (j<=l)
		{
			if (j == l)
			{
				//system("pause");
			}
		}
		else
		{
			//take int length from string s
			std::string length;
			//find substring with length
			int k = 0;
			int point = 76;
			if ('0' <= s[point] && s[point] <= '9')
			{
				while (s[point] != ' ')
				{
					length = length + s[point];
					point++;
				}
				int i = std::stoi(length, nullptr, 10);
				//	std::cout << i;
				list->push_back(i);
			}
			else
			{

			}
		}
	}
	file.close();
}
int compare_first_come_par(std::vector<int>& list, std::vector<int>& res, bool flag)
{
	int list_size = list.size();
	
	for (int i = 0; i < list_size; i++)
	{
		
		res.push_back(list[i]);
		int res_size = res.size();
		bool flag1 = true;
		if (res_size > int(list_size / 2))
		{
			flag = true;
			//std::cout << "Baze parameter is bigger then half of whole list, so, it can't be not unique" << std::endl;
			//return 3;
		}
		for (int j = res_size; j <= list_size - res_size; j++)
		{
			int counter=0;
			for (int k = 0; k < res_size; k++)
			{
				if (res[k] == list[j + k])
				{
					counter++;
				}
				else
				{}
			}
			if (counter == res_size)
			{
				flag1 = false;
			}
			else { }
			
		}
		if (flag1 == true)
		{
			return 2;
		}
	}
	return 1;
}
void single_eleme_comp(std::vector<int>& list, int c, bool flag1)  //checked
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
			c = check;
			flag1 = true;
		}
	}
	if (flag1 == false) { std::cout << "No single baze param" << std::endl; }
	
}
void show_vect(std::vector<int>& list)
{
	int list_size = list.size();
	std::cout << "Begin of vector" << std::endl;
	for (int i = 0; i < list_size; i++)
	{
		std::cout << list[i] << std::endl;
	}
	std::cout << "End of vector" << std::endl;
	system("pause");
}
void write_file(std::string adress, std::vector <int> list)
{
	std::ofstream out(adress, std::ios::app);
	for (int i = 0; i < list.size(); i++)
	{
		out << list[i] << std::endl;
	}
	out << "//" << std::endl;
	out.close();

}
void write_fileSum(std::string adress, std::vector <int> list)
{
	std::ofstream out(adress, std::ios::app);
	out << list.size() << std::endl;
	int sum=0;
	for (int i = 0; i < list.size(); i++)
	{
		sum = sum + list[i];
	}
	out << sum << std::endl;
	out << "//" << std::endl;
	out.close();
}
void clearFile(std::string adress)
{
	std::ofstream out(adress);
	out.close();
}