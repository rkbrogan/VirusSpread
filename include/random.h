#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>

// Function that returns random number between zero and one
double rand01() 
{
    static int needsrand = 1;

    // need to decouple the seed
    if (needsrand) 
    {
        srand(time(NULL));
        needsrand = 0;
    }

    return (rand()/(1.0 + RAND_MAX));
}

// Function that returns normal distribution
double normal() 
{
    int nroll = 12;
    double sum = 0;
    
    for (int i = 0; i < nroll; i++ )
    {
        sum += rand01();
    }

    return (sum - 6.0);
}

#endif // RANDOM_H
