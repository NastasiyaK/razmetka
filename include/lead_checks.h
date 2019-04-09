#pragma once

#include "add_structs.h"

/**
 * @brief This additional class saves average values
 * of variables and calculates average value
 */

class average_value
{
private:
	
	//for analysis used last 3 number
	const size_t N = 3;
	float* list_value = new float[N];
	float sum = 0.f;
	int  place = 0;
	

public:

	average_value() {};
	virtual ~average_value();

	///to add values for calculating
	void set(float);

	/// set value firstly
	void set_start_value(float);
	///get an average value
	float get();

};