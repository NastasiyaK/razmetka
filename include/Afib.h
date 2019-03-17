#pragma once
/*
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

//we use intervals to find parameters for AFib analyse
class AFibr
{
private:
  float u_tp_expected, u_tp_actual, sigma_tp_expected, sigma_tp_real,thr_tpr,thr_se,thr_rmssd;
 vector<int>RR_len;
public:
  float shannonEntropy( vector<int>signal,const int& win);

  void turningPointRatio( vector<int>&,const int& window);

  float rootMeanSquareSuccessiveDifferences(const  vector<int>&,const int&);

  //here we decide there's pathology or not
  bool decision(const float&,const float&);
  void set_RR_int( vector<int>& intervals){
  RR_len = intervals;  
  };
    
};

