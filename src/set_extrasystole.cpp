/*
 *this function to check new peak is it extrsystole and 
 * push into array of them for further analysis
 */
#include "stdafx.h"
#include "one lead.h"

bool one_lead::set_extrasystole(const int& probably_extrasystole,const int& peak_for_analysis)

{
	bool result = false;
    //for analisys new peak  - if it isn'tsimiliar R
    int dist  = set_indices(probably_extrasystole,count_iter,mem,mem_sdvig);
    double diff = 1;

	if (dist - (int)(2 * Fs*QRS.low) > 0)
	{
		diff = (filter_signal.at(dist) - * min_element(filter_signal.begin() + dist - static_cast<int>(Fs*QRS.low),
			filter_signal.begin() + dist));
		amplitude_new_peak = filter_signal.at(dist);
	}


	if (main_peak_in_interval == 'S')
		diff =  abs(diff);
	
	
if ( (!array_of_extrasys.empty() && probably_extrasystole != *(array_of_extrasys.end()-1) ) || array_of_extrasys.empty() )
//the threholds are lower because of filter signal
 if (diff > QRS_hight_min &&
         abs( probably_extrasystole - peak_for_analysis ) > 2*RR.middle*Fs/3 )
 {
	 
     if ( array_of_extrasys.empty() )
	 {
         int dist = probably_extrasystole - peak_for_analysis;
         int i2 = probably_extrasystole;
         i2 =set_indices(i2,count_iter,mem,mem_sdvig);
         auto min =  min_element(filter_signal.begin() + i2 - dist,filter_signal.begin() + i2);

         if ( (*min/amplitude_new_peak) < 0.3 )
		 {
			result = true;
            push_el(array_of_extrasys,(probably_extrasystole),n_peaks);
            amplitude_extrasys = amplitude_new_peak;
         }
     }else
	 {
         //we can catch not a new peak,only beside point;
         if (probably_extrasystole -*(array_of_extrasys.end()-1)<Fs*QRS.height &&
                 amplitude_extrasys < amplitude_new_peak){
          *(array_of_extrasys.end()-1) = probably_extrasystole;
         }else {
             int ind_vn = 0;
             int i1 = *(array_of_extrasys.end() - 1);
             int i2 = probably_extrasystole;
             set_indices(ind_vn, i1, i2, count_iter, mem, mem_sdvig);

             if (i1 > 0 && i2 < filter_signal.size() && i1 < i2 )  {

                 auto it = min_element(filter_signal.begin() + i1, filter_signal.begin() + i2);
                 if ((*it - isolinia) < 0.5 * amplitude_new_peak) {
                     if (array_of_extrasys.size() > 1) {
                         result = true;
                         push_el(array_of_extrasys, probably_extrasystole, n_peaks);
                         amplitude_extrasys = probably_extrasystole;
                     } else {
                         //if ampitudes aren't familiar,it's usually wave before/after extrasystole
                         if (2 * amplitude_extrasys < amplitude_new_peak) {
                             array_of_extrasys.erase(array_of_extrasys.end() - 1);
                             result = true;
                             push_el(array_of_extrasys, probably_extrasystole, n_peaks);
                             amplitude_extrasys = amplitude_new_peak;
                         } else {
                             if (!(amplitude_extrasys > 2 * amplitude_new_peak) ||
                                 amplitude_new_peak > ampl_T_standart) {
                                 result = true;
                                 push_el(array_of_extrasys, probably_extrasystole, n_peaks);
                                 amplitude_extrasys = amplitude_new_peak;
                             }
                         }
                     }
                 }
             }
         }
     }
 }
 else {
	 if (probably_extrasystole - peak_for_analysis < QRS.height * Fs/2 &&
		 amplitude_new_peak > amplitude_old_peak) 
	 {
		 *(array_of_peak_R.end() - 1) = probably_extrasystole;
		 R.amplitude = amplitude_new_peak;
	 }

 }
 return result;
}