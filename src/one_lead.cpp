

#include "one lead.h"

one_lead::one_lead(leads_name type, int N_lead, info_for_new_peak* ptr_info_new_peak)
{
	type_of_lead = type;
	count = 0;
	N_leads = N_lead;
	average_R = static_cast<int>(RR.middle*Fs);
	this->ptr_info_new_peak = ptr_info_new_peak;
	list_extrasys.reserve(n_peaks);

};

void one_lead::get_ptr_mem(int** mem_sdvig, int** count_iter )
{
	*mem_sdvig  = new int;
	*count_iter  = new int;
	**mem_sdvig = this->mem_sdvig;
	**count_iter = this->count_iter;
};

vector< pair<int,  pat_name > >* one_lead::get_peaks(const char* peak)
{
	if (peak == "all peaks" || !peaks_with_types.empty())
		return &peaks_with_types;
	return nullptr;
}
vector<int>* one_lead::get_peaks(char peak)
{
	if (peak == 'V')
		return &list_extrasys;
	return nullptr;

}
leads_name one_lead:: get_lead_name() const
{
	return type_of_lead;
}
vector<float>*  one_lead::get_signal(char* type_signal)
{
	if (type_signal == "O")
		return &signal;
	else
		return &filter_signal;

}


int one_lead::get_VF(char* type_signal )
{
	static int answer = 0;
	;
		if (pathology_signal.VFib != 0)
		{
			if (start_vf2 == 1)
			{
				answer = start_vf;
				
			}
		}
		
		if (pathology_signal.VFib == 0)
		{
			if (finish_vf)
			{
				start_vf = 0;
				start_vf2 = 2;
			}
			return 0;
		}
	
	return answer;
	
};
 int one_lead::get_count()const
{
	return count;
}