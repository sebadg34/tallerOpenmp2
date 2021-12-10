  GNU nano 4.9                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  fibonacci.c
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define CUTOFF 10
int fib_s(int n){
if(n==0 || n==1)
        return n;
int res, a,b;
a = fib_s(n-1);
b = fib_s(n-2);

res = a + b;

return res;
}

long long fib(long long n, int co)
{

if(co >= CUTOFF) return fib_s(n);


        long long i, j;

        if (n < 2)
                return n;
        else
        {
co++;
// Limitar paralelizacion para no crear demasiados tasks
if(n<20){
return (fib(n-1,co)+fib(n-2,co));
}
else
{
#pragma omp task shared(i)
                i = fib(n - 1,co);
#pragma omp task shared(j)
                j = fib(n - 2,co);
#pragma omp taskwait

                return i + j;
}


 }
}

int factor(long long num)
{

        int isPrime, firstValue, hasFactors;
        long long aux,i,j;
        hasFactors = 0;
        firstValue = 1;

        for (i = 2; i < num; i++)
        {
                aux = num;

                if (num % i == 0)
                {

                        /* Check 'i' for factor of num */

                        /* Check 'i' for Prime */
                        isPrime = 1;
                        for (j = 2; j <= i / 2; j++)
                        {
                                if (i % j == 0)
                                {
                                        isPrime = 0;
                                        break;
                                }
                        }

                        /* If 'i' is Prime number and factor of num */

                        if (isPrime == 1)
                        {

                                while (aux % i == 0)
                                {
                                        hasFactors = 1;
                                        if (firstValue == 1)
                                        {
                                                printf("%d", i);
                                                firstValue = 0;
                                        }
                                        else
                                        {
                                                printf(" x %d", i);
                                        }
                                        aux = aux / i;
                                }
                        }
                }
        }

        return hasFactors;
}

int main(int argc, char **argv)
{
        clock_t tic = clock();
        int n, i, num, j, base;
        unsigned long long result;
        char *a = argv[1];
        n = atoi(a);


        for (base = 1; base <= n; base++)
        {
#pragma omp parallel
                {
#pragma omp single
                        result = fib(base,1);

                printf("para \033[33m%d\033[0m: ", base);

                printf("\033[0mvalor %llu = ", result);

                // En caso de que el unico factor sea el resultado mismo (primo)
                #pragma omp single
                if (factor(result) == 0)
               {
                      printf("\033[32m%llu", result);
                }
                printf("\033[0m\n");
                }

        }

        clock_t toc = clock();
        printf("\033[36mTiempo ejecucion: %f seconds\n", (double)(toc - tic) / (double)CLOCKS_PER_SEC);
}



































