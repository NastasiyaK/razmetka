//
// Created by amantayr on 05.05.19.
//
#include <array>
#include "functions.h"

namespace razmetka
{
	int N_extrem = 4;
	float  casual_outliers_threhold = 0.25f;
}

bool casual_outliers(vector<float>* signal, const size_t peak, const int QRS_length, float QRS_amplitude, const int diff_last)
{
	vector <int>extremums;
	extremums.reserve(razmetka::N_extrem);
	bool other_peak = false;
	
	if (peak < signal->size() )
	{
		//for left extrmums
		int i = peak - 1;
		while (i != 1 && extremums.size() <= razmetka::N_extrem)
		{
			if ((signal->at(i) - signal->at(i - 1)) * (signal->at(i + 1) - signal->at(i)) < 0)
			{
				extremums.push_back(i);
			}
			i--;
		}
		bool other_large_peak = false;
		int N_less_param = 0;
		if (!extremums.empty())
		{
		for (size_t i = 0; i < extremums.size() - 1; i++)
		{
			if (abs(signal->at(extremums.at(i)) - signal->at(extremums.at(i + 1))) > razmetka::casual_outliers_threhold)
			{
				N_less_param++;
			}
			
			if (i % 2 == 1 && abs(signal->at(extremums.at(i)) - signal->at(peak)) < razmetka::casual_outliers_threhold
			    && signal->at(extremums.at(i)) < QRS_amplitude * 0.7 )
				other_large_peak = true;
			
		}
		if (abs(signal->at(peak) -signal->at(extremums.at(0))) < diff_last * 0.4 &&
				abs(signal->at(peak) -signal->at(extremums.at(2))) < diff_last * 0.4)
			return true;
		
		if (N_less_param >= extremums.size() / 2 && (peak - *(extremums.end() - 1)) < QRS_length * 2 &&
		    other_large_peak)
			return true;
		
		
		//for right extremums
		
		extremums.clear();
		extremums.reserve(razmetka::N_extrem);
		i = peak + 1;
		while (i != signal->size() - 1 && extremums.size() <= razmetka::N_extrem)
		{
			if ((signal->at(i) - signal->at(i - 1)) * (signal->at(i + 1) - signal->at(i)) < 0)
			{
				extremums.push_back(i);
			}
			i++;
		}
	}
		
		N_less_param = 0;
		if (!extremums.empty())
		{
			for (size_t i = 0; i < extremums.size() - 1; i++)
			{
				if (abs(signal->at(extremums.at(i)) - signal->at(extremums.at(i + 1))) <
				    razmetka::casual_outliers_threhold)
				{
					N_less_param++;
				}
				if (i % 2 == 1 &&
				    abs(signal->at(extremums.at(i)) - signal->at(peak)) < razmetka::casual_outliers_threhold &&
				    signal->at(extremums.at(i)) < QRS_amplitude * 0.7)
					if (!other_large_peak )
						other_large_peak = true;
					else
						return true;
				
			}
			
			if (N_less_param >= extremums.size() / 2 && (*(extremums.end() - 1) - peak) < QRS_length * 2 &&
			    other_large_peak)
				return true;
		}
		
		
	
	
	}
	return false;
}
