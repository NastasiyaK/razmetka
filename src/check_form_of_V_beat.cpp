//
// Created by amantayr on 20.05.19.
//

#include "one lead.h"

bool one_lead::check_V_forme(vector<pair<int, pat_name>>& peaks, int average_RR)

{
	if (peaks.size() > 4 )
		if ( (peaks.end()-1)->second == N_b && (peaks.end()-2)->second == V_b &&  (peaks.end()-3)->second == N_b &&
				(peaks.end()-4)->second == N_b)
		{
			if (abs((peaks.end()-2)->first - (peaks.end()-3)->first) < average_RR/2 &&
					abs((peaks.end()-3)->first - (peaks.end()-4)->first) < 2*average_RR/3)
			{
				int _first = set_indices(*(array_of_peak_R.end() - 4), count_iter, mem, mem_sdvig);
				int _second = set_indices(*(array_of_peak_R.end() - 3), count_iter, mem, mem_sdvig);
				if (signal.at(_first)/signal.at(_second) > 1.1 ||  signal.at(_first)/signal.at(_second) < 0.9)
				{
					peaks_with_types.erase(peaks_with_types.end() - 3);
					array_of_peak_R.erase(array_of_peak_R.end() - 3);
					return true;
				}
				//peaks.erase(peaks.end()-3);
				
			}
				
		}
		return false;
}