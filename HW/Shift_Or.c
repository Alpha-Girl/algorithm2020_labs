#include <stdio.h>
#include <string.h>
#define ASIZE 5
int t(char x)
{
    switch (x)
    {
    case 'A':
        return 0;
        break;
    case 'C':
        return 1;
        break;
    case 'D':
        return 2;
        break;
    case 'G':
        return 3;
        break;
    case 'T':
        return 4;
        break;
    default:
        break;
    }
}
void kk(unsigned int x)
{
    unsigned int i = x;
    for (int j = 0; j < 10; j++)
    {
        printf("%d", i % 2);
        i = i / 2;
    }
    printf("\n");
}
unsigned int preSo(char *x, int m, unsigned int S[])
{
    unsigned int j, lim;
    int i;
    for (i = 0; i < ASIZE; i++)
    {
        S[i] = ~0;
    }
    for (lim = i = 0, j = 1; i < m; i++, j <<= 1)
    {
        S[t(x[i])] &= ~j;
        lim |= j;
    }
    for (i = 0; i < ASIZE; i++)
    {
        kk(S[i]);
    }
    lim = ~(lim >> 1);
    return (lim);
}

void SO(char *x, int m, char *y, int n)
{
    unsigned int lim, state;
    unsigned int S[ASIZE];
    int j;
    lim = preSo(x, m, S);
    kk(lim);
    for (state = ~0, j = 0; j < n; j++)
    {
        state = (state << 1) | S[t(y[j])];
        printf("\n%o ", state);
        kk(state);
        if (state < lim)
            printf(" %d", j - m + 1);
    }
}

int main()
{
    char P[11] = "DAGCDGDAGC\0";
    char T[30] = "ACGCTDAGAAGDCAGADGTDAGCDGDAGC\0";
    SO(P, strlen(P), T, strlen(T));
}