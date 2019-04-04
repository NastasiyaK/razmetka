#pragma once
/*
 * The class is for detection of atrial flutter.
 * If parameters are higher threshold, it will be pathology. statistic methods
 * :RMMSD,Shennon entropy  and turning point ratio.
 * The thereholds in article:
 * https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=7411055 
 */
#include "stdafx.h"
#include <algorithm>
#include <numeric>
#include "functions.h"
#include  <numeric>

//we use intervals to find parameters for AFib analysis
class AFibr
{
private:
    //these variables are calculating values of parameters
  float u_tp_expected, u_tp_actual, sigma_tp_expected, sigma_tp_real,thr_tpr,thr_se,thr_rmssd;
 vector<int>RR_len;

public:
    AFibr(){};
    ~AFibr(){};
    /*The fuctions calculate values of Shennon entropy,  turning point Entropy and
     * root Mean Square Successive Differences
     */
  float shannonEntropy( vector<int>signal,const int& win);

  void turningPointRatio( vector<int>&,const int& window);

  float rootMeanSquareSuccessiveDifferences(const  vector<int>&,const int&);

  //here we decide there's the pathology or not
  bool decision(const float&,const float&);
  //to set intervals for the analysis
  void set_RR_int( vector<int>& intervals){
  RR_len = intervals;  
  };
    
};

