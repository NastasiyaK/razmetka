//
// Created by amantayr on 15.05.19.
//
#include "functions.h"

/**
 *
 * @param index  - vector of indexes
 * @param signal - signal which is approximated
 * @param num_of_points 0 number of points for approximate
 * @param peak - index of exploring peak
 * @return - slope of approximated line;
 */

int find_double_peak(char direction, const vector<float>* signal, int peak, int otstup)
{
	int second_peak = 0;
	if (peak > 0)
	{
		
		if (direction == 'L')
		{
			for (int i = peak - 2 * otstup; i < peak; i++)
				if ((signal->at(i) - signal->at(i - 1)) * (signal->at(i - 1) - signal->at(i - 2)) < 0 &&
				    (signal->at(i) - signal->at(i - 1) < 0))
				{
					second_peak = i;
					return second_peak;
				}
		}
		if (direction == 'R')
		{
			for (int i = peak + 2; i < peak + 2 * abs(otstup); i++)
				if ((signal->at(i) - signal->at(i - 1)) * (signal->at(i - 1) - signal->at(i - 2)) < 0 &&
				    (signal->at(i) - signal->at(i - 1) < 0))
				{
					second_peak = i;
					return second_peak;
				}
		}
	}

return second_peak;
}

pair<float, float> getApprox(const vector<int>& index,const vector<float>& signal, int num_of_points, int& peak)
{
	float a = 0.f;
	float b = 0.f;
	
	if (peak > 0)
	{
		
		float sumx = 0.f;
		float sumy = 0.f;
		float sumx2 = 0.f;
		float sumxy = 0.f;
		int _ind_count = 0;
		
		vector<float> bufer;
		int second_peak = 0;
		if (num_of_points > 0)
		{
			///char dest = 'L';
			int second_peak = find_double_peak('L', &signal, peak, num_of_points);
			if (abs(signal.at(second_peak) - signal.at(peak)) < 0.3)
				peak = second_peak;
			int max_ind = distance(signal.begin(),
			                       max_element(signal.begin() + peak - num_of_points, signal.begin() + peak + 1));
			if (peak - max_ind < 3)
				peak = max_ind;
			
			copy(begin(signal) + peak - num_of_points, begin(signal) + peak + 1, back_inserter(bufer));
			//second_peak = find_double_peak('L', &signal, peak, num_of_points);
			//if (second_peak != 0 && abs(signal.at(second_peak) - signal.at(peak)) < 0.5)
			//	peak = second_peak;
		} else
		{
			
			int max_ind = distance(signal.begin(),
			                       max_element(signal.begin() + peak + 1, signal.begin() + peak + 5 - num_of_points));
			if (peak - max_ind < 3)
				peak = max_ind;
			
			
			second_peak = find_double_peak('R', &signal, peak, num_of_points);
			
			if (second_peak != 0 && abs(signal.at(second_peak) - signal.at(peak)) < 0.3)
				peak = second_peak;
			copy(begin(signal) + peak, begin(signal) + peak - num_of_points, back_inserter(bufer));
		}
		num_of_points = bufer.size();
		
		for (size_t i = 0; i < bufer.size(); i++)
		{
			
			sumx += index.at(_ind_count);
			sumy += bufer.at(i);
			sumx2 += index.at(_ind_count) * index.at(_ind_count);
			sumxy += index.at(_ind_count) * bufer.at(i);
			_ind_count++;
		}
		a = ((num_of_points) * sumxy - (sumx * sumy)) / (num_of_points * sumx2 - sumx * sumx);
		b = (sumy - a * sumx) / num_of_points;
		
		
	}
	return make_pair(a,b);
}