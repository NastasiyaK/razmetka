// razmetka.cpp : Defines the entry point for the console application.
//


#include <chrono>
#include <iomanip>
#include <iostream>  
#include <fstream>
#include "leads.h"
#include "one lead.h"
#include "functions.h"
#include "Leads_info.h"
#include <string>
#include "All_leads.h"
#include "LeadII_V.h"


int All_Leads::count_leads = 0;
int Leads_Info::N_leads = 1;
float Leads_Info::Fs = 257;
size_t Leads_Info::window = static_cast<size_t>(30 * Fs);
size_t Leads_Info::mem = static_cast<size_t>(Fs * 8 * 60);

void test_one_lead();
int n = 100000;
 //string input_path = "C:\\Users\\Amantayr\\Documents\\Visual Studio 2015\\Projects\\razmetka\\razmetka\\signals for project\\";
 string input_path = "/home/amantayr/signals for projects/";

 vector<float> get_signal( ifstream &,int);
 void test_leadII();


int main()
{
	test_leadII();
	//test_one_lead();
	
    return 0;
}



void test_leadII()
{
	int N_leads = 12;
	//ofstream output("new_.txt");
	//output << "fdf"  << endl;
	ifstream input("I21.txt");
	vector<vector<float>> leads_samples(13);

	float sam = 0;
	if (input)
	{
		std::string line{};

		while (std::getline(input, line)) {
			std::stringstream strStream(line);

			for (int i = 0; i <= 12; i++) {

				strStream >> sam;
				if (i != 0)
				    leads_samples[i-1].push_back(move(sam));
			}

		}
	}
	else
		{
		cout << "file isn't open." <<  endl;
		}


	info_for_new_peak* info_new_peak = new info_for_new_peak;
	All_Leads array_of_leads(info_new_peak,N_leads);


	leads Leads_control;
	Leads_control.set_new_peak_info(info_new_peak);
	Leads_control.set_all_leads(array_of_leads);



	leadII_V lead2(II, info_new_peak, N_leads, array_of_leads.At(1)->get_signal("O"), array_of_leads.At(6));
	lead2.set_all_leads(&array_of_leads);
	float c = 0;
	bool res;
	if (N_leads ==12) {

        for (int k = 0; k < n; k++) {
        cout<< k << endl;
          for (int i = 0; i < 12; i++) {
              array_of_leads.At(i)->processing_lead(leads_samples.at(i).at(k));

          }

            if (k == 1666)
            {
                int b = 1;
            }

        lead2.get_new_peaks();
        }
    }
    if (N_leads == 1) {
        for (int k = 1; k < n; k++) {
            if (k == 1100)
                int a = 1;


            array_of_leads.At(1)->processing_lead(leads_samples.at(1).at(k));


            //cout << k << endl;

            //lead2.get_new_peaks();
        }
    }

	delete info_new_peak;

}






 vector<float> get_signal( ifstream &input,int n)
 {
	 vector<float> signal_of_lead;

	// ifstream input(signal);
	float sam = 0;
	if (input) 
	{
		for (int h = 0; h<n; h++)
		{
			input >> sam;
			signal_of_lead.push_back( move(sam));
		}

	}
	else {
		 cout << "file isn't open." <<  endl;
	}
	return signal_of_lead;
}

