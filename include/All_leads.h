#pragma once


#include "one lead.h"

/**
 * @brief This class is for storage of all leads and
 * some functions.
 *
 * ptr_info_new_peak provide
 * information of obtained peaks.  N - a number of leads
 */
using namespace std;

class All_Leads {
public:

	friend one_lead;

	///A list of all 12 leads
	vector<one_lead*> temp_leads;

	/**
	 * @param ptr_info_new_peak points out the object that storages info
	 * about current new peak
	 * @param N is a number of operating leads
	 */
	All_Leads(info_for_new_peak* ptr_info_new_peak, int N);
	virtual ~All_Leads();

	///to get time of a lead
	const int time();

	///to get one lead
	one_lead* At(const int i);

	///to get a number of all current leads
	int get_N_leads();

	///get a number of initialized leads
	static int get_count_leads();

	///get number of leads
	size_t size();
	
private:

	///numbers of leads
	int N_leads;

	///numbers of initialized leads
	static int count_leads;
};
