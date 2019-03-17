#include "stdafx.h"
#include "functions.h"


void new_filter( vector<double>* input_signal,  vector<double>* output_signal)
{
	
	int new_element = 2 * *(output_signal->end() - 1) - *(output_signal->end() - 2) + *(input_signal->end() - 1) -
		2 * *(input_signal->end() - 6) + *(input_signal->end() - 12);
	
	int new_element2 = 32 * *(input_signal->end() - 16) - (*(output_signal->end() - 1) + *(input_signal->end() - 1) -
		- *(input_signal->end() - 16));
}


double derivative_of_filtered_signals( vector<double>* input_signal) 
{
	double new_deriv_element = 0;
	if (input_signal->size() > 3)
	{
		new_deriv_element = (1. / 8)*(-*(input_signal->end() - 4) - 2 * *(input_signal->end() - 3) +
			2 * *(input_signal->end() - 2) + *(input_signal->end() - 1));
		
	}
	return new_deriv_element;
}