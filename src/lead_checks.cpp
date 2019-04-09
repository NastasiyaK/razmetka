
#include "lead_checks.h"

void average_value::set(float new_value)
{
	list_value[place] = new_value;
	place++;
	if (place == N)
	{
		place = 0;
		sum = 0;
		for (int i = 0; i < N; i++)
			sum += list_value[i];
		sum /= 2*N;
	}

}

float average_value::get()
{
	return sum;
}

void average_value::set_start_value(float start_value)
{
	sum = start_value;
}
average_value:: ~average_value()
{
	delete[] list_value;

}