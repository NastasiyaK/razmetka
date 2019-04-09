/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.62499
 */


#include "one lead.h"
#include "LeadII_V.h"


bool value_ok(const int& ind,const int& size){
    return(ind>0 && ind<size);   
};
#define  SHIFT_POINT(ptr_signal);  \
while (start_R<type_of_finding*ptr_signal->size()-1 && value_ok(start_R+2,ptr_signal->size())  \
&&  abs(type_of_finding*ptr_signal->at(start_R) - isolinia_here)>= abs(type_of_finding*ptr_signal->at(start_R + 2) - isolinia_here)) \
	start_R++;\


/*To find start of R peak we catch max and min,then approximate the straight line. 
 *With a stop of peak logic is the same  */


/*The fuction has some some modes - For original and filtered signal/ The first is used for  peak R only. 
The second - for all peaks (extrasystoles and peaks R). 
It depends on variable type. If 0 - original signal,else filtered

Other modes is for different type of finding. Some leads have main peak S. So start and stop we find in reversed
signal to not make new method 

It depends from variable main peak. It can be S or R. Signal is reversed or not.
*/
int Leads_Info::start_of_R(const int &peak, float otstup, bool type, vector<float> *use_signal)
{
ptr_signal = &signal;
 vector<float>bufer;
int ind,ind2,ind_vn;
ind = peak - static_cast<int>(QRS.height*Fs/2);
ind2 = peak;
int start_R = 0;
set_indices(ind_vn,ind,ind2,count_iter,mem,mem_sdvig); 
 vector<float>::iterator min_point;
int type_of_finding = 1; // if main_peak S it's necessary to reverse our_signal;
float current_amplitude = filter_signal.at(ind2);

if (ind >=0 && ind2 >0 && ptr_signal->size()>ind2)
{
	float isolinia_here;
	if (!type) 
	{
		isolinia_here = original_isolinia;
		copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
		current_amplitude = ptr_signal->at(ind2);
		
		if (current_amplitude - isolinia_here < QRS_hight_min)
			isolinia_here -= QRS_hight_min;
	}else 
	{
		copy(begin(filter_signal) + ind, begin(filter_signal) + ind2, back_inserter(bufer));
		isolinia_here = isolinia;
		
	}
	
    min_point =  min_element(bufer.begin(),bufer.begin()+bufer.size()/2);
    int min_point_ind = static_cast<int>( distance(bufer.begin(),min_point)+ind_vn);
    float k = (current_amplitude -*min_point)/(peak - min_point_ind);
    float b = current_amplitude - k*(peak);
	float x = (isolinia_here-b)/k;
 
 start_R =static_cast<int>(round(x));
 int start = 0;
 if (start_R<min_point_ind)
     start_R = min_point_ind+1;
 if (start_R>mem)
 {
     start = static_cast<int>(mem_sdvig + (count_iter-1)*mem);
    set_indices(ind_vn,start_R,ind2,count_iter,mem,mem_sdvig);
 }else
 {
     ind_vn = 0;
 }
 if (!type) 
 {
	
	 SHIFT_POINT(ptr_signal);
 }
 else 
 {
	  vector<float>* ptr_filter = &filter_signal;
	 SHIFT_POINT(ptr_filter);
 }
 
 if (!type && (ind2 - start_R) >= static_cast<int> (QRS.height*Fs)/2) 
 {
	 int temp = (ind2 - start_R) - static_cast<int> (QRS.low*Fs)/2;
	 if ((start_R + temp <type_of_finding*ptr_signal->size()) &&
		 (type_of_finding*ptr_signal->at(start_R + temp) - ptr_signal->at(start_R + temp) < 0.1))
		 start_R += temp;
 }
 
start_R+=start;
return start_R;
 }
return start_R;
}
int Leads_Info::stop_of_R(const int peak, bool type)
{

	 vector<float>bufer;
	 vector<float>::iterator min_point;
	int stop_R = 0;
	int ind, ind2, ind_vn;
	ind = peak;
	ind2 = peak + static_cast<int>(Fs*QRS.height);
	set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);
	int type_of_finding = 1;
	if (ind >= 0 && ind2 >0 && signal.size()>ind2) {
		float amplitude = ptr_signal->at(ind);
		float isolinia_here, current_amplitude = filter_signal.at(ind);
		copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
		if (!type)
		{
			isolinia_here = original_isolinia;
			copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
			current_amplitude = ptr_signal->at(ind);
		}
		else {
			copy(begin(filter_signal) + ind, begin(filter_signal) + ind2, back_inserter(bufer));
			isolinia_here = isolinia;

		}
		if (main_peak_in_interval == 'S')
		{
			for (auto& i : bufer)
				i = -i;
			isolinia_here = -isolinia_here;
			current_amplitude = -ptr_signal->at(ind);
			type_of_finding = -1;
		}
		min_point =  min_element(bufer.begin(), bufer.begin() + static_cast<int>(Fs*(QRS.height) / 2));

		auto max_addic =  max_element(min_point, bufer.end());
		if (*max_addic - isolinia_here>0.3 && *max_addic - *min_point>0.15
			&& *max_addic - *min_point<amplitude*0.5)
			min_point =  min_element(max_addic, bufer.end());
		int min_point_ind = static_cast<int>( distance(bufer.begin(), min_point) + ind_vn);
		if (peak == min_point_ind)
			min_point_ind = ind2 + 3;
		float k = (current_amplitude - *min_point) / (peak - min_point_ind);
		float b = current_amplitude - k*(peak);
		float x = (isolinia_here - b) / k;
		stop_R = static_cast<int>(round(x));
		stop_R = (stop_R>0) ? stop_R : ind2;
		stop_R = (stop_R>min_point_ind) ? min_point_ind - 1 : stop_R;
		int start = 0;
		if (peak>mem)
		{
			start = mem_sdvig + (count_iter - 1)*mem;
			set_indices(ind_vn, stop_R, ind2, count_iter, mem, mem_sdvig);
		}
		else
			ind_vn = 0;

		while (value_ok(stop_R, ptr_signal->size() - 1) &&  abs(type_of_finding*ptr_signal->at(stop_R) - isolinia_here)>
			 abs(type_of_finding*ptr_signal->at(stop_R + 1) - isolinia_here) && stop_R<min_point_ind) {
			stop_R++;
		}
		while (value_ok(stop_R, ptr_signal->size()) && stop_R>min_point_ind
			&&  abs(ptr_signal->at(stop_R) - isolinia_here)> abs(ptr_signal->at(stop_R - 1) - isolinia_here)) {
			stop_R--;
		}
		stop_R += start;
		if ( abs(stop_R - peak)>len_R / 2)
			stop_R = peak + static_cast<int>(1.3*Fs*(QRS.height) / 2);
		return stop_R;
	}
	return stop_R;
}


