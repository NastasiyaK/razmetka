#pragma once
#include "stdafx.h"
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
/*
 * This calss is created for some auxillary information
 * It collects the info about a new peak, about leads,
 * about type of work
 */
class All_Leads;

class leads:protected Leads_Info
{
public:

	All_Leads* all_leads;
	/*S - start with original  signals; D - debugging of R-s; 	*/
	leads(char Type);

	virtual ~leads() {};

	void set_new_peak_info(info_for_new_peak* ptr_info_new_peak);
	void set_all_leads(All_Leads&new_leads);

	template <typename T>
	void print(T& value,  string paths)
	{
		 string path_full = where + paths;
		 ofstream output(path_full,  ios::app);
		 output << value <<  "\n";
	}	
	
protected:	

	info_for_new_peak* ptr_info_new_peak;
	char type;
	storage_of_pathology our_pathology;
	 vector< pair<int, char*> > checked_all_peaks;
	 vector<int> peaks_R;
	double temporal_rhythm, average_R;
	 vector< vector<int>> debug_rhythm;
	 vector<int> extrasystoles;

};


