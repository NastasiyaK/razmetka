

#include "functions.h"
#include "one lead.h"
#include "Afib.h"
//when it's necessary to clean some time in storage of pathology
void erase_in_range( vector<wave>& v, const int a, const int b) {
	if (v.size()>1)
	{
		int shift = 0;
		 vector<wave>::iterator a1 = v.begin(), b1 = v.begin();
		for (int i = 0; i<v.size() - 1; i++) 
		{
			if (v.at(i).peak > a)
			{
				a1 = v.begin() + i;
				shift++;
			}
			if (v.at(i).peak > b)
			{
				b1 = v.begin() + (i);
				shift++;
			}
		}
		if (b1 == v.begin())
			b1 = v.end();
		else
			b1--;
		if (shift!=0)
		v.erase(a1, b1);
	}
}

template<typename T>
void erase_in_range( vector<T>& v, const T a, const T b) {
	bool A_STOP = 0;
	if (v.size()>2) {
		auto a1 = v.begin() + 1, b1 = v.begin();
		for (size_t i = 1; i<v.size() - 1; i++) 
		{
			if (v.at(i) > a && !A_STOP) 
			{
				a1 = v.begin() + i;
				A_STOP = 1;
			}
			if (v.at(i)>b)
				b1 = v.begin() + (i);
		}
		if (b1 == v.begin())
			b1 = v.end();
		else
			b1--;
		if (a1 == v.begin() + 1)
			a1 = v.end();
		v.erase(a1, b1);
	}
}

void Leads_Info::erase_add(const int a, const int b,  pat_name pat,  pat_name pat2) {
	erase_in_range(array_of_peak_R, a, b);
	erase_in_range(R_v, a, b);
	erase_in_range(P_v, a, b);
	erase_in_range(S_v, a, b);
	erase_in_range(T_v, a, b);
	erase_in_range(Q_v, a, b);
	erase_in_range(array_of_extrasys, a, b);
	erase_in_range(all_extrasys_of_lead, a, b);
	
	path_mathods.erase(pathologies,a, b, pat, pat2);


}