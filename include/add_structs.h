#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
/*
 * This structs describe all types of the pathologies, which are analyzed and all types of leads
 */
enum pat_name {N_b, V_b, SV_b, VT, E, WPW, A_b, AFIBR, no_AFIBR, VFIBR, no_VFIBR, AFl, SVT, BLOCKII, V_T, V_B, SBR, no_VT,No, AS, A_B,A_T, SV_B, SV_T  };
enum leads_name { I, II, III, aVR, aVL, aVF, v1, v2, v3, v4, v5, v6 };

/*
 * these marks is denoting a containers for using of pathologies
 *
 */
using my_map =  map<int,  pat_name >;
using vector_pair =  vector< pair<int, pat_name> >;


/*
 * The class helps to synchronize the search of peaks and
 * the analyse of rhythm
 */

class info_for_new_peak
{
private:
	int sample = 0;
	bool variable_for_new_peak = 0;
	bool COLLECT = false;
	int time;
	double Fs = 0;
	

public:
	info_for_new_peak(){};
	~info_for_new_peak(){};
	const double fusion_window_sec = 0.3;
	void set_is_peak(bool peak_is);
	void set_sample(int sample);

	void increment_time(const double& Fs);

	int get_sample();

	bool get_R_is();
	bool  get_collect();
	void  set_collect(bool collect);
};


//this stucture for detection of faulty intervals;
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
		

};


//addictinal structures
//this for information of ST
struct segment_ST
{
	int start = 0;
	string type;
	float slope = 0;	
};

//this for information of every wave
struct wave
{
	int peak = 0;
	int start = 0;
	int stop = 0;
	double amplitude = 0;
	
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
