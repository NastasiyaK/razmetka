#pragma once
/*
 * The class is used for storaging of pathologies
 * and providing some functions for comfortable work
 * with map
 */
#include "stdafx.h"
#include "functions.h"
#include <iostream>
#include <fstream>

class storage_of_pathology{
    
public:

    void insert(my_map& pathology, int,  pat_name ,const int&);

    void push_el(my_map& pathology, const int,  pair<int,  pat_name>);

    int find(my_map& pathology, const  pat_name&)const;
    
    //function check existing of some pathologies
    bool count_map(my_map& pathology,  pat_name name)const{
        for (auto i:pathology){ 
        if (i.second == name)
            return true;
        }
        return false;
    }
    //these function delete a pathology anytime and not
    void erase(my_map& pathology, pat_name, int );
    void erase(my_map& pathology,const int a,const int b, pat_name pat, pat_name pat2);
   
   
    void print(my_map& pathology,  string& path_full)const
    {
             ofstream output(path_full,  ios::app);
            auto a1 = pathology.begin();
            for (auto i =a1;i!=pathology.end();i++){
                output <<i->first<< ", "<<i->second<< endl; 
            }
    }
	my_map::iterator ind_f_VF;

    
           
};