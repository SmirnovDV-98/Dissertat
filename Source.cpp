#include "Header.h"

void read_data_anom_search(std::string posled_adress, std::string sum_adress, std::vector<Posled>* sum_vect, std::vector<std::vector<int>>* posled_vect)
{
	//read posled
	std::string s;

	std::ifstream file(posled_adress);
	int a = 0;
	std::vector<int> v;
	std::vector<int>* vPtr = &v;
	while (std::getline(file, s))
	{

		if (s != "//")
		{
			int i = std::stoi(s, nullptr, 10);
			vPtr->push_back(i);
		}
		else if (s == "//")
		{
			a++;
			std::cout << "Read:" << a << std::endl;
			posled_vect->push_back(v);
			v.erase(v.begin(), v.begin() + v.size());
		}
	}
	file.close();
	std::cout << std::endl << std::endl << "Done reading posled" << std::endl;
	//read sum info
	std::string g;
	std::ifstream file1(sum_adress);
	int k = 0;
	int b = 0;
	Posled p;
	while (std::getline(file1, g))
	{
		if (k == 0)
		{
			std::cout << g << std::endl;
			p.size = std::stoi(g, nullptr, 10); k++; continue;
		}
		if (k == 1)
		{
			std::cout << g << std::endl;
			p.length = std::stoi(g, nullptr, 10); k++; continue;
		}
		if (k == 2)
		{
			std::cout << g << std::endl;
			p.time = std::stof(g);k ++; continue;
		}
		if (k == 3)
		{
			std::cout << g << std::endl;
			p.sourceDiff = std::stoi(g, nullptr, 10); k++; continue;
		}
		if (g=="//")
		{
			sum_vect->push_back(p);
			k = 0;
			b++;
			std::cout << "Read sum " << b << std::endl; continue;
		}
	}
	file1.close();
	std::cout << "DONE WITH READING" << std::endl;
}
void find_av_pers_disp_our_type(std::vector<Posled>& sum_vect, std::vector<std::vector<int>>& posled_vect, std::vector<std::vector<int>>& Anomal_Number, double mSizeMed, double mLengMed, double mDiffMed,double nMed)//[0]- Длины, [1] - размеры, [2]-сложности, [3] - для базовой при размере N, [4] - Разбиение наше, [5] - разбиение по книжке
{
	int s = sum_vect.size();
	std::vector<int> lengths;
	std::vector<int> sizes;
	std::vector<int> difficulties;
	std::vector<int> native;
	std::string m;
	std::ifstream fileN("C:\\D2\\rff_try_posled_native.txt");

	std::vector<anom> size_anom;
	std::vector<anom> size_norm;
	std::vector<anom> length_anom;
	std::vector<anom> length_norm;
	std::vector<anom> nat_anom;
	std::vector<anom> nat_norm;
	std::vector<anom> dif_anom;
	std::vector<anom> dif_norm;
	anom a;

	while (std::getline(fileN, m))
	{
		int g = std::stoi(m, nullptr, 10);
		native.push_back(g);
	}

	for (int i = 0; i < s; i++)
	{
		lengths.push_back(sum_vect[i].length);
		sizes.push_back(sum_vect[i].size);
		difficulties.push_back(sum_vect[i].sourceDiff);
		std::cout << "Create data base, please wait" << std::endl;
	}
	for (int i = 0; i < lengths.size(); i++)
	{
		std::cout << "Search though our gen:" << i << std::endl;
		std::vector<int> m = native;
		std::vector<int> local;
		int len = sizes[i];
		int beg = 0;

		for (int j = 0; j < i; j++)
		{
			beg = beg + sizes[j];
		}
		for (int j = 0; j < len; j++)
		{
			local.push_back(native[beg + j]);
		}
		m.erase(m.begin() + beg, m.begin() + beg + len);

		double mid = nMed;

		float sumPDall = 0;
		for (int j = 0; j < m.size(); j++)
		{
			sumPDall = sumPDall + (m[j] - mid)/mid * 100;
		}
		sumPDall = sumPDall / m.size();
		float X2 = 0;
		float PDn = 0;
		for (int j = 0; j < len; j++)
		{
			float PD;
			PD = (native[beg + j] - mid)/mid * 100;
			PDn = PDn + PD;
			X2 = X2 + (sumPDall - PD) * (sumPDall - PD) / PD;
		}
		PDn = PDn / len;
		//Условие аномальности

		if (X2 >= PDn * PDn) {
			Anomal_Number[4].push_back(i);
			a.numbae = i;
			a.value = X2 / (PDn * PDn) * 100;  nat_anom.push_back(a);
		}
		else {
			a.numbae = i;
			a.value = X2 / (PDn * PDn) * 100; nat_norm.push_back(a);
		}
	}
	for (int i = 0; i < s; i++)//Для каждой находим процентное отклонение, среднее для оставшейся последовательности и сравниваем. 
	{

		std::cout << "Search for anomalys through sum data " << i << std::endl;
		std::vector<int> l = lengths;
		l.erase(l.begin() + i);
		std::vector<int> s = sizes;
		s.erase(s.begin() + i);
		std::vector<int> d = difficulties;
		d.erase(d.begin() + i);
		double Lmid = mLengMed, Smid = mSizeMed, Dmid = mDiffMed;
		float LiPD = (lengths[i] - Lmid)/Lmid * 100;
		float SiPD = (sizes[i] - Smid)/Smid * 100;
		float DiPD = (difficulties[i] - Dmid)/Smid * 100;
		float LsPD = 0.0;
		float SsPD = 0.0;
		float DsPD = 0.0;
		for (int j = 0; j < l.size(); j++)
		{
			LsPD = LsPD + (l[j] - Lmid)/Lmid * 100;
			SsPD = SsPD + (s[j] - Smid)/Smid * 100;
			DsPD = DsPD + (d[j] - Dmid)/Dmid * 100;
		}
		LsPD = LsPD / l.size();
		SsPD = SsPD / l.size();
		DsPD = DsPD / l.size();
		//Нужно условие отбора аномалии, подумать. Для отбора по суммарным данным
		float X1 = ((LsPD - LiPD) * (LsPD - LiPD) / LiPD);
		float X3 = ((SsPD - SiPD) * (SsPD - SiPD) / SiPD);
		float X4 = ((DsPD - DiPD) * (DsPD - DiPD) / DiPD);
		if (X1 > LiPD * LiPD){
			Anomal_Number[0].push_back(i);
			a.numbae = i;
			a.value = X1 / (LiPD * LiPD) * 100;  length_anom.push_back(a);
		}
		else {
			a.numbae = i;
			a.value = X1 / (LiPD * LiPD) * 100;  length_norm.push_back(a);
		}
		if (X3 > SiPD * SiPD){
			Anomal_Number[1].push_back(i);
			a.numbae = i;
			a.value = X3 / (SiPD * SiPD) * 100; size_anom.push_back(a);
		}
		else {
			a.numbae = i;
			a.value = X3 / (SiPD * SiPD) * 100; size_norm.push_back(a);
		}
		if (X4 > DiPD * DiPD){
			Anomal_Number[2].push_back(i);
			a.numbae = i;
			a.value = X4 / (DiPD * DiPD) * 100;   dif_anom.push_back(a);
		}
		else {
			a.numbae = i;
			a.value = X4 / (DiPD * DiPD) * 100;  dif_norm.push_back(a);
		}
	}
	std::ofstream out("C:\\Users\\dimaj\\Desktop\\D2\\my_anomal_grap.txt");
	std::vector<int> max;
	max.push_back(length_anom.size()); max.push_back(length_norm.size()); max.push_back(size_anom.size()); max.push_back(size_norm.size()); max.push_back(nat_anom.size()); max.push_back(nat_norm.size()); max.push_back(dif_anom.size()); max.push_back(dif_norm.size());
	sort(max.begin(), max.end()); int mmax = max[max.size() - 1];
	for (int l = 0; l < mmax; l++)
	{
		if (l < size_anom.size()) {
			out << "Anom Size/" << size_anom[l].numbae << "/" << size_anom[l].value << "/";
		}
		else {
			out << "Anom Size/" << "/" << "/";
		}
		if (l < length_anom.size()) {
			out << "Anom length/" << length_anom[l].numbae << "/" << length_anom[l].value << "/";
		}
		else {
			out << "Anom length/" << "/" << "/";
		}
		if (l < nat_anom.size()) {
			out << "Anom nat/" << nat_anom[l].numbae << "/" << nat_anom[l].value << "/";
		}
		else {
			out << "Anom nat/" << "/" << "/";
		}
		if (l < dif_anom.size()) {
			out << "Anom dif/" << dif_anom[l].numbae << "/" << dif_anom[l].value << "/";
		}
		else {
			out << "Anom dif/" << "/" << "/";
		}

		if (l < size_norm.size()) {
			out << "Norm Size/" << size_norm[l].numbae << "/" << size_norm[l].value << "/";
		}
		else {
			out << "Anom Size/" << "/" << "/";
		}
		if (l < length_norm.size()) {
			out << "norm length/" << length_norm[l].numbae << "/" << length_norm[l].value << "/";
		}
		else {
			out << "norm length/" << "/" << "/";
		}
		if (l < nat_norm.size()) {
			out << "norm nat/" << nat_norm[l].numbae << "/" << nat_norm[l].value << "/";
		}
		else {
			out << "norm nat/" << "/" << "/";
		}
		if (l < dif_norm.size()) {
			out << "norm dif/" << dif_norm[l].numbae << "/" << dif_norm[l].value << "/";
		}
		else {
			out << "norm ndif/" << "/" << "/";
		}
		out << std::endl;
	}
	out.close();
}
void write_my(std::string orig_try_file, std::string new_sum_file, std::string anom_info_result,double mSizeMed, double mLengMed, double mDiffMed,double nMed)
{
	std::vector<std::vector<int>> posled_vect_anom;
	std::vector<std::vector<int>>* posled_vect_anom_ptr = &posled_vect_anom;
	std::vector<Posled> sum_vect_anom;
	std::vector<Posled>* sum_vect_anom_ptr = &sum_vect_anom;
	std::vector<std::vector<int>>anom_result;
	for (int i = 0; i < 10; i++)
	{
		std::vector<int>p;
		anom_result.push_back(p);
	}

	read_data_anom_search(orig_try_file, new_sum_file, sum_vect_anom_ptr, posled_vect_anom_ptr);

	find_av_pers_disp_our_type(sum_vect_anom, posled_vect_anom, anom_result, mSizeMed,mLengMed, mDiffMed,nMed);

	std::cout << " done with calculating.Write in file" << std::endl;

	std::ofstream out2(anom_info_result);

	std::vector<int>max;
	max.push_back(anom_result[0].size()); max.push_back(anom_result[1].size()); max.push_back(anom_result[2].size()); max.push_back(anom_result[3].size()); max.push_back(anom_result[4].size());
	sort(max.begin(), max.end());
	int m = max[max.size() - 1];
	for (int i = 0; i < m; i++)
	{
		std::cout << " whrite info about :" << i << " iteration" << std::endl;
		if (i < anom_result[0].size())
		{
			out2 << anom_result[0][i] << "/";
		}
		else
		{
			out2 << " " << "/";
		}
		if (i < anom_result[1].size())
		{
			out2 << anom_result[1][i] << "/";
		}
		else
		{
			out2 << " " << "/";
		}
		if (i < anom_result[2].size())
		{
			out2 << anom_result[2][i] << "/";
		}
		else
		{
			out2 << " " << "/";
		}
		if (i < anom_result[3].size())
		{
			out2 << anom_result[3][i] << "/";
		}
		else
		{
			out2 << " " << "/";
		}
		if (i < anom_result[4].size())
		{
			out2 << anom_result[4][i] << "/";
		}
		else
		{
			out2 << " " << "/";
		}
		out2 << std::endl;
	}
	out2.close();
}
void read_data_anom_search_g(std::string posled_adress, std::string sum_adress, std::vector<Posled>* sum_vect, std::vector<std::vector<int>>* posled_vect) 
	{
		//read posled
		std::string s;

		std::ifstream file(posled_adress);
		int a = 0;
		std::vector<int> v;
		std::vector<int>* vPtr = &v;
		while (std::getline(file, s))
		{

			if (s != "//")
			{
				int i = std::stoi(s, nullptr, 10);
				vPtr->push_back(i);
			}
			else if (s == "//")
			{
				a++;
				std::cout << "Read:" << a << std::endl;
				posled_vect->push_back(v);
				v.erase(v.begin(), v.begin() + v.size());
			}
		}
		file.close();
		std::cout << std::endl << std::endl << "Done reading posled" << std::endl;
		//read sum info
		std::string g;
		std::ifstream file1(sum_adress);
		int k = 0;
		int b = 0;
		Posled p;
		while (std::getline(file1, g))
		{
			if (k == 0)
			{
				p.size = std::stoi(g, nullptr, 10); k++; continue;
			}
			if (k == 1)
			{
				p.length = std::stoi(g, nullptr, 10); k++; continue;
			}
			if (k == 2)
			{
				p.time = std::stof(g); k++; continue;
			}
			if (g=="//")
			{
				sum_vect->push_back(p);
				k = 0;
				b++;
				std::cout << "Read sum " << b << std::endl; continue;
			}
		}
		file1.close();
		std::cout << "DONE WITH READING" << std::endl;
	}
