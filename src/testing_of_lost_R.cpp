

#include "one lead.h"


bool  Leads_Info::check_extras(const int& new_peak){

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
bool Leads_Info::check_peak_R(const int& new_peak){
 
/*checking of new peak. There is so number "if", becase sometime
 * signal is bad, and different mistakes occured. 

	if (amplitude_old_peak != 0 && amplitude_new_peak < 0.3*amplitude_old_peak)
		return false;
	int peak1 = *(array_of_peak_R.end() - 1), 

		peak2 = 0;

	if (array_of_peak_R.size() == 1)
		peak1 = 0;

if (array_of_peak_R.size() > 1 && ind_of_last_extrasystole < *(array_of_peak_R.end()-1) &&
	ind_of_last_extrasystole > *(array_of_peak_R.end() - 2))
    peak2 = ind_of_last_extrasystole;
else
	if (array_of_peak_R.size() > 1) {
		peak2 = *(array_of_peak_R.end() - 2);
	}

if (array_of_extrasys.size()==1 && new_peak - peak1>average_R)
	peak1 = ind_of_last_extrasystole;


int temp = static_cast<int>(0.6*average_R);
if (average_R>1.2*RR.middle*Fs)  temp = static_cast<int>(RR.middle*Fs);

if ((1.9*len_R <= RR.middle*Fs) || (array_of_peak_R.size()<=3))
	temp = static_cast<int>(0.6 *RR.middle*Fs);

if (array_of_peak_R.size()>1 && ind_of_last_extrasystole >= *(array_of_peak_R.end() - 2))
	temp = static_cast<int>(0.6 *RR.middle*Fs);

	//sometimes a lot of peaks are lost
	if (new_peak-peak2>1.5*average_R)
		return true;

	//the case, when because of extrasystole the interval is misteken
if (ind_of_last_extrasystole == peak2 && new_peak - peak1 > average_R*0.8 &&
	amplitude_new_peak > 0.8*(R.amplitude + isolinia))
	return true;
	//the case when intervals are wright;

 if (( abs((double)(new_peak-peak1)/(peak1-peak2))<1.4 &&  abs((double)(new_peak-peak1)/(peak1-peak2))>0.6)
	 && ((peak1 - peak2) >0.9*average_R || new_peak - peak2<2*average_R ))
        return true;
 if ((new_peak-peak1)> RR.middle*Fs*0.9)
 	return true;

 if (peak1 == 0 && peak2 == 0)
 	return true;
    
return false;
};*/
/*
this two fuctions to compare last peaks; if one of them isn't similar, 
it can be mistake (function 1) or extrasystole (function 2)
*/
bool Leads_Info::check_peak_amplitudes_max(int& first_peak, int& second_peak, int& third_peak)
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
bool Leads_Info::check_peak_amplitudes_min(int&first_peak, int&second_peak, int&third_peak,int type)
{
	
	int first = set_indices(first_peak, count_iter, mem, mem_sdvig);
	int second = set_indices(second_peak, count_iter, mem, mem_sdvig);
	int third = set_indices(third_peak, count_iter, mem, mem_sdvig);
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
