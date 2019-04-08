

#include "one lead.h"
#include "LeadII_V.h"

#define NAME(name, field);       \
for_mac = name;		    	 \
for_mac +=field;			 \

#define PRINT_WAVE(v,name)				 \
for (int i = dist; i < v.size(); i++) {\
NAME(name,"_peak.txt");\
print(v.at(i).peak, for_mac);		 \
NAME(name, "_start.txt");\
print(v.at(i).start, for_mac); \
NAME(name, "_stop.txt");\
print(v.at(i).stop, for_mac);   \
NAME(name, "_amplitude.txt");\
print(v.at(i).peak, v.at(i).amplitude, for_mac);\
}	



void Leads_Info::print( pair<int,  string>& value,  string paths) {
	 string type_string;
	MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);
	 string path_full = where + type_string + "/" + paths;
	 ofstream output(path_full,  ios::app);
	output << value.first << ": " << value.second << "\n";
}
void Leads_Info::print(int start,  string type, double slope,  string paths) 
{
	 string type_string;
	MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);

	 string path_full = where + type_string + "/" + paths;
	 ofstream output(path_full,  ios::app);
	output << start << ": " << "type " << type << "; slope " <<slope << "\n";
}

void leadII_V::printing_vector(const  vector<wave>& printed_vector, string name, int time_find)
{
	if (!printed_vector.empty()) {
		 string for_mac;
		// ofstream output(path_full,  ios::app);
		 string path = name + ".txt";
		auto i = printed_vector.end() - 1;
		if (printed_vector.size() > 1) {
			while (i !=  next(printed_vector.begin()) && i->peak > time_find) {
				i--;
				if (i->peak < time_find)
					break;
			}
		}
		if (printed_vector.size()!=1 && i != printed_vector.end() - 1)
			i++;

		int dist =  distance(printed_vector.begin(), i);
		if (i->peak >= time_find)
			PRINT_WAVE(printed_vector, name);
	}
}

void leadII_V::print_all_pathologies() {

	 string type_string;
	MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);

	 string path_full = where + type_string+ "/" + "all_pathologies.txt";
	 ofstream output(path_full,  ios::app);
	
		for (auto i = pathologies.begin(); i != pathologies.end(); i++) {

			output << i->first << ", " << pat_to_string(i->second) << '\n';
            output << i->first << ", " << (i->second) << '\n';
		}

}

void leadII_V::printing_vector(const  vector<int>& printed_vector,  string name, int time_find) 
{
	if (!printed_vector.empty()) {
		// ofstream output(path_full,  ios::app);
		 string path = name + ".txt";
		auto i = printed_vector.end() - 1;
		while (i !=  next(printed_vector.begin()) && *i > time_find && i!= printed_vector.begin()) {
			i--;
			if (*i < time_find)
				break;
		}
		int dist =  distance(printed_vector.begin(), i);
		if (i != printed_vector.end() - 1 && *i < time_find)
			i++;
		if (*i >= time_find)
			for (size_t i = dist; i < printed_vector.size(); i++)
				print(printed_vector.at(i), path);
	}
}

void leadII_V::print_all() {
	
	/*in every minute print points
	* in every 5 minutes(wintow = 5 minutes)
	* print pathology
	*/
	count = ptr_all_leads->temp_leads.at(1)->get_count();
	//if (R_s.size()>1 &&
	//	*(R_s.end()-1) - 60 * Fs* 2 * minutes>2*Fs * 60)
	if (count- 60 * Fs* 2 * minutes > 2*Fs * 60)
	{
		
		minutes++;
		int print_min = 2;
		 string path, path_full;
		int time_find = (count - static_cast<int>(1.3 * print_min * 60 * Fs));
        if (time_find < 0)
            time_find = 0;
		
		//printing_vector(array_of_peak_R, "main_peak", time_find);
		//printing_vector(R_v, "R", time_find);
		//printing_vector(P_v, "P", time_find);
		//printing_vector(Q_v, "Q", time_find);
		//printing_vector(S_v, "S", time_find);
		//printing_vector(T_v, "T", time_find);
		//printing_vector(all_extrasys_of_lead, "R", time_find);

		//all peaks
		//cout<<clean_peaks.size() << endl;if (!clean_peaks.empty())
		{
			auto i = clean_peaks.end() - 1;

			while (i !=  next(clean_peaks.begin()) && i->first > time_find) {
				i--;
				if (i->first < time_find)
					break;
			}
			int dist =  distance(clean_peaks.begin(), i);
			if (i != clean_peaks.end() - 1 && i->first < time_find)
				i++;
			if (i->first >= time_find)
				for (size_t i = dist; i < clean_peaks.size(); i++)
					print(clean_peaks.at(i));
		}
		
		//for (auto i:ST_v)
		//	print(ST.start, ST.type, ST.slope, "ST.txt");

		if (!pathologies.empty())
			print(pathologies, count - window, count);
	}
}


void Leads_Info::print(const my_map& paths, int time_start, int time_stop) const {

	auto a1 = paths.begin(), b1 = paths.end();
	for (auto i = paths.begin(); i != paths.end(); i++) {
		if (i->first>time_start)
			a1 = i;
		if (i->first>time_stop)
			b1 = i;
	}
	if (b1 == paths.end() && b1 != paths.begin())
		b1--;
	 string type_string;
	MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);
	 string path_full = where + type_string + "pathologies.txt";
	 ofstream output(path_full,  ios::app);
	//output << time_start <<  setw(7) << " window " << time_start / (window + 1) << ":   " << "\n";
	

	if (a1 == paths.begin() && a1->first >time_start) {
		for (auto i = a1; i != b1; i++)
		{
			output << i->first << ", " << pat_to_string(i->second) << "\n";
		}
	}
	if (a1 == b1 && b1 != paths.end())
		output << a1->first << ", " << pat_to_string(a1->second)  << "\n";
	output <<  endl;

}


void Leads_Info::print( pair<int, pat_name>& peaks) const
{
	if (peaks.first == 92159)
		int a = 1;

	 string type_string;
	MAKE_TYPE_LEAD_STRING(type_string, type_of_lead);
	string path_full;
	if (peaks.first >8500)
	    int a = 1;
	if (peaks.second == N_b)
	 path_full = where + type_string + "/norm_peaks.txt";
	else
		path_full = where + type_string + "/ne_norm_peaks.txt";

	 ofstream output(path_full,  ios::app);
	//output << peaks.first << ": " << peaks.second << '\n';
	output << peaks.first << "\n";
}

