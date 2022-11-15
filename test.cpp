#include <bits/stdc++.h>

using namespace  std;

int main(void)
{
    int numbers[5] = {0, 1,2,3,4};
    double doubles[5] = {0.1, 0.2, 0.3, 0.05, 0.35};
    double sum = 0.0, accum = 0.0;

    srand(time(0));

    for (auto n : numbers)
        sum += doubles[n];
    //printf("sum: %f", sum);

    /*default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    double nextSpot = distribution (generator);*/
    float nextSpot = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / sum));
    printf("Next Spot: %f\n\n", nextSpot);

    for (auto n : numbers)
    {
        //printf("%d: %f\n", n, nextSpot);
        accum += (doubles[n]/sum);
        printf("accum in %d: %f\n", n, accum);
        if (nextSpot < accum)
        {
            printf("return %d\n", n);
            break;
        }
    }
    printf("return %d\n", 5-1);
    return 0;
}
