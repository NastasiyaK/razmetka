

#include <point_of_intersection.h>
#include "one lead.h"



#define ADD_EXRASYS(type);\
if (check_extras(*(array_of_peak_R.end() - 2))){ \
class_of_sys = type; \
N_count--;\
peak2 = 0; \
change_type_in_all_peak(peaks_with_types,type,*(array_of_peak_R.end() - 2), ptr_info_new_peak->fusion_window_sec *Fs /2);\
if (type == V_b)   \
pathology_signal.ventr_comlex++;  \
else \
pathology_signal.ventr_comlex=0; \
array_of_peak_R.erase(array_of_peak_R.end() - 2); \
}\


namespace razmetka {
	float slope_VE = 0.07/(1000.f/360.f);
};
//vectricular extrasystole
bool one_lead::check_ventr_extrasys(vector<float>*signal, const int& peak1, int& peak2, const int& peak3)
{
	if (peak1 != peak2 && peak2 != peak3 && peak3 != 0 && peak2 != 0)


	
		{
			int dist = set_indices(peak2, count_iter, mem, mem_sdvig);

			if (dist - static_cast<int>(Fs*QRS.height / 2) > 0 &&
				dist + static_cast<int>(Fs*QRS.height / 2) < signal->size())
			{
				vector<int>indexes;
				for (int i = 0; i < static_cast<int>(3*Fs*QRS.height / 2); i++)
					indexes.push_back(i+1);
				
				
				
					float diff = signal->at(dist) -
					             *min_element(signal->begin() + dist - static_cast<int>(3 * Fs * QRS.height / 2),
					                          signal->begin() + dist);
					float diff2 = signal->at(dist) - *min_element(signal->begin() + dist, signal->begin() + dist +
					                                                                      static_cast<int>(3 * Fs *
					                                                                                       QRS.height) /
					                                                                      2);
					//int start_int = start_peak(peak2, &filter_signal);
					//int stop_int = stop_peak(peak2, &filter_signal);
					
					//int st_tem = set_indices(start_int, count_iter, mem, mem_sdvig);
					//int st_tem2 = set_indices(stop_int, count_iter, mem, mem_sdvig);
				
				
				if ((diff < QRS_filtered_min) || (diff2 < 0.9 * QRS_filtered_min) )
				//|| ((stop_int - start_int) > static_cast<int>(Fs * QRS.height + 1)))
				{
					if ((diff < QRS_filtered_min) && (diff2 < QRS_filtered_min))
					{
						array_of_peak_R.erase(array_of_peak_R.end() - 2);
						peak2 = 0;
					}
				}
				
				if (((diff < average_amplitude.get() / 3) || (diff2 < average_amplitude.get() / 3))
				&& min(diff,diff2) < QRS_filtered_min)
				
				{
					array_of_peak_R.erase(array_of_peak_R.end() - 2);
					peak2 = 0;
					
				}
				
				pair<float,float> ab = getApprox(indexes, *signal, static_cast<size_t>(Fs*QRS.height / 4), dist);
				pair<float,float> ab_right{0,0};
				
				dist = set_indices(peak2, count_iter, mem, mem_sdvig);
				if (signal->size() >   dist +                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      static_cast<size_t>(Fs*QRS.height / 4))
					ab_right = getApprox(indexes, *signal, - static_cast<size_t>(Fs*QRS.height / 4), dist);
				
				ab_right.first = abs(ab_right.first);
				ab.first = abs(ab.first);
				
				if (type_of_lead == II && ( 1.6 * ab.first  <  ab_right.first ) && dist != 0 &&
				min(ab.first/(1000.f/Fs),ab_right.first/(1000.f/Fs)) < razmetka::slope_VE &&
						last_slope > 0.9f * ( ab.first + ab_right.first)/2 )
				{
					peak2 = 0;
					ADD_EXRASYS(V_b);
				}
				
				if ((type_of_lead == II
					&& peak2 != 0 && ab.first/(1000.f/Fs) < razmetka::slope_VE && ab_right.first/(1000.f/Fs) < razmetka::slope_VE)
				|| (last_slope > 1.15 * ab.first && last_slope > 1.15 * ab_right.first ) && peak2 != 0)
				
				{
					peak2 = 0;
					ADD_EXRASYS(V_b);
				} else
				
				{
					if (last_slope == 0 && ab.first != 0)
						last_slope = ab.first;
					else
					{
						if (ab.first != 0 && ab_right.first != 0 )
							last_slope = (last_slope + min(ab.first, abs(ab_right.first))) / 2;
					}
				}
				int dist2 = set_indices(peak3, count_iter, mem, mem_sdvig);
				float diff_third_peak  = signal->at(dist2) -
				                               *min_element(signal->begin() + dist2 - static_cast<int>(3 * Fs * QRS.height / 2),
				                                            signal->begin() + dist2);
				if (diff/diff_third_peak > 1.7  && abs( dist - dist2) < 2.5f*RR.middle * Fs && array_of_peak_R.size() > 3)
				{
					peak2 = 0;
					ADD_EXRASYS(V_b);
				}
				
					/*if (peak2 != 0 && st_tem2 < filter_signal.size() && st_tem > 0 && st_tem < filter_signal.size()
					    && abs(filter_signal.at(dist) - filter_signal.at(st_tem)) < 0.9 * QRS_filtered_min &&
					    abs(filter_signal.at(dist) - filter_signal.at(st_tem2)) < 0.9 * QRS_filtered_min)
					{
						peak2 = 0;
						ADD_EXRASYS(V_b);
						return true;
					}*/
					
					
				}
				
			
		}
	return false;
}

