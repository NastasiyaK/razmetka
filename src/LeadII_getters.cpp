//
// Created by amantayr on 09.04.19.
//

#include "LeadII_V.h"
#include "ouput_struct_of_pathlogies.h"
bool operator<(const wave& v1, const wave& v2) {
    return (v1.peak < v2.peak);
}
bool operator<(const wave& v1, const unsigned int& v2) {
    return (v1.peak < v2);
}

bool operator<(const segment_ST& v1, const segment_ST& v2) {
    return (v1.start < v2.start);
}

bool operator<(const segment_ST& v1, const unsigned int& v2) {
    return (v1.start < v2);
}

vector<wave> leadII_V::get_R(){
    size_t index_start_copy = 0;
    vector<wave> R_v;
    if ((this->R_v.end()-1)->peak - 3 * Fs >0)
       index_start_copy = (this->R_v.end()-1)->peak - 3 * Fs;

    auto lower = lower_bound(this->R_v.begin(), this->R_v.end(),index_start_copy);

    if ( lower != this->R_v.end() && (this->R_v.end()-1)->peak < index_start_copy) {
        R_v.reserve(lower - this->R_v.begin());
        copy(this->R_v.begin(), lower, R_v.begin());

        this->R_v.erase(this->R_v.begin(), lower);
    }
    return R_v;
}
// index_start_wave_copy
vector<wave> leadII_V::get_P(){

    vector<wave> P_v;
    if ((this->P_v.end()-1)->peak - 3 * Fs >0)
        index_start_wave_copy = (this->P_v.end()-1)->peak - 3 * Fs;

    auto lower = lower_bound(this->P_v.begin(), this->P_v.end(),index_start_wave_copy);

    if ( lower != this->P_v.end() && (this->P_v.end()-1)->peak < index_start_wave_copy) {
        P_v.reserve(lower - this->P_v.begin());
        copy(this->P_v.begin(), lower, P_v.begin());

        this->P_v.erase(this->P_v.begin(), lower);
    }

    return P_v;
}

vector<wave> leadII_V::get_S(){
    vector<wave> S_v;
    if ((this->S_v.end()-1)->peak - 3 * Fs >0)
        index_start_wave_copy = (this->S_v.end()-1)->peak - 3 * Fs;

    auto lower = lower_bound(this->S_v.begin(), this->S_v.end(),index_start_wave_copy);

    if ( lower != this->S_v.end() && (this->S_v.end()-1)->peak < index_start_wave_copy) {
        S_v.reserve(lower - this->S_v.begin());
        copy(this->S_v.begin(), lower, S_v.begin());

        this->S_v.erase(this->S_v.begin(), lower);
    }


    return S_v;
}

vector<wave> leadII_V::get_Q(){
    vector<wave> Q_v;
    if ((this->Q_v.end()-1)->peak - 3 * Fs >0)
        index_start_wave_copy = (this->Q_v.end()-1)->peak - 3 * Fs;

    auto lower = lower_bound(this->Q_v.begin(), this->Q_v.end(),index_start_wave_copy);

    if ( lower != this->Q_v.end() && (this->Q_v.end()-1)->peak < index_start_wave_copy) {
        Q_v.reserve(lower - this->Q_v.begin());
        copy(this->Q_v.begin(), lower, Q_v.begin());

        this->Q_v.erase(this->Q_v.begin(), lower);
    }

    return Q_v;
}

vector<wave> leadII_V::get_T(){
    vector<wave> T_v;
    if ((this->T_v.end()-1)->peak - 3 * Fs >0)
        index_start_wave_copy = (this->T_v.end()-1)->peak - 3 * Fs;

    auto lower = lower_bound(this->T_v.begin(), this->T_v.end(),index_start_wave_copy);

    if ( lower != this->T_v.end() && (this->T_v.end()-1)->peak < index_start_wave_copy) {
        T_v.reserve(lower - this->T_v.begin());
        copy(this->T_v.begin(), lower, R_v.begin());

        this->T_v.erase(this->T_v.begin(), lower);
    }
    return T_v;
}

vector<segment_ST> leadII_V::get_ST(){
    vector<segment_ST> ST;
    if ((ST_v.end()-1)->start - 3 * Fs >0)
        index_start_wave_copy = (ST_v.end()-1)->start - 3 * Fs;

    auto lower = lower_bound(this->ST_v.begin(), this->ST_v.end(),index_start_wave_copy);

    if ( lower != ST_v.end() && (ST_v.end()-1)->start < index_start_wave_copy) {
        ST.reserve(lower - ST_v.begin());
        copy(ST_v.begin(), lower, ST_v.begin());

        ST_v.erase(this->ST_v.begin(), lower);
    }

    return ST;
}

list_of_output_pathlogies& leadII_V::get_pathologies(){
    delete[] list.data;
    list = create_list_of_pathlogies(index_start_wave_copy, pathologies, list );
    return list;
}