#include "stdafx.h"
#include "leads.h"
#include "LeadII_V.h"

/*if peaks are dense it is tach,otherwise it can be some iextrasystoles 
 * in the long distance. 
 * Also some points can be duplicated*/
 

/*this function for cheking extrasystole
 * if number >0  cheking for alothythmia
 * For this checking valuable class_of_sys - it memorized classof extrasystole*/

void leadII_V::allorhythm_lead(vector_pair & peaks, pair<int, pat_name> & new_pair) {

if (peaks.size() > 1){
    if ((peaks.end()-2)->second == new_pair.second ){
        if (new_pair.second == V_b)
            path_mathods.insert(pathologies, new_pair.first, V_B, n_peaks);

        if (new_pair.second == A_b)
            path_mathods.insert(pathologies, new_pair.first, A_B, n_peaks);

        if (new_pair.second == SV_b)
            path_mathods.insert(pathologies, new_pair.first, SV_B, n_peaks);

    }

}
    if (peaks.size() > 2){
        if ((peaks.end()-3)->second == new_pair.second ){
            if (new_pair.second == V_b)
                path_mathods.insert(pathologies, new_pair.first, V_B, n_peaks);

            if (new_pair.second == A_b)
                path_mathods.insert(pathologies, new_pair.first, A_B, n_peaks);

            if (new_pair.second == SV_b)
                path_mathods.insert(pathologies, new_pair.first, SV_B, n_peaks);

        }

    }



}




/*
void Leads_Info::allorhythm_lead( vector<int>& array_of_peak_R, const int extrasys,  pat_name class_of_sys)
{

	if ((!all_extrasys_of_lead.empty() && *(all_extrasys_of_lead.end() - 1) != extrasys) || all_extrasys_of_lead.empty())
	{
		 pat_name pat = class_of_sys;

		int ind_extrasys_temp = ind_of_last_extrasystole;

		if (extrasys == ind_of_last_extrasystole)
			ind_extrasys_temp = ind_last_extrasys_old;

		if (array_of_peak_R.size() >= 4 && old_class_of_sys == class_of_sys)
		{
			if (ind_extrasys_temp <*(array_of_peak_R.end() - 2) &&
				ind_extrasys_temp>*(array_of_peak_R.end() - 3) && pat != No)
			{
				pat = V_B;
			}else 
			{

				if (ind_extrasys_temp > *(array_of_peak_R.end() - 4) &&
					ind_extrasys_temp < *(array_of_peak_R.end() - 3) && pat != No)
				{
					pat = V_T;
				}
				else 
					pat = E;
			}

			path_mathods.insert(pathologies, extrasys, pat, n_peaks);
		}
		else
		{
			pat = E;
			path_mathods.insert(pathologies, extrasys, pat, n_peaks);
		}
		if ((!all_extrasys_of_lead.empty() && *(all_extrasys_of_lead.end() - 1)) || all_extrasys_of_lead.empty())
			push_el(all_extrasys_of_lead, extrasys, n_peaks);

		if (extrasys != ind_of_last_extrasystole)
			ind_last_extrasys_old = ind_of_last_extrasystole;

		ind_of_last_extrasystole = extrasys;
		old_class_of_sys = class_of_sys;
	}
};
*/