/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "one lead.h"
#include "LeadII_V.h"



int leadII_V::finding_of_T(const int& peak){

 vector <float> bufer;
// string operation = "T";
int g1,g2,ind_vn,otstup,start_of_T =0;
float ampl_st_of_T; 
//isolinia here because of there is R beat


//finding of parameters of T   
otstup = average_R;
g1 = peak + static_cast<int>((length.ST_seg + QRS.low)*Fs/2);
g2 = peak + static_cast<int>(otstup*length.QT_perc +Fs*QRS.height/2);            
set_indices(ind_vn,g1,g2,count_iter,mem,mem_sdvig); 

/*we finding of max deviation of bufer
 * if it>0 T>0 else T<0. 
 * futher we find other parameters of peak
 */

if (g1>0 && g2<ptr_signal->size()) 
{
	
    copy(begin(*ptr_signal)+g1,begin(*ptr_signal)+g2,back_inserter(bufer));
     vector<float>temp_new;

	temp_new = abs(bufer);
    auto it =  max_element(temp_new.begin(),temp_new.end()-1);
    char* reversing = "no";

    int it_ind =  distance(temp_new.begin(),it);
	
		if ( bufer.at(it_ind)-isolinia<0)
		{
		 for_each(bufer.begin(), bufer.end(), [](float &n) { n = n*(-1); });
		reversing= "yes";
    }
    T.peak = it_ind+ind_vn;
    T.amplitude = bufer.at(it_ind);
    if (reversing =="yes")
        T.amplitude = -T.amplitude;
	T.amplitude -= isolinia;
    start_T(bufer,ind_vn);
	
    //amplitude(bufer,ind_vn,operation,reversing);

	// stop_T
	float iso = isolinia;
	if (reversing == "yes")
		iso *=(-1);
	
	 vector <float> temp_ar;
	
	int ind_naim = bufer.size() - 1;
	float naim =  abs(iso - *(bufer.end()- 1));
	int count_t = 0;
	
	for (int j = bufer.size() - 2; j > peak; j--) {
		temp_ar.push_back( abs(bufer.at(j) - iso));
		if (temp_ar.at(count_t) <= naim) {
			naim = temp_ar.at(count_t);
			ind_naim = j;
		}
		count_t++;
	}
	T.stop = ind_naim + ind_vn;
    if (T.start - ind_vn<bufer.size())
        ampl_st_of_T = bufer.at(T.start-ind_vn);
    push_el(T_v,T,n_peaks);
}   

return start_of_T;

}


//--------------------------ST-segment ---------------------------------//
/*ST can be curve or as line. if the first and last points is same level, 
 * second - not, St - curve, otherwise ST -line end we find incline
 */
void leadII_V::finding_of_ST(const int& peak){
 vector <float> bufer;
int g1,g2,ind_vn;
//finding of parameters of T 
g1 = peak + static_cast<int>(Fs*(QRS.height/2));
g2 = peak + static_cast<int>(Fs*(QRS.height/2 + length.ST_seg));
set_indices(ind_vn,g1,g2,count_iter,mem,mem_sdvig);  
if (g1 >=0 && g2>g1){
    size_t min_zde=(g2>ptr_signal->size())?ptr_signal->size()-1:g1;
    if(g1<min_zde) {
        copy(begin(*ptr_signal)+g1,begin(*ptr_signal)+min_zde ,back_inserter(bufer));
        level_of_segment(bufer,ind_vn);
        //segment isn't linear - no slope    
        float del1,del2,del3;
        del1 = bufer.at(0);
        del2 =bufer.at(bufer.size()/2);
        del3 = bufer.at(bufer.size()-1);
        int start_ST = start_of_peak(bufer,ind_vn, "length.ST_segment");
        if ((del1 <del2 && del2<del3) || (del1 >del2 && del2>del3) ){
          slope(bufer,ind_vn);
        }else{
         if (!( abs(del1 -del2)<0.1 ||  abs(del2-del3)<0.1 )){
             ST.start = start_ST;
             ST.type = "curve";
         }else{
         slope(bufer,ind_vn);      
        }
        }
		push_el(ST_v, ST, n_peaks);
		
    }
}

}
