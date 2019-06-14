

#include "one lead.h"
#include "LeadII_V.h"


void leadII_V::start_P( vector<float>& bufer,int& ind_start,bool& lost_R_is){
 vector<float> diff_bufer;
int peak;
size_t start_z = 0;
float max_del,limit_pq;
//finding of peak, its index

peak = P.peak-ind_start;
if (bufer.size()>3){

//find of start (the derivative will be 0.7 of the maximum)
	 vector<float> diff_bufer;
	for (int i = 1; i < bufer.size(); i++) {
		diff_bufer.push_back((bufer.at(i) - bufer.at(0)) / i);
	}
 vector<float>::iterator it =  max_element(diff_bufer.begin(), diff_bufer.end());
max_del = *it;
limit_pq = 0.1*max_del;
//left bound
if (peak > 4)
for (size_t j = 0;j<peak-2;j++){
	if ( diff_bufer.at(j) >limit_pq) {
		if (diff_bufer.at(j + 2) > diff_bufer.at(j)) {
			start_z = j;
			break;
		}
    }
}

float naim =  abs(*(bufer.end()-1) -bufer.at(start_z));
size_t stop_z =bufer.size()-1;
for(size_t j = bufer.size()-2;j>peak;j--){
    if ( abs(bufer.at(j) -bufer.at(start_z))<naim && naim !=0){
       naim = abs(bufer.at(j) -bufer.at(start_z)) ;
       stop_z = j;
    }
}
original_isolinia = bufer.at(start_z);
P.start = start_z + ind_start;
P.amplitude = *( max_element(bufer.begin(), bufer.end())) - bufer.at(start_z);
P.stop = ind_start + stop_z + 2;
}
}


int Leads_Info::start_of_peak( vector<float>& bufer,const int& start_in_sig,const  string& name){
int ind_of_start=0;
 vector<float>::iterator it =  max_element(bufer.begin(),bufer.end());
size_t ind_peak =static_cast<size_t>( distance(bufer.begin(),it));

float min =  abs((isolinia - bufer.at(0)));
for (size_t i = 1;i<ind_peak;i++){
    if (min> abs(bufer.at(i)-isolinia) && min!=0){
        min =  abs(bufer.at(i)-isolinia);
        ind_of_start= i;
    }
}

for (size_t i =ind_peak;i>=1;i--){
    if (min/ abs(bufer.at(i)-isolinia) <=0.1){
        ind_of_start= i;
        break;
    }
}
    
ind_of_start+=start_in_sig;

if (name =="Q"){
   Q.peak =ind_peak+start_in_sig;
   Q.amplitude = -*it - isolinia;
}
return ind_of_start;
}

int Leads_Info::stop_of_peak( vector<float>& bufer,const int& start_in_sig,const  string& name){

int ind_peak =  distance(bufer.begin(), max_element(bufer.begin(),bufer.end()));
int ind_of_stop=ind_peak;
float min =  abs(isolinia - (bufer.at(ind_peak)));
for (int i = ind_peak+1;i<bufer.size();i++){
    if (min> abs(bufer.at(i)-isolinia)){
        min =  abs(bufer.at(i)-isolinia);
        ind_of_stop = i;
    }
}  
if (min != 0){
for (int i = ind_peak;i<bufer.size();i++){
    if (min/ abs(bufer.at(i)-isolinia) <=0.1){
        ind_of_stop= i;
        break;
    }
}
}
ind_of_stop+=start_in_sig;
return ind_of_stop;
}



void leadII_V::start_T( vector<float>& bufer,int& ind_start){
 vector<float> diff_bufer;
int peak, start_z = 0;
float max_del,limit_pq;
//finding of peak

peak = T.peak-ind_start;
if (peak==0)
    peak+=2;
//his index
for (int i = 1; i < bufer.size(); i++) {
	diff_bufer.push_back((bufer.at(i) - bufer.at(0)) / i);
}
 vector <float> abs_diff = abs(diff_bufer);
if (abs_diff.size()>1){
 vector<float>::iterator it =  max_element(abs_diff.begin(),abs_diff.end());
max_del = *it;
limit_pq = 0.05*max_del;
float naim;
//left bound
if (peak  >=diff_bufer.size())
    peak = diff_bufer.size() -1;
naim =  abs(diff_bufer.at(0)-limit_pq);

for (int j = 1;j<=peak;j++){
    if ( abs(diff_bufer.at(j)) >limit_pq){                   
        start_z = j;
    break;
    }
}

naim =  abs(bufer.at(bufer.size()-1) -bufer.at(start_z));
size_t stop_z = 0;
   for(size_t j = bufer.size()-2;j>peak;j--){
       if ( abs(bufer.at(j) -bufer.at(start_z))<naim && naim !=0){
          naim = abs(bufer.at(j) -bufer.at(start_z)) ;
          stop_z = j;
       }

   }

 if (naim !=0){
     stop_z =bufer.size()-1;
   for(size_t j = peak;j<bufer.size()-1;j++){
      if (naim/ abs(bufer.at(j)-bufer.at(start_z))<=0.1){                   
          stop_z = j;
          break;
      }
   }
 }  
 T.start = start_z+ind_start;
}
}
