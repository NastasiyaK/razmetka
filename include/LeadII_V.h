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

/*
 * This main class is responsible for analysis of pathologies, a delineation of
 * of different peaks. The ctor obtains a type of main lead (II or v5), pointer to
 * class that cantains info about new peaks, pointer to signal of main lead for these class
 * and pointer to signal of lead v5.
 */

class leadII_V : public Leads_Info
{
public:

    //bool& processing_lead(double& sam, bool&);
    //bool check_last_four_peaks( vector<pair<int,pat_name > > & , const int& );
	//void initialization(char*);
	/*
     * This function gets new peaks from  the objects - leads
     * Then if there is new peaks, the function analyzes the data and
     * makes decision about pathlogies
     */
	void get_new_peaks();



	//There is the object to get info about new peaks
	info_for_new_peak* ptr_info_new_peak;

	
	leadII_V(leads_name type, info_for_new_peak* ptr_info_new_peak, int N_leads, vector<double>* ptr_signal, one_lead* ptr_leadV);
	virtual ~leadII_V();

	// The functions print data into file.txt
	void printing_vector(const  vector<wave>&,  string, int);
	void printing_vector(const  vector<int>&,  string, int);
	void print_all();
	void print_all_pathologies();

	//The function set pointer that points to the vector of the current leads
	void set_all_leads(All_Leads* ptr_leads);

	//to get data
	template <typename T>
	vector<T>* get_peaks(char* type) {
		if (type == "P")
			return P_v;
		else if (type == "R")
			return R_v;
		else if (type == "S")
			return S_v;
		else if (type == "Q")
			return Q_v;
		else if (type == "T")
			return T_v;
		else if (type == "ST")
			return ST_v;
	}

private:
	//The variable stores type of wave P (normal or abnormal)
    int peaks_p_norm = 0;
	//the pointer that points to all leads
	All_Leads* ptr_all_leads = nullptr;
	//vector of R peaks only
	vector<int>R_s;
	//to main filtered signal, usual lead II
	vector<double>* ptr_signal;
	//variables for atrial fibrillation finding
	vector<bool> afibr_decision_memory;

	int N_peaks_fibr;

	vector<int>extrasystoles; //for all extrasystoles of lead
	one_lead* leadV;
	//for ventricular flutter list of peaks and the amplitudes
	vector<int>list_extrasys;
	vector<double>list_ampl;
	//the point of sart of pathlogies
	int start_vf;
    vector<int> R_peak_for_fibr;


	/*THis vector stores peaks after collecting data from all leads.
	 *Every pair is the sample of peak and its type
	 */
	vector_pair clean_peaks{  pair<int, pat_name >(0,No) };

	//The function checks type of the extrasystole
	bool check_SV_A_extrasustole( vector<pair<int,pat_name > > & peaks, const int& );

    //to find a start and a stop of peak
	int start_of_R(const int &peak, double otstup, bool type);
    int stop_of_R(const int, bool type);

	//These function checks pathlogies after getting beats
	void check_BlockII( vector<int>&, int );
	void check_Afibr(vector<int> &array_of_RR, const int &last_point);
	void check_WPW( vector<wave>&);
    void allorhythm_lead(vector_pair &, pair<int, pat_name> &);

	//in this fuction decision about pathology of cardiointervals
	void set_pathology( pair<int,  pat_name>&,  vector<int>&);


	//this function for managing of points
	void set_peaks(int&);


	//These functions to find points of cardiointerval
	void finding_of_ST(const int&);
	//These two functions for ST segement
	void slope( vector<double>&, int&);
	void level_of_segment( vector<double>&, const int&);

	int  finding_of_Q(const int&);
	bool finding_of_P(bool&, const int&);
	void finding_of_S(const int&);
	int finding_of_T(const int&);
    void start_T( vector<double>&, int&);

	/*some_sometimes there'ra different type of wave P - it can be as usual, in
	can be inverted or absented - 1,-1 or 0.
	*/

	/*The function obtaines new point and calculates
	 *the rhythm of patient
	 */
	void rhythm(pair <int, pat_name >, vector<int>&);

    /*the function check an existing of sventricular pathologies, because of they change
     * the morphology of ECG sufficently
     */
	bool check_VT();
	bool check_last_four_peaks( vector<pair<int,pat_name > > &, const int& );


};
