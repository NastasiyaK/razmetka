


#include "leads.h"
/*
#define COMPARE(sample, type);\
if (sample.second == #type) \
counter.type++;        \

*/
#define COMPARE_TYPES(sample) \
COMPARE(sample,V)  \
COMPARE(sample,SV) \
COMPARE(sample,A)  \


/* there's extrasystoles which are taken from get_extr(). It's need to find useful extrasystoles
and find folowing pathology;The size of the first vector is N_leads. The internal vector is 
the  extrasytoles of cardiointerval. We find the most popular values end assume them to be correct
*/
/*
struct type_counter{
	int V = 0;
	int SV = 0;
	int A = 0;
	void  set_start() {
		V = 0;
		A = 0;
		SV = 0;
	}
};*/



