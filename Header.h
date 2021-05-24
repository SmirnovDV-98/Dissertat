#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

void read_list(std::string adress, std::vector <int>* list, std::string for_save_adress);
int compare_first_come_par(std::vector<int>& list, std::vector<int>& res, bool flag);
void single_eleme_comp(std::vector<int>& list, int c, bool flag1);
void show_vect(std::vector<int>& list);
void write_file(std::string adress, std::vector <int>list);
void write_fileSum(std::string adress, std::vector <int> list);
void clearFile (std::string adress);
//void asd(int i,std::vector <int>* list);
