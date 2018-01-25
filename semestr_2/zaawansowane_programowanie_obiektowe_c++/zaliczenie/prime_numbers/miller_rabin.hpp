#ifndef _MILLER_RABIN_
#define _MILLER_RABIN_

#include <iostream>

long long mulmod(long long a, long long b, long long mod);
long long modulo(long long base, long long exponent, long long mod);
bool Miller(long long p,int iteration);

#endif