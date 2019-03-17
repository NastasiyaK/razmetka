/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "stdafx.h"
//methodss for interactions with storage of pathologis  
#include "pat_storage.h"

void storage_of_pathology::erase(my_map& pathology, pat_name name, int time_threhold)
{
    
	for (auto it = pathology.begin(); it != pathology.end();)
	{
		if (it->second == name && time_threhold<it->first && 
			it->second != VT && it->second != no_VT && it->second != VFIBR && it->second != no_VFIBR) {
			it = pathology.erase(it);
			//++it;
		} else 
		{
			++it;
		}
	}
}

int storage_of_pathology::find(my_map& pathology, const   pat_name& name)const
{

	if (pathology.size()>1){
		auto it = --pathology.end();
		for (it; it != pathology.begin();) {
			if (it->second == name) {
				return (it->first);
			} 
			--it;
		}
	}
	return 0;
}

void storage_of_pathology::push_el(my_map& pathology,const int pat_size, pair<int, pat_name >new_pair)
{
	if (pathology.size() > pat_size)
	{
	   pathology.erase(pathology.begin());
	} 
	pathology.insert(new_pair);
}


void storage_of_pathology::insert(my_map& pathology, int a, pat_name b, const int& n_peaks)
{

	if (b == WPW || pathology.size() == 0 || b == E)
		pathology.insert(pair<int, pat_name>(a, b));
	else
		if (!pathology.empty())
		{
			my_map::iterator it = pathology.end();
			auto k = (--it);
			if (pathology.size() > 1)
			{
				if (k->second != b && (--k)->second != b)
					push_el(pathology, n_peaks, pair<int, pat_name >(a, b));
			}
			else
				if (k->second != b) {
					push_el(pathology, n_peaks, pair<int, pat_name >(a, b));
				}
		}
}

void storage_of_pathology::erase(my_map& pathology, const int a, const int b, pat_name pat, pat_name pat2)
{

	my_map::iterator a1 = pathology.begin(), b1 = pathology.end();
	if (pathology.size() >= 0) {

		ind_f_VF = pathology.end();
		for (auto it = pathology.begin(); it != (pathology.end()); it++)
		{

			if (it->second != pat && it->second != pat2) {
				if (it->first > a)
				{
					a1 = it;
				}
				if (it->first > b && it->second != pat2) {
					b1 = (it);
				}
			}
			else {
				if (a1->first > a && a1->second != pat2) {
					pathology.erase(a1, it);

					a1 = next(it);
				}
			}
			if (it->second == VFIBR || it->second == VT ) {
				if (ind_f_VF == pathology.end())
					ind_f_VF = next(it);
				else {
					pathology.erase(ind_f_VF, it);
					ind_f_VF = next(it);
				}
			}
			if (it->second == no_VFIBR )
				ind_f_VF = pathology.end();
		}
		ind_f_VF = pathology.end();
		if (a1 != pathology.end()) {
			if (a1 == pathology.begin() && !(a1->first > a))
				a1 = pathology.end();
		}
		//int nj = pathology.size();
		auto ab = distance(a1, b1);
		pathology.erase(a1, b1);
		if (pathology.size() > 2)
			b1 = prev(prev(pathology.end()));

		while (pathology.size() > 2 && prev(b1) != pathology.begin() && prev(b1)->second == b1->second) {
			pathology.erase(b1);
			b1 = prev(prev(pathology.end()));
		}
	}
}

void erase(vector<wave>* dirty_vector, const int start_clean)
{
	for (int i = dirty_vector->size()-1; i >= 0; --i)
	{
		if (dirty_vector->at(i).peak >= start_clean)
			dirty_vector->erase(dirty_vector->end()-1);
	}

}

void erase(vector<int>* dirty_vector,const int start_clean)
{
	for (int i = dirty_vector->size()-1; i >= 0; --i)
	{
		if (dirty_vector->at(i) >= start_clean)
			dirty_vector->erase(dirty_vector->end() - 1);
	}

}

void erase(vector<segment_ST>* dirty_vector, const int start_clean)
{
	for (int i = dirty_vector->size()-1; i >= 0; --i)
	{
		if (dirty_vector->at(i).start >= start_clean)
			dirty_vector->erase(dirty_vector->end() - 1);
	}

}