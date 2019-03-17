
#include "stdafx.h"
#include "one lead.h"

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

/*analysis of extrasys
*if we haven't any axtrasystoles, but RR is more then normal or
*there are some outliers, probably extrasystoles are lost or
*block II
*/
void one_lead::first_check_of_anormal_RR( vector<int>& array_of_extrasys)

{
	if (array_of_extrasys.size() == 2)
	{
		int ind1 = *(array_of_extrasys.end() - 1);
		int ind2 = *(array_of_extrasys.end() - 2);
		int ind_vn = ind1;

		set_indices(ind_vn, ind1, ind2, count_iter, mem, mem_sdvig);
		double diff = 0;
		if (ind1 - (int)(3 * Fs*QRS.low / 2) > 0) {
			diff = filter_signal.at(ind1) - * min_element(filter_signal.begin() + ind1 - static_cast<int>(Fs*QRS.low),
				filter_signal.begin() + ind1);
				
		}

		double diff2 = 0;
		if (ind1 + (int)(Fs*QRS.height) <filter_signal.size())
		{
			diff2 = filter_signal.at(ind1) - * min_element(filter_signal.begin() + ind1 ,
				filter_signal.begin() + ind1 + static_cast<int>(Fs*QRS.low));
		}
		if (!(diff2 > QRS_filtered_min && diff > QRS_filtered_min))
			array_of_extrasys.erase(array_of_extrasys.begin());




		if (ind2 - (int)(3 * Fs*QRS.low / 2) > 0) {
			diff = filter_signal.at(ind2) - * min_element(filter_signal.begin() + ind1 - static_cast<int>(Fs*QRS.low),
				filter_signal.begin() + ind1);
		}

		if (ind2 + (int)(3 * Fs*QRS.low / 2) <filter_signal.size())
		{
			diff2 = filter_signal.at(ind2) - * min_element(filter_signal.begin() + ind1,
				filter_signal.begin() + ind1 + static_cast<int>(Fs*QRS.low));
		}
		if (!(diff2 > QRS_filtered_min && diff > QRS_filtered_min))
			array_of_extrasys.erase(array_of_extrasys.begin());


		if (array_of_extrasys.size() == 2)
		{
			//we can have variant, when one peak is the peak before V E
			//if distance normal and hight's different  - VE

			int ind, ind2, ind_vn;
			ind2 = array_of_extrasys.at(1) + static_cast<int>(QRS.height*Fs);
			ind = array_of_extrasys.at(0) - static_cast<int>(QRS.height*Fs);
			set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);

			if (ind > 0 && ind2 < signal.size() && array_of_extrasys.at(1) != array_of_extrasys.at(0))
			{
				 vector <double> bufer;
				copy(begin(signal) + ind, begin(signal) + ind2, back_inserter(bufer));

				auto temp =  min_element(bufer.begin() + (array_of_extrasys.at(0) - ind_vn),
					bufer.begin() + (array_of_extrasys.at(1) - ind_vn - 1));
				int temp_d =  distance(bufer.begin(), temp);
				if (temp_d > 0 && bufer.at(temp_d) - isolinia < -0.25*QRS_height)
				{
					ADD_EXRASYS(V_b, array_of_extrasys.at(1));
				}
				else
				{
					//else we have only two extrasystole
					ADD_EXRASYS(V_b, array_of_extrasys.at(0));
					ADD_EXRASYS(V_b, array_of_extrasys.at(1));
					change_type_in_all_peak(peaks_with_types, V_b, *(array_of_peak_R.end() - 2), ptr_info_new_peak->fusion_window_sec *Fs /2); \
				}

			}

			if (array_of_extrasys.at(1) == array_of_extrasys.at(0))
				ADD_EXRASYS(V_b, array_of_extrasys.at(0));
		}
	}
	if (array_of_extrasys.empty())
	{

		//here we coud lost V E
		///len>norm, one peak R can be lost

		if (array_of_peak_R.size() >= 2 && *(array_of_peak_R.end() - 1) - *(array_of_peak_R.end() - 2) > RR.middle*Fs*1.7)
		{
			len_R = *(array_of_peak_R.end() - 1) - *(array_of_peak_R.end() - 2);
			int i2 = *(array_of_peak_R.end() - 1) - static_cast<int>(QRS.height*Fs);
			int ind_vn;
			int i1 = *(array_of_peak_R.end() - 2) + static_cast<int>(QRS.height*Fs);
			set_indices(ind_vn, i1, i2, count_iter, mem, mem_sdvig);
			auto it_max_lost =  max_element(begin(signal) + i1, begin(signal) + i2);
			auto it_min_lost =  min_element(begin(signal) + i1, begin(signal) + i2);

			if ( max(*it_max_lost - original_isolinia,  abs(*it_min_lost - original_isolinia)) > QRS_hight_min)
				set_extrasystole(static_cast<int>( distance(signal.begin() + i1, (it_max_lost)) + QRS.height*Fs) + *(array_of_peak_R.end() - 2), *(array_of_peak_R.end() - 2));

		}
		if (array_of_peak_R.size() >= 2 && *(array_of_peak_R.end() - 1) - *(array_of_peak_R.end() - 2) >  max(average_R*1.4, static_cast<const double>(RR.middle*Fs)))
		{
			len_R = *(array_of_peak_R.end() - 1) - *(array_of_peak_R.end() - 2);
			int i2 = *(array_of_peak_R.end() - 1) - static_cast<int>(QRS.height*Fs);
			int ind_vn;
			int i1 = *(array_of_peak_R.end() - 2) + static_cast<int>(QRS.height*Fs);
			set_indices(ind_vn, i1, i2, count_iter, mem, mem_sdvig);
			auto it_max_lost =  max_element(begin(signal) + i1, begin(signal) + i2);
			if (*it_max_lost - original_isolinia > QRS_hight_min)
				set_extrasystole( distance(signal.begin() + i1, (it_max_lost)) + static_cast<int>(QRS.height*Fs) + *(array_of_peak_R.end() - 2), *(array_of_peak_R.end() - 2));
		}
	}
	//starting analysis of different array of extrasystole
	if ((array_of_extrasys.size() == 1) && new_peak - array_of_extrasys.at(0) < length.PQ_int*Fs &&
		new_peak != array_of_extrasys.at(0))
	{
		array_of_extrasys.clear();
	}
	if (array_of_extrasys.size() == 1 && array_of_peak_R.size() > 2)
	{
		int peak1 = *(array_of_peak_R.end() - 1);
		int peak2 = *(array_of_peak_R.end() - 2);
		int peak3 = *(array_of_peak_R.end() - 3);
		if (static_cast<float>((peak1 - peak2) / (peak2 - peak3) > 0.8) &&
			static_cast<float>((peak1 - peak2) / (peak2 - peak3) < 1.2) &&
			static_cast<float>((peak1 - peak2) < 1.2*average_R) && static_cast<float>(peak2 - peak3) < 1.2*average_R)
			array_of_extrasys.clear();
	}
	if (array_of_extrasys.size() == 1 &&  abs(array_of_extrasys.at(0) - new_peak) > Fs*RR.middle / 4)
	{

		int dist = *(array_of_peak_R.end() - 1) - array_of_extrasys.at(0);
		int dist2 = array_of_extrasys.at(0) - *(array_of_peak_R.end() - 2);
		// in this case it can be extrasystole or peak R (V E)
		// if disnance between R and extrasys is normal, ex is R or V E
		int ind_extra = set_indices(array_of_extrasys.at(0), count_iter, mem, mem_sdvig);
		if (((double)(dist) / (dist2) > 1.2 || ((double)(dist) / (dist2)) < 0.8) && ind_extra > 0)
		{
			//here V E

			double amp = filter_signal.at(ind_extra);
			int start_peak = start_of_R(array_of_extrasys.at(0), 2 * Fs * (QRS.height), 1, nullptr);
			double diff_end_of_peak = filter_signal.at(ind_extra) - filter_signal.at(ind_extra + static_cast<int>( Fs*QRS.height ));
			double temp_QRS2 = (double)(array_of_extrasys.at(0) - start_peak) / Fs;
			// here R
			if (QRS.height / 2 > temp_QRS2 && diff_end_of_peak > QRS_hight_min)
				if (type_of_P(array_of_extrasys.at(0)) == 1)
				{
					ADD_EXRASYS(A_b, array_of_extrasys.at(0));
				}
				else
				{
					ADD_EXRASYS(SV_b, array_of_extrasys.at(0));
				}
			else
				ADD_EXRASYS(V_b, array_of_extrasys.at(0));
		}
		else
			if (((double)(dist) / (dist2) < 1.2 && ((double)(dist) / (dist2)) > 0.8))
			{
				int index_of_extrasys = set_indices(array_of_extrasys.at(0), count_iter, mem, mem_sdvig);
				double dif_stop_R = signal.at(index_of_extrasys) - signal.at(index_of_extrasys + static_cast<int>(Fs*(QRS.height) / 2));
				double dif_start_R = signal.at(index_of_extrasys) - signal.at(index_of_extrasys - static_cast<int>(Fs*(QRS.height) / 2));

				// here R
				if ( min(dif_stop_R, dif_start_R) > QRS_hight_min)
				{
					int temp = *(array_of_peak_R.end() - 1);
					array_of_peak_R.at(array_of_peak_R.size() - 1) = array_of_extrasys.at(0);
					push_el(array_of_peak_R, temp, n_peaks);
					N_count++;
				}
				else
				{
					ADD_EXRASYS(V_b, array_of_extrasys.at(0))
				}
			}
	}
	if ( peaks_with_types.size() > 2 &&
	        (peaks_with_types.end()-1)->first < (peaks_with_types.end()-2)->first )
	{
        auto temp = *(peaks_with_types.end() - 1);
        *(peaks_with_types.end() - 1) = *(peaks_with_types.end() - 2);
        *(peaks_with_types.end() - 2) = temp;
    }

	array_of_extrasys.clear();
}