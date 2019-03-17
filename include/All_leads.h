#pragma once

#include "stdafx.h"
#include "one lead.h"

using namespace std;

class All_Leads {
public:
	friend one_lead;
	
	All_Leads(info_for_new_peak* ptr_info_new_peak, int N);

	const int time();

	virtual ~All_Leads();

	one_lead* At(const int i);

	vector<one_lead*> temp_leads;
	int get_N_leads();
	static int get_count_leads();
	size_t size();
	
private:
	int N_leads;
	static int count_leads;
};
