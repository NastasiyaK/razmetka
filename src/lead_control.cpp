#include "All_leads.h"
#include "leads.h"



leads::leads()
{

	average_R = RR.middle*Fs;
};

void leads::set_new_peak_info(info_for_new_peak* ptr_info_new_peak)
{
	this->ptr_info_new_peak = ptr_info_new_peak;
}


void leads::set_all_leads(All_Leads&new_leads)
{
	all_leads = &new_leads;
}