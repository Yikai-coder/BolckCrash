#include <stdio.h>
#include <stdlib.h>
#define ZERO 1e-6

struct VECTOR  //记录两个木块速度的二元组
{
    long double v1;
    long double v2;
};

struct VECTOR calculate(long double v1, long double v2, int n)//计算一次碰撞后的速度
{
    struct VECTOR newVector;

    newVector.v1 = (long double)((n-1)*v1 + 2*v2)/(n+1);
    newVector.v2 = (long double)((1-n)*v2 + 2*n*v1)/(n+1);

    return newVector;
}

void handleCrash(struct VECTOR verb, int n)
{
    int count = 0;

    while(1)
    {
        /**第一次接触的情况*/
        if(verb.v1 > 0 && verb.v2 == 0)
        {
            verb = calculate(verb.v1, verb.v2, n);
            count++;
        }

        /**同时往墙壁反方向跑*/
        if(verb.v1 < 0 && verb.v2 < 0)
        {
            /**再也追不上了*/
            if(verb.v1 - verb.v2 <= ZERO)
            {
                printf("When n = %ld, the times they will crash is %d\n", n, count);
                return;
            }

            /**反向追能追上时*/
            else
            {
                verb = calculate(verb.v1, verb.v2, n);
                count++;
            }
        }
        /**同时往墙壁方向跑*/
        if(verb.v1 > 0 && verb.v2 > 0)
        {
            verb.v2 = -verb.v2;
            count++;                 //这种情况下只有可能是小木块撞墙反弹回来再和大木块相碰
        }

        /**对冲的情况*/
        if(verb.v1 > 0 && verb.v2 < 0)
        {
            verb = calculate(verb.v1, verb.v2, n);
            count++;
        }

        /**相离的情况*/
        if(verb.v1 < 0 && verb.v2 > 0)
        {
            verb.v2 = -verb.v2;
            count++;                 //v2反向
        }

    }

}



int main()
{
    long long n = 100;
    struct VECTOR verb;

    for(; n <= 100e7; n*=100)
    {
        verb.v1 = 1;
        verb.v2 = 0;
        handleCrash(verb, n);
    }

    return 0;
}
