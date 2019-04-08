
#include "one lead.h"
#include "LeadII_V.h"


void leadII_V::set_peaks(int& peak)

{   
	int ind = set_indices(peak, count_iter, mem, mem_sdvig);

	if (ptr_signal->size() > ind && ind > 0)
	{
		bool lost_R_is = 0;

		if (peak - static_cast<int>(Fs*QRS.height) > 0)
		{
			auto supposed_R =  max_element(ptr_signal->begin() + peak - static_cast<int>(Fs*QRS.height),
				ptr_signal->begin() + peak);

			peak = peak +  distance(ptr_signal->begin() + peak, supposed_R);
			amplitude_new_peak = *supposed_R;
			R.peak = peak;

		}
		if (pathology_signal.AFIb == 0 && pathology_signal.VFib == 0)
		{
			finding_of_P(lost_R_is, peak);
			T.start = finding_of_T(peak);
			finding_of_ST(peak);
			Q.start = finding_of_Q(peak);
			finding_of_S(peak);
		}
		int start_p = set_indices(P.start, count_iter, mem, mem_sdvig);
		R.peak = peak;
		R.amplitude = ptr_signal->at(ind) - original_isolinia;
		R.start = start_of_R(peak, 3 * Fs * (QRS.height) / 2, 0);
		R.stop = stop_of_R(peak, 0);
		push_el(R_v, R, n_peaks);

		N_peaks_fibr++;
		int ind = set_indices(R.start, count_iter, mem, mem_sdvig);
		//if (ind > 0 && ind < filter_signal.size())
		//	isolinia = filter_signal.at(ind);
	}

}
