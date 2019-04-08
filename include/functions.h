#pragma once


#include <algorithm>
#include "add_structs.h"

using namespace std;


/*
 * This fuction merges peaks in the case of ventricular flutter.
 * the peaks from one vector are inserted to other vector.
 */

//vector<int> checking_of_lost_peaks(const  vector<int>&, const int&, float);

void to_merge_peaks(vector< pair<int, pat_name>>*, vector<int>*, int);

//for ventricular flutter
/*
 * The fuction determines the start of this pathology.
 */
int start_severe_distortion(vector<int> *extrasystoles, vector<int> *R_peaks, const int &start_VF,
                            const int &average_interval);
//The function checks indixes
bool value_ok(const int& ind,const int&);

//The additional function changes type of beat in the vector of beats.
void change_type_in_all_peak( vector <  pair<int, pat_name >>&, pat_name, const int&, const double);


//These functions erase wrong data
 void erase(vector<wave>*, const int );
 void erase(vector<int>*, const int);
 void erase(vector<segment_ST>*, const int);

 //The function returns an absolute value of vector
template <typename T>
 vector <T> abs(const  vector <T>& v)
 {
	 vector <T> new_v;
	new_v.reserve(v.size());
	for (auto i : v)
		new_v.push_back( abs(i));
	return new_v;
}
//These functions push new elements into storage
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
int set_indices(int, const int&, size_t&, const size_t&);
void set_indices(int&, int&, int&, const int&, size_t&, const size_t&);

