

#include "one lead.h"

/*If the distance between adjacent R is more 
 * than average length, check presence of some missing teeth.
 */
 //if rhythm isn't normal, it can be extrasystole

#define ADD_EXRASYS(type,extr)\
if (check_extras(extr)){ \
push_el(array_of_extrasys,extr,n_peaks);\
class_of_sys = type; \
push_el(peaks_with_types,extr,type,n_peaks); \
if (type == V_b){  \
pathology_signal.ventr_comlex++;  \
}else \
pathology_signal.ventr_comlex=0; \
} \


bool one_lead::check_peak()
{

	bool R_is = 0;
	int dist = set_indices(new_peak, count_iter, mem, mem_sdvig);
	
	//start of RR sometimes isn't correct,with diff extra test of R peak
	float diff = 0;
	if (dist - (int)(3*Fs*QRS.low/2) > 0) {
		diff = filter_signal.at(dist) - *min_element(filter_signal.begin() + (dist - static_cast<int>(Fs*QRS.low / 2)),  filter_signal.begin() + dist);
	}

	if (type_of_lead == II)
		int a = 1;
    if (array_of_peak_R.size() !=0 && new_peak - *(array_of_peak_R.end()-1) > length.T_middle/2 && diff > average_amplitude.get() &&
			filter_signal.at(dist) > 0.8*QRS_filtered_min)
	{
		int start_R = start_of_R(new_peak, (Fs * QRS.height) / 2, 1, nullptr);

		//if length of R/2 >norm, it can be extrasys 
		if ((  abs(new_peak - start_R) >= static_cast<int>((Fs*QRS.height) / 2) + 2) &&
			 abs(new_peak - start_R) <= 3 * static_cast<int>((Fs*QRS.height) / 2))
		{
			ADD_EXRASYS(V_b, new_peak);
		}

		//if new_peak hasn't become extrasystole yet, it's normal R beat
		if (new_peak - *(array_of_peak_R.end() - 1) > Fs*QRS.height && diff > QRS_hight_min &&
			 abs(new_peak - start_R) <= 3 * static_cast<int>( (Fs*QRS.height) / 2) && filter_signal.at(dist) > QRS_hight_min)
		{

			if (!array_of_extrasys.empty() && new_peak - *(array_of_extrasys.end() - 1) < (Fs*QRS.height))
				array_of_extrasys.erase(array_of_extrasys.end() - 1);

                push_el(array_of_peak_R, (new_peak), n_peaks); //there's normal R beat
                push_el(peaks_with_types, new_peak, N_b, n_peaks);
                R_is = true;
                start_R = R.start;
                N_count++;
                amplitude_old_peak = amplitude_new_peak;
                QRS_hight_min = amplitude_new_peak / 2;

                if (QRS_hight_min < QRS_filtered_min)
                    QRS_hight_min = QRS_filtered_min;
                if (QRS_hight_min > 3 * QRS_filtered_min )
                    QRS_hight_min =  QRS_hight_min/2;
                R.amplitude = amplitude_new_peak - isolinia;
                R.peak = new_peak;
                average_amplitude.set(amplitude_old_peak);
                first_check_of_anormal_RR(array_of_extrasys);
			
		}
	}
	else 
	{
		if (dist - (int)(Fs*QRS.height) > 0)
		{
			diff = filter_signal.at(dist) - *min_element(filter_signal.begin() + dist - static_cast<int>(Fs*QRS.height),
				filter_signal.begin() + dist);

			if (diff > QRS_filtered_min)
			{
				if (set_extrasystole(new_peak, *(array_of_peak_R.end() - 1)))
				{
					if (!array_of_extrasys.empty() &&
						abs(*(array_of_extrasys.end() - 1) - *(array_of_peak_R.end() - 1)) > RR.middle * Fs / 2)
						R_is = true;
				}

			}
		}
	}
		return R_is;
	};