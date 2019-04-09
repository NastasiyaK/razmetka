#pragma once
/*!
 * @brief The class is for detection of atrial flutter.
 *
 * @details If parameters are higher than thresholds, the pathology exists.
 * Statistic methods: RMMSD,Shennon entropy  and turning point ratio.
 * The thereholds are in article:
 * https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=7411055 
 */
#include <algorithm>
#include <numeric>
#include "functions.h"
#include  <numeric>

//we use intervals to find parameters for AFib analysis
class AFibr
{
private:
///these variables are calculating values of parameters
  float u_tp_expected, u_tp_actual, sigma_tp_expected, sigma_tp_real,thr_tpr,thr_se,thr_rmssd;

//Container cantains current RR intervals
 vector<int> RR_len;

public:
    AFibr(){};
    ~AFibr(){};
    /*!
     * The fuction calculates values of Shennon entropy.
     * @param signal is a number of RR-intervals
     * @param window is a window of RR-intervals
     * @return it returns a value of the parameter.
     */

  float shannonEntropy(vector<int>& signal, const int& window);
    /*!
       * The fuction calculate values of turning point Entropy
       * @param signal is a number of RR-intervals
       * @param window is a window of RR-intervals
       * @return it returns a value of the parameter.
       */

  void turningPointRatio(vector<int>& signal, const int& window);

    /*!
       * The fuction calculates values of root Mean Square Successive Differences
       * @param signal is a number of RR-intervals
       * @param window is a window of RR-intervals
       * @return it returns a value of the parameter.
       */
    float rootMeanSquareSuccessiveDifferences(const vector<int>& signal);
  //float rootMeanSquareSuccessiveDifferences(const vector<int>& signal, const int& window);

  ///the function decides there is fibrillation or not
  /**
   * @param se  - the value of Shennon Entropy
   * @param rmssd - the value of root Mean Square Successive Differences
   * @return False - there is not the pathlogy, True - the pathology exists
   */
  bool decision(const float &se,const float& rmssd);

  ///to set intervals for the analysis. Lengths of RR are in indexes, not time.
  void set_RR_int(vector<int> & intervals){
    RR_len = intervals;
  };
    
};

