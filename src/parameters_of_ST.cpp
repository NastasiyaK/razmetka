

#include "one lead.h"
#include "LeadII_V.h"


float sum( vector<float>& v){
float s = 0;
for (auto i:v){
    s+=i;   
}
return s;    
}
float sum2( vector<float>& v,  vector<float>& v2){
float s = 0;
for (size_t i=0;i<v.size();i++){
    s+=v.at(i)*v2.at(i); 
}
return s;    
}

void leadII_V::slope( vector<float>&y,int& ind_vn){
 vector <float>x;

for(size_t i=0;i<y.size();i++)
   x.push_back(i);   
float b,a;
size_t m = x.size();
a = (m*sum2(x,y) - sum(x)*sum(y))/(m*sum2(x,x) - pow((sum(x)),2));

b = (sum(y) - a*sum(x))/m;
if ( abs(a) > 0.1)
{
    ST.start = ind_vn;
    ST.type = "inclined ";
}
}

void leadII_V::level_of_segment( vector<float>& bufer, const int& ind1)
{
float sum=0;
for (size_t i = 0;i<bufer.size();i++)
{
    sum+=bufer.at(i);
}
sum/=bufer.size();
float level_of_ST =sum - isolinia;
}