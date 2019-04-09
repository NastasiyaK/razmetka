/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Afib.h"

float AFibr::rootMeanSquareSuccessiveDifferences(const  vector<int>& signal_part){
 vector<float>signal_minus_outliers;
//Find length of signal
for (auto i:signal_part)
    signal_minus_outliers.push_back((float)i);
//signal_minus_outliers = signal_part;
//Identify maximum outliers
for (int n =0 ;n<=7;n++){
     vector<float>::iterator max_min_outl =  max_element(signal_minus_outliers.begin(),signal_minus_outliers.end());
    int max_index = distance(signal_minus_outliers.begin(),max_min_outl);
    signal_minus_outliers.at(max_index) = 0;
}

//Identify minimum outliers
for (int n =0 ;n<=7;n++){
     vector<float>::iterator min_min_outl =  min_element(signal_minus_outliers.begin(),signal_minus_outliers.end());
    int min_index = distance(signal_minus_outliers.begin(),min_min_outl);
    signal_minus_outliers.at(min_index) = 0;
}


for (int i =signal_minus_outliers.size()-1;i>=0;i--)
        if (signal_minus_outliers.at(i)==0)
            signal_minus_outliers.erase(signal_minus_outliers.begin()+i);
int signal_length = signal_minus_outliers.size();

//Initialize rmssd
float rmssd = 0;

//Calculate RMSSD
for (int j = 0;j<(signal_length - 1);j++){
    rmssd = rmssd +  pow(signal_minus_outliers.at(j + 1) - signal_minus_outliers.at(j),2);
}
rmssd /=(signal_length - 1);
rmssd = sqrt(rmssd);
return rmssd;
}
