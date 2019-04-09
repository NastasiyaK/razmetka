
#include "one lead.h"

#include <numeric>

void push_el( vector <  pair<int,  pat_name >> &v, const  pair<int,  pat_name>& new_el, const size_t n_peaks)
{
	if (v.size() < n_peaks) {
		v.push_back(new_el);
	}
	else {
		 rotate(v.begin(), v.begin() + 1, v.end());
		v.at(n_peaks - 1) = new_el;
	}
}


void push_el( vector <  pair< int, pat_name >> &v, int sample, pat_name type, const size_t n_peaks)
{
	 pair<int, pat_name> new_el(sample,type);
	if (v.size() < n_peaks) {
		v.push_back( move(new_el));
	}
	else {
		 rotate(v.begin(), v.begin() + 1, v.end());
		v.at(n_peaks - 1) =  move(new_el);
	}
}



 vector<int> checking_of_lost_peaks(const  vector<int>& new_peaks, const int& last_point, float average_R) {
	 vector<int> checked_peaks;
	checked_peaks.reserve(new_peaks.size());
	bool result = false;

	for (auto i : new_peaks) {
		if (i - last_point<static_cast<int>(5*average_R) || last_point==0) {
			checked_peaks.push_back(i);
		}
	}
	return checked_peaks;
}
 vector<float> start_value( vector <float>&a,  vector <float>&b,  vector<float>&in_ECG,const int& n) {
	//start values for bufer for filter
	 vector<float> after_filter1;
	float zn1, zn2;
	in_ECG.emplace(in_ECG.begin(), 0);
	for (int count = 0; count <= n; count++) {
		zn1 = 0;
		zn2 = 0;
		for (int i = 0; i <= count; i++) {
			zn1 += b.at(i)*in_ECG.at(count - i + 1);
			if (count != 0 && (i != count)) {
				if (i != 0) {
					zn2 -= a.at(1 + i)*after_filter1.at(count - i);
				}
			}
		}
		after_filter1.push_back(zn1 + zn2);
	}
	in_ECG.erase(in_ECG.begin());
	return after_filter1;
}
void set_indices(int& ind_vn, int& ind, int& ind2, const int& count_iter, size_t& mem, const size_t& mem_sdvig) {
	if (count_iter>1) {
		ind -= (count_iter - 1)*mem;
		ind2 -= (count_iter - 1)*mem;
	}
	if (count_iter>0) {
		ind -= mem_sdvig;
		ind2 -= mem_sdvig;
	}
	if (count_iter == 0) {
		ind_vn = ind;

	}
	else {
		ind_vn = ind + mem_sdvig + (count_iter - 1)*mem;
	}
	if (ind2 < 0) ind2 = 0;
	if (ind < 0) ind = 0;
}

int set_indices(int ind, const int& count_iter, size_t& mem, const size_t& mem_sdvig) {
	if (count_iter>1) {
		ind -= (count_iter - 1)*mem;
	}
	if (count_iter>0) {
		ind -= mem_sdvig;
	}
	if (ind < 0) 
		ind = 0;
	return ind;
}


void change_type_in_all_peak( vector <  pair<int, pat_name >>& changing_vector, pat_name new_type, const int& sample, const float fusion_window)
{
	int i = 1;
	while (i != changing_vector.size() )
	{
		if (abs((changing_vector.end() - i)->first - sample) < fusion_window)
		{
			(changing_vector.end() - i)->second = (new_type);
		}
		i++;
	}
}