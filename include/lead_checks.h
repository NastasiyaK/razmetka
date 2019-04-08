#pragma once

#include "add_structs.h"

/*This additional class saves average values of variables and
 * calculates average value
 */

class average_value
{
private:
	
	//for analysis used last 3 number
	const size_t N = 3;
	double* list_value = new double[N];
	double sum = 0.;
	int  place = 0;
	

public:
	average_value() {};
	virtual ~average_value();
	void set(double);
	void set_start_value(double);
	double get();
};