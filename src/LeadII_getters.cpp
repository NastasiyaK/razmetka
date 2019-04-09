//
// Created by amantayr on 09.04.19.
//

#include "LeadII_V.h"
#include "ouput_struct_of_pathlogies.h"

vector<wave>* leadII_V::get_R(){
    return &R_v;
}

vector<wave>* leadII_V::get_P(){
    return &P_v;
}

vector<wave>* leadII_V::get_S(){
    return &S_v;
}

vector<wave>* leadII_V::get_Q(){
    return &Q_v;
}

vector<wave>* leadII_V::get_T(){
    return &T_v;
}

vector<segment_ST>* leadII_V::get_ST(){
    return &ST_v;
}

list_of_output_pathlogies* leadII_V::get_pathlogies(){
    return get_pathlogies();
}