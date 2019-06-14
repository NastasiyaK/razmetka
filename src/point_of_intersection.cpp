//
// Created by amantayr on 28.05.19.
//
#include "point_of_intersection.h"
int get_intersection(vector<float>* signal, const int peak, pair<float,float> ab, int otstup, float isolinia)
{
	/*
	 * y = isolinia;
	 *
	x = (y - b)/a
	 y = signal.at(peak)
	 x = peak
	 */
	int x = (signal->at(peak) - ab.second)/ab.first;
	return peak - x;
};