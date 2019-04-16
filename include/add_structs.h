#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
///This structure describes all types of the pathologies, which are analyzed and all types of leads
enum pat_name {N_b, V_b, SV_b, VT, E, WPW, A_b, AFIBR, no_AFIBR, VFIBR, no_VFIBR, AFl, SVTA, BLOCKII, V_T, V_B, SBR, no_VT,No, AS, A_B,A_T, SV_B, SV_T  };

///This structure contains all types of leads
enum leads_name { I, II, III, aVR, aVL, aVF, v1, v2, v3, v4, v5, v6 };

/*
 * these marks is denoting a containers for using of pathologies
 *
 */
using my_map =  map<int,  pat_name >;
using vector_pair =  vector< pair<int, pat_name> >;


/**
 * @brief
 * The class helps to synchronize the search of peaks and
 * the analyse of rhythm
 * @details
 * The class contains an index of new peak, permissions to read and set info about new peak and time
 * that runs from last peaks.
 */

class info_for_new_peak
{
private:
	int sample = 0;
	bool variable_for_new_peak = 0;
	bool COLLECT = false;
	int time;
	float Fs = 0;
	

public:

	info_for_new_peak(){};
	~info_for_new_peak(){};

    ///The function set the variable that accounts for existing of new peak
	void set_is_peak(bool peak_is);

	/// The function set the index of new peak
	void set_sample(int sample);

	/// The function incrementes time that runs form last peak. When the time is equal to
	///window, the function can find next peak.
	/// @param Fs - sampling frequency of ECG
	void increment_time(const float & Fs);

	/// The function returns index of new peak
	int get_sample();

	/// The function returns existing of current new peak
	bool get_R_is();
	/// The function returns variable which permits read info
	bool get_collect();
	/// The function changes variable which permits read info
	void set_collect(bool collect);
	//it is length of window, where the scun of new peaks is in different leads.
    const float fusion_window_sec = 0.3;
};


///this stucture for detection of faulty intervals;
struct Signal{

	int VFib = 0;
	int AFIb = 0;
	int AFl = 0;
	int WPW = 0;
	int Asystol = 0;
	int BlockII = 0;
	int ventr_comlex = 0;
	int SBR = 0;
	int VT = 0;
	int SVTA = 0;
	int P_peaks_normal  = 0;


};


//addictinal structures
/// This structure for information of ST
struct segment_ST
{
	int start = 0;
	string type;
	float slope = 0;	
};

//this structure saves information of every wave
struct wave
{
	int peak = 0;
	int start = 0;
	int stop = 0;
	float amplitude = 0;
	
};

/* these two macroses and the fuction change enum type
 * to string for convenience
 *
 * */

#define MAKE_TYPE_LEAD_STRING(type_string, type_of_lead )\
switch ( type_of_lead )  \
{  \
case I: \
	type_string = "I"; \
	break; \
case II: \
	type_string = "II"; \
	break; \
case III: \
	type_string = "III"; \
	break; \
case aVF: \
	type_string = "aVF"; \
	break; \
case aVL: \
	type_string = "aVL"; \
	break; \
case aVR: \
		type_string = "aVR"; \
		break; \
case v1: \
		type_string = "v1"; \
		break; \
case v2: \
		type_string = "v2"; \
		break; \
case v3: \
		type_string = "v3"; \
		break; \
case v4: \
		type_string = "v4"; \
		break; \
case v5: \
		type_string = "v5"; \
		break; \
case v6: \
		type_string = "v6"; \
		break; \
}\


#define StringToPat(des,patho) \
\
if (des == "N")\
    patho = N_b; \
    else if (des == "V")\
        patho = V_b; \
        else if (des == "SV")\
            patho = SV_b; \
            else if (des == "A")\
                patho = A_b; \


string pat_to_string( pat_name );
