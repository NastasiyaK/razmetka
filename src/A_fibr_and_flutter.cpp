
#include "stdafx.h"
#include "leads.h"
#include "Afib.h"
#include "Leads_info.h"

//method for interation with testing of fibrillation 
bool Leads_Info::fibr( vector<int>&reshaped)
{
	AFibr detect_fibr;
	detect_fibr.set_RR_int(reshaped);
	detect_fibr.turningPointRatio(reshaped, win_fibr);
	float se = detect_fibr.shannonEntropy(reshaped, win_fibr);
	float rmssd = detect_fibr.rootMeanSquareSuccessiveDifferences(reshaped, win_fibr);
	bool dec = detect_fibr.decision(se, rmssd);
	return dec;
}


bool Leads_Info::flutter(const vector<int>& array_of_peak_R, const vector<double>* ptr_signal ) {
	/*if max deviation of section of P > therehold
	* it can be flutter. Firstly we build line because of
	* deviation of isolinia
	*/
	
	int ind, ind2, ind_vn;
	double max_el_temp = *(array_of_peak_R.end() - 1);
	ind = static_cast<int>(max_el_temp - (length.PQ_int + (QRS.height / 2))*Fs);
	ind2 = static_cast<int>(max_el_temp - Fs*(QRS.height / 2));
	set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);
	double y1 = ptr_signal->at(ind);
	double y2 = ptr_signal->at(ind2);
	double k = (y1 - y2) / (ind - ind2);
	double b = y1 - k*ind;
	double max_v = ptr_signal->at(ind) - (ind*k + b);
	for (int j = ind + 1; j <= ind2; j++) {
		if ( abs(ptr_signal->at(j) - (j*k + b)) > max_v)
			max_v =  abs(ptr_signal->at(j) - (j*k + b));
	}
	if (max_v < ampl_P_threshold) {

		pathology_signal.AFl++;
		return true;
	}else
		pathology_signal.AFl = 0;
	return false;
}