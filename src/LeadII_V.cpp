
#include "LeadII_V.h"

leadII_V::leadII_V(leads_name type, info_for_new_peak* ptr_info_new_peak, int N_leads, vector<float>* ptr_signal, one_lead* ptr_leadV)
{
	this->N_leads = N_leads;
	type_of_lead = type;
	count = 0;
	last_peak_for_rhythm = 0;
	average_R = static_cast<int>(RR.middle*Fs);
	this->ptr_info_new_peak = ptr_info_new_peak;
	this->ptr_signal = ptr_signal;
	leadV = ptr_leadV;
	//signal = *ptr_signal;

};

leadII_V:: ~leadII_V() 
{
	
	print_all_pathologies();
	delete mem_sdvig;
	delete count_iter;
	
};

void leadII_V::set_all_leads(All_Leads* ptr_leads)
{
	ptr_all_leads = ptr_leads;
};