#pragma once
#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "Leads_info.h"
#include "add_structs.h"
#include "functions.h"
#include "pat_storage.h"
#include "All_leads.h"


class leadII_V : public Leads_Info
{
public:
	void get_new_peaks();
	info_for_new_peak* ptr_info_new_peak;

	
	leadII_V(leads_name type, info_for_new_peak* ptr_info_new_peak, int N_leads, vector<double>* ptr_signal, one_lead* ptr_leadV);

	virtual ~leadII_V();

	void printing_vector(const  vector<wave>&,  string, int);
	void printing_vector(const  vector<int>&,  string, int);

	bool& processing_lead(double& sam, bool&);
	void set_all_leads(All_Leads* ptr_leads);

private:
    int peaks_p_norm = 0;
	bool check_SV_A_extrasustole( vector<pair<int,pat_name > > & peaks, const int& );
	bool check_last_four_peaks( vector<pair<int,pat_name > > & , const int& );
	void print_all();
	vector_pair clean_peaks{  pair<int, pat_name >(0,No) };
	int start_of_R(const int &peak, double otstup, bool type);
	 vector<int>R_s;
	 vector<double>* ptr_signal;
	All_Leads* ptr_all_leads = nullptr;
	void print_all_pathologies();
	//void initialization(char*);
	void check_BlockII( vector<int>&, int );
	void check_Afibr( vector<int>&);
	void check_WPW( vector<wave>&);

	//in this fuction decision about pathology of cardiointervals
	void set_pathology( pair<int,  pat_name>&,  vector<int>&);

	//variables for atrial fibrillation finding
	 vector<bool> afibr_decision_memory;

	int N_peaks_fibr;

	 vector<int>extrasystoles; //for all extrasystoles of lead

								   //this function for managing of points 
	void set_peaks(int&);

	//finding

	void finding_of_ST(const int&);
	void slope( vector<double>&, int&);
	void level_of_segment( vector<double>&, const int&);

	int  finding_of_Q(const int&);
	bool finding_of_P(bool&, const int&);
	void finding_of_S(const int&);
	int finding_of_T(const int&);
	int stop_of_R(const int, bool type);

	/*some_sometimes there'ra different type of wave P - it can be as usual, in
	can be inverted or absented - 1,-1 or 0.
	*/
	
	one_lead* leadV;
	void start_T( vector<double>&, int&);
	void rhythm(pair <int, pat_name >, vector<int>&);
	

	//for ventricular flutter
	 vector<int>list_extrasys;
	 vector<double>list_ampl;
	int start_vf;

	bool check_VT();

};
