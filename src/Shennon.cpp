/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <map>
#include "Afib.h"
#include <math.h>

 map<float,int> hist(const  vector<float>&, const int&);
float AFibr::shannonEntropy( vector<int>& signal,const int& window_size){
    
    //Set constant calculation parameters
    int bin_size = 16;
    //Create vector for signal without outliers
     vector<float> signal_minus_outliers;

    for (auto i:signal)
        signal_minus_outliers.push_back(static_cast<float>(i));
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

    //Remove outliers
    for (int i =signal_minus_outliers.size()-1;i>=0;i--)
        if (signal_minus_outliers.at(i)==0)
            signal_minus_outliers.erase(signal_minus_outliers.begin()+i);
    //Calculate histogram bins
     map<float,int> h = hist(signal_minus_outliers, bin_size);

    //Create empty vector for bin probabilities
     vector<float>probabilities;
    //Calculate probability of each bin
    for ( pair<float,int> i:h){
        probabilities.push_back((float)i.second/(window_size - bin_size));
    }
    //Initialize shannon entropy
    float se = 0;
    //Calculate shannon entropy
    
    for (int n =0 ;n<bin_size;n++){
    if (probabilities.at(n) != 0)
            se += probabilities.at(n) * (log(probabilities.at(n))/log(1.0f/16));
    }
    return se;
}

    
 map<float,int> hist(const  vector<float>& signal_minus_outliers, const int& bin_size){
auto max =  max_element(signal_minus_outliers.begin(),signal_minus_outliers.end());
auto 

min =  min_element(signal_minus_outliers.begin(),signal_minus_outliers.end());
float duration = (*max - *min)/bin_size;
 map<float,int> hist;
float d = *min+(duration)/2;
for (int i = 0;i<bin_size;i++){
    hist[d] = 0;
    d+=duration;
}

for (size_t i = 0;i< signal_minus_outliers.size();i++){
    for ( pair<float,int>j:hist){
        //if (signal_minus_outliers.at(i)==*max)
        if (j.first+duration/1.7>=signal_minus_outliers.at(i) && 
                j.first-duration/1.7<=signal_minus_outliers.at(i)  )
            hist[j.first]++;
    }   

}

return hist;
};