
#include "stdafx.h"
#include  "one lead.h"
#include "Afib.h"
#include <numeric>
#include "LeadII_V.h"


#define ERASE_PTHOLOGIES(therehold)\
path_mathods.erase(pathologies,"WPW", therehold);  \
path_mathods.erase(pathologies,"SBR ",therehold);\
path_mathods.erase(pathologies,"lost_R", therehold);\
path_mathods.erase(pathologies,"SV B",therehold);\
path_mathods.erase(pathologies,"V B", therehold);\
path_mathods.erase(pathologies,"V T", therehold);\
path_mathods.erase(pathologies,"E", therehold);\
path_mathods.erase(pathologies,"SVTA", therehold);\

vector<int> check_SV_A_extras(vector<int>&, int, int );

void leadII_V::check_BlockII( vector<int>& array_of_peak_R, int ind_of_last_extrasystole)
{

	if (array_of_peak_R.size() > 1 && ind_of_last_extrasystole < *(array_of_peak_R.end()-2) &&
		*(array_of_peak_R.end() - 1) - *(array_of_peak_R.end() - 2) > 1.8 * average_R)
	{

		vector_pair* ptr_vector_new_peaks = ptr_all_leads->temp_leads.at(1)->get_peaks("all peaks");

		int _ind = 1;
		while (_ind < ptr_vector_new_peaks->size() &&
		(ptr_vector_new_peaks->end()-_ind)->first >= *(array_of_peak_R.end() - 2)  && _ind < 4  )
		{
			_ind++;

		}
		if ((ptr_vector_new_peaks->end()-_ind)->first == *(array_of_peak_R.end() - 2))
		{
			int i2 = *(array_of_peak_R.end() - 1) - static_cast<int>(len_R / 2 - (QRS.height * Fs) / 2);
			int ind_vn;
			int i1 = *(array_of_peak_R.end() - 1) -
					 static_cast<int>(len_R / 2 - length.PQ_int * Fs + (QRS.height * Fs) / 2);
			set_indices(ind_vn, i1, i2, count_iter, mem, mem_sdvig);
			if (ptr_signal->size() > i2 + static_cast<int>((QRS.height * Fs) / 2)) {
				auto it_max_lost = max_element(begin(*ptr_signal) + i2,
											   begin(*ptr_signal) + i2 + static_cast<int>((QRS.height * Fs) / 2));
				int dur = it_max_lost - begin(*ptr_signal) + ind_vn - i1;
				if (*it_max_lost / R.amplitude > 1.2 || *it_max_lost / R.amplitude < 0.8)// &&

					pathology_signal.BlockII++;
				bool lost_R_is = true;
				finding_of_P(lost_R_is, *(array_of_peak_R.end() - 1));
			}
		}
	}


	if (!R_s.empty() && pathology_signal.BlockII >= 1 && pathology_signal.AFIb == 0)
		{
			path_mathods.insert(pathologies, *(R_s.end() - 1), BLOCKII, n_peaks);
		}

	if (!R_s.empty() && pathology_signal.BlockII >= 1 && pathology_signal.AFIb == 0)
		{
			path_mathods.insert(pathologies, *(R_s.end() - 1), BLOCKII, n_peaks);
		}

}



void leadII_V::check_Afibr( vector<int>& array_of_peak_R)
{
	N_peaks_fibr++;
	if (array_of_peak_R.size() >= win_fibr && N_peaks_fibr >= win_fibr)
	{
		vector<int>intervals(win_fibr);
		adjacent_difference(array_of_peak_R.end() - win_fibr, array_of_peak_R.end(), intervals.begin());
		bool afibr_decision = fibr(intervals);
		push_el(afibr_decision_memory, afibr_decision, n_peaks);	

		if (afibr_decision_memory.size() > 1 && afibr_decision == 1 && *(afibr_decision_memory.end() - 2) == 1)
		{
			if (pathology_signal.AFIb == 0)
			{
				path_mathods.insert(pathologies, array_of_peak_R.at(array_of_peak_R.size() - win_fibr), AFIBR, n_peaks);
				erase(&Q_v, array_of_peak_R.at(array_of_peak_R.size() - win_fibr));//array_of_peak_R.at(n_peaks - win_fibr)
				erase(&P_v, array_of_peak_R.at(array_of_peak_R.size()- win_fibr));
				erase(&T_v, array_of_peak_R.at(array_of_peak_R.size() - win_fibr));
				erase(&ST_v, array_of_peak_R.at(array_of_peak_R.size() - win_fibr));

				
			}

			pathology_signal.AFIb++;
		}else
		{
			if (afibr_decision_memory.size() > 1 && afibr_decision == 0 && pathology_signal.AFIb != 0) 
			{
				path_mathods.insert(pathologies, *(array_of_peak_R.end() - win_fibr), no_AFIBR, n_peaks);
				pathology_signal.AFIb = 0;
			}
			
		}
		N_peaks_fibr = win_fibr - 32;//as window
	}
	
}
void leadII_V::check_WPW( vector<wave>& R_s)
{
	if (!R_s.empty() && ((R_s.end() - 1)->peak - (R_s.end() - 1)->start >= static_cast<int>(QRS.height *Fs/2)-1) &&
			(R_s.end() - 1)->start - (R_s.end() - 1)->stop < static_cast<int>(RR.middle*Fs))
			pathology_signal.WPW++;
		else
			if (pathology_signal.WPW > 0)
				pathology_signal.WPW = -1;

		if (pathology_signal.WPW == -1) 
		{
			pathology_signal.WPW = 0;
		}
		if (R_s.size() > 1 && pathology_signal.WPW > 2)
			path_mathods.insert(pathologies, (R_s.end() - 2)->peak, WPW, n_peaks);
	
}


