
#include "stdafx.h"
#include "one lead.h"
#include "LeadII_V.h"


double sum( vector<double>& v){
double s = 0;
for (auto i:v){
    s+=i;   
}
return s;    
}
double sum2( vector<double>& v,  vector<double>& v2){
double s = 0;
for (size_t i=0;i<v.size();i++){
    s+=v.at(i)*v2.at(i); 
}
return s;    
}

void leadII_V::slope( vector<double>&y,int& ind_vn){
 vector <double>x;

for(size_t i=0;i<y.size();i++)
   x.push_back(i);   
double b,a;
size_t m = x.size();
a = (m*sum2(x,y) - sum(x)*sum(y))/(m*sum2(x,x) - pow((sum(x)),2));

b = (sum(y) - a*sum(x))/m;
if ( abs(a) > 0.1)
{
    ST.start = ind_vn;
    ST.type = "inclined ";
}
}

void leadII_V::level_of_segment( vector<double>& bufer, const int& ind1)
{
double sum=0;
for (size_t i = 0;i<bufer.size();i++)
{
    sum+=bufer.at(i);
}
sum/=bufer.size();
double level_of_ST =sum - isolinia;
}