//here last three peaks are used. Second peak is checking  - maybe it's extrasystole
void one_lead::testing_of_RR() 
{
    if (array_of_peak_R.size() > 3)
    {
    	if ((abs(*(array_of_peak_R.end() - 2) - *(array_of_peak_R.end() - 3)) <  1.1 * Fs * (length.T_middle + length.ST_seg + QRS.height/2) &&
			             abs(*(array_of_peak_R.end() - 4) - *(array_of_peak_R.end() - 3)) < 2*average_R / 3 && (peaks_with_types.end() - 4)->second == N_b))
	    {
    		int _first = set_indices(*(array_of_peak_R.end() - 4), count_iter, mem, mem_sdvig);
		    int _second = set_indices(*(array_of_peak_R.end() - 3), count_iter, mem, mem_sdvig);
		    if (signal.at(_first)/signal.at(_second) > 1.6 ||  signal.at(_first)/signal.at(_second) < 0.6)
		    {
			    peaks_with_types.erase(peaks_with_types.end() - 3);
			    array_of_peak_R.erase(array_of_peak_R.end() - 3);
		    }
	    }
	    else
	        if (abs(*(array_of_peak_R.end() - 2) - *(array_of_peak_R.end() - 3)) <  1.1 * Fs * (length.T_middle + length.ST_seg + QRS.low/2) )
			{
				int _first = set_indices(*(array_of_peak_R.end() - 3), count_iter, mem, mem_sdvig);
	
				if (filter_signal.at(_first) < QRS_hight_min * 1.5)
					array_of_peak_R.erase(array_of_peak_R.end()-3);
				else
				{
					peaks_with_types.erase(peaks_with_types.end() - 2);
					array_of_peak_R.erase(array_of_peak_R.end() - 2);
				}
	
			}
		
    }


	if (array_of_peak_R.size() > 2)
	{
		//if peaks aren't in order
		if (*(array_of_peak_R.end() - 2) < *(array_of_peak_R.end() - 3))
			 swap(*(array_of_peak_R.end() - 2), *(array_of_peak_R.end() - 3));

		if (type_of_lead == II)
		    int a = 1;

		//for camfortable using
		int peak1 = *(array_of_peak_R.end() - 1);
		int peak2 = *(array_of_peak_R.end() - 2);
		int peak3 = *(array_of_peak_R.end() - 3);
		
		
		int temp_peak = set_indices(peak3, count_iter, mem, mem_sdvig);
		average_amplitude.set(filter_signal.at(temp_peak));
		
		if (temp_peak - (int)(Fs*QRS.low) > 0)
		{
			diff_last_peak = filter_signal.at(temp_peak) - *min_element(filter_signal.begin() + ( (int)(Fs*QRS.low / 2)),  filter_signal.begin() + temp_peak);
			if (diff_last_peak > 0.8 * QRS_height)
				diff_last_peak = QRS_height/2;
		}
		
		
		S_amplitude = *min_element(signal.begin() + temp_peak, signal.begin() + temp_peak + (int)QRS.height * Fs);
		
		
		
		temp_peak = set_indices(peak2, count_iter, mem, mem_sdvig);
			
		if (temp_peak != 0)
		{
			bool split = splitting(temp_peak, &filter_signal, Fs * QRS.height );
			
			if (!split)
				bool res = check_ventr_extrasys(&filter_signal, peak1, peak2, peak3);
		}

		
		
		//mistaken value of peaks (one peak twice)
		if ((peak1 - peak2) < 3 * Fs*QRS.height)
		{
			array_of_peak_R.erase(array_of_peak_R.end() - 2);
			if (array_of_peak_R.size() > 3)
			{
				peak2 = *(array_of_peak_R.end() - 3);
				peak3 = *(array_of_peak_R.end() - 4);
			}
		}

		int count_cur = 0;

		if (ind_of_last_extrasystole < peak3)
		{
			while (peak2 != 0 && peak3 != 0 &&  abs(peak2 - peak3) < average_R && (peak1 - peak2) > 0.95 * average_R
				&& static_cast<float>(peak2 - peak3) / (peak1 - peak2) < 0.75 && peak1 - peak3 < (2 + count_cur / 2.0)*1.1*average_R) {
				count_cur++;
                int peak_f = set_indices(peak2, count_iter, mem, mem_sdvig);
                bool ventr = check_diffic_ventr(&filter_signal, peak_f, QRS.low *Fs);

				if ( ! ventr) {
				   if ( type_of_P(peak2) > 0) { ADD_EXRASYS(A_b);

                   }else {
				       ADD_EXRASYS(SV_b);
                   }
				}
				if (ventr)
                {ADD_EXRASYS(V_b);}

				if (array_of_peak_R.size() >= 2 + count_cur)
					peak2 = *(array_of_peak_R.end() - (2 + count_cur));
				else
					peak2 = 0;
				if (array_of_peak_R.size() >= 3 + count_cur)
					peak3 = *(array_of_peak_R.end() - (3 + count_cur));
				else
					peak3 = 0;


			}
		}

	
	} 
}


bool check_diffic_ventr(vector<float >* signal, const int& peak2, float delta){

    if (peak2 > 0 && signal->size() > peak2 + delta)
    {
    	//int dist = distance(signal->begin(), min_element(signal->begin()+peak2, signal->begin()+peak2 + delta ));
    	
        float min_amplituda = *min_element(signal->begin()+peak2, signal->begin()+peak2 + delta ) ;
        if (abs(min_amplituda) > signal->at(peak2))
            return true;
    }
    return false;

}