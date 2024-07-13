#include <math.h>
#include <stdio.h>

int i_sqrt(int x)
{
    if (x <= 1) /* Assume x is always positive */
        return x;

    int z = 0;
    for (int m = 1UL << ((31 - __builtin_clz(x)) & ~1UL); m; m >>= 2) {
        int b = z + m;
        z >>= 1;
        if (x >= b)
            x -= b, z += m;               
    }
    return z;
}

int main()
{
    int N = 36;
    printf("%d\n", i_sqrt(N));
    return 0;
}