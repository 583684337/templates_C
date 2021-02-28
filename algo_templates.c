#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long gcd(long long a, long long b);          //最大公约数
long long lcm(long long a, long long b);          //最小公倍数
int sieveprime(long long prime[], long long n);   //欧拉筛
long long inv(long long x, long long p);          //求x在模p意义下的乘法逆元
long long fastp(long long base, long long index); //快速幂(没有取模)
int main(void)
{
    long long a;

    a = fastp(10, 4);

    return 0;
}

long long gcd(long long a, long long b)
{
    return (b == 0 ? a : gcd(b, a % b));
}

long long lcm(long long a, long long b)
{
    return a * b / gcd(a, b);
}

int sieveprime(long long prime[], long long n) //d是素数表
{
    long long i, j;
    int count;
    bool *b;

    b = (bool *)malloc(n + 1);
    memset(b, true, n + 1);

    for (i = 2, count = 0; i <= n; i++)
    {
        if (b[i])
            prime[count++] = i;
        for (j = 0; j < count && prime[j] * i <= n; j++)
        {
            b[prime[j] * i] = false;
            if (i % prime[j] == 0) //essence!!
                break;
        }
    }

    return count;
}

long long inv(long long x, long long p)
{
    if (x == 1)
        return 1;
    else
        return (p - p / x) * inv(p % x, p) % p;
}

long long fastp(long long base, long long index)
{
    long long r = 1;
    while (index)
    {
        if (1 & index) //取最后一位进行与运算，等价于index%2
            r *= base;
        base *= base;
        index >>= 1; //等价于index/=2
    }
    return r;
}