

#include "one lead.h"


bool one_lead::check_extras(const int& new_peak){

if (array_of_peak_R.size()>=2){
    int peak1,peak2;
    if (ind_of_last_extrasystole >= *(array_of_peak_R.end()-2))
        peak1 = ind_of_last_extrasystole;
    else
        peak1 =*(array_of_peak_R.end()-2);
    
    peak2 = *(array_of_peak_R.end()-1);
    if (new_peak==peak1)
        peak1 = peak2;
 if (  abs(new_peak-peak1) > (length.T_middle + length.ST_seg) * Fs )
    return true;
 
} 
return false;
};


/*
this two fuctions to compare last peaks; if one of them isn't similar, 
it can be mistake (function 1) or extrasystole (function 2)
*/
bool one_lead::check_peak_amplitudes_max(int& first_peak, int& second_peak, int& third_peak)
{

	int first = set_indices(first_peak, count_iter, mem, mem_sdvig);
	int second = set_indices(second_peak, count_iter, mem, mem_sdvig);
	int third = set_indices(third_peak, count_iter, mem, mem_sdvig);

	
	if (first > 0 && third < signal.size() && second_peak!=0)
	{
		
		if ( abs(0.5*filter_signal.at(first)) >  abs(filter_signal.at(second)) &&
			 abs(0.5*filter_signal.at(third)) >  abs(filter_signal.at(second)))
		{
			return false;
		}
	}
	return true;
}
//if type >1 they are peak R 
//else peak S
bool one_lead::check_peak_amplitudes_min(int&first_peak, int&second_peak, int&third_peak,int type)
{
	
	size_t first = set_indices(first_peak, count_iter, mem, mem_sdvig);
	size_t second = set_indices(second_peak, count_iter, mem, mem_sdvig);
	size_t third = set_indices(third_peak, count_iter, mem, mem_sdvig);
	if (type == 1)
	{
		if (first > 0 && third < signal.size() && second_peak != 0)
		{
			if ((filter_signal.at(first)) < 0.75*filter_signal.at(second) &&
				(filter_signal.at(third)) < 0.75*filter_signal.at(second))
			{
				return false;
			}


		}
		else {
			if ( abs(filter_signal.at(first)) <  abs(0.6*filter_signal.at(second)) &&
				 abs((filter_signal.at(third))) <  abs(0.6*filter_signal.at(second)))
		return false;
		}

	}
	return true;
}
