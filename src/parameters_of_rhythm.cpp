
#include "stdafx.h"
#include "one lead.h"
#include "LeadII_V.h"

void leadII_V::rhythm(pair<int, pat_name > new_some_point, vector<int>& array_of_peak_R)
{
	int new_point = new_some_point.first;
	if (last_peak_for_rhythm < new_point)
	{
		if (last_points.size()<3)
			last_points.push_back(new_point);
		else
			last_points.at(N_last_points) = new_point;

		N_last_points++;

		if (last_points.size() == 1)
			current_rhythm = 0;
		else
			if (last_points.size() == 2)
				current_rhythm = static_cast<float>(last_points.at(1) - last_points.at(0));
			else
				if (last_points.size() >= 3) 
				{
					if (N_last_points == 1)
						current_rhythm = static_cast<float>(((last_points.at(2) - last_points.at(1)) + (last_points.at(0) - last_points.at(2)))) / 2;
					if (N_last_points == 2)
						current_rhythm = static_cast<float>(((last_points.at(1) - last_points.at(0)) + (last_points.at(1) - last_points.at(2)))) / 2;
					if (N_last_points == 3) {
						current_rhythm = static_cast<float>(((last_points.at(2) - last_points.at(1)) + (last_points.at(1) - last_points.at(0)))) / 2;
						N_last_points = 0;
					}

				}

		if ( current_rhythm !=0 &&  60 * Fs / current_rhythm + 1 < 55 && R_v.size() > 3)
			pathology_signal.SBR++;

		if (current_rhythm != 0 && 60 * Fs / current_rhythm + 1 > 55 && pathology_signal.SBR > 0)
		{
			pathology_signal.SBR = -1;
			if (pathology_signal.SBR > 4)
				pathology_signal.SBR++;
		}

		if (current_rhythm != 0 && 60 * Fs / current_rhythm >= 100 && R_v.size() > 3)
			pathology_signal.SVTA++;
		else
			pathology_signal.SVTA = 0;

		if (current_rhythm != 0 && 60 * Fs / current_rhythm >= 120 && R_v.size() > 3)
			pathology_signal.VFib++;
		else
			pathology_signal.VFib = 0;


		
		last_peak_for_rhythm = new_point;

		if (new_some_point.second == N_b)
		{
			if (array_of_peak_R.size() > 2)
			{
				average_R += (*(array_of_peak_R.end() - 1) - *(array_of_peak_R.end() - 2));
				average_R /= 2;
			}
			if (array_of_peak_R.size() == 2)
			{
				average_R = array_of_peak_R.at(1) - array_of_peak_R.at(0);
				//average_R /= 2;
			}

			//Check value bounds of average R 
			if (average_R < 0)
				average_R = abs(average_R);

			if (average_R > 1.7*RR.middle*Fs)
				average_R = static_cast<int>(RR.middle*Fs);

			if (average_R < 0.3*RR.middle*Fs)
				average_R = static_cast<int>(RR.middle*Fs);
		}
	}
}