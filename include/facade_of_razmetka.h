//
// Created by amantayr on 20.03.19.
//

#ifndef RAZMETKA_FACADE_OF_RAZMETKA_H
#define RAZMETKA_FACADE_OF_RAZMETKA_H
#include "one lead.h"
#include "Leads_info.h"
#include "add_structs.h"
#include "functions.h"
#include "All_leads.h"
#include "leads.h"
#include "LeadII_V.h"



class facade_of_razmetka {
public:
    facade_of_razmetka(){};
    ~facade_of_razmetka();
    void set_init_values(int );
    void set_new_signal(double* );

    template <typename T>
    vector<T>* get_peaks(char* type) {
        vector<T> t;
        //lead2->get_peaks("R");
    }

    //? get_data_of_pathologies();
    int* get_pathologies();
protected:
    leadII_V* lead2 = nullptr;
    All_Leads* ptr_array_of_leads;
    info_for_new_peak* info_new_peak;
    bool razmetka_is_on = false;
    int N_leads;
};


#endif //RAZMETKA_FACADE_OF_RAZMETKA_H
