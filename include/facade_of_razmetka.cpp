//
// Created by amantayr on 20.03.19.
//

#include "facade_of_razmetka.h"
/*
int All_Leads::count_leads = 0;
int Leads_Info::N_leads = 1;
double Leads_Info::Fs = 257;
size_t Leads_Info::window = static_cast<size_t>(30 * Fs);
size_t Leads_Info::mem = static_cast<size_t>(Fs * 8 * 60);
*/

void facade_of_razmetka::set_init_values(int N_leads)
{

    this->N_leads = N_leads;
   if (!razmetka_is_on) {
       int N_leads = 12;


       info_new_peak = new info_for_new_peak;
       leads Leads_control('S');

       ptr_array_of_leads = new All_Leads(info_new_peak,N_leads);
       Leads_control.set_new_peak_info(info_new_peak);
       Leads_control.set_all_leads(*ptr_array_of_leads);

       lead2 = new leadII_V(II, info_new_peak, N_leads, ptr_array_of_leads->At(1)->get_signal("O"), ptr_array_of_leads->At(6));
       lead2->set_all_leads(ptr_array_of_leads);



   }
}
facade_of_razmetka::~facade_of_razmetka()
{
    delete info_new_peak;
    delete ptr_array_of_leads;
    delete lead2;
}

void facade_of_razmetka::set_new_signal(double* new_data){

    for (int i  = 1;i < N_leads; i++)
    {
        //ptr_array_of_leads->At(i)->processing_lead(leads_samples.at(i).at(k), res);
    }
    lead2->get_new_peaks();


};
/*
vector<wave>* facade_of_razmetka::get_peaks(char* type){
    if (type == "P")
        return lead2->get_signal(type);
    else
        if (type == "R")
            return lead2->get_signal(type);
        else
            if (type == "S")
                return lead2->get_signal(type);
            else
                if (type == "Q")
                    return lead2->get_signal(type);
                else
                    if (type == "T")
                        return lead2->get_signal(type);


}*/
