/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Afib.h"
template <typename T>
float stdev( vector<T>& v) { // накопление квадратов отклонений
   float amean =0; 
amean =  accumulate(v.begin(),v.end(),amean)/v.size();
float sq_sum = 0;
for(auto i:v){
    sq_sum = sq_sum+(i-amean)*(i-amean);
}
sq_sum/=(v.size()-1);
sq_sum = sqrt(sq_sum);
return (sq_sum);
}
 
void AFibr::turningPointRatio( vector<int>& qrs_signal,const int& qrs_len){
//Initialize vector for turning points
 vector<int>tp;
tp.push_back(0);
size_t qrs_length = qrs_signal.size();
//Find turning point 
for (size_t j = 1;j<=(qrs_length - 2);j++){
    if ((qrs_signal.at(j - 1) < qrs_signal.at(j)) &&  (qrs_signal.at(j + 1) < qrs_signal.at(j)))
        tp.push_back(1);
    else if ((qrs_signal.at(j - 1) > qrs_signal.at(j)) &&  (qrs_signal.at(j + 1) > qrs_signal.at(j)))
        tp.push_back(1);
    else
        tp.push_back(0);
}
tp.push_back(0);
//Determine segment length
size_t l = tp.size();

//Determine mean of turning point ratio
u_tp_expected = (2.0f * l - 4) / 3;
u_tp_actual = 0;
u_tp_actual =  accumulate(tp.begin(),tp.end(),u_tp_actual);

//Determine standard deviation of turning point ratio
sigma_tp_expected =  sqrt((16.0f * l - 29) / 90);
sigma_tp_real = stdev(tp);

        
}

