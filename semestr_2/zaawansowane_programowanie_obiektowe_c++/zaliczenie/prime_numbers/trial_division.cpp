#include "trial_division.hpp"

bool trialDivision(unsigned long long n)
{
    if(n<=1) return false;
    if(n==2) return true;
    for(unsigned int i=2; i<=sqrt(n); ++i)
    {
        if(n%i==0) return false;
    }
    return true;
}