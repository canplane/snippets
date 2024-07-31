/* counting binary tree
 * 20200212
 * catalan numbers : C(0) = 1, C(n) = C(0)C(n-1) + C(1)C(n-2) + ... + C(n-2)C(1) + C(n-1)C(0) (n > 0)
 * using memoization (dynamic programming)
 */

#include <stdio.h>
#include <string.h>

#define MEMOSZ 100
int memo[MEMOSZ];

int countBT(int size)
{
    int i, sum;
    if (memo[size])
        return memo[size];
    else {
        if (!size)
            return memo[size] = 1;
        else {
            sum = 0;
            for (i = 0; i <= size - 1; i++)
                sum += countBT(i) * countBT((size - 1) - i);
            return memo[size] = sum;
        }
    }
}

/* main */

#define N 20
int main()
{
    int i;
    for (i = 0; i <= N; i++)
        printf("C(%d) = %d\n", i, countBT(i));

    return 0;
}