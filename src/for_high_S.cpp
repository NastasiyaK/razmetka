

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



#define ADD_EXRASYS_DEL(type)\
if (check_extras(*(array_of_peak_R.end() - 2))){ \
class_of_sys = type; \
N_count--;\
change_type_in_all_peak(peaks_with_types,type,*(array_of_peak_R.end() - 2));\
if (type =="V "){  \
pathology_signal.ventr_comlex++;  \
}else \
pathology_signal.ventr_comlex=0; \
array_of_peak_R.erase(array_of_peak_R.end() - 2); \
}\


bool one_lead::first_check_peak_S()
{

	bool R_is = 0, lost_R_is = 0;
	int dist = set_indices(new_peak, count_iter, mem, mem_sdvig);

	//start of RR sometimes isn't correct,with diff extra test of R peak
	double diff = 0;
	if (dist - (int)(3 * Fs*QRS.low / 2) > 0) {
		diff =  abs(filter_signal.at(dist) - filter_signal.at(dist - (int)(3 * Fs*QRS.low / 2)));
	}

	//if (check_peak_R(new_peak) && diff > average_amplitude.get())
	if (array_of_peak_R.size() !=0 && new_peak - *(array_of_peak_R.end()-1) > length.T_middle/2 && diff > average_amplitude.get() )
	{
		int start_R = start_of_R(new_peak, (Fs * QRS.height) / 2, 1, nullptr);

		//if length of R/2 >norm, it can be extrasys 
		if (( abs(new_peak - start_R) >= static_cast<int>((Fs*QRS.height) / 2) + 2) &&
			 abs(new_peak - start_R) <= 3 * static_cast<int>((Fs*QRS.height) / 2))
		{
			ADD_EXRASYS(V_b, new_peak);
		}


		//if new_peak hasn't become extrasystole yet, it's normal R beat
		if (new_peak - *(array_of_peak_R.end() - 1) > Fs*QRS.height && diff > QRS_filtered_min &&
			 abs(new_peak - start_R) <= 3 * static_cast<int>((Fs*QRS.height) / 2))
		{

			if (!array_of_extrasys.empty() && new_peak - *(array_of_extrasys.end() - 1) < (Fs*QRS.height))
				array_of_extrasys.erase(array_of_extrasys.end() - 1);

			if (dist - (int)(Fs*QRS.low / 2) > 0) {
				//double original_hight_peak =  abs(signal.at(dist) -
				//	* min_element(signal.begin() + dist - (int)(Fs*QRS.low / 2), signal.begin() + dist));

				//Sometimes filtered signal isn't as original,so added check is useful
				//if (original_hight_peak > QRS_hight_min)
				//{
				push_el(array_of_peak_R, (new_peak), n_peaks); //there's normal R beat
				push_el(peaks_with_types, new_peak, N_b, n_peaks);
				R_is = true;
				start_R = R.start;
				N_count++;
				amplitude_old_peak = amplitude_new_peak;
				R.amplitude = amplitude_new_peak - isolinia;
				//push_el(peaks_amplitudes, amplitude_new_peak - isolinia, 3);
				R.peak = new_peak;
				QRS_hight_min = amplitude_new_peak / 2;

				if (QRS_hight_min < QRS_filtered_min)
					QRS_hight_min = QRS_filtered_min;
				if (QRS_hight_min > 3 * QRS_filtered_min)
					QRS_hight_min = QRS_hight_min / 2;

				average_amplitude.set(amplitude_old_peak);
				first_check_of_anormal_RR(array_of_extrasys);
				/***/




				/*
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
                        auto it_min_lost =  min_element(begin(signal) + i1, begin(signal) + i2);
                        if (*it_min_lost - original_isolinia > QRS_hight_min)
                            set_extrasystole( distance(signal.begin() + i1, (it_min_lost)) + static_cast<int>(QRS.height*Fs) + *(array_of_peak_R.end() - 2), *(array_of_peak_R.end() - 2));
                    }
                }

                //starting analysis of different array of extrasystole
                if ((array_of_extrasys.size() == 1) && new_peak - array_of_extrasys.at(0) < length.PQ_int*Fs)
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
                        double diff_end_of_peak = signal.at(ind_extra) - signal.at(ind_extra + static_cast<int>(Fs*QRS.height));
                        double temp_QRS2 = (double)(array_of_extrasys.at(0) - start_peak) / Fs;
                        // here R
                        if (QRS.height / 2 > temp_QRS2 && diff_end_of_peak > QRS_hight_min)
                            if (type_of_P(array_of_extrasys.at(0)) == 1)
                            {
                                ADD_EXRASYS(A_b, array_of_extrasys.at(0));
                            }
                            else {
                                ADD_EXRASYS(SV_b, array_of_extrasys.at(0));
                            }
                        else
                            array_of_extrasys.clear();
                    }
                    else
                        if (((double)(dist) / (dist2) < 1.2 && ((double)(dist) / (dist2)) > 0.8))
                        {
                            int index_of_extrasys = set_indices(array_of_extrasys.at(0), count_iter, mem, mem_sdvig);
                            double dif_stop_R =  abs(signal.at(index_of_extrasys) - signal.at(index_of_extrasys + static_cast<int>(Fs*(QRS.height) / 2)));
                            double dif_start_R =  abs(signal.at(index_of_extrasys) - signal.at(index_of_extrasys - static_cast<int>(Fs*(QRS.height) / 2)));

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
                if (array_of_extrasys.size() == 2)
                {
                    int dist = *(array_of_peak_R.end() - 1) - *(array_of_extrasys.end() - 1);
                    int dist2 = *(array_of_extrasys.end() - 1) - *(array_of_extrasys.end() - 2);


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
                            //change_type_in_all_peak(peaks_with_types, "V ", *(array_of_peak_R.end() - 2));
                        }
                        if (array_of_extrasys.at(1) == array_of_extrasys.at(0))
                            ADD_EXRASYS(V_b, array_of_extrasys.at(0));
                    }
                    push_el(peaks_with_types, new_peak, N_b, n_peaks);
                }*/
			}
		}
	}
	else
	{
		if (diff > QRS_filtered_min)
			if (set_extrasystole(new_peak, *(array_of_peak_R.end() - 1)))
			{
				if (!array_of_extrasys.empty() &&
					abs(*(array_of_extrasys.end() - 1) - *(array_of_peak_R.end() - 1)) > RR.middle * Fs / 2)
					R_is = true;
			}
	}
	return R_is;
};
