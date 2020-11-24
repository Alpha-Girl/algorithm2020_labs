#include <stdio.h>
#include <malloc.h>
#include "complex.h"
void recursive_fft(complex *array, complex *result);
int main()
{
}

void recursive_fft(complex *array, complex *result, int length)
{
    int n = length;
    if (n == 1)
    {
        equal(result, array);
        return;
    }
    complex omiga_n, tmp;
    exp_i(2 / (float)n, &omiga_n);
    complex omiga = {1, 0};
    complex *a_0, *a_1, *y_0, *y_1;
    a_0 = (complex *)calloc(n / 2, sizeof(complex));
    a_1 = (complex *)calloc(n / 2, sizeof(complex));
    y_0 = (complex *)calloc(n / 2, sizeof(complex));
    y_1 = (complex *)calloc(n / 2, sizeof(complex));
    for (int i = 0; i < n / 2; i++)
    {
        a_0[i].Re = array[2 * i].Re;
        a_0[i].Im = array[2 * i].Im;
        a_1[i].Re = array[2 * i + 1].Re;
        a_1[i].Im = array[2 * i + 1].Im;
    }
    recursive_fft(a_0, y_0, n / 2);
    recursive_fft(a_1, y_1, n / 2);
    for (int k = 0; k < n / 2; k++)
    {
        multiply(&omiga, &y_1[k], &tmp);
        plus(&y_0[k], &tmp, &result[k]);
        miuns(&y_0[k], &tmp, &result[k + n / 2]);
        multiply(&omiga_n, &omiga, &tmp);
        equal(&tmp, &omiga);
    }
    return;
}
