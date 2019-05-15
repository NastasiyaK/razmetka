

#include "one lead.h"

/*If the distance between adjacent R is more 
 * than average length, check presence of some missing teeth.
 */
 //if rhythm isn't normal, it can be extrasystole

#define ADD_EXRASYS(type,extr)\
if (check_extras(extr)){ \
push_el(array_of_extrasys,extr,n_peaks);\
class_of_sys = type; \
push_el(peaks_with_types,extr,type,n_peaks); \
if (type == V_b){  \
pathology_signal.ventr_comlex++;  \
}else \
pathology_signal.ventr_comlex=0; \
} \


bool one_lead::check_peak()
{

	bool R_is = 0;
	int dist = set_indices(new_peak, count_iter, mem, mem_sdvig);
	
	//start of RR sometimes isn't correct,with diff extra test of R peak
	float diff = 0;
	if (dist - (int)(Fs*QRS.low) > 0) {
		diff = filter_signal.at(dist) - *min_element(filter_signal.begin() + dist - static_cast<int>(Fs*QRS.low),  filter_signal.begin() + dist);
	}

	if (type_of_lead == II)
		int a = 1;
	
	bool outliers = false;
	if ( (average_amplitude.get() > 0.5f || diff >1.5f) && array_of_peak_R.size() > 1)
	{
		int peak1 = set_indices( *(array_of_peak_R.end() - 1), count_iter, mem, mem_sdvig);
		if (last_peak_outlier < *(array_of_peak_R.end() - 1))
		{
			outliers = casual_outliers(&filter_signal, peak1, QRS.low * Fs,
			                           average_amplitude.get(),
			                           diff_last_peak);
			last_peak_outlier = *(array_of_peak_R.end() - 1);
			
		}
	}
	
	if (outliers)
		array_of_peak_R.erase(array_of_peak_R.end()-1);
	cout << min(0.3 * diff_last_peak,0.5)<<endl;
	if (array_of_peak_R.size() !=0 && new_peak - *(array_of_peak_R.end()-1) > 0.8 * (length.T_middle + length.ST_seg + QRS.height/2) * Fs &&
    (diff > 0.35 * average_amplitude.get() || filter_signal.at(dist) >  2 * QRS_hight_min) &&
			filter_signal.at(dist) > 0.8 * QRS_filtered_min && diff > min(0.3f * diff_last_peak,0.45f) // &&
			/*filter_signal.at(dist) > param_limit * average_amplitude.get() */)
	{
		int start_R = start_of_R(new_peak, (Fs * QRS.height) / 2, 1, nullptr);

        if (abs(new_peak - start_R) < Fs * QRS.height/4 )
            int diff = 0;
		
        
		
		//if new_peak hasn't become extrasystole yet, it's normal R beat
		if (new_peak - *(array_of_peak_R.end() - 1) > Fs*QRS.height && diff > QRS_hight_min &&
			 abs(new_peak - start_R) <= 3 * static_cast<int>( (Fs * QRS.height) / 2) && filter_signal.at(dist) > 0.85*QRS_hight_min )
		{

                push_el(array_of_peak_R, (new_peak), n_peaks); //there's normal R beat
                push_el(peaks_with_types, new_peak, N_b, n_peaks);
                R_is = true;
                
                N_count++;
                amplitude_old_peak = amplitude_new_peak;
                QRS_hight_min = amplitude_new_peak / 3;

                if (QRS_hight_min < QRS_filtered_min)
                    QRS_hight_min = QRS_filtered_min;
                if (QRS_hight_min > 3 * QRS_filtered_min )
                    QRS_hight_min =  QRS_hight_min/2;
                R.amplitude = amplitude_new_peak - isolinia;
                R.peak = new_peak;
                //diff_last_peak = diff;
                
			
		}
	}
	
	
	if (array_of_peak_R.size() !=0 && new_peak - *(array_of_peak_R.end()-1) <= Fs * QRS.low &&
	    (diff > 0.4 * average_amplitude.get() || filter_signal.at(dist) >  2 * QRS_hight_min) &&
	    filter_signal.at(dist) > 0.8*QRS_filtered_min)
	{
		int peak0 = set_indices(new_peak, count_iter, mem, mem_sdvig);
		int peak1 = set_indices(*(array_of_peak_R.end()-1), count_iter, mem, mem_sdvig);
		
		if (filter_signal.at(peak0) > filter_signal.at(peak1) )
		{
			*(array_of_peak_R.end()-1) = new_peak; //there's normal R beat
			(peaks_with_types.end()-1)->first = new_peak;
			
		}
		
	}
		return R_is;
	};