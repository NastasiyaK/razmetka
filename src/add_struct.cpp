//#include  "stdafx.h"

#include "add_structs.h"
#include <iostream>

void info_for_new_peak::set_is_peak(bool peak_is)
{
	variable_for_new_peak = peak_is;
}
void info_for_new_peak::set_sample(int sample)
{

    if (this->sample == 0)
        this->sample = sample;
    else
	    if ((sample - fusion_window_sec * Fs )>this->sample)
		    this->sample = sample;

}


void info_for_new_peak::increment_time(const float& Fs)
{
	this->Fs = Fs;

	if (variable_for_new_peak)
		time++;
	else
		time = 0;

	if (time > (int)(fusion_window_sec*Fs / 2))
	{
		time = 0;
		COLLECT = true;
	}
};

int info_for_new_peak::get_sample()
{
	return sample;
}

bool info_for_new_peak::get_R_is()
{
	return variable_for_new_peak;
}
bool  info_for_new_peak::get_collect()
{
	return COLLECT;
}
void  info_for_new_peak::set_collect(bool collect)
{
	COLLECT = collect;
}

string pat_to_string(pat_name pat)
{
	switch (pat) {
		case N_b:
			return "N";
		case V_b:
			return "V";
		case SV_b:
			return "SV";
		case VT:
			return "VT";
		case E:
			return "E";
		case WPW:
			return "WPW";
		case A_b:
			return "A_b";
		case AFIBR:
			return "AFIBR";
		case AFl:
			return "AFl";
		case BLOCKII:
			return "BLOCKII";
		case V_T:
			return "V_T";
		case V_B:
			return "V_B";
		case SBR:
			return "SBR";
		case AS:
			return "AS";
		case VFIBR:
			return "VFIBR";
		case SV_T:
			return "SV_T";
		case SV_B:
			return "SV_B";
		case A_T:
			return "A_T";
		case A_B:
			return "A_B";
		default:
			return "No";
	}


}