#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

typedef struct complex
{
    float Re;
    float Im;
} complex;

void plus(complex *a, complex *b, complex *result)
{
    result->Re = a->Re + b->Re;
    result->Im = a->Im + b->Im;
}

void miuns(complex *a, complex *b, complex *result)
{
    result->Re = a->Re - b->Re;
    result->Im = a->Im - b->Im;
}

void multiply(complex *a, complex *b, complex *result)
{
    result->Re = a->Re * b->Re - a->Im * b->Im;
    result->Im = a->Re * b->Im + a->Im * b->Re;
}

void exp_i(float a, complex *result)
{
    result->Re = cos(a * M_PI);
    result->Im = sin(a * M_PI);
}
