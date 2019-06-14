

#include "one lead.h"
#include "LeadII_V.h"
//
void leadII_V::finding_of_S(const int& peak) {

	 string operation = "S";
	int ind, ind2, ind_vn, max_value;
	ind2 = peak + static_cast<int>(((QRS.height)*Fs) / 2);
	ind = peak;
	set_indices(ind_vn, ind, ind2, *count_iter, mem, *mem_sdvig);
	if (ind >= 0 && ptr_signal->size() > ind2) {

		 vector <float> bufer;
		copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
		S.peak =  distance(bufer.begin(),  min_element(bufer.begin(), bufer.end()));
		S.amplitude = bufer.at(S.peak);
		auto  t =  max_element(bufer.begin() + S.peak, bufer.end());
		max_value =  distance(bufer.begin(), t) + ind_vn;

		 for_each(bufer.begin(), bufer.end(), [](float &n) { n = n*(-1); });

		S.stop = stop_of_peak(bufer, ind_vn, operation);
		S.peak = S.peak + ind_vn;
		if (max_value < S.stop)
			S.stop = max_value;
		push_el(S_v, S, n_peaks);
	}
}
