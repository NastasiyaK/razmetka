#pragma once
#include "stdafx.h"
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

struct qrs
{
//length
const double low = 0.11;	//100 mc length of QRS
const double height = 0.074;	

};

struct rr
{
	//length
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

class Leads_Info
{
private:
	

public:
	 Leads_Info() {};
	virtual ~Leads_Info() {};

	
protected:
	
	 vector <  pair<int,  string >> all_peaks_in_lead;

	//for new algorythm
	
	 vector<double> derivatived_signal;
	 vector<double>* ptr_signal;


	void start_P( vector<double>&, int&, bool&);
	virtual int start_of_R(const int &, double, bool, vector<double> *use_signal);
	virtual int stop_of_R(const int peak, bool type);

	//which lead:I,II,...
	leads_name type_of_lead;
	

	const  string where = "Results/";
	const int n = 6; //filter order
	const int n_peaks = 300;
	const size_t win_fibr = 96;
	static int N_leads;
	static size_t window, mem;
	static double Fs;
	char main_peak_in_interval;
	const double T_length = 0.2;

	
	//variables for providing the analysis
	qrs QRS;
	rr RR; 
	Lengths length;

	double QRS_hight_min, QRS_height, ampl_P_threshold = 0.1,
		ampl_P_standart, ampl_T_standart, QRS_filtered_min;
	average_value average_amplitude;

	//functions for analysing
	void allorhythm_lead( vector<int>& ,const int,  pat_name);
	int  start_of_peak( vector<double>&, const int&, const  string&);
	int stop_of_peak( vector<double>& bufer, const int& start_in_sig, const  string& name);

	
	//pathologies
	my_map pathologies;
	storage_of_pathology path_mathods;
	bool fibr( vector<int>&);
	bool flutter(const vector<int>&,const vector<double>* );
	Signal pathology_signal;

	
	//tracking of points
	double  isolinia, amplitude_new_peak, amplitude_old_peak, original_isolinia;
	int last_peak = 0, average_R,ind_of_last_extrasystole = 0;
	 vector <double> filter_signal, signal;// , peaks_amplitudes;
	int count_iter = 0, sdvig = 0, count;
	int N_count = 0;//number of intervals
	int new_peak, len_R, minutes;
	double amplitude_extrasys;
	 vector<int> array_of_peak_R;
	size_t mem_sdvig = 0;
	
	
	//for rhythm
	 vector<int>last_points;
	int N_last_points;
	int last_peak_for_rhythm;
	double current_rhythm;


	///for extrasystoles
	int ind_last_extrasys_old = 0;
	 pat_name old_class_of_sys = No;
	 vector<int>array_of_extrasys;	//array for temporal extrasystoles, in this cardiointerval only

	//checking	
	bool check_peak_amplitudes_max(int&, int&, int&,int type);
	bool check_peak_amplitudes_min(int&, int&, int&,int type);
	bool check_peak_R(const int&);
	bool check_extras(const int& new_peak);
	

	 string class_of_sys;
	
	//arrays ofpoints
	 vector<wave> R_v, P_v, S_v, T_v, Q_v;
	 vector<segment_ST> ST_v;
	 vector<int>all_extrasys_of_lead;
	wave R, P, S, T, Q;
	segment_ST ST;


	//additional methods

	void erase_add(const int a, const int b,  pat_name pat,  pat_name pat2);
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
