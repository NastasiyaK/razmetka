

#include  "one lead.h"
#include "Afib.h"
#include <numeric>
#include "LeadII_V.h"

namespace razmetka
{
	
	float pr_WPW = 0.12f; //sec
};
vector<int> check_SV_A_extras(vector<int>&, int, int );

void leadII_V::check_BlockII( vector<int>& array_of_peak_R, int ind_of_last_extrasystole)
{

	if (array_of_peak_R.size() > 1 && ind_of_last_extrasystole < *(array_of_peak_R.end()-2) &&
		*(array_of_peak_R.end() - 1) - *(array_of_peak_R.end() - 2) > 1.8 * average_R)
	{

		vector_pair* ptr_vector_new_peaks = ptr_all_leads->temp_leads.at(1)->get_peaks("all peaks");

		size_t _ind = 1;
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
			
			set_indices(ind_vn, i1, i2, *count_iter, mem, *mem_sdvig);
			
			if (ptr_signal->size() > i2 + static_cast<int>((QRS.height * Fs) / 2)) {
				auto it_max_lost = max_element(begin(*ptr_signal) + i2,
											   begin(*ptr_signal) + i2 + static_cast<int>((QRS.height * Fs) / 2));
				int dur = it_max_lost - begin(*ptr_signal) + ind_vn - i1;
				if (*it_max_lost / R.amplitude > 1.2 || *it_max_lost / R.amplitude < 0.8) {// &&

					bool lost_R_is = true;
					if (finding_of_P(lost_R_is, *(array_of_peak_R.end() - 1))) {
                        pathology_signal.BlockII++;
                        pathology_signal.SBR = 0;
                    }

				}

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



void leadII_V::check_Afibr(vector<int> &array_of_RR, const int &last_point)
{
	N_peaks_fibr++;
	static bool Fibr_is = false;
	
	if (pathology_signal.P_peaks_normal > 10 )
	{
		if ( Fibr_is )
		{
			path_mathods.insert(pathologies, last_point, no_AFIBR, n_peaks);
			Fibr_is = false;
			cout <<last_point <<" fin" <<endl;
			
		}
		if ( pathology_signal.AFIb > 0)
			pathology_signal.AFIb = 0;
	}
	
	if (array_of_RR.size() >= win_fibr && N_peaks_fibr >= win_fibr)
	{

		bool afibr_decision = fibr(array_of_RR);
		push_el(afibr_decision_memory, afibr_decision, n_peaks);

		
		static int last_point_afib = 0;
        if (pathology_signal.P_peaks_normal < 3 && afibr_decision && afibr_decision_memory.size() > 1 && *(afibr_decision_memory.end() - 2))
        {
	        if ( pathology_signal.AFIb == 0)
		        last_point_afib = last_point;
            pathology_signal.AFIb++;
           
        }
        
        
        if (Fibr_is &&  pathology_signal.AFIb == 0)
        	int a = 1;
		
		
		
		if (!Fibr_is && pathology_signal.AFIb > 3)
		{

            path_mathods.insert(pathologies, last_point_afib, AFIBR, n_peaks);
            cout<< last_point_afib << " st "<<endl;
            erase(&Q_v, last_point_afib);//array_of_peak_R.at(n_peaks - win_fibr)
            erase(&P_v, last_point_afib);
            erase(&T_v, last_point_afib);
            erase(&ST_v, last_point_afib);
            Fibr_is = true;
				
        }

        if (Fibr_is && afibr_decision_memory.size() > 1 && !afibr_decision && pathology_signal.AFIb != 0)
        {
        	cout <<last_point <<" fin" <<endl;
            path_mathods.insert(pathologies, last_point, no_AFIBR, n_peaks);
            pathology_signal.AFIb = 0;
            Fibr_is = false;
            last_point_afib = 0;
        }
			

		N_peaks_fibr = win_fibr - 32;//as window
	}

	
}
void leadII_V::check_WPW( vector<wave>& R_s)
{
	if (!R_s.empty() && ((R_s.end() - 1)->peak - (R_s.end() - 1)->start > static_cast<int>((QRS.low + QRS.height) *Fs/4)-1) &&
			(R_s.end() - 1)->stop- (R_s.end() - 1)->start < static_cast<int>(RR.middle*Fs))
	{
		float pr = 0.f;
		if  ( !P_v.empty() )
			float pr = ((R_s.end() - 1)->peak - (P_v.end() - 1)->peak)/Fs;
		if (pr < razmetka::pr_WPW && pr != 0)
			pathology_signal.WPW++;
	}
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
		allorhythm_lead(clean_peaks, new_pair);

	
	
	if (new_pair.second == N_b)
	{
		if (R_s.size() >= win_fibr) {
			check_Afibr(R_peak_for_fibr, *(R_s.end() - win_fibr));
			index_start_wave_copy = *(R_s.end() - win_fibr);
		}
		check_BlockII(R_s, ind_of_last_extrasystole);
		set_peaks(new_pair.first);
		check_WPW(R_v);

		vector<int>_extrasystoles = check_SV_A_extras(R_s, ind_of_last_extrasystole, average_R);

		if (!_extrasystoles.empty() )
		{
			for (int j = 1; j < _extrasystoles.size(); j++)
			{
				for (int i = 1; i < 5; i++) {
					if (_extrasystoles.at(j) == clean_peaks.at(i).first){

					}
					
				}
		}
		}

		static bool VT_is = false;
		bool res = find_VT(clean_peaks, Fs);
		
		if (res)
		{
			path_mathods.insert(pathologies, (clean_peaks.end() - 4)->first, VT, n_peaks);
			VT_is = true;
		}
		
		if ( !res  && VT_is)
		{
			path_mathods.insert(pathologies, (clean_peaks.end() - 3)->first, No, n_peaks);
			VT_is = false;
		}
		
		//atrial flutter
		if (array_of_peak_R.size() > 3 && pathology_signal.AFl >= 3)
		{
			path_mathods.insert(pathologies, *(array_of_peak_R.end() - 3), AFl, n_peaks);
		}
	}

	auto it = pathologies.end();
	static bool SVTA_is = false;
	
	if (pathologies.size() > 1 && (current_rhythm != 0) && pathology_signal.SVTA>=2
		&& (--it)->second != no_VFIBR && !SVTA_is)
	{
		SVTA_is = true;
		if (R_v.size() > 0)
			if (pathology_signal.ventr_comlex == 0)
				path_mathods.insert(pathologies, (R_v.end() - 1)->peak, SVTA, n_peaks);
			else
				path_mathods.insert(pathologies, (R_v.end() - 1)->peak, VT, n_peaks);
	} else
	{
		if (pathology_signal.SVTA < 2 && SVTA_is)
		{
			SVTA_is = false;
		}
	}
	
	static bool SBR_is = false;
	
	if (R_s.size()>1 && pathology_signal.SBR>2 && !SBR_is )
	{
		path_mathods.insert(pathologies, *(R_s.end() - 2), SBR, n_peaks);
		SBR_is = true;
	}

	if (!R_s.empty() && pathology_signal.SBR == -1)
	{
		pathology_signal.SBR = 0;
		SBR_is = false;
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
	
	if( abs(path_mathods.find(pathologies, no_VFIBR)-2*count) > Fs)
	{
		path_mathods.erase(pathologies, BLOCKII, count - 2*Fs);
		path_mathods.erase(pathologies, SBR, count - 2*Fs);
		path_mathods.erase(pathologies, VT, count - 2*Fs);
	}

	if (path_mathods.find(pathologies, SVTA) - count > Fs)
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
			   && static_cast<float>(peak2 - peak3) / (peak1 - peak2) < 0.75 &&
			   peak1 - peak3 < (2 + count_cur / 2.0) * 1.05 * average_R) {

			count_cur++;


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