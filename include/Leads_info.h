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

const float low = 0.11;	//100 mc length of QRS
const float height = 0.074;	

};

struct rr
{
	const float low = 1.1;	// 55 low length of RR
	const float height = 0.7;// 80 high length of RR
	const float middle = (low + height) / 2;
};

struct Lengths 
{
float PQ_int = 0.22,
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
	
	int count_iter = 0;
	int mem_sdvig = 0;
public:
	 Leads_Info() {};
	virtual ~Leads_Info() {};

	
protected:
	 vector <  pair<int,  string >> all_peaks_in_lead;
	 
	 //Point out vector of original ECG signal
	 vector<float>* ptr_signal;
	 

	//which lead:I,II,...
	leads_name type_of_lead = None;
	

	const  string where = "Results/";	//for directory with reuslts
	const int n = 6; 					//filter order
	const int n_peaks = 300;			//a number of saving peaks
	const size_t win_fibr = 96; 		// length of window for atrial flutter
	static int N_leads;
	static size_t window, mem;			//window - for ventricular flutter, mem is a number of saving sample of signal
	static float Fs;					//sampling frequency
	char main_peak_in_interval;			//defines the highest peak (module)during cardioibterval - R or S

	//Standart values for an analysis
	qrs QRS;
	rr RR; 
	Lengths length;

	float QRS_hight_min, QRS_height, ampl_P_threshold = 0.05,
		ampl_P_standart, ampl_T_standart, QRS_filtered_min;
	average_value average_amplitude;    //average amplitude of QRS peaks

    //tracking of points
    float  isolinia, amplitude_new_peak, amplitude_old_peak, original_isolinia;
    int last_peak = 0, average_R, ind_of_last_extrasystole = 0;

    vector <float> filter_signal, signal;// vectors with signals
    float last_slope = 0.f;
    
    int count; //awful variable of awful tracking of signal' data
    int N_count = 0;//number of intervals
    int new_peak, len_R, minutes;
    float amplitude_extrasys;
    vector<int> array_of_peak_R;



    //for rhythm
    vector<int>last_points;
    int N_last_points = 0;
    int last_peak_for_rhythm;
    float current_rhythm;
	int sdvig = 0;
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
	
	int  start_of_peak( vector<float>&, const int&, const  string&);
	int stop_of_peak( vector<float>& bufer, const int& start_in_sig, const  string& name);
	
	Signal pathology_signal;
	//pathologies
	my_map pathologies;
	bool  check_extras(const int& new_peak);


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
	
	
	template <typename T>
	void print_diapazon(T& value1, T& value2,  string paths)
	
	{
		string type_string;
		MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);  //make_path(type_string, type_of_lead);
		
		string path_full= where + type_string + "/" + paths;
		ofstream output(path_full,  ios::app);
		output << value1 << " "<<value2<< '\n';
	}

	void print(int,  string, float,  string);

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