int leadII_V::stop_of_R(const int peak,bool type)
{

 vector<float>bufer;
 vector<float>::iterator min_point;
int stop_R = 0;
int ind,ind2,ind_vn;
ind = peak;
ind2 = peak+ static_cast<int>(Fs*QRS.height);
set_indices(ind_vn,ind,ind2,count_iter,mem,mem_sdvig); 

if (ind >=0 && ind2 >0 && ptr_signal->size()>ind2)
{
    
    copy(begin(*ptr_signal)+ind,begin(*ptr_signal)+ind2,back_inserter(bufer));
	
	float isolinia_here = original_isolinia;
	copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
	float current_amplitude = ptr_signal->at(ind);
	
	
    min_point =  min_element(bufer.begin(),bufer.begin() + static_cast<int>(Fs*(QRS.height)/2));
    
    auto max_addic  =  max_element(min_point,bufer.end());
    if ( *max_addic- isolinia_here>0.3 && *max_addic - *min_point>0.15 
            && *max_addic - *min_point<current_amplitude*0.5)
        min_point =  min_element(max_addic,bufer.end());
    int min_point_ind = static_cast<int>( distance(bufer.begin(),min_point)+ind_vn);
    if (peak == min_point_ind)
        min_point_ind = ind2+3;
    float k = (current_amplitude-*min_point)/(peak - min_point_ind);
    float b = current_amplitude - k*(peak);
    float x = (isolinia_here-b)/k;
    stop_R =static_cast<int>(round(x));
    stop_R = (stop_R>0)?stop_R:ind2;
    stop_R = (stop_R>min_point_ind)?min_point_ind-1:stop_R;
    int start = 0;     
    if (peak>mem)
	{
       start = mem_sdvig + (count_iter-1)*mem;
       set_indices(ind_vn,stop_R,ind2,count_iter,mem,mem_sdvig); 
	} else 
        ind_vn = 0;

    while (value_ok(stop_R,ptr_signal->size()-1 )  &&  abs(ptr_signal->at(stop_R)-isolinia_here)>
		 abs(ptr_signal->at(stop_R+1)-isolinia_here) && stop_R<min_point_ind){
       stop_R++; 
    }
 while (value_ok(stop_R,ptr_signal->size()) && stop_R>min_point_ind
        &&  abs(ptr_signal->at(stop_R)- isolinia_here)> abs(ptr_signal->at(stop_R-1)- isolinia_here)){
    stop_R--; 
 }
    stop_R+=start;
    if ( abs(stop_R- peak)>len_R/2)
        stop_R = peak+ static_cast<int>(1.3*Fs*(QRS.height)/2);
return stop_R;
}
return stop_R;
}


