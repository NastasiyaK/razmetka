
#include "stdafx.h"
#include "LeadII_V.h"

bool leadII_V::check_VT()

{
	int count_VT_is = 0;
	bool des;
	for (int i = 0; i < N_leads; i++)
	{
		if (ptr_all_leads->At(i) != nullptr)
		{
			des = ptr_all_leads->At(i)->get_VT("VT");
			if (des)
			{
				count_VT_is++;
				start_vf = ptr_all_leads->At(i)->get_VT("sample");
			}
		}

	}
	if (count_VT_is > N_leads / 2)
		return true;
	else
		return false;


}