
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

pair<int,pat_name > min_delta(const vector<pair<int,pat_name > >* data, const int peak){
    pair<int, pat_name> data_min_dalta = make_pair(-peak,No);
	int data_size = data->size();
    for (size_t i = 0; i < min(data->size(),(size_t)6); i++ )
    {
        if (abs(data->at(data_size-1 - i).first - peak) < abs(data_min_dalta.first - peak)) {
            data_min_dalta = data->at(data_size - i - 1);
        }
    }
     return data_min_dalta;
}

#define CHECK_TYPE( type_of_beats,type); \
switch (type) \
{\
    case N_b: \
        type_of_beats.N++;\
        break;\
    case V_b: \
        type_of_beats.V++; \
        break;\
    case SV_b: \
        type_of_beats.SV++; \
        break;\
    case A_b: \
        type_of_beats.A++; \
        break;\
} \




#define CHECK_MAX_TYPES(des) \
CHECK_MAX_TYPE(V,SV,A,N,des) \
CHECK_MAX_TYPE(SV,V,A,N,des) \
CHECK_MAX_TYPE(A,V,SV,N,des) \
CHECK_MAX_TYPE(N,V,SV,A,des) \

#define CHECK_MAX_TYPE(T1,T2,T3,T4,des) \
if (type_of_beats.T1 >= type_of_beats.T2  && type_of_beats.T1 >= type_of_beats.T3 &&  \
type_of_beats.T1 >= type_of_beats.T4) \
des = #T1; \




  pair< int,  pat_name> in_window( vector< deque< pair< int, pat_name> >>& array_of_new_peaks,const int& Fs,int N_leads,float fusion_window_sec)
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
	float sum = 0;

	if (!array_of_new_peaks.empty() && !array_of_new_peaks.at(0).empty())
	{
		NUM_PEAKS = 1;
		sum = array_of_new_peaks.at(0).begin()->first;

		CHECK_TYPE(type_of_beats, array_of_new_peaks.at(0).begin()->second);

		for (size_t i = 1; i < array_of_new_peaks.size(); i++)
		{
			
			if (!array_of_new_peaks.at(i).empty() &&  abs(array_of_new_peaks.at(i).begin()->first - 
				array_of_new_peaks.at(0).begin()->first) < Fs * fusion_window_sec )
			{
				NUM_PEAKS++;
				sum += array_of_new_peaks.at(i).begin()->first;
				if (array_of_new_peaks.at(i).size() == 1)
					array_of_new_peaks.erase(array_of_new_peaks.begin() + i);
				else
					array_of_new_peaks.at(i).pop_front();
				CHECK_TYPE(type_of_beats,array_of_new_peaks.at(0).begin()->second);
			}
			

		}
		array_of_new_peaks.at(0).pop_front();
		sum /= NUM_PEAKS;
		for (int i = array_of_new_peaks.size()-1; i >= 0; i--)
		{
			if (array_of_new_peaks.at(i).size() == 0)
				if (array_of_new_peaks.size() == 1)
					array_of_new_peaks.clear();
				else
					array_of_new_peaks.erase(array_of_new_peaks.begin() + i);
		}

	}
	if ( NUM_PEAKS < _num_of_leads/2 || _num_of_leads < N_leads/2)
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
    static int count_err = 0;
	
	if (!check_VT())
	{
		
		 
		vector< deque< pair<int,  pat_name >>> new_peaks_of_all_leads;
		deque< pair<int,  pat_name >>* new_peaks_ptr = new deque<pair<int,  pat_name >>(5);
		deque< pair<int,  pat_name >> new_peaks = *new_peaks_ptr;
		new_peaks_of_all_leads.reserve(12);
		
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
			for (int i = 0; i < 12; i++)
			{
                if (ptr_all_leads->temp_leads.at(i) != nullptr)
                {
                	static bool get_mem  = true;
                	if (get_mem)
	                {
		                ptr_all_leads->temp_leads.at(i)->get_ptr_mem(&mem_sdvig,&count_iter);
		                //get_mem = false;
	                }
                    leads_name type = ptr_all_leads->temp_leads.at(i)->get_lead_name();

                    vector_pair *ptr_vector_new_peaks = ptr_all_leads->temp_leads.at(i)->get_peaks("all peaks");

                    //because of we take the third peak
                    count_peaks = 3;
                    new_peaks.clear();
                    if (ptr_vector_new_peaks != nullptr && !ptr_vector_new_peaks->empty()) {

                        while (count_peaks <= ptr_vector_new_peaks->size() &&
                               (ptr_vector_new_peaks->end() - count_peaks)->first > (clean_peaks.end() - 1)->first)
                        {

                            if (_last_peak < (ptr_vector_new_peaks->end() - count_peaks)->first &&
                                (abs(_sample_of_new_iteration - (ptr_vector_new_peaks->end() - count_peaks)->first) <
                                 ptr_info_new_peak->fusion_window_sec * Fs / 2 ||
                                 _sample_of_new_iteration > (ptr_vector_new_peaks->end() - count_peaks-1)->first))
                            {
                            	
                                if (type == II && !new_peaks.empty())
                                {
                                    auto info_II = min_delta(ptr_vector_new_peaks, _sample_of_new_iteration);

                                    point_II = info_II.first;
                                    pat_II = info_II.second;
                                }
                                new_peaks.push_front(*(ptr_vector_new_peaks->end() - count_peaks));
                            }
                            count_peaks++;
                        }
                    }


                    if (!new_peaks.empty())
                        new_peaks_of_all_leads.push_back(new_peaks);
                }
            }
			if (!new_peaks.empty())
				_last_peak = (new_peaks.end() - 1)->first;

			//here we're analysing them  - to provide some pathologies.

			int NUM_OF_PEAK = 0;
			int count_while = 0;

            pair< int,  pat_name> type_sample_des = make_pair(0,No);
			while ( (new_peaks_of_all_leads.size() > 0) )
			{
				count_err++;
				//cout << count_err << endl;
				
				count_while++;
				type_sample_des = in_window(new_peaks_of_all_leads, Fs, N_leads, ptr_info_new_peak->fusion_window_sec);


				if (clean_peaks.empty() ||
					!(clean_peaks.empty() && type_sample_des.first > (clean_peaks.end() - 1)->first)) {
                    if (clean_peaks.empty() ||
                        (!clean_peaks.empty() &&
                         (type_sample_des.first - (clean_peaks.end() - 1)->first) > 0.8*(length.T_middle + length.ST_seg + QRS.height/2) * Fs))
                    {
                        if (clean_peaks.size() == 1 && clean_peaks.at(0).first == 0)
                            clean_peaks.clear();

                        if (abs (type_sample_des.first  - point_II ) < ptr_info_new_peak->fusion_window_sec *Fs ) {
							type_sample_des.first = point_II;
							type_sample_des.second = pat_II;

						}
						//bool res_e = check_SV_A_extrasustole( clean_peaks, average_R);

                        rhythm(type_sample_des, R_s);
						//if (res_e)
						//	type_sample_des.second = E;

						
						if ( type_sample_des.second == N_b &&
								clean_peaks.size() > 1  &&  (clean_peaks.end() - 1)->second == N_b ){

							push_el(R_peak_for_fibr,(type_sample_des.first -  (clean_peaks.end() - 1)->first), n_peaks);
						}

                        if ((clean_peaks.end()-1)->second != N_b && type_sample_des.second == V_b &&
                                abs( (clean_peaks.end()-1)->first - type_sample_des.first ) < Fs * RR.middle /3 )
                            *(clean_peaks.end()-1) = type_sample_des;
                        else
                            push_el(clean_peaks, type_sample_des,n_peaks);

                        if (type_sample_des.first !=0) {
                            if (type_sample_des.second == N_b) {
                                if (!R_s.empty())
                                    len_R = abs(*(R_s.end() - 1) - type_sample_des.first);
                                else
                                    len_R = RR.middle * Fs;

                                push_el(R_s, type_sample_des.first, n_peaks);
                            }
                            set_pathology(*(clean_peaks.end() - 1), R_s);
                        }

                    }
                }
			}
		}
	} else 
	{
		if (leadV != nullptr)
		{
			int a = 1;
			// vector<int>* auto_vector = leadV->get_peaks('V');
			//to_merge_peaks(&clean_peaks,auto_vector,start_vf);
			
		}

	}
	print_all();

}