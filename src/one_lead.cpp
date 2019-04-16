

#include "one lead.h"

one_lead::one_lead(leads_name type, int N_lead, info_for_new_peak* ptr_info_new_peak)
{
	type_of_lead = type;
	count = 0;
	N_leads = N_lead;
	average_R = static_cast<int>(RR.middle*Fs);
	this->ptr_info_new_peak = ptr_info_new_peak;

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

int one_lead::get_VT(char* type_signal)
{
	if (type_signal == "VT")
	{
		if (pathology_signal.VT != 0)
			return start_vf;

		if (pathology_signal.VT == 0)
			return 0;
	}
		return 0;

};
 int one_lead::get_count()const
{
	return count;
}