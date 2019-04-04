#include "stdafx.h"
#include <deque>
#include "leads.h"
#include "All_leads.h"
#include "LeadII_V.h"


struct Type_Of_Beats
{
	int V = 0;
	int SV = 0;
	int N = 0;
	int A = 0;

};


#define CHECK_FIELDS(field,type)   \
if (field == type){ \
type_of_beats.field++; }\

#define CHECK_TYPE( type_of_beats,type); \
switch (type) \
{\
    case N_b: \
        type_of_beats.N++;\
    case V_b: \
        type_of_beats.V++; \
    case SV_b: \
    type_of_beats.SV++; \
    case A_b: \
    type_of_beats.A++; \
} \

//{/*CHECK_FIELDS(V,type) ; \
CHECK_FIELDS(SV,type) ; \
CHECK_FIELDS(N,type) ; \
CHECK_FIELDS(A,type) ;} \*/


#define CHECK_MAX_TYPES(des) \
CHECK_MAX_TYPE(V,SV,A,N,des) \
CHECK_MAX_TYPE(SV,V,A,N,des) \
CHECK_MAX_TYPE(A,V,SV,N,des) \
CHECK_MAX_TYPE(N,V,SV,A,des) \

#define CHECK_MAX_TYPE(T1,T2,T3,T4,des) \
if (type_of_beats.T1 >= type_of_beats.T2  && type_of_beats.T1 >= type_of_beats.T3 &&  \
type_of_beats.T1 >= type_of_beats.T4) \
des = #T1; \




inline  pair< int,  pat_name> in_window( vector< deque< pair< int, pat_name> >>& array_of_new_peaks, int sample_for_window,const int& Fs,int N_leads,double fusion_window_sec)
{
    int NUM_PEAKS = 0;
	int _num_of_leads = 0;
	Type_Of_Beats type_of_beats;
	for (int i = array_of_new_peaks.size() - 1; i >= 0; i--)
	{
		if (array_of_new_peaks.at(i).size() == 0)
			array_of_new_peaks.erase(array_of_new_peaks.begin() + i);
	}
    _num_of_leads = array_of_new_peaks.size();
	double sum = 0;

	if (!array_of_new_peaks.empty() && !array_of_new_peaks.at(0).empty())
	{
		NUM_PEAKS = 1;
		sum = array_of_new_peaks.at(0).begin()->first;

		CHECK_TYPE(type_of_beats, array_of_new_peaks.at(0).begin()->second);

		for (size_t i = 1; i < array_of_new_peaks.size(); i++)
		{
			
			if (!array_of_new_peaks.at(i).empty() &&  abs(array_of_new_peaks.at(i).begin()->first - 
				array_of_new_peaks.at(0).begin()->first) < 2*Fs * fusion_window_sec/3 )
			{
				NUM_PEAKS++;
				sum += array_of_new_peaks.at(i).begin()->first;
				array_of_new_peaks.at(i).pop_front();
				CHECK_TYPE(type_of_beats,array_of_new_peaks.at(0).begin()->second);
			}
			

		}
		array_of_new_peaks.at(0).pop_front();
		sum /= NUM_PEAKS;
		for (int i = array_of_new_peaks.size()-1; i >= 0; i--)
		{
			if (array_of_new_peaks.at(i).size() == 0)
				array_of_new_peaks.erase(array_of_new_peaks.begin() + i);
		}

	}
	if (NUM_PEAKS < _num_of_leads/2 || NUM_PEAKS < N_leads/2-2)
	    sum = 0;
	char* des;
	pat_name patho;
	CHECK_MAX_TYPES(des);
	StringToPat(des,patho);
	return  pair<int, pat_name>(sum,patho);
}


