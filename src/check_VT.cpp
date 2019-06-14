

#include "LeadII_V.h"

bool leadII_V::check_VT()

{
	bool new_des = false;
	static bool old_des = false;
	int count_VT_is = 0;
	bool des;
	
	for (int _i = 0; _i < 12; _i++)
	{
		if (ptr_all_leads->At(_i) != nullptr)
		{
			
			des = ptr_all_leads->At(_i)->get_VF("VF");
			if (old_des )
			{
				int res_temp = ptr_all_leads->At(_i)->get_VF("sample");
				if (res_temp != 0)
					start_vf = res_temp;
			}
			if (des)
			{
				count_VT_is++;
				
			}
		}

	}
	
	if (count_VT_is > N_leads / 2)
	{
		new_des = true;
	}
	else
	{
		if (old_des)
		{
			
			if (start_vf < count && start_vf != 0)
			{
				cout << "start VF: " << start_vf << " end VF"<< count <<endl;
				path_mathods.insert(pathologies, start_vf, VFIBR, n_peaks);
				path_mathods.insert(pathologies, count, no_VFIBR, n_peaks);
				print(start_vf, count, "V_diapazon.txt");
				
			}
		}
	}
	
	old_des = new_des;
	return new_des;
}