void find_av_pers_disp_our_type_g(std::vector<Posled>& sum_vect, std::vector<std::vector<int>>& posled_vect, std::vector<std::vector<int>>& Anomal_Number,double genSizeMed,double genLengMed,double nMed)
{
	int s = sum_vect.size();
	std::vector<int> lengths;
	std::vector<int> sizes;
	std::vector<int> difficulties;
	std::vector<int> native;
	std::string m;
	std::ifstream fileN("C:\\D2\\rff_try_posled_native.txt");
	std::vector<anom> size_anom;
	std::vector<anom> size_norm;
	std::vector<anom> length_anom;
	std::vector<anom> length_norm;	
	std::vector<anom> nat_anom;
	std::vector<anom> nat_norm;
	anom a;
	while (std::getline(fileN, m))
	{
		int g = std::stoi(m, nullptr, 10);
		native.push_back(g);
	}

	for (int i = 0; i < s; i++)
	{
		lengths.push_back(sum_vect[i].length);
		sizes.push_back(sum_vect[i].size);
		std::cout << "Create data base, please wait" << std::endl;
	}
	for (int i = 0; i < lengths.size(); i++)
	{
		std::cout << "Search though our gen:" << i << std::endl;
		std::vector<int> m = native;
		std::vector<int> local;
		int len = sizes[i];
		int beg = 0;

		for (int j = 0; j < i; j++)
		{
			beg = beg + sizes[j];
		}
		for (int j = 0; j < len; j++)
		{
			local.push_back(native[beg + j]);
		}
		m.erase(m.begin() + beg, m.begin() + beg + len);
		//sort(m.begin(), m.end());

		double mid = nMed;

		float sumPDall = 0;
		for (int j = 0; j < m.size(); j++)
		{
			sumPDall = sumPDall + (m[j] - mid)/mid * 100;
		}
		sumPDall = sumPDall / m.size();
		float X2 = 0;
		float PDn = 0;
		for (int j = 0; j < len; j++)
		{
			float PD;
			PD = (native[beg + j] - mid)/mid * 100;
			PDn = PDn + PD;
			X2 = X2 + (sumPDall - PD) * (sumPDall - PD) / PD;
		}
		PDn = PDn / len;
		//Условие аномальности

		if (X2 >= PDn * PDn){
			Anomal_Number[2].push_back(i);
			a.numbae = i;
			a.value = X2 / (PDn * PDn) * 100; 
			//if (a.value > 200){a.value = 200;} 
			nat_anom.push_back(a);
		}
		else{
			a.numbae = i;
			a.value = X2 / (PDn * PDn) * 100; 
			//if (a.value < -100) {	a.value = -100;}
			nat_norm.push_back(a);
		}
	}
	for (int i = 0; i < s; i++)//Для каждой находим процентное отклонение, среднее для оставшейся последовательности и сравниваем. 
	{

		std::cout << "Search for anomalys through sum data " << i << std::endl;
		std::vector<int> l = lengths;
		l.erase(l.begin() + i);
		std::vector<int> s = sizes;
		s.erase(s.begin() + i);


//		sort(l.begin(), l.end());
//		sort(s.begin(), s.end());

		double Lmid = genLengMed, Smid = genSizeMed;

		float LiPD = (lengths[i] - Lmid)/Lmid * 100;
		float SiPD = (sizes[i] - Smid)/Smid * 100;
		float LsPD = 0.0;
		float SsPD = 0.0;
		for (int j = 0; j < l.size(); j++)
		{
			LsPD = LsPD + (l[j] - Lmid)/Lmid * 100;
			SsPD = SsPD + (s[j] - Smid)/Smid  * 100;
		}
		LsPD = LsPD / l.size();
		SsPD = SsPD / l.size();
		//Нужно условие отбора аномалии, подумать. Для отбора по суммарным данным
		float X1 = ((LsPD - LiPD) * (LsPD - LiPD) / LiPD);
		float X3 = ((SsPD - SiPD) * (SsPD - SiPD) / SiPD);
		if (X1 > LiPD * LiPD){
			Anomal_Number[0].push_back(i);
			a.numbae = i;
			a.value = X1 / (LiPD * LiPD) * 100; length_anom.push_back(a);
		}
		else {
			a.numbae = i;
			a.value = X1 / (LiPD * LiPD) * 100;  length_norm.push_back(a);
		}
		if (X3 > SiPD * SiPD){
			Anomal_Number[1].push_back(i);
			a.numbae = i;
			a.value = X3 / (SiPD * SiPD) * 100;  size_anom.push_back(a);
		}
		else {
			a.numbae = i;
			a.value = X3 / (SiPD * SiPD) * 100; size_norm.push_back(a);
		}
	}
	std::ofstream out("C:\\Users\\dimaj\\Desktop\\D2\\gen_anomal_grap.txt");
	std::vector<int> max;
	max.push_back(length_anom.size()); max.push_back(length_norm.size()); max.push_back(size_anom.size()); max.push_back(size_norm.size()); max.push_back(nat_anom.size()); max.push_back(nat_norm.size());
	sort(max.begin(), max.end()); int mmax = max[max.size() - 1];
	for (int l = 0; l < mmax; l++)
	{
		if (l < size_anom.size()) {
			out << "Anom Size/" << size_anom[l].numbae << "/" << size_anom[l].value << "/";
		}
		else {
			out << "Anom Size/" << "/" << "/";
		}
		if (l < length_anom.size()) {
			out << "Anom length/" << length_anom[l].numbae << "/" << length_anom[l].value << "/";
		}
		else {
			out << "Anom length/" << "/" << "/";
		}
		if (l < nat_anom.size()) {
			out << "Anom nat/" << nat_anom[l].numbae << "/" << nat_anom[l].value << "/";
		}
		else {
			out << "Anom nat/" << "/" << "/";
		}

		if (l < size_norm.size()) {
			out << "Norm Size/" << size_norm[l].numbae << "/" << size_norm[l].value << "/";
		}
		else {
			out << "Anom Size/" << "/" << "/";
		}
		if (l < length_norm.size()) {
			out << "norm length/" << length_norm[l].numbae << "/" << length_norm[l].value << "/";
		}
		else {
			out << "norm length/" << "/" << "/";
		}
		if (l < nat_norm.size()) {
			out << "norm nat/" << nat_norm[l].numbae << "/" << nat_norm[l].value << "/";
		}
		else {
			out << "norm nat/" << "/" << "/";
		}
		out << std::endl;
	}
	out.close();
}
void write_gen(std::string new_gen_adress, std::string gen_sum, std::string anom_info_result,  double genSizeMed,  double genLengMed,double nMed)
{
	std::vector<std::vector<int>> posled_vect_anom;
	std::vector<std::vector<int>>* posled_vect_anom_ptr = &posled_vect_anom;
	std::vector<Posled> sum_vect_anom;
	std::vector<Posled>* sum_vect_anom_ptr = &sum_vect_anom;
	std::vector<std::vector<int>>anom_result;
	for (int i = 0; i < 5; i++)
	{
		std::vector<int>p;
		anom_result.push_back(p);
	}

	read_data_anom_search_g(new_gen_adress, gen_sum, sum_vect_anom_ptr, posled_vect_anom_ptr);

	find_av_pers_disp_our_type_g(sum_vect_anom, posled_vect_anom, anom_result, genSizeMed, genLengMed, nMed);

	std::cout << " done with calculating.Write in file" << std::endl;


	std::ofstream out2(anom_info_result);
	std::vector<int>max;
	max.push_back(anom_result[0].size()); max.push_back(anom_result[1].size()); max.push_back(anom_result[2].size());
	sort(max.begin(), max.end());
	int m = max[max.size() - 1];
	for (int i = 0; i < m; i++)
	{
		std::cout << " whrite info about :" << i << " iteration" << std::endl;
		if (i < anom_result[0].size())
		{
			out2 << anom_result[0][i] << "/";
		}
		else
		{
			out2 << " " << "/";
		}
		if (i < anom_result[1].size())
		{
			out2 << anom_result[1][i] << "/";
		}
		else
		{
			out2 << " " << "/";
		}
		if (i < anom_result[2].size())
		{
			out2 << anom_result[2][i] << "/";
		}
		else
		{
			out2 << " " << " ";
		}
		out2 << std::endl;
	}
	std::cout << m;
	out2.close();
}
void read_native(std::string nat_adress, std::vector<std::vector<int>>& native_split,std::vector<int>& n)
{
	std::vector<int>v;
	std::string s;
	std::ifstream file(nat_adress);
	int k = 0;
	while (std::getline(file, s))
	{
		v.push_back(stoi(s, nullptr, 10));
		n.push_back(stoi(s, nullptr, 10));
		k++;
		if (k == 40)
		{
			k = 0; native_split.push_back(v); v.clear();
		}
	}
	if (v.size() != 0)
	{
		native_split.push_back(v);
	}
}
void find_av_P_disp_native(std::vector<std::vector<int>>& native_split, std::vector<int>& Anom_data,std::vector<int>&native, double med)
{
	anom a;
	std::vector<anom> grap;
	std::vector<anom> norm;
	int s = native_split.size()-1;
	//double med;
	std::vector<int> use_n;
	std::vector<int>l;
	const int step = native_split[0].size();
	for (int i = 0; i < s; i++)
	{
		std::cout << "Check for " << i << std::endl;
		l = native_split[i];
		use_n = native;
		use_n.erase(use_n.begin() + i * step, use_n.begin() + (i+1) * step);
		//sort(use_n.begin(), use_n.end());
		//if (use_n.size() % 2 == 0){med = (use_n[use_n.size() / 2] + use_n[use_n.size() / 2 + 1]) / 2;}
		//else{med = use_n[use_n.size() / 2 + 1];}

		float sumPDall = 0;
		for (int j = 0; j < use_n.size(); j++)
		{
			sumPDall = sumPDall + (use_n[j] - med)/med * 100;
		}
		sumPDall = sumPDall / use_n.size();
		float X2 = 0;
		float PDn = 0;
		for (int j = 0; j < l.size(); j++)
		{
			float PD;
			PD = (l[j] - med)/med * 100;
			PDn = PDn + PD;
			X2 = X2 + (sumPDall - PD) * (sumPDall - PD) / PD;
		}
		PDn = PDn / l.size();
		
		//Условие аномальности

		if (X2 >= PDn * PDn)
		{
			Anom_data.push_back(i);a.numbae = i;
			a.value = X2/(PDn * PDn);
			grap.push_back(a);
		}
		else {
			a.numbae = i;
			a.value = X2 / (PDn * PDn);
			norm.push_back(a);
		}
	}
	std::ofstream out("C:\\Users\\dimaj\\Desktop\\D2\\native_anom_grap.txt"); 
	for (int m = 0; m < norm.size(); m++)
	{
		if (m < grap.size()) {
			out << "Anom/" << grap[m].numbae << "/" << grap[m].value << "/";
		}
		else {
			out << "Anom/" << "/" << "/";
		}
		out << "Norm/" << norm[m].numbae << "/" << norm[m].value << "/" << std::endl;
	}
	out.close();
}
void write_native_anom(std::string nat_adress, std::string anom_info_result,double med)
{
	std::vector<std::vector<int>>native_splitted;
	std::vector<int>native;
	std::vector<int>Anom;
	read_native(nat_adress, native_splitted, native);
	find_av_P_disp_native(native_splitted, Anom,native,med);
	int s = native_splitted[0].size();
	std::ofstream out(anom_info_result);
	for (int i = 0; i < Anom.size(); i++)
	{
		std::cout << "Write native line " << i << std::endl;
		out << i * s << "-" << (i + 1) * s - 1 << "/" << Anom[i] << "/"<<i*s<<"/"<<(i+1)*s-1<<"/"<<std::endl;
	}
}
void fill_data(std::string file_my, std::string file_gen, std::string nfile, std::vector<int>& sizeM, std::vector<int>& sizeG, std::vector<int>& lengM, std::vector<int>& lengG, std::vector<int>& diffM, std::vector<int>& native)
{
	std::string s;
	std::ifstream readM(file_my);

	std::string g;
	std::ifstream readG(file_gen);
	std::string n;
	std::ifstream nat(nfile);
	int k = 0;
	while (std::getline(readM, s)) {
		if (k == 0) { sizeM.push_back(stoi(s, nullptr, 10)); k++; continue; }
		if (k == 1) { lengM.push_back(stoi(s, nullptr, 10)); k++; continue; }
		if (k == 2) { k++; continue; }
		if (k == 3) { diffM.push_back(stoi(s, nullptr, 10)); k++; continue; }
		if (s == "//") { k = 0; }
	}
	k = 0;
	while (std::getline(readG, s)) {
		if (k == 0) { sizeG.push_back(stoi(s, nullptr, 10)); k++; continue; }
		if (k == 1) { lengG.push_back(stoi(s, nullptr, 10)); k++; continue; }
		if (k == 2) { k++; continue; }
		if (s == "//") { k = 0; }
	}
	while (std::getline(nat, n))
	{
		native.push_back(std::stoi(n, nullptr, 10));
	}
}
void find(std::vector<Data>& v, std::vector<int>& n)
{
	sort(n.begin(), n.end());
	Data D;
	D.number = 1; D.value = n[0];
	n.erase(n.begin());
	while (n.size() != 0) {
		if (n[0] == D.value) {
			D.number++;
			n.erase(n.begin());
		}
		else {
			v.push_back(D);
			D.value = n[0]; D.number = 1; n.erase(n.begin());
		}
	}

	//попытка убрать шумы
/*	int k = 0;
	for (int i = 0; i < v.size(); i++)
	{
		k = k + v[i].number;
	}
	k = k / v.size();
	std::vector<Data> l;
	for (int j = 0; j < v.size(); j++)
	{
		if ((v[j].number <= k))
		{
			l.push_back(v[j]);
		}
	}
	v = l;*/
}
void wright(std::string final, std::vector<Data>& sizeM, std::vector<Data>& sizeG, std::vector<Data>& lengM, std::vector<Data>& lengG, std::vector<Data>& diffM, std::vector <Data>& native, std::vector<int>& raspred_mySize, std::vector<int>& raspred_myLength, std::vector<int>& raspred_myDiff, std::vector<int>& raspred_genSize, std::vector<int>& raspred_genLength, std::vector<int>& raspred_native)
{
	std::ofstream out(final);
	std::vector<int> m;
	m.push_back(sizeM.size()); 
	m.push_back(sizeG.size());
	m.push_back(lengM.size());
	m.push_back(lengG.size()); 
	m.push_back(diffM.size());
	m.push_back(native.size()); 
	sort(m.begin(), m.end());
	int max = m[m.size() - 1];
	for (int i = 0; i < max; i++)
	{
		out << "My sizes" << "/";
		if (i < sizeM.size())
		{
			out << sizeM[i].value << "/" << sizeM[i].number << "/";
		}
		else {
			out << "/" << "/";
		}
		out << "My lengths" << "/";
		if (i < lengM.size())
		{
			out << lengM[i].value << "/" << lengM[i].number << "/";
		}
		else {
			out << "/" << "/";
		}
		out << "My diff" << "/";
		if (i < diffM.size())
		{
			out << diffM[i].value << "/" << diffM[i].number << "/";
		}
		else {
			out << "/" << "/";
		}
		out << "Gen sizes" << "/";
		if (i < sizeG.size())
		{
			out << sizeG[i].value << "/" << sizeG[i].number << "/";
		}
		else {
			out << "/" << "/";
		}
		out << "Gen lengths" << "/";
		if (i < lengG.size())
		{
			out << lengG[i].value << "/" << lengG[i].number << "/";
		}
		else {
			out << "/" << "/";
		}
		out << "Native" << "/";
		if (i < native.size()) {
			out << native[i].value << "/" << native[i].number << "/";
		}
		else {
			out << "/" << "/";
		}
		out << std::endl;
	}
	for (int i = 0; i < sizeM.size(); i++){
		raspred_mySize.push_back(sizeM[i].value);
	}
	for (int i = 0; i < sizeG.size(); i++) {
		raspred_genSize.push_back(sizeG[i].value);
	}
	for (int i = 0; i < lengM.size(); i++) {
		raspred_myLength.push_back(lengM[i].value);
	}
	for (int i = 0; i < lengG.size(); i++) {
		raspred_genLength.push_back(lengG[i].value);
	}
	for (int i = 0; i < diffM.size(); i++) {
		raspred_myDiff.push_back(diffM[i].value);
	}
	for (int i = 0; i < native.size(); i++) {
		raspred_native.push_back(native[i].value);
	}
}