//
// Created by amantayr on 04.03.19.
//
#include "one lead.h"
#include "LeadII_V.h"



bool leadII_V::check_SV_A_extrasustole( vector<pair<int,pat_name > > & peaks, const int& average_interval)

{
    bool result = false;
    if (peaks.size() >= 3) {
        int peak1 = (peaks.end() - 1)->first;
        int peak2 = (peaks.end() - 2)->first;
        int peak3 = (peaks.end() - 3)->first;
        //int peak4 = (peaks.end() - 4)->first;

        size_t count_cur = 0;
        if ((peaks.end() - 2)->second == N_b && (peaks.end() - 1)->second == N_b &&
            (peaks.end() - 3)->second == N_b)
            while (peak2 != 0 && peak3 != 0 && abs(peak2 - peak3) < average_R && (peak1 - peak2) > 0.95 * average_R
                   && static_cast<float>(peak2 - peak3) / (peak1 - peak2) < 0.75 &&
                   peak1 - peak3 < (2 + count_cur / 2.0) * 1.05 * average_R) {
                count_cur++;
                result = true;
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

    return result;
}