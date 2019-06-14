//
// Created by amantayr on 17.05.19.
//
#include "LeadII_V.h"


bool find_VT(const vector<pair<int, pat_name>>& peaks_with_types, float Fs)
{
	if (peaks_with_types.size()>5)
	{
		float time = 0.f;
		if ((peaks_with_types.end() - 2)->second != N_b && (peaks_with_types.end() - 3)->second != N_b
		    && (peaks_with_types.end() - 4)->second != N_b)
		{
			time = (peaks_with_types.end()-2)->first - (peaks_with_types.end()-5)->first;
			int N_beats = 3/(time/Fs)*60;
			
			if (N_beats > 105)
				return true;
		}
		
		
	}
	return false;
}