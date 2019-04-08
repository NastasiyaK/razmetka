


#include "leads.h"

#define COMPARE(sample, type);\
if (sample.second == #type) \
counter.type++;        \


#define COMPARE_TYPES(sample) \
COMPARE(sample,V)  \
COMPARE(sample,SV) \
COMPARE(sample,A)  \


/* there's extrasystoles which are taken from get_extr(). It's need to find useful extrasystoles
and find folowing pathology;The size of the first vector is N_leads. The internal vector is 
the  extrasytoles of cardiointerval. We find the most popular values end assume them to be correct
*/
struct type_counter{
	int V = 0;
	int SV = 0;
	int A = 0;
	void  set_start() {
		V = 0;
		A = 0;
		SV = 0;
	}
};




/*
void leads::controle_of_temporal_extrasystoles( vector< vector< pair<int,  string>>> extrasystoles) {
	type_counter counter;
	bool same_size = true;
	
	int min_number_of_extrasystols = extrasystoles.at(0).size();
	for (auto i : extrasystoles) {
		if (i.size() < min_number_of_extrasystols) {
			min_number_of_extrasystols = i.size();
		}
	}
	for (auto i : extrasystoles)
		if (i.size() != min_number_of_extrasystols)
			same_size = false;

	if (min_number_of_extrasystols >= 3) {
		//finding_of_supravent_tac();
	}

	if (same_size) {
		for (auto in_lead_e = 0;in_lead_e<same_size;in_lead_e++)
			for (auto lead_extrasystoles:extrasystoles) {
				counter.set_start();
				COMPARE_TYPES(lead_extrasystoles.at(in_lead_e));
				if (counter.V > counter.SV && counter.SV > counter.A)
					allorhythm(lead_extrasystoles.at(in_lead_e).first,"V ");
				else
					if (counter.SV > counter.V && counter.V > counter.A)
						allorhythm(lead_extrasystoles.at(in_lead_e).first,"SV ");
					else
						allorhythm(lead_extrasystoles.at(in_lead_e).first,"A ");
		}
		
	}
	else
		 cout << "different number of extrasystoles" <<  endl;
	
	
	


}*/