#include "stdafx.h"
#include "Afib.h"

bool AFibr::decision(const float& se,const float& rmssd){  
    
float thr_rmssd = 0.0f;
thr_se= 0.76f;
thr_tpr = 0.02f;
thr_rmssd = 0.19f;
float tpr_ratio = u_tp_actual/(128-16-2);
if ((tpr_ratio > thr_tpr) && (se>thr_se) && (rmssd> thr_rmssd))
    return 1;
return 0;
}

