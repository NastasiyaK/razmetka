


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


//here last three peaks are used. Second peak is checking  - maybe it's extrasystole
void one_lead::testing_of_SS()
{

	if (main_peak_in_interval == 'S')
	{
		if (array_of_peak_R.size() > 1)
		{
			if (abs(*(array_of_peak_R.end() - 2) - *(array_of_peak_R.end() - 1)) < Fs * (length.T_middle + length.ST_seg) )
			{
				int _first = set_indices(*(array_of_peak_R.end() - 2), count_iter, mem, mem_sdvig);

				if (abs(filter_signal.at(_first)) < QRS_hight_min * 1.5)
					array_of_peak_R.erase(array_of_peak_R.end()-2);
				else
					array_of_peak_R.erase(array_of_peak_R.end()-1);

			}

		}

		if (array_of_peak_R.size() > 2)
		{
			//if peaks aren't in order
			if (*(array_of_peak_R.end() - 2) < *(array_of_peak_R.end() - 3))
				 swap(*(array_of_peak_R.end() - 2), *(array_of_peak_R.end() - 3));

			//going to original signal and checking those peaks
			//int peak2 = set_indices(*(array_of_peak_R.end() - 2), count_iter, mem, mem_sdvig);
			/*auto i =  min_element(signal.begin() + peak2 - (int)(Fs*QRS.height), signal.begin() + peak2);
			int ind_min_tem = static_cast<int>( distance(signal.begin() + peak2, i));
			if (signal.at(peak2 + ind_min_tem) < signal.at(peak2)) {
				*(array_of_peak_R.end() - 2) = ind_min_tem + peak2;
			}
*/
			//for camfortable using
			int peak1 = *(array_of_peak_R.end() - 1);
			int peak2 = *(array_of_peak_R.end() - 2);
			int peak3 = *(array_of_peak_R.end() - 3);


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
				while (peak2 != 0 && peak3 != 0 &&  abs(peak2 - peak3) < average_R && (peak1 - peak2) > average_R
					&& static_cast<double>(peak2 - peak3) / (peak1 - peak2) < 0.75 && peak1 - peak3 < (2 + count_cur / 2.0)*0.9*average_R) {
					count_cur++;
					if (type_of_P(peak2 - static_cast<int>(Fs*QRS.height)) == -1) {
						ADD_EXRASYS(A_b);
					}
					else {
						ADD_EXRASYS(SV_b);
					}
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
			//vectricular extrasystole
			if (!R_v.empty() && static_cast<double>((peak1 - peak2) / (peak2 - peak3)) < 1.2 &&
				static_cast<double>((peak1 - peak2) / (peak2 - peak3)) < 1 / 1.2  && ind_of_last_extrasystole < peak2)
			{
				int dist = set_indices(peak2, count_iter, mem, mem_sdvig);
				if (dist - static_cast<int>(Fs*QRS.height) < signal.size() && dist - static_cast<int>(Fs*QRS.height) < signal.size())
				{
					double diff =  abs(signal.at(dist) - * min_element(signal.begin() + dist - static_cast<int>(Fs*QRS.height / 2), signal.begin() + dist)); 
					double diff2 =  abs(signal.at(dist) - * min_element(signal.begin() + dist, signal.begin() + dist + static_cast<int>(Fs*QRS.height) / 2)); 

						if ((diff < QRS_hight_min) || (diff2 < QRS_hight_min) && diff2 != 0)
						{
							ADD_EXRASYS(V_b);
						}

				}
			}
			//Sometimes it can be other outlers,not a useful peak. this outlier can be noise or arthefact. 
			//So this amplitude isn't similiar to adjusted amplitudes;
			if (!(check_peak_amplitudes_max(peak1, peak2, peak3, 1)))
			{
				array_of_peak_R.erase(array_of_peak_R.end() - 2);
				peak2 = 0;
			}
			/*if (!(check_peak_amplitudes_min(peak1, peak2, peak3, 1)))
			{
				if (static_cast<double>((peak2 - peak3) / (peak1 - peak2) < 1.2 &&
					static_cast<double>((peak2 - peak3) / (peak1 - peak2) > 0.8) && ind_of_last_extrasystole < peak3))
				{
					ADD_EXRASYS(V_b);
				}
				else {
					ADD_EXRASYS(SV_b);
				}
			}*/

		}
	}
}

