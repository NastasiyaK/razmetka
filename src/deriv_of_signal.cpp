/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "one lead.h"



void one_lead::deriv_of_signal(double& new_sample) {

	mem_sdvig++;
	//saving signal:new sample - sample of original signal

	if (signal.size() == mem)
	{
		 rotate(signal.begin(), signal.begin() + 1, signal.end());
		*(signal.end() - 1) = new_sample;
		if (mem_sdvig > mem) {
			mem_sdvig -= mem;
			count_iter++;
		}
	}else 
	{
		signal.push_back(new_sample);
	}

	filter(signal, filter_signal, n);

	double dif = 0;
	if (main_peak_in_interval == 'R')
	{
		if (*(filter_signal.end() - 1) < 0)
			push_el(filter_signal_pol, 0., mem);
		else
			push_el(filter_signal_pol, *(filter_signal.end() - 1), mem);
	} else
		{
			if (*(filter_signal.end() - 1) > 0)
				push_el(filter_signal_pol, 0., mem);
			else
				push_el(filter_signal_pol, *(filter_signal.end() - 1), mem);
		}
	if (filter_signal_pol.size() > 2)
	{
		dif = (*(filter_signal_pol.end() - 1) - *(filter_signal_pol.end() - 3))/2;
		push_el(after_diff_signal, dif, mem);
		//print(dif, "dif.txt");
	}

		/*if (filter_signal.size() > 3) {
			dif = (1. / 8)*(-*(filter_signal.end() - 4) - 2 * *(filter_signal.end() - 3) +
				2 * *(filter_signal.end() - 2) + *(filter_signal.end() - 1));
			
		}*/
	
}



void one_lead::filter( vector<double>&input,  vector<double>&output, int order)
{
	static  vector<float> a, b;

	static bool first_loading = 1;
	if (first_loading)
	{
		ifstream input("buter_koef.txt");
		float koef;
		for (size_t i = 0; i <= order; i++)
		{
			input >> koef;
			b.push_back(koef);
		}

		for (size_t i = 0; i <= order; i++)
		{
			input >> koef;
			a.push_back(koef);
		}
		first_loading = 0;
	}
	order = a.size();
	for (int i = 0; i<order + 1; i++)
		z.push_back(0);      // Creates zeros if input z is omitted

	if (a.at(0) != 1) 
	{
		for (int i = 0; i <= order; i++) {
			b.at(i) /= a.at(0);  
			a.at(i) /= a.at(0);
		}
	}
	
	double new_sample = b.at(0) * *(input.end() - 1) + z.at(0);
	
	for (int i = 1; i < order; i++) 
	{
		z.at(i - 1) = b.at(i) * *(input.end() - 1) + z.at(i) - a.at(i) * new_sample;
	}
	
	z.erase(z.end() - 1);
	print(new_sample, "filtered.txt");
	output.push_back(new_sample);

};