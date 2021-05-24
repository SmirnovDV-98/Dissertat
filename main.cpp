#include "Header.h"

int main()
{
	std::string file_adress;
	file_adress = "C:\\rff.txt";
	std::string file_posled = "C:\\posled_real.txt";
	std::string file_posled_sum = "C:\\posled_sum.txt";
	std::vector <int> list;
	std::vector<int>* list_ptr = &list;
	std::vector<std::vector<int>> posled_list;
	read_list(file_adress, list_ptr,file_posled);
	int res_single = 0;
	
	int list_size = list.size();
	//clearFile(file_posled);
	//clearFile(file_posled_sum);
	int k = 0;
	while (list_size != 0)
	{
		k++;
		std::cout << "Calculate for " << k << std::endl;
	bool flag_single = false;
	bool sequance_flag= false;
	std::vector <int> result;
	std::vector<int>* res_ptr = &result;
	compare_first_come_par(list,result,sequance_flag);
	int res_size = result.size();

	write_file(file_posled, result);
	write_fileSum(file_posled_sum, result);
	list.erase(list.begin(), list.begin() + res_size);
	if (list.size() == 0)
	{
		break;
	}
	}
	
	
	
	
	/*if (flag_single == true)
	{
		std::cout << "First found min baze param is:" << res_single << std::endl;
	}
	else
	{
		int i;
		std::cout << "What baze param you'd like to search:" << std::endl << "1) First, started from first number" << std::endl << "2)Smallest not single one"<<std::endl;
		std::cin >> i;
	}*/
	//show_vect(result);
	return 0;
}