#include "stdafx.h"
#include "one lead.h"
#include "LeadII_V.h"

/*Finding of peak Q. As Q is negative, We reversing Q andfind usual peak
 */


//--------------------------Q - zubez ---------------------------------//
int leadII_V::finding_of_Q(const int& peak){

 string operation  = "Q";
 vector <double> bufer;
int ind,ind2,ind_vn;  
ind =  peak - static_cast<int>(Fs*QRS.height);
ind2 = peak;
set_indices(ind_vn,ind,ind2,count_iter,mem,mem_sdvig); 


if (peak - Fs*(QRS.height/2)>0 && ind>0 && ind2>ind){
	 
      copy(begin(*ptr_signal)+ind,begin(*ptr_signal)+ind2 ,back_inserter(bufer));
	  for_each(bufer.begin(), bufer.end(), [](double &n) { n = n*(-1); });
	 auto wave_peak =  max_element(bufer.begin(), bufer.end());
     Q.start = start_of_peak(bufer,ind_vn,operation);
	 Q.peak =  distance(bufer.begin(), wave_peak) + ind_vn;
	 Q.amplitude = *wave_peak;
}  

push_el(Q_v,Q,n_peaks);

return (Q.start);
}
