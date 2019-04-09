#pragma once
#include "one lead.h"
#include "Leads_info.h"
#include "add_structs.h"
#include "functions.h"
#include "All_leads.h"
#include "leads.h"
#include "LeadII_V.h"
#include "ouput_struct_of_pathlogies.h"



class facade_of_razmetka {
public:

    facade_of_razmetka(){};

    ~facade_of_razmetka();

    void set_init_values(int );
    void set_new_signal(float* );

    /**
     * Gets data
     * @return array of QRS (a number of waves)
     */

    vector<wave>* get_R();

    /**
     * Gets data
     * @return array of P (a number of waves)
     */

    vector<wave>* get_P();

    /**
     * Gets data
     * @return array of S (a number of waves)
     */

    vector<wave>* get_S();
    /**
     * Gets data
     * @return array of Q(a number of waves)
     */

    vector<wave>* get_Q();
    /**
     * Gets data
     * @return array of T (a number of waves)
     */

    vector<wave>* get_T();
    /**
     * Gets data
     * @return array of ST (a number of waves)
     */

    vector<segment_ST>* get_ST();
    /**
     * Gets data
     * @return array of structure which contains info about pathlogies
     */

    list_of_output_pathlogies* get_pathlogies();



protected:
    leadII_V* lead2 = nullptr;
    All_Leads* ptr_array_of_leads;
    info_for_new_peak* info_new_peak;
    bool razmetka_is_on = false;
    int N_leads;
};