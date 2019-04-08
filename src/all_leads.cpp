

#include "All_leads.h"


All_Leads::All_Leads (info_for_new_peak* ptr_info_new_peak, int N)
{

	N_leads = N;
	for (int i = 0; i < 12; i++) {
		temp_leads.push_back(NULL);
	}
	if (N_leads == 1)
		temp_leads[1] = new one_lead(II, N_leads, ptr_info_new_peak);

	if (N_leads == 2) 
	{
		//temp_leads[0] = new one_lead(I, N_leads, ptr_info_new_peak);
		temp_leads[1] = new one_lead(II, N_leads, ptr_info_new_peak);
		temp_leads[10] = new one_lead(v5, N_leads, ptr_info_new_peak);
	}

	if (N_leads == 3) 
	{
		temp_leads[0] = new one_lead(I, N_leads, ptr_info_new_peak);
		temp_leads[1] = new one_lead(II, N_leads, ptr_info_new_peak);
		temp_leads[2] = new one_lead(III, N_leads, ptr_info_new_peak);

	}
	/*
	if (N_leads == 3) {
	temp_leads[8] = new one_lead("aVR", N_leads);
	temp_leads[9] = new one_lead("aVL", N_leads);
	temp_leads[10] = new one_lead(aVF, N_leads);

	}
	*/
	if (N_leads == 5) 
	{
		temp_leads[0] = new one_lead(I, N_leads, ptr_info_new_peak);
		temp_leads[1] = new one_lead(II, N_leads, ptr_info_new_peak);
		temp_leads[2] = new one_lead(III, N_leads, ptr_info_new_peak);
		temp_leads[5] = new one_lead(aVF, N_leads, ptr_info_new_peak);
		temp_leads[6] = new one_lead(v1, N_leads, ptr_info_new_peak);
	}
	/*if (N_leads == 6) {
	temp_leads[0] = new one_lead(I, N_leads);
	temp_leads[1] = new one_lead(II, N_leads);
	temp_leads[2] = new one_lead(III, N_leads);
	temp_leads[3] = new one_lead(aVL,N_leads);
	temp_leads[4] = new one_lead(aVR, N_leads);
	temp_leads[5] = new one_lead(aVF, N_leads);
	}*/

	if (N_leads == 7) 
	{
		temp_leads[0] = new one_lead(I, N_leads, ptr_info_new_peak);
		temp_leads[1] = new one_lead(II, N_leads, ptr_info_new_peak);
		temp_leads[2] = new one_lead(III, N_leads, ptr_info_new_peak);
		temp_leads[3] = new one_lead(aVL, N_leads, ptr_info_new_peak);
		temp_leads[4] = new one_lead(aVR, N_leads, ptr_info_new_peak);
		temp_leads[5] = new one_lead(aVF, N_leads, ptr_info_new_peak);
		temp_leads[6] = new one_lead(v1, N_leads, ptr_info_new_peak);
	}
	if (N_leads == 6) 
	{
		temp_leads[6] = new one_lead(v1, N_leads, ptr_info_new_peak);
		temp_leads[7] = new one_lead(v2, N_leads, ptr_info_new_peak);
		temp_leads[8] = new one_lead(v3, N_leads, ptr_info_new_peak);
		temp_leads[9] = new one_lead(v4, N_leads, ptr_info_new_peak);
		temp_leads[10] = new one_lead(v5, N_leads, ptr_info_new_peak);
		temp_leads[11] = new one_lead(v6, N_leads, ptr_info_new_peak);
	}
	if (N_leads == 12)
	{
		temp_leads[0] = new one_lead(I, N_leads, ptr_info_new_peak);
		temp_leads[1] = new one_lead(II, N_leads, ptr_info_new_peak);
		temp_leads[2] = new one_lead(III, N_leads, ptr_info_new_peak);
		temp_leads[3] = new one_lead(aVL, N_leads, ptr_info_new_peak);
		temp_leads[4] = new one_lead(aVR, N_leads, ptr_info_new_peak);
		temp_leads[5] = new one_lead(aVF, N_leads, ptr_info_new_peak);
		temp_leads[6] = new one_lead(v1, N_leads, ptr_info_new_peak);
		temp_leads[7] = new one_lead(v2, N_leads, ptr_info_new_peak);
		temp_leads[8] = new one_lead(v3, N_leads, ptr_info_new_peak);
		temp_leads[9] = new one_lead(v4, N_leads, ptr_info_new_peak);
		temp_leads[10] = new one_lead(v5, N_leads, ptr_info_new_peak);
		temp_leads[11] = new one_lead(v6, N_leads, ptr_info_new_peak);
	}

};

const int All_Leads::time() 
{
	return count_leads;
}

All_Leads::~All_Leads()
{
	for (int i = 0; i<12; i++)
		delete temp_leads.at(i);
}

one_lead* All_Leads::At(const int i)
{
	return temp_leads.at(i);
}

int All_Leads::get_N_leads()
{
	return N_leads;
};

int All_Leads::get_count_leads()
{
	return count_leads;
}

size_t All_Leads::size()
{
	return temp_leads.size();
}



