#pragma once 

long long gcd(long long a, long long b);
int has_finite_representation(double x, int base);
void check_fractions(int base, int count, ...);

enum errors {
    OUT_OF_RANGE,

};