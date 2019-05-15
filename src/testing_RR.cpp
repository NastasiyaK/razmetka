

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

//vectricular extrasystole
bool one_lead::check_ventr_extrasys(vector<float>*signal, const int& peak1, int& peak2, const int& peak3)
{
	if (peak1 != peak2 && peak2 != peak3 && peak3 != 0 && peak2 != 0)


		{
			int dist = set_indices(peak2, count_iter, mem, mem_sdvig);

			if (dist - static_cast<int>(Fs*QRS.height / 2) > 0 &&
				dist + static_cast<int>(Fs*QRS.height / 2) < signal->size())
			{

				float diff = signal->at(dist) - *min_element(signal->begin() + dist - static_cast<int>(Fs*QRS.height / 2), signal->begin() + dist);
				float diff2 = signal->at(dist) - *min_element(signal->begin() + dist, signal->begin() + dist + static_cast<int>(Fs*QRS.height) / 2);
				int start_int = start_peak(peak2, &filter_signal);
                int stop_int = stop_peak(peak2, &filter_signal);

				int st_tem = set_indices(start_int, count_iter, mem, mem_sdvig);
				int st_tem2 = set_indices(stop_int, count_iter, mem, mem_sdvig);

				
				if (st_tem2 < filter_signal.size() && st_tem > 0  && st_tem < filter_signal.size()
				&& abs(filter_signal.at(dist) - filter_signal.at(st_tem)) < 0.9 * QRS_filtered_min &&
								abs(filter_signal.at(dist) - filter_signal.at(st_tem2)) < 0.9 * QRS_filtered_min)
				{
					peak2 = 0;
					ADD_EXRASYS(V_b);
					return true;
				}

				if ((diff < QRS_filtered_min) || (diff2 < 0.9 * QRS_filtered_min)  || ((stop_int - start_int) > static_cast<int>(Fs*QRS.height+1) ))
				{
					if ((diff < QRS_filtered_min) && (diff2 < QRS_filtered_min )) {
						array_of_peak_R.erase(array_of_peak_R.end() - 2);
						peak2 = 0;
					}else {
						peak2 = 0;
						ADD_EXRASYS(V_b);
						return true;
					}
				}
				if ((diff < average_amplitude.get()/3) || (diff2 < average_amplitude.get()/3)  || ((stop_int - start_int) > static_cast<int>(Fs*QRS.height+1) ))
				{
					if ((diff <average_amplitude.get()/3) && (diff2 <average_amplitude.get()/3 )) {
						array_of_peak_R.erase(array_of_peak_R.end() - 2);
						peak2 = 0;
					}
				}
				
			}
		}
	return false;
}

//here last three peaks are used. Second peak is checking  - maybe it's extrasystole
void one_lead::testing_of_RR() 
{
    if (array_of_peak_R.size() > 1)
    {
        if (abs(*(array_of_peak_R.end() - 2) - *(array_of_peak_R.end() - 1)) < Fs * (length.T_middle + length.ST_seg) )
		{
			int _first = set_indices(*(array_of_peak_R.end() - 2), count_iter, mem, mem_sdvig);

			if (filter_signal.at(_first) < QRS_hight_min * 1.5)
				array_of_peak_R.erase(array_of_peak_R.end()-2);
			else
			{
				peaks_with_types.erase(peaks_with_types.end() - 1);
				array_of_peak_R.erase(array_of_peak_R.end() - 1);
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
		
		
		//Sometimes it can be other outlers,not a useful peak. this outlier can be noise or arthefact. 
		//So this amplitude isn't similiar to adjusted amplitudes;
		if (!(check_peak_amplitudes_max(peak1, peak2, peak3)))
		{
			ADD_EXRASYS(V_b);
		}
		if (!(check_peak_amplitudes_min(peak1, peak2, peak3, 1)))
		{
			if (static_cast<float>((peak2 - peak3) / (peak1 - peak2) > 1.2 ||
				static_cast<float>((peak2 - peak3) / (peak1 - peak2) < 0.8) && ind_of_last_extrasystole < peak3) &&
				peak1 - peak2 < 2 * RR.middle * Fs )
			{
				ADD_EXRASYS(V_b);
			}

		}
		
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
				&& static_cast<float>(peak2 - peak3) / (peak1 - peak2) < 0.75 && peak1 - peak3 < (2 + count_cur / 2.0)*1.05*average_R) {
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
		//res = check_ventr_extrasys(&filter_signal, peak1, peak2, peak3);

		/*if (extrasystoles.size() > 2)
		{
			bool n1 = ( abs(ind_of_last_extrasystole - *(extrasystoles.end() - 2)) < 3 * QRS.height*Fs);

			bool n2 = ( abs(ind_of_last_extrasystole - *(extrasystoles.end() - 3)) < 3 * QRS.height*Fs);
			if (n1 || n2) 
			{
				 vector<float>bufer;

				int ind, ind2, ind_vn;
				if (n1)
					ind = *(extrasystoles.end() - 2);
				else
					ind = *(extrasystoles.end() - 3);
				ind2 = ind_of_last_extrasystole;
				if (ind > ind2)
					 swap(ind, ind2);
				set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);
				copy(begin(signal) + ind, begin(signal) + ind2, back_inserter(bufer));

				if (ind > 0 && ind2 > ind)
				{
					auto temp =  min_element(bufer.begin(), bufer.end());

					size_t temp_d =0;
					if (temp != bufer.end())
					    temp_d =  distance(bufer.begin(), temp);

					if (temp_d > 0 && bufer.at(temp_d) - isolinia < -0.25*QRS_height &&
						signal.at(ind + static_cast<int>(Fs*QRS.height)) < 0.6) {
						extrasystoles.erase(extrasystoles.end() - 1);
					}
					if (temp_d < bufer.size() / 3) {
						extrasystoles.erase(extrasystoles.end() - 1);
					}
				}
			}
		}*/
	} 
}


bool check_diffic_ventr(vector<float >* signal, const int& peak2, float delta){

    if (peak2 > 0 && signal->size() > peak2 + delta)
    {
    	int dist = distance(signal->begin(), min_element(signal->begin()+peak2, signal->begin()+peak2 + delta ));
        float min_amplituda = *min_element(signal->begin()+peak2, signal->begin()+peak2 + delta ) ;
        if (abs(min_amplituda) > signal->at(peak2))
            return true;
    }
    return false;

}