void leadII_V::get_new_peaks()
{


    count = ptr_all_leads->temp_leads.at(1)->get_count();
	if (!check_VT())
	{
		 deque< pair<int,  pat_name >> new_peaks;
		 vector< deque< pair<int,  pat_name >>> new_peaks_of_all_leads;
		static int _last_peak = 0;
		int point_II = 0;
		pat_name pat_II;

		//here to collect new peaks - peaks R and  other beats
		if (ptr_info_new_peak->get_collect() && ptr_info_new_peak->get_R_is())
		{
			//for collection of info only
			ptr_info_new_peak->set_is_peak(false);
			ptr_info_new_peak->set_collect(false);
			int _sample_of_new_iteration = ptr_info_new_peak->get_sample();
			int count_peaks = 1;
			if (abs(_sample_of_new_iteration - _last_peak) > ptr_info_new_peak->fusion_window_sec *Fs / 2 )
			for (int i = 0; i < N_leads; i++)
			{
			    auto type = ptr_all_leads->temp_leads.at(i)->get_lead_name();

				vector_pair* ptr_vector_new_peaks = ptr_all_leads->temp_leads.at(i)->get_peaks("all peaks");

				//because of we take the third peak
				count_peaks = 3;
				new_peaks.clear();
				if (ptr_vector_new_peaks != nullptr && !ptr_vector_new_peaks->empty())
				{

					while (count_peaks <= ptr_vector_new_peaks->size() &&
						(ptr_vector_new_peaks->end() - count_peaks)->first > (clean_peaks.end() - 1)->first)
					{
						//cout << (ptr_vector_new_peaks->end() - count_peaks)->first << endl;
						if (_last_peak < (ptr_vector_new_peaks->end() - count_peaks)->first &&
							( abs(_sample_of_new_iteration - (ptr_vector_new_peaks->end() - count_peaks)->first) <
								ptr_info_new_peak->fusion_window_sec*Fs / 2 ||
								_sample_of_new_iteration > (ptr_vector_new_peaks->end() - count_peaks)->first))
						{
							new_peaks.push_front(*(ptr_vector_new_peaks->end() - count_peaks));
						}
						count_peaks++;
					}
				}

				if (type == II && !new_peaks.empty()) {
					point_II = (new_peaks.end() - 1)->first;
					pat_II = ( new_peaks.end() - 1 )->second;
				}

				if (!new_peaks.empty())
					new_peaks_of_all_leads.push_back(new_peaks);
			}
			if (!new_peaks.empty())
				_last_peak = (new_peaks.end() - 1)->first;

			//here we're analysing them  - to provide some pathologies.

			int NUM_OF_PEAK = 0;
			int count_while = 0;
			while (!new_peaks_of_all_leads.empty())
			{

				count_while++;
				auto type_sample_des = in_window(new_peaks_of_all_leads, _sample_of_new_iteration, Fs, N_leads, ptr_info_new_peak->fusion_window_sec);


				if (clean_peaks.empty() ||
					!(clean_peaks.empty() && type_sample_des.first > (clean_peaks.end() - 1)->first)) {
                    if (clean_peaks.empty() ||
                        (!clean_peaks.empty() &&
                         (type_sample_des.first - (clean_peaks.end() - 1)->first) > (length.T_middle + length.ST_seg) * Fs))
                    {
                        if (clean_peaks.size() == 1 && clean_peaks.at(0).first == 0)
                            clean_peaks.clear();

                        if (abs (type_sample_des.first  - point_II ) < ptr_info_new_peak->fusion_window_sec *Fs ) {
							type_sample_des.first = point_II;
							type_sample_des.second = pat_II;

						}
						//bool res = check_last_four_peaks( clean_peaks, average_R);
						bool res_e = check_SV_A_extrasustole( clean_peaks, average_R);

						//if (!res)
							rhythm(type_sample_des, R_s);
						if (res_e)
							type_sample_des.second = E;

						//R_peak_for_fibr
						if ( type_sample_des.second == N_b &&
								clean_peaks.size() > 1  &&  (clean_peaks.end() - 1)->second == N_b ){

							push_el(R_peak_for_fibr,(type_sample_des.first -  (clean_peaks.end() - 1)->first), n_peaks);
						}

						push_el(clean_peaks, type_sample_des,n_peaks);




                        if (type_sample_des.second == N_b)
                        {
                            if (!R_s.empty())
                                len_R = abs (*(R_s.end() - 1) - type_sample_des.first);
                            else
                                len_R = RR.middle * Fs;

                            push_el(R_s,type_sample_des.first,n_peaks);
                        }
                        set_pathology(*(clean_peaks.end() - 1), R_s);

                    }
                }
			}
		}
	} else 
	{
		if (leadV != nullptr)
		{
			// vector<int>* auto_vector = leadV->get_peaks('V');
			//to_merge_peaks(&clean_peaks,auto_vector,start_vf);
			
		}

	}
	print_all();

}