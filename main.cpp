#include "Header.h"

int main()
{
	std::string new_sum_file = "C:\\D2\\rff_try_time_sum.txt";
	std::string orig_try_file = "C:\\D2\\rff_try_posled.txt";
	std::string anom_info_result = "C:\\D2\\anom_info_my.txt";
	std::string new_gen_adress = "C:\\D2\\rff_try_gens.txt";
	std::string gen_sum = "C:\\D2\\rff_try_new_gen_sum.txt";
	std::string anom_info_resultg = "C:\\Users\\dimaj\\Desktop\\D2\\alpha.txt";
	std::string anom_info_resultN = "C:\\Users\\dimaj\\Desktop\\D2\\native_anom.txt";
	std::string native_adress = "C:\\D2\\rff_try_posled_native.txt";
	std::string my_sum = "C:\\D2\\rff_try_time_sum.txt";
	std::string gen_sum1 = "C:\\D2\\rff_try_new_gen_sum.txt";
	std::string save_file = "C:\\Users\\dimaj\\Desktop\\D2\\raspredel.txt";
	std::string natve = "C:\\D1\\rff_try_posled_native.txt";
	//Распределение
	std::vector <Data> sizes_my; std::vector<Data> sizes_gen; std::vector <Data> length_my; std::vector <Data> length_gen; std::vector <Data> diff; std::vector <Data> native;
	std::vector <int> sizes_my_n; std::vector<int> sizes_gen_n; std::vector <int> length_my_n; std::vector <int> length_ge_n; std::vector <int> diff_n; std::vector <int> native_n;
	std::vector<int> raspred_mySize; std::vector<int> raspred_myLength; std::vector<int> raspred_myDiff; std::vector<int> raspred_genSize; std::vector<int> raspred_genLength; std::vector<int> raspred_native;
	fill_data(my_sum, gen_sum1, natve, sizes_my_n, sizes_gen_n, length_my_n, length_ge_n, diff_n, native_n);
	find(sizes_gen, sizes_gen_n); find(sizes_my, sizes_my_n); find(length_my, length_my_n); find(length_gen, length_ge_n); find(diff, diff_n); find(native, native_n);
	wright(save_file, sizes_my, sizes_gen, length_my, length_gen, diff, native, raspred_mySize, raspred_myLength, raspred_myDiff, raspred_genSize, raspred_genLength, raspred_native);

	double mSizeMediana, mLengthMediana, mDiffMediana, nMediana, gSizeMediana, gLengthMediana;
	if (raspred_mySize.size() % 2 == 0){
		mSizeMediana = (raspred_mySize[raspred_mySize.size() / 2 + 1]+ raspred_mySize[raspred_mySize.size() / 2])/2;
	}
	else{
		mSizeMediana = raspred_mySize[raspred_mySize.size() / 2 + 1];
	}
	if (raspred_genSize.size() % 2 == 0) {
		gSizeMediana = (raspred_genSize[raspred_genSize.size() / 2 + 1] + raspred_genSize[raspred_genSize.size() / 2]) / 2;
	}
	else {
		gSizeMediana = raspred_genSize[raspred_genSize.size() / 2 + 1];
	}
	if (raspred_myLength.size() % 2 == 0) {
		mLengthMediana = (raspred_myLength[raspred_myLength.size() / 2 + 1] + raspred_myLength[raspred_myLength.size() / 2]) / 2;
	}
	else {
		mLengthMediana = raspred_myLength[raspred_myLength.size() / 2 + 1];
	}
	if (raspred_genLength.size() % 2 == 0) {
		gLengthMediana = (raspred_genLength[raspred_genLength.size() / 2 + 1] + raspred_genLength[raspred_genLength.size() / 2]) / 2;
	}
	else {
		gLengthMediana = raspred_genLength[raspred_genLength.size() / 2 + 1];
	}
	if (raspred_myDiff.size() % 2 == 0) {
		mDiffMediana = (raspred_myDiff[raspred_myDiff.size() / 2 + 1] + raspred_myDiff[raspred_myDiff.size() / 2]) / 2;
	}
	else {
		mDiffMediana = raspred_myDiff[raspred_myDiff.size() / 2 + 1];
	}
	if (raspred_native.size() % 2 == 0) {
		nMediana = (raspred_native[raspred_native.size() / 2 + 1] + raspred_native[raspred_native.size() / 2]) / 2;
	}
	else {
		nMediana = raspred_native[raspred_native.size() / 2 + 1];
	}
	//Мои аномалии

	write_my(orig_try_file, new_sum_file, anom_info_result, mSizeMediana, mLengthMediana, mDiffMediana,nMediana);

	//Аномалии гена
	write_gen(new_gen_adress,gen_sum,anom_info_resultg,gSizeMediana,gLengthMediana,nMediana);

	//От чистого. Размер - 40
	write_native_anom(native_adress,anom_info_resultN,nMediana);

	return 0;
}