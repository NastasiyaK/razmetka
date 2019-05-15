
#include  "leads.h"
#include "functions.h"
/*We're finfding start of probable VFL - 
if signal have regular high peaks in
*the lenght of last interval RR. 
 if there're rhythm 240  - VFL*/


#define GET_START_VF(start_vf, count,average_R); \
start_vf = static_cast<int>(count - 3 * Fs); \
start_vf = start_severe_distortion(&all_extrasys_of_lead, &array_of_peak_R, start_vf, average_R); \
if (start_vf < 0)\
	start_vf = 0; \
if (type_of_lead == II || type_of_lead == v5) \
to_merge_peaks(&peaks_with_types,&list_extrasys, start_vf); \



//fuction to merge array of all different peaks and ventricular peaks
void to_merge_peaks( vector< pair<int,pat_name >>* main_peaks,  vector<int>* odd_peaks, int start)
{
	size_t start_in_first = 0;
	for (size_t i = main_peaks->size() - 1; i >=  max(start,2); i--)
	{
		
		if (main_peaks->at(i - 1).first >= start && main_peaks->at(i - 2).first <= start)
		{
			start_in_first = i;
			break;
		}
		
	}
	main_peaks->erase(main_peaks->begin()+ start_in_first, main_peaks->end());



	if (!odd_peaks->empty())
	for (size_t i = odd_peaks->size() - 1; i >=  max(start, 2); i--)
	{
		
		if (odd_peaks->at(i - 1) >= start && odd_peaks->at(i - 2) <= start)
		{
			
			start_in_first = i;
			break;
		}
	}
	
	for (size_t i = start_in_first; i < odd_peaks->size(); i++)
	{
		main_peaks->push_back( pair< int, pat_name>(odd_peaks->at(i),V_b));
	}

};



bool one_lead::ventr_flutter(size_t st_f, const int& len_st) {

	bool decision = false;
	 vector <float>vect0;
	//finding of real max value of signal  	
	if (signal.size() - len_st > 0)
		st_f = signal.size() - len_st;
	else
		st_f = 0;

	 copy(begin(filter_signal) + st_f, end(filter_signal) - 1, back_inserter(vect0));

	//finding of the next peak, its amplitude
	int max_el = static_cast<int>( distance(vect0.begin(),  max_element(vect0.begin(), vect0.end())));
	float max_ampl = *( max_element(vect0.begin(), vect0.begin() + max_el));
	float ampl = vect0.at(max_el);
	max_el += st_f;

	size_t d1 = 0;
	if (max_el - static_cast<int>(QRS.height*Fs) < 0)
		d1 = max_el;
	else
		d1 = static_cast<int>(QRS.low*Fs);

	//peak is saved if min value between other peaks enough good
	auto min1 =  min_element(filter_signal.begin() + max_el - d1, filter_signal.begin() + max_el);
	

	int extras_last = 0;
	if ( !list_extrasys.empty() )
		extras_last = set_indices(*(list_extrasys.end()-1), count_iter, mem, mem_sdvig);


	if ( abs(ampl - *min1)>QRS_hight_min && extras_last >= 0 && extras_last < filter_signal.size() &&
	ampl > 0.3*filter_signal.at(extras_last))
	{
		max_el = (count_iter == 0) ? (max_el) : (max_el + (count_iter - 1)*(mem)+mem_sdvig);
		
		if (list_extrasys.size() == 0 || ( abs(max_el - *(list_extrasys.end() - 1)) > 2 * QRS.height*Fs))
		{
			
			push_el(list_extrasys, max_el, n_peaks);
			push_el(list_ampl, max_ampl, n_peaks);


			if (list_extrasys.size() > 1)
			{
				int ind = set_indices(*(list_extrasys.end() - 2), count_iter, mem, mem_sdvig);
				int ind2 = set_indices(*(list_extrasys.end() - 1), count_iter, mem, mem_sdvig);
				if (filter_signal.at(ind) - filter_signal.at(ind + QRS.height*Fs) < static_cast<int>(QRS_hight_min) ||
					 abs(filter_signal.at(ind) / filter_signal.at(ind2)) < 1 / 2.5 )
				{
					if ( abs(ind2 - ind) < length.T_middle/2 * Fs)
						list_extrasys.erase(list_extrasys.end() - 2);
				}
				if ( (ind2 - ind) < 2 * QRS.height*Fs)
					list_extrasys.erase(list_extrasys.end() - 2);
				
			}
			if (list_extrasys.size() > 2 )
				print(*(list_extrasys.end()-3),"ventr.txt");
		}
	}

	/*there type of window */
	static int win1 = 0, win2 = static_cast<int>(3 * Fs);
	 vector <int> peaks_rhythm;

	if (signal.size()>3 * RR.middle*Fs)
	{
		size_t i = 0;
		int num_beat = 0;
		while (i<list_extrasys.size() && list_extrasys.at(i) <= win2) 
		{
			if (list_extrasys.at(i) >= win1)
				num_beat++;

			push_el(peaks_rhythm, list_extrasys.at(i), n_peaks);

			i++;
		}
		float rhythm_vf = (static_cast<float>(num_beat)) / 3 * 60;

		//part of heart rating analysing
		if (rhythm_vf > 180 && rhythm_vf < 200)

		{
			//cout<<type_of_lead<<endl;
			current_rhythm = 60.f * Fs / rhythm_vf;
			if (pathology_signal.VT == 0 && start_vf == 0) 
			{
				GET_START_VF(start_vf, count,average_R)
				
			} else 
			{
				static int window_old = 0;
				if (window_old != win1) 
					window_old = win1;
			}
		} else 
		{
			if (pathology_signal.VT > 0) 
			{
				pathology_signal.VT = 0;
				decision = true;
				start_vf = 0;
			}
		}
		if (rhythm_vf >= 200) 
		{
			current_rhythm = 60 * Fs / rhythm_vf;
			if (pathology_signal.VFib == 0 && start_vf == 0) 
			{
				GET_START_VF(start_vf,count,average_R);

			}else {
				static int window_old = 0;
				if (window_old != win1) {
					window_old = win1;
				}
			}
		} else {
			if (pathology_signal.VFib>0) {
				decision = true;
				//if there's end VF - deleting of all points because of 
				//they're mistaken
				pathology_signal.SVTA = 0;
				
				start_vf = 0;
				pathology_signal.VFib = 0;

			}
			else
				pathology_signal.VFib = 0; //temp_state.vf = 0;
		}
	}
	//shifting of window
	if (list_extrasys.size()>0)
	{
		if (*(list_extrasys.end() - 1)>win2)
		{
			win1 += static_cast<int>(Fs);
			win2 += static_cast<int>(Fs);
		}
	}
	return decision;
}



int start_severe_distortion(vector<int> *extrasystoles, vector<int> *R_peaks, const int &start_VF,
							const int &average_interval)
{
	int start = start_VF;
	//n_tryed - number of attemp to find first distortion
	//n_extrasystoles for analysing
	int n_tryed = 1;
	if (!extrasystoles->empty() && !R_peaks->empty())
	while (n_tryed < 3)
	{
		if (*(extrasystoles->end() - n_tryed) < *(R_peaks->end() - n_tryed) &&
			*(extrasystoles->end() - n_tryed - 1) > *(R_peaks->end() - n_tryed - 1))
		{
			start = *(extrasystoles->end() - 2);
		}
		n_tryed++;

	}
	if (extrasystoles->size() >1 && abs(*(extrasystoles->end() - 2) - *(extrasystoles->end() - 1)) < average_interval/3)
		start = start_VF;
	return start;
}