#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>  
#include <numeric>
#include <fstream>
#include <vector>
#include "functions.h"
#include "add_structs.h"
#include  <iomanip>
#include "pat_storage.h"
#include "lead_checks.h"

using namespace std;

/**
 *@file structures contain standart values of several intervals and waves of ECG
 */
struct qrs
{

const double low = 0.11;	//100 mc length of QRS
const double height = 0.074;	

};

struct rr
{
	const double low = 1.1;	// 55 low length of RR
	const double height = 0.7;// 80 high length of RR
	const double middle = (low + height) / 2;
};

struct Lengths 
{
double PQ_int = 0.22,
	   QT_perc = 0.5,
	   P = 0.12,
	   T_middle = 0.2,
	   ST_seg = 0.1,
	   PQ_seg = 0.1;
};
/**
 * @brief The class determines several additional parameters and common functions.
 *
 * @details
 * The fields of the class contain info for finding R,
 * filtering,several windows, the functions that are used in
 * inheritors.
 *
 */
class Leads_Info
{
private:
	

public:
	 Leads_Info() {};
	virtual ~Leads_Info() {};

	
protected:
	//vector<double> derivatived_signal;
    //const double T_length = 0.2;
    //void allorhythm_lead( vector<int>& ,const int,  pat_name);
    //bool check_peak_R(const int&);
    //void erase_add(const int a, const int b,  pat_name pat,  pat_name pat2);

	 vector <  pair<int,  string >> all_peaks_in_lead;


	 //Point out vector of original ECG signal
	 vector<double>* ptr_signal;



	//which lead:I,II,...
	leads_name type_of_lead;
	

	const  string where = "Results/";	//for directory with reuslts
	const int n = 6; 					//filter order
	const int n_peaks = 300;			//a number of saving peaks
	const size_t win_fibr = 96; 		// length of window for atrial flutter
	static int N_leads;
	static size_t window, mem;			//window - for ventricular flutter, mem is a number of saving sample of signal
	static double Fs;					//sampling frequency
	char main_peak_in_interval;			//defines the highest peak (module)during cardioibterval - R or S

	//Standart values for an analysis
	qrs QRS;
	rr RR; 
	Lengths length;

	double QRS_hight_min, QRS_height, ampl_P_threshold = 0.1,
		ampl_P_standart, ampl_T_standart, QRS_filtered_min;
	average_value average_amplitude;    //average amplitude of QRS peaks

    //tracking of points
    double  isolinia, amplitude_new_peak, amplitude_old_peak, original_isolinia;
    int last_peak = 0, average_R, ind_of_last_extrasystole = 0;

    vector <double> filter_signal, signal;// vectors with signals
    size_t mem_sdvig = 0;
    int count_iter = 0, sdvig = 0, count; //awful variable of awful tracking of signal' data
    int N_count = 0;//number of intervals
    int new_peak, len_R, minutes;
    double amplitude_extrasys;
    vector<int> array_of_peak_R;



    //for rhythm
    vector<int>last_points;
    int N_last_points;
    int last_peak_for_rhythm;
    double current_rhythm;

    string class_of_sys;

    //arrays ofpoints
    vector<wave> R_v, P_v, S_v, T_v, Q_v;
    vector<segment_ST> ST_v;
    vector<int>all_extrasys_of_lead;
    wave R, P, S, T, Q;
    segment_ST ST;


    ///for extrasystoles
    //int ind_last_extrasys_old = 0;
   // pat_name old_class_of_sys = No;
    vector<int>array_of_extrasys;	//array for temporal extrasystoles, in this cardiointerval only


    //functions for analysing

	int  start_of_peak( vector<double>&, const int&, const  string&);
	int stop_of_peak( vector<double>& bufer, const int& start_in_sig, const  string& name);

    void start_P( vector<double>&, int&, bool&);
    virtual int start_of_R(const int &, double, bool, vector<double> *use_signal);
    virtual int stop_of_R(const int peak, bool type);

    //pathologies
	my_map pathologies;
	storage_of_pathology path_mathods;
	bool fibr( vector<int>&);
	bool flutter(const vector<int>&,const vector<double>* );
	Signal pathology_signal;



	///checking	amplitudes of last 3 peaks because of second peak can be a random disturbance
	bool check_peak_amplitudes_max(int& first_peak, int& second_peak, int& third_peak);

    ///checking	amplitudes of last 3 peaks because of second peak can be extrasystole with other amplitude
	bool check_peak_amplitudes_min(int& first_peak, int& second_peak, int& third_peak, int type);

	///checks a place of extrasystole comparing with last peak R
	bool check_extras(const int& new_peak);


	/**
	 * @name Print-functions
	 * all functions print some info about lead' data
	 */

	void print( pair<int,  string>& value,  string paths);

	template <typename T>
	void print(T& value,  string paths) 
	
	{
		string type_string;
		MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);  //make_path(type_string, type_of_lead);

		string path_full= where + type_string + "/" + paths;
		 ofstream output(path_full,  ios::app);
		output << value <<  '\n';
	}

	void print(int,  string, double,  string);

	template <typename T, typename T2>
	void print(T& value, T2& second_value,  string paths) 
	{
		 string type_string;
		MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);
		
		//make_path(type_string, type_of_lead);
		 string path_full = where + type_string + "/" + paths;
		 ofstream output(path_full,  ios::app);
		output << value << ": " << second_value << '\n';
	}
	void print(const my_map&, int time_start, int time_stop) const;
	void print( pair<int, pat_name>&) const;

};
