//
// Created by amantayr on 02.05.19.
//

#include "one lead.h"

namespace razmetka{
	float splitting_value = 0.1f;
};
bool one_lead::splitting(int peak, vector<float>*signal, const int otstup)
{
	int min_left = distance(signal->begin(), min_element(signal->begin() + (peak) - otstup, signal->begin() + (peak) ));
	int min_right = distance(signal->begin(), min_element(signal->begin() + (peak) , signal->begin() + (peak) + otstup));
	int max2 = 0;
	bool splitting = 0;
	
	if (peak - min_left > min_right - peak)
	{
		int min_left2 =  distance(signal->begin(),min_element(signal->begin() + (peak) - otstup/2, signal->begin() + (peak) ));
		if (min_left2 != min_left && min_left > 0)
		{
			if (peak - otstup < min_left2)
				max2 =  distance(signal->begin(),max_element(signal->begin() + (peak)- otstup, signal->begin() + min_left2));
			else
			{
				if (min_left2 < peak - otstup)
					max2 = distance(signal->begin(),
				                max_element(signal->begin() + min_left2, signal->begin() + peak - otstup));
			}
			if (signal->at(max2)-signal->at(min_left2) > razmetka::splitting_value)
				splitting = true;
		}
	}else{
		int min_right2 =  distance(signal->begin(),min_element(signal->begin() + peak, signal->begin() + peak + otstup/2) );
		
		if (min_right2 != min_right)
		{
			if (peak + otstup/2 < min_right2)
				max2 =  distance(signal->begin(),max_element(signal->begin()+ peak+ otstup/2, signal->begin()+ min_right2));
			else
			{
				if (min_right2 < peak + otstup)
				max2 = distance(signal->begin(),
				                max_element(signal->begin() + min_right2, signal->begin() + peak + otstup));
			}
			if (signal->at(max2)-signal->at(min_right2) > razmetka::splitting_value)
				splitting = true;
		}
	}
	
return splitting;
}