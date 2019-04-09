#pragma once
/**
 * @brief The class is used for storaging of pathologies
 * and providing some functions for comfortable work
 * with map
 */

#include "functions.h"
#include <iostream>
#include <fstream>

class storage_of_pathology{
    
public:
    ///Inserts new pathlogy and its index into a storage
    void insert(my_map& pathology, int,  pat_name ,const int&);

    ///Inserts a pair of new pathology and its index into a storage
    void push_el(my_map& pathology, const int,  pair<int,  pat_name>);

    ///Returns last index of pathologies in a storage
    int find(my_map& pathology, const  pat_name&)const;
    
    ///Returns the pathology exists or not
    bool count_map(my_map& pathology,  pat_name name)const{
        for (auto i:pathology){ 
        if (i.second == name)
            return true;
        }
        return false;
    }

    ///Deletes a pathology from the index
    void erase(my_map& pathology, pat_name, int index);

    ///Deletes a pathology from the index (a) to the second index (b) except for pathologies pat and pat2
    void erase(my_map& pathology,const int a,const int b, pat_name pat, pat_name pat2);
   
   ///Prints content of storage to the file
    void print(my_map& pathology,  string& path_full) const
    {
             ofstream output(path_full,  ios::app);
            auto a1 = pathology.begin();
            for (auto i =a1;i!=pathology.end();i++){
                output <<i->first<< ", "<<i->second<< endl; 
            }
    }
private:

    ///Points out to index of Ventricular Flutter
	my_map::iterator ind_f_VF;

    
           
};