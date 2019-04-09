# pragma once

using  namespace std;

struct list_of_output_pathlogies {
    list_of_output_pathlogies(){};
    ~list_of_output_pathlogies()
    {
        delete[] data;
    };

    unsigned int V_beat = 0;    //<several beats, their number
    unsigned int SV_beat = 0;
    unsigned int A_beat = 0;

    ///pathologies which is existing or not

    bool WPW    = false;
    bool VT     = false;
    bool SVTA   = false;
    bool AFIBR  = false;
    bool Afl    = false;
    bool BlockII= false;
    bool SBR    = false;
    bool VFl    = false;

    bool V_T    = false;
    bool V_B    = false;
    bool SV_T   = false;
    bool SV_B   = false;
    bool A_T    = false;
    bool A_B    = false;

    int* data = nullptr;


};