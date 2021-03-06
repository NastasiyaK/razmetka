#pragma once


#include <algorithm>
#include "add_structs.h"
#include "ouput_struct_of_pathlogies.h"
#include "pat_storage.h"
using namespace std;




//vector<int> checking_of_lost_peaks(const  vector<int>&, const int&, float);
/**
 *  @brief merges peaks in the case of ventricular flutter.
 * the peaks from one vector are inserted to other vector.
 * @param main_peaks - it is a vector which should be changed
 * @param odd_peaks - it is vector which cantains new values
 * @param start - it is the point which is start to changes
 * @remark for ventricular flutter only
 */
void to_merge_peaks(vector< pair<int, pat_name>>*main_peaks,  vector<int>* odd_peaks, int start);


/**
 * @brief determines the start of this pathology
 * @details The function change start of ventricular flutter because of usually ventricular complexes
 * are found before start of pathology
 * @param start_VF  - found start of ventricular flutter.
 * @param average_interval - current average RR interval
 */
int start_severe_distortion(vector<int> *extrasystoles, vector<int> *R_peaks, const int &start_VF,
                            const int &average_interval);

///The function checks indixes
bool value_ok(const int& ind,const int&);

///The additional function changes type of beat in the vector of beats.
void change_type_in_all_peak( vector<  pair<int, pat_name> >&, pat_name, const int&, const float);

pair<float,float> getApprox(const vector<int>& index,const vector<float>& signal, int num_of_points, int& peak);

///These functions erase wrong data from index to end
 void erase(vector<wave>*, const int index);
 void erase(vector<int>*, const int index );
 void erase(vector<segment_ST>*, const int index);


bool find_VT(const vector<pair<int, pat_name>>& peaks_with_types, float Fs);

 ///The function returns an absolute value of vector
template <typename T>
 vector <T> abs(const  vector <T>& v)
 {
	 vector <T> new_v;
	new_v.reserve(v.size());
	for (auto i : v)
		new_v.push_back( abs(i));
	return new_v;
}
///These functions push new elements into storage
template <typename T>
void push_el( vector <T>&v,const T new_el, const size_t n_peaks) 
{
	
	if (v.size()< n_peaks) {
		v.push_back(new_el);
	}
	else {
		 rotate(v.begin(), v.begin() + 1, v.end());
		v.at(n_peaks - 1) = new_el;
	}
}

void push_el( vector <  pair<int,  pat_name >> &, const  pair<int,  pat_name>&, const size_t);
void push_el( vector <  pair<int, pat_name >> &,int, pat_name , const size_t);


//They change indexes to find them in the storage
int set_indices(int, int&, size_t&,  int&);
void set_indices(int&, int&, int&, int&, size_t&, int&);

/**
 * @brief creates list of pathologies for output
 * @param int index_start_wave_copy is the last possible point in the storage
 * @param pathologies is a storage of pathology
 * @list is a structure which stores info about apthlogies for output
 */

list_of_output_pathlogies& create_list_of_pathlogies(unsigned int index_start_wave_copy, my_map& pathologies, list_of_output_pathlogies& list );

/**
 * @brief sometimes it is easy to make a Ventricular extrasystole as others.
 * @param delta  - for finding minimum
 * @return decision of forme of peak
 */
bool check_diffic_ventr(vector<float >* signal, const int& peak2, float delta);


/**
 * @brief This awful function explores outliers in the signal near peak and counts a number of
 * peaks that cross a threshold which contains in the space razmetka.
 *
 * @param QRS_length - the parameter provides estimates for duration between extremums
 * @param QRS_amplitude  - in the case of splitting QRS
 * @return a decision about aoutliers
 */
bool casual_outliers(vector<float>* signal, const size_t peak, const int QRS_length, const float QRS_amplitude, const int diff_last);