
#include "one lead.h"
#include "LeadII_V.h"

bool leadII_V::finding_of_P(bool& lost_R_is,const int& peak){

 vector <double> bufer;
 vector<double>::iterator it = bufer.begin();
int ind,ind2,ind_vn,otstup;


otstup = (lost_R_is) ? abs( 0.9 * average_R) : 0;

ind = peak  - static_cast<int>(length.PQ_int*Fs + (Fs*QRS.low)/2)-otstup;
ind2 = peak - static_cast<int>((Fs*QRS.height)/2+length.PQ_seg*Fs/2)-otstup;

set_indices(ind_vn,ind,ind2,count_iter,mem,mem_sdvig);

if (ind>0 && ind2>ind)
{
     copy(begin(*ptr_signal)+ind,begin(*ptr_signal)+ind2 ,back_inserter(bufer));
    it =  max_element(bufer.begin(),bufer.end());
    P.peak =  distance(bufer.begin(), it) +ind_vn;
    start_P(bufer,ind_vn,lost_R_is);
	int start_p = set_indices(ind2, count_iter, mem, mem_sdvig);
    P.amplitude =  abs(*it - ptr_signal->at(start_p));
   
     

	if (P.amplitude > ampl_P_threshold) {
		push_el(P_v, P, n_peaks);
        peaks_p_norm++;
		return true;

	}

	 if (P.amplitude < ampl_P_threshold){
         peaks_p_norm = 0;
         flutter(R_s, ptr_signal);
    }
		return false;
}
}

int one_lead::type_of_P(int start_peak) 
{

	int decision = 1;
	 vector <double> bufer;
	 vector<double>::iterator it = bufer.begin();
	int ind, ind2, ind_vn;

	ind = start_peak - static_cast<int>(length.PQ_int*Fs + (Fs*QRS.low) / 2);
	ind2 = start_peak - static_cast<int>((Fs*QRS.height) / 2 + length.PQ_seg*Fs / 2);

	set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);
	copy(begin(signal) + ind, begin(signal) + ind2, back_inserter(bufer));
	 vector<double>temp_new;

	temp_new = abs(bufer);
	auto it_max =  max_element(temp_new.begin(), temp_new.end() - 1);
	decision = 1;

	int it_ind =  distance(temp_new.begin(), it_max);
	if (bufer.at(it_ind) - original_isolinia<0) {
		decision = -1;
	}
	if (abs(bufer.at(it_ind) - original_isolinia < ampl_P_threshold))
		decision = 0;
	if (abs(bufer.at(it_ind) - original_isolinia > ampl_P_standart))
		decision = 2;
	return decision;

}

void one_lead::finding_of_P(const int& peak) 
{

	 vector <double> bufer;
	 vector<double>::iterator it = bufer.begin();
	int ind, ind2, ind_vn;


	ind = peak - static_cast<int>(length.PQ_int*Fs + (Fs*QRS.low) / 2);
	ind2 = peak - static_cast<int>((Fs*QRS.height) / 2 + length.PQ_seg*Fs / 2);

	set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);

	if (ind>0 && ind2>ind)
	{
		 copy(begin(signal) + ind, begin(signal) + ind2, back_inserter(bufer));
		it =  max_element(bufer.begin(), bufer.end());
		original_isolinia = start_P(bufer, ind_vn);
		int start_p = set_indices(ind2, count_iter, mem, mem_sdvig);

	}
	
}

double one_lead::start_P( vector<double>& bufer, int& ind_start)
{
	double original_isolinia = 0;
	 vector<double> diff_bufer;
	size_t start_z = 0;
	double max_del, limit_pq;
	//finding of peak, its index

	int peak =  max_element(bufer.begin(), bufer.end()) - bufer.begin();
	if (bufer.size()>3)
	{

		//find of start (the derivative will be 0.7 of the maximum)
		 vector<double> diff_bufer;
		for (int i = 1; i < bufer.size(); i++) 
		{
			diff_bufer.push_back((bufer.at(i) - bufer.at(0)) / i);
		}
		 vector<double>::iterator it =  max_element(diff_bufer.begin(), diff_bufer.end());
		max_del = *it;
		limit_pq = 0.1*max_del;
		//left bound
		if (peak > 4)
			for (size_t j = 0; j<peak - 2; j++) 
			{
				if (diff_bufer.at(j) >limit_pq)
				{
					if (diff_bufer.at(j + 2) > diff_bufer.at(j)) 
					{
						start_z = j;
						break;
					}
				}
			}

		original_isolinia = bufer.at(start_z);
	}
	return original_isolinia;
}
