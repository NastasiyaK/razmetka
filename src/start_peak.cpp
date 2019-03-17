//
// Created by amantayr on 11.03.19.
//

#include "LeadII_V.h"



int one_lead::start_peak(const int &peak, vector<double> *ptr_signal) {

    vector<double> bufer;
    int ind, ind2, ind_vn;
    ind = peak - static_cast<int>(2 * QRS.height * Fs / 3);
    ind2 = peak;
    int start_R = 0;
    set_indices(ind_vn, ind, ind2, count_iter, mem, mem_sdvig);
    vector<double>::iterator min_point;
    //int type_of_finding = 1; // if main_peak S it's necessary to reverse our_signal;

    if (ind >= 0 && ind2 > 0 && ptr_signal->size() > ind2) {
        double isolinia_here = isolinia;
        copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
        double current_amplitude = ptr_signal->at(ind2);


        min_point = min_element(bufer.begin(), bufer.begin() + bufer.size() / 2);
        int min_point_ind = static_cast<int>( distance(bufer.begin(), min_point) + ind_vn);
        double k = (current_amplitude - *min_point) / (peak - min_point_ind);
        double b = current_amplitude - k * (peak);
        double x = (isolinia_here - b) / k;

        start_R = static_cast<int>(round(x));
        int start = 0;



      //  while (start_R < ptr_signal->size() - 1 && value_ok(start_R + 2, ptr_signal->size())
        //       && (abs(ptr_signal->at(start_R) - isolinia_here) >= abs(ptr_signal->at(start_R + 2) - isolinia_here))) {
       //     start_R++;
       // }
        bool _FIND_VAL = 0;
        if (start_R < 0)
            start_R = 0;
        int  i = start_R+1;

        for (i ; i < ind2; i++)
        {
            if ( !_FIND_VAL &&
                    abs(ptr_signal->at(i) - ptr_signal->at( start_R )) > 0.13 &&
                    (abs( ptr_signal->at( start_R ) - isolinia) < 0.2 || abs( ptr_signal->at( start_R ) - 0) < 0.2))
            {
                _FIND_VAL = true;
                start_R =  i ;
                break;
            }
        }

        if (start_R < min_point_ind  && start_R >ind)
            start_R = min_point_ind + 1;

        if (ptr_signal->size() > start_R && abs( ptr_signal->at( start_R ) - isolinia) > 0.4 &&
        abs( ptr_signal->at( start_R ) - 0) > 0.4)
            start_R = min_point_ind;

        if (start_R > mem) {
            start = static_cast<int>(mem_sdvig + (count_iter - 1) * mem);
            set_indices(ind_vn, start_R, ind2, count_iter, mem, mem_sdvig);
        } else {
            ind_vn = 0;
        }

        if ( (ind2 - start_R) >= static_cast<int> (QRS.height * Fs) / 2) {
            int temp = (ind2 - start_R) - static_cast<int> (QRS.low * Fs) / 2;
            if ((start_R + temp < ptr_signal->size()) &&
                (ptr_signal->at(start_R + temp) - ptr_signal->at(start_R + temp) > 0.1))
                start_R += temp;
        }

        start_R += start;

        return start_R;
    }
    return start_R;
}


int one_lead::stop_peak(const int peak, vector<double>* ptr_signal)
{

    vector<double>bufer;
    vector<double>::iterator min_point;
    int stop_R = 0;
    int ind,ind2,ind_vn;
    ind = peak;
    ind2 = peak+ static_cast<int>(Fs*QRS.height);
    set_indices(ind_vn,ind,ind2,count_iter,mem,mem_sdvig);

    if (ind >=0 && ind2 >0 && ptr_signal->size() > ind2)
    {

        copy(begin(*ptr_signal)+ind,begin(*ptr_signal)+ind2,back_inserter(bufer));

        double isolinia_here = isolinia;
        copy(begin(*ptr_signal) + ind, begin(*ptr_signal) + ind2, back_inserter(bufer));
        double current_amplitude = ptr_signal->at(ind);


        min_point =  min_element(bufer.begin(),bufer.begin() + static_cast<int>(Fs*(QRS.height)/2));

        auto max_addic  =  max_element(min_point,bufer.end());
        if ( *max_addic- isolinia_here > 0.3 && *max_addic - *min_point>0.15
             && *max_addic - *min_point < current_amplitude*0.5)
            min_point =  min_element(max_addic,bufer.end());
        int min_point_ind = static_cast<int>( distance(bufer.begin(),min_point)+ind_vn);
        if (peak == min_point_ind)
            min_point_ind = ind2+3;
        double k = (current_amplitude-*min_point)/(peak - min_point_ind);
        double b = current_amplitude - k*(peak);
        double x = (isolinia_here-b)/k;
        stop_R =static_cast<int>(round(x));
        stop_R = (stop_R > 0) ? stop_R : ind2;
        stop_R = (stop_R > min_point_ind) ? min_point_ind - 1 : stop_R;
        int start = 0;


        //while (value_ok(stop_R,ptr_signal->size()-1 )  &&  abs(ptr_signal->at(stop_R)-isolinia_here)>
         //                                                  abs(ptr_signal->at(stop_R+1)-isolinia_here) && stop_R<min_point_ind){
        //    stop_R++;
       // }

        bool _FIND_VAL = 0;
       for (int  i = 1 ; i < stop_R - ind; i++)
       {
           if ( !_FIND_VAL && stop_R < ptr_signal->size() &&
             abs(ptr_signal->at(stop_R) - ptr_signal->at(stop_R - i)) > 0.07)
           {
               stop_R = stop_R - i ;
               _FIND_VAL = true;
               break;

           }
       }
        //while (value_ok(stop_R,ptr_signal->size()) && stop_R>min_point_ind
       //        &&  abs(ptr_signal->at(stop_R)- isolinia_here)> abs(ptr_signal->at(stop_R-1)- isolinia_here)){
       //     stop_R--;
        //}
        if (peak > mem)
        {
            start = mem_sdvig + (count_iter-1)*mem;
            set_indices(ind_vn,stop_R,ind2,count_iter,mem,mem_sdvig);
        } else
            ind_vn = 0;

        stop_R+=start;
        if ( abs(stop_R- peak)> RR.middle * Fs / 0.3)
            stop_R = peak+ static_cast<int>(1.3*Fs*(QRS.height)/2);
        return stop_R;
    }
    return stop_R;
}