void leadII_V::set_pathology( pair<int, pat_name >& new_pair,  vector<int>& R_s)
{
	pat_name old_type = N_b;
	
	if (new_pair.second != N_b)
		allorhythm_lead(R_s, new_pair.first, new_pair.second);

	
	
	if (new_pair.second == N_b)
	{
		check_Afibr(R_s);
		check_BlockII(R_s, ind_of_last_extrasystole);
		set_peaks(new_pair.first);
		check_WPW(R_v);
		vector<int>_extrasystoles = check_SV_A_extras(R_s, ind_of_last_extrasystole, average_R);

		if (!_extrasystoles.empty() )
		{
			for (int j = 1; j < _extrasystoles.size(); j++)
			{
				for (int i = 1; i < 5; i++) {
					if (_extrasystoles.at(j) == clean_peaks.at(i).first)
						clean_peaks.at(i).second = E;

				}
		}
		}

		//atrial flutter
		if (array_of_peak_R.size() > 3 && pathology_signal.AFl >= 3)
		{
			path_mathods.insert(pathologies, *(array_of_peak_R.end() - 3), AFl, n_peaks);
		}
	}

	auto it = pathologies.end();
	if ((current_rhythm != 0) && pathology_signal.SVTA>=3 && (--it)->second != no_VT
		&& (--it)->second != no_VFIBR)
	{
		if (R_v.size() > 0)
			if (pathology_signal.ventr_comlex == 0)
				path_mathods.insert(pathologies, (R_v.end() - 1)->peak, SVT, n_peaks);
			else
				path_mathods.insert(pathologies, (R_v.end() - 1)->peak, VT, n_peaks);
	}
	
		
	if (R_s.size()>1 && pathology_signal.SBR>2 )
		path_mathods.insert(pathologies, *(R_s.end() - 2), SBR, n_peaks);

	if (!R_s.empty() && pathology_signal.SBR == -1) {
			
		pathology_signal.SBR = 0;
	}

	
		
		//asystolia
	if (!array_of_peak_R.empty() && (count - *(array_of_peak_R.end() - 1) > Fs * 5))
		path_mathods.insert(pathologies, count, AS, n_peaks);

	if ( array_of_peak_R.empty() && !array_of_extrasys.empty() && count - *(array_of_extrasys.end() - 1) > Fs * 5) {
		path_mathods.insert(pathologies, count, AS, n_peaks);
	}

		
		
		
	if( abs(path_mathods.find(pathologies, AFIBR)-2*count) > Fs)
	{
		path_mathods.erase(pathologies, BLOCKII, count - 2*Fs);
	}

	if (path_mathods.find(pathologies, SVT) - count > Fs)
	{
		path_mathods.erase(pathologies, WPW, count - Fs);
	}

	old_type = new_pair.second;
	}
		
vector<int> check_SV_A_extras(vector<int>& array_of_peak_R, int ind_of_last_extrasystole, int average_R) {
	vector<int> decision;
	//for camfortable using
	int peak1 = *(array_of_peak_R.end() - 1);
	int peak2 = *(array_of_peak_R.end() - 2);
	int peak3 = *(array_of_peak_R.end() - 3);

	int count_cur = 0;
	if (ind_of_last_extrasystole < peak3) {
		while (peak2 != 0 && peak3 != 0 && abs(peak2 - peak3) < average_R && (peak1 - peak2) > average_R
			   && static_cast<double>(peak2 - peak3) / (peak1 - peak2) < 0.75 &&
			   peak1 - peak3 < (2 + count_cur / 2.0) * 1.05 * average_R) {
			count_cur++;
			//if (type_of_P(peak2) > 0) {
			//ADD_EXRASYS(A_b);
			//}
			//else {
			//ADD_EXRASYS(SV_b);
			//}
			decision.push_back(peak2);
			peak2 = 0;
			array_of_peak_R.erase(array_of_peak_R.end() - 2);

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
	return decision;
}