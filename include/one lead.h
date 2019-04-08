#pragma once

#include <iostream>
#include <string>
#include "Leads_info.h"
#include "add_structs.h"
#include "functions.h"
#include "pat_storage.h"
#include <iostream>
#include <algorithm>

//using namespace std;

//one lead is class to first analysis of signals - to find peaks R or extrasystoles
class one_lead: protected Leads_Info
{
public:
	one_lead(leads_name type, int N_lead, info_for_new_peak* ptr_info_new_peak);
	virtual ~one_lead() {};

	info_for_new_peak* ptr_info_new_peak;
	//for new algorythm
	void new_processing(double);
	
	
	vector< pair<int,  pat_name > >* get_peaks(const char* peak);
	vector<int>* get_peaks(char peak);
	vector<double>* get_signal(char* type_signal);
	int get_VT(char* type_signal);
	
	bool& processing_lead(double& sam, bool&);
	const int get_count() const;
    const leads_name get_lead_name() const;
	int stop_peak(const int , vector<double>*);
private:
	int start_peak(const int & , vector<double> * );
	bool check_ventr_extrasys( vector<double>*, const int&, int&, const int&);

	 vector< pair<int, pat_name>> peaks_with_types;

	bool check_last_four_peaks( vector< int > &, const int& );
	void initialization( leads_name );
	bool set_extrasystole( const int& probably_extrasystole, const int & peak_for_analysis);
	bool finding_of_R(); //true - new peak, false - no new peak;

	void finding_of_P(const int& peak);
	double start_P( vector<double>& bufer, int& ind_start);
	void first_check_of_anormal_RR( vector<int>& array_of_extrasys);

	//variables and functions for  finding R
	const float limit = 0.0002f;//const float limit = 0.05f * 360.0f/Fs;//= 0.25*360/Fs;//sampling frequency //5000 *10   360 *10 no QRS.height,
	 vector <double>  after_diff_signal; 
	int st = 0;
	 vector<double> array_of_pol, vect_of_2part;
	 vector<double>after_filter, in_ECG, filter_signal_pol;
	void deriv_of_signal(double&);
	void filter( vector<double>&,  vector<double>&, int);

	//additional vector for filtering
	 vector<double>z;

	//this functions for cheking of supposed peaks
	bool first_check_peak_S();
	void testing_of_RR();
	bool check_peak();
	void testing_of_SS();
	 vector<int>extrasystoles; //for all extrasystoles of lead

	//finding

	/*some_sometimes there'ra different type of wave P - it can be as usual, in
	can be inverted or absented - 1,-1 or 0.
	*/
	int type_of_P(int start_peak);
	bool ventr_flutter(size_t st_f, const int& len_st);
	//for ventricular flutter
	 vector<int>list_extrasys;
	 vector<double>list_ampl;
	int start_vf = 0;

};