int leadII_V::start_of_R(const int &peak, float otstup, bool type)
{

	 vector<float>bufer;
	int ind, ind2, ind_vn;
	ind = peak - static_cast<int>(QRS.height*Fs / 2);
	ind2 = peak;
	int start_R = 0;
	set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);
	 vector<float>::iterator min_point;
	//int type_of_finding = 1; // if main_peak S it's necessary to reverse our_signal;
	
	if (ind >= 0 && ind2 >0 && ptr_signal->size()>ind2)
	{
		float isolinia_here = original_isolinia;
		copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
		float current_amplitude = ptr_signal->at(ind2);


		min_point =  min_element(bufer.begin(), bufer.begin() + bufer.size() / 2);
		int min_point_ind = static_cast<int>( distance(bufer.begin(), min_point) + ind_vn);
		float k = (current_amplitude - *min_point) / (peak - min_point_ind);
		float b = current_amplitude - k*(peak);
		float x = (isolinia_here - b) / k;

		start_R = static_cast<int>(round(x));
		int start = 0;
		if (start_R<min_point_ind)
			start_R = min_point_ind + 1;
		if (start_R>mem)
		{
			start = static_cast<int>(mem_sdvig + (count_iter - 1)*mem);
			set_indices(ind_vn, start_R, ind2, count_iter, mem, mem_sdvig);
		}
		else
		{
			ind_vn = 0;
		}
		while (start_R<ptr_signal->size() - 1 && value_ok(start_R + 2, ptr_signal->size())  
			&&  abs(ptr_signal->at(start_R) - isolinia_here) >=  abs(ptr_signal->at(start_R + 2) - isolinia_here)) 
			start_R++;


		if (!type && (ind2 - start_R) >= static_cast<int> (QRS.height*Fs) / 2)
		{
			int temp = (ind2 - start_R) - static_cast<int> (QRS.low*Fs) / 2;
			if ((start_R + temp <ptr_signal->size()) &&
				(ptr_signal->at(start_R + temp) - ptr_signal->at(start_R + temp) > 0.1))
				start_R += temp;
		}

		start_R += start;
		//if (start_R < min_point_ind)
		//	start_R = min_point_ind;
		return start_R;
	}
	return start_R;
}

