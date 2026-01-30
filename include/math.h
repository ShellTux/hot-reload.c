#ifndef INCLUDE_INCLUDE_MATH_H_
#define INCLUDE_INCLUDE_MATH_H_

#include <stddef.h>

size_t factorial(const size_t number);

typedef double (*trig_func)(const double);

double msin(const double angleRad);
double mcos(const double angleRad);
double mtan(const double angleRad);
double mcosh(const double angleRad);
double msinh(const double angleRad);

#endif // INCLUDE_INCLUDE_MATH_H_
