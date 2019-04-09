#pragma once
#include "ouput_struct_of_pathlogies.h"

#include <iostream>
#include <algorithm>
#include <string>
#include "Leads_info.h"
#include "add_structs.h"
#include "functions.h"
#include "pat_storage.h"
#include "All_leads.h"

/**
 * @brief Provides an analysis of pathlogies from all N_leads
 * @details This main class is responsible for analysis of pathologies, a delineation of
 * of different peaks. The c-tor obtains a type of main lead (II or v5), a pointer to
 * a class that contains info about new peaks, a pointer to signal of main lead for these class
 * and pointer to signal of lead v5.
 */

class leadII_V : public Leads_Info
{
public:

    //bool& processing_lead(float& sam, bool&);
    //bool check_last_four_peaks( vector<pair<int,pat_name > > & , const int& );
	//void initialization(char*);
    //bool check_last_four_peaks( vector<pair<int,pat_name > > &, const int& );

	/*
     * This function gets new peaks from  the objects - leads
     * Then if there is new peaks, the function analyzes the data and
     * makes decision about pathlogies
     */
	void get_new_peaks();



	//There is the object to get info about new peaks
	info_for_new_peak* ptr_info_new_peak;

	/**
	 * @param ptr_info_new_peak  - points out to object which stores info about a current new peak
	 * @param N_leads - a number of operating leads
	 * @param ptr_leadV - points out to signal of lead v5
	 * @param type - defines a name of main lead (v5 - for ventricular pathlogies and II  - for atrial)
	 */
	leadII_V(leads_name type, info_for_new_peak* ptr_info_new_peak, int N_leads, vector<float>* ptr_signal, one_lead* ptr_leadV);
	virtual ~leadII_V();

	/// The functions print data into file.txt
	void printing_vector(const  vector<wave>&,  string, int);
	void printing_vector(const  vector<int>&,  string, int);

	/**
	 * @brief prints all data of patient
	 */
	void print_all();
    /**
     * @brief prints all disturbances
     */
	void print_all_pathologies();

	///The function set pointer that points to the vector of the current leads
	void set_all_leads(All_Leads* ptr_leads);

	///to get data of cardiuntervals
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
		return nullptr;
	}

	/**
     * Gets data
     * @return array of QRS (a number of waves)
     */

	vector<wave>* get_R();

	/**
     * Gets data
     * @return array of P (a number of waves)
     */

	vector<wave>* get_P();

	/**
     * Gets data
     * @return array of S (a number of waves)
     */

	vector<wave>* get_S();
	/**
     * Gets data
     * @return array of Q(a number of waves)
     */

	vector<wave>* get_Q();
	/**
     * Gets data
     * @return array of T (a number of waves)
     */

	vector<wave>* get_T();
	/**
     * Gets data
     * @return array of ST (a number of waves)
     */

	vector<segment_ST>* get_ST();
	/**
     * Gets data
     * @return array of structure which contains info about pathlogies
     */

    list_of_output_pathlogies* get_pathlogies();

private:

	///The variable stores type of wave P (normal or abnormal)
    int peaks_p_norm = 0;
	///the pointer that points to all leads
	All_Leads* ptr_all_leads = nullptr;
	///vector of R peaks only
	vector<int>R_s;
	///to main filtered signal, usual lead II
	vector<float>* ptr_signal;
	///variables for atrial fibrillation finding
	vector<bool> afibr_decision_memory;

	int N_peaks_fibr;

	vector<int>extrasystoles; //for all extrasystoles of lead
	one_lead* leadV;
	///for ventricular flutter list of peaks and the amplitudes
	vector<int>list_extrasys;
	vector<float>list_ampl;
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
	int start_of_R(const int &peak, float otstup, bool type);
    int stop_of_R(const int, bool type);

	/**
	 * @brief Check a length of last RR intervals and absence of extrastole
	 */
	void check_BlockII( vector<int>& array_of_RR, int ind_of_last_extrasystole);
	/**
	 * @param array_of_RR is a vector of intervals
	 * @param last_point  is an index of the first R in the first RR interval
	 */
	void check_Afibr(vector<int>& array_of_RR, const int& last_point);
	/**
	 * @brief Checks length of last R peak
	 */
	void check_WPW(vector<wave>& R_peaks);
	/**
	 * @brief Finds allorhythms by comparing types of all peaks and type of new peak
	 */
    void allorhythm_lead(vector_pair& all_peaks, pair<int, pat_name>& new_peak);

	///Makes decisions about pathologies of cardiointervals and operates other methods
	void set_pathology( pair<int,  pat_name>&,  vector<int>&);


	//this function for managing of points for this peak R
	void set_peaks(int& index_of_R);


	//These functions to find points of cardiointerval
	void finding_of_ST(const int&);
	///Finds a slope of ST segment
	void slope( vector<float>& signal, int& start_of_ST);
	///Finds a level of ST
	void level_of_segment( vector<float>& signal, const int& start_of_ST);
    ///Finds peak Q  for peak R (peak)
	int  finding_of_Q(const int& peak);
	///Finds peak P  for peak R (peak) or if otstup is true, finds wave p for absent peak
	bool finding_of_P(bool& otstup, const int& peak);
	///Finds peak S  for peak R (peak)
	void finding_of_S(const int& peak);
	///Finds peak T  for peak R (peak)
	int finding_of_T(const int& peak);
	///Finds start of wave T for peak R (peak) with the point of possible start of peak
    void start_T( vector<float>& peak, int& start_of_peak);


	/**Obtaines a new point and calculates
	 *a rhythm of patient
	 */
	void rhythm(pair <int, pat_name >, vector<int>&);

    /**Check an existing of ventricular pathologies, because of they change
     * the morphology of ECG sufficently
     */
	bool check_VT();



};
