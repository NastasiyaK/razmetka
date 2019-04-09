#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>                                  
#include <iterator>
#include "one lead.h"
#include "pat_storage.h"
/* type of leads: st I,II,III; aVR,aVL,aVF;
v1,v2,v3,v4,v5,v,v6 */
/**
 * @brief This auxiliary class is created for some information
 * It collects the info about a new peak, about leads,
 */
class All_Leads;

class leads:protected Leads_Info
{
public:

	///point out to objects of all leads
	All_Leads* all_leads;

	leads();
	virtual ~leads() {};


	void set_new_peak_info(info_for_new_peak* ptr_info_new_peak);
	void set_all_leads(All_Leads& new_leads);

	template <typename T>
	void print(T& value,  string paths)
	{
		 string path_full = where + paths;
		 ofstream output(path_full,  ios::app);
		 output << value <<  "\n";
	}	
	
protected:	

	 storage_of_pathology our_pathology; ///Saves pathologies of all leads


	 vector<int> peaks_R;
	 vector<int> extrasystoles;
	 double average_R;
	info_for_new_peak* ptr_info_new_peak;

	//vector< pair<int, char*> > checked_all_peaks;
	//double temporal_rhythm,


};


