#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <algorithm>
#include <initializer_list>
#include <cmath>
const double c = 1e-5;

struct anom {
	int numbae; float value;
};
struct Posled
{
	int size;
	int length;
	float time;
	int sourceDiff;
};
struct Data { int value = 0; int number = 0; };
void wright(std::string final, std::vector<Data>& sizeM, std::vector<Data>& sizeG, std::vector<Data>& lengM, std::vector<Data>& lengG, std::vector<Data>& diffM, std::vector <Data>& native, std::vector<int>& raspred_mySize, std::vector<int>& raspred_myLength, std::vector<int>& raspred_myDiff, std::vector<int>& raspred_genSize, std::vector<int>& raspred_genLength, std::vector<int>& raspred_native);
void fill_data(std::string file_my, std::string file_gen, std::string nfile, std::vector<int>& sizeM, std::vector<int>& sizeG, std::vector<int>& lengM, std::vector<int>& lengG, std::vector<int>& diffM, std::vector<int>& native);
void find(std::vector<Data>& v, std::vector<int>& n);
void read_data_anom_search(std::string posled_adress, std::string sum_adress, std::vector<Posled>* sum_vect, std::vector<std::vector<int>>* posled_vect);
void find_av_pers_disp_our_type(std::vector<Posled>& sum_vect, std::vector<std::vector<int>>& posled_vect, std::vector<std::vector<int>>& Anomal_Number, double mSizeMed, double mLengMed, double mDiffMed, double nMed);
void write_my(std::string orig_try_file, std::string new_sum_file, std::string anom_info_result, double mSizeMed, double mLengMed, double mDiffMed,double nMed);
void read_data_anom_search_g(std::string posled_adress, std::string sum_adress, std::vector<Posled>* sum_vect, std::vector<std::vector<int>>* posled_vect);
void find_av_pers_disp_our_type_g(std::vector<Posled>& sum_vect, std::vector<std::vector<int>>& posled_vect, std::vector<std::vector<int>>& Anomal_Number, double genSizeMed, double genLengMed,double nMed);
void write_gen(std::string new_gen_adress, std::string gen_sum, std::string anom_info_result, double genSizeMed, double genLengMed, double nMed);
void read_native(std::string nat_adress,std::vector<std::vector<int>>& native_split,std::vector<int>& n);
void find_av_P_disp_native(std::vector<std::vector<int>>& native_split,std::vector<int>&Anom_data, std::vector<int>& native,double med);
void write_native_anom(std::string nat_adress, std::string anom_info_result,double med);