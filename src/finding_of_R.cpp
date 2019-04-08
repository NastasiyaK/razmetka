
#include "one lead.h"

bool one_lead::finding_of_R() {
	bool result = 0;
	 vector <double> array_temp;
	int temp_d;
	size_t Npol_P, min_zde;
	//duration for finding
	static size_t len_st = (int)((QRS.height*Fs) / 4);
	temp_d = (after_diff_signal.size() - 1);
	//finding of start positive part

	if (*(after_diff_signal.end() - 1) > 0) {
		array_of_pol.push_back(*(after_diff_signal.end() - 1));
		sdvig++;
	}
	//start of negative part
	if (*(after_diff_signal.end() - 1) < 0) {
		vect_of_2part.push_back(*(after_diff_signal.end() - 1));
		sdvig++;
	}
	
	//finish of negative part
	
	//point of chanching of sign of derivative
	if ((main_peak_in_interval =='R') && (after_diff_signal.size() - len_st > 0) && *(after_diff_signal.end() - 2) < 0 && (*(after_diff_signal.end() - 1) >= 0) ||
		((main_peak_in_interval == 'S') &&  *(after_diff_signal.end() - 2) > 0 && (*(after_diff_signal.end() - 1) <= 0))) {
		if (array_of_pol.empty()) 
			array_of_pol.push_back(0);
		if (vect_of_2part.empty()) 
			vect_of_2part.push_back(0);
		
		Npol_P = array_of_pol.size();
		 reverse(begin(array_of_pol), end(array_of_pol));
		 sort(array_of_pol.begin(), array_of_pol.end());
		 sort(vect_of_2part.begin(), vect_of_2part.end());
		

		min_zde = (vect_of_2part.size() < array_of_pol.size()) ? vect_of_2part.size() : array_of_pol.size();

		for (int k = 0; k < min_zde; k++) 
		{
			array_temp.push_back(vect_of_2part.at(k) - array_of_pol.at(k));
		}

		array_temp.push_back(* max_element(array_of_pol.begin(), array_of_pol.end()) - * min_element(vect_of_2part.begin(), vect_of_2part.end()));
		vect_of_2part.clear();
		//temple array for finding for max value
		 vector <double>abs_temp = abs(array_temp);

		double m = * max_element(abs_temp.begin(), abs_temp.end());

		if (* max_element(abs_temp.begin(), abs_temp.end()) < limit) {
			array_of_pol.clear();
			sdvig = 0;
		}
		//st save thestrart of peak;
		st = after_diff_signal.size() - sdvig - 1 - n;
		
		double up_limit = * max_element(abs_temp.begin(), abs_temp.end());
		//cout<<up_limit<<endl;
		if (st> 0 && * max_element(abs_temp.begin(), abs_temp.end()) >= limit) {
			ventr_flutter(st, len_st);
			int min_zde = (temp_d < st + Npol_P - 1) ? temp_d : st + Npol_P - 1;
			int count_temp = 0;

			if (st < min_zde) {
				for (int k = st; k <= min_zde - 1; k++) {
					count_temp++;
					after_diff_signal.at(k) =
						(after_diff_signal.at(k) - array_of_pol.at(array_of_pol.size() - count_temp));
				}
				array_of_pol.clear();
				 vector <double>vect0;
				//finding of real max value of signal  
				st = (filter_signal.size() >= st) ? st - len_st / 4 : filter_signal.size() - len_st / 4;
				st = (0 >= st) ? 1 : st;
				 copy(begin(filter_signal) + st, end(filter_signal) - 1, back_inserter(vect0));


				size_t max_el = 0;
				if (main_peak_in_interval == 'R') {
					max_el =  distance(vect0.begin(),  max_element(vect0.begin(), vect0.end()));
				} else {
					max_el =  distance(vect0.begin(),  min_element(vect0.begin(), vect0.end()));
				}
					amplitude_old_peak = amplitude_new_peak;
					amplitude_new_peak =  abs(vect0.at(max_el));

				if (amplitude_new_peak > 0.25*QRS_hight_min)  //filtered signal has other amplitude of peak R
				{
					max_el = (count_iter == 0) ? (max_el + st) : (max_el + st + (count_iter - 1)*(mem)+mem_sdvig);

					sdvig = 0;
					new_peak = max_el;
					

					if (!array_of_peak_R.empty())
						result = true;
					//finding of first peak R;
					if (array_of_peak_R.empty()) 
					{
						int min_t = ((QRS.height / 2 + length.P * RR.middle)*Fs >= filter_signal.size()) ? filter_signal.size() - 1
							: static_cast<int>( (QRS.height / 2 + length.P*RR.middle)*Fs);

						if ( new_peak - min_t <0)
						{
							min_t = new_peak;
						}
						auto temp_iso =  min_element(filter_signal.begin() + new_peak - min_t, filter_signal.begin() + new_peak);
						isolinia = (*temp_iso) / 2;
						amplitude_new_peak -= (*temp_iso) / 2;
						if (new_peak - QRS.height > 0)
							original_isolinia = signal.at(new_peak - QRS.height);
						else
							original_isolinia = signal.at(0);

						if (amplitude_new_peak > QRS_hight_min && amplitude_new_peak < 1.2*QRS_height) {
							array_of_peak_R.push_back(max_el);
							
							R.amplitude = amplitude_new_peak;
							//push_el(peaks_amplitudes, amplitude_new_peak, 3);
							result = true;
							N_count++;
							push_el(peaks_with_types, new_peak, N_b, n_peaks);
						}

					}
					}
				}
			}
		
	}
	return result;
}
