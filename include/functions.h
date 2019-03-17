#pragma once

#include "stdafx.h"
#include <algorithm>
#include "add_structs.h"

using namespace std;

//for new algorythm
void new_filter( vector<double>*,  vector<double>* );
double derivative_of_filtered_signals(vector<double>*);
void to_merge_peaks(vector< pair<int, pat_name>>*, vector<int>*, int);

//for ventricular flutter
int start_severe_distortion( vector<int>*,  vector<int>*, const int&);
bool value_ok(const int& ind,const int&);
void change_type_in_all_peak( vector <  pair<int, pat_name >>&, pat_name, const int&, const double);

 vector<int> checking_of_lost_peaks(const  vector<int>&, const int&, float);

 void erase(vector<wave>*, const int );
 void erase(vector<int>*, const int);
 void erase(vector<segment_ST>*, const int);

template <typename T>
 vector <T> abs(const  vector <T>& v)
 {
	 vector <T> new_v;
	new_v.reserve(v.size());
	for (auto i : v)
		new_v.push_back( abs(i));
	return new_v;
}

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


//void processing_of_samples(int, struct All_Leads);
int set_indices(int, const int&, size_t&, const size_t&);
void set_indices(int&, int&, int&, const int&, size_t&, const size_t&);

