#include <math.h>

#include "stats.h"

double calculateMean(double sum, int count)
{
    if(count == 0)
    {
        return 0.0;
    }

    return sum / count;
}

double calculateRMS(double sumSquares, int count)
{
    if(count == 0)
    {
        return 0.0;
    }

    return sqrt(sumSquares / count);
}

double calculateStdDev(double sum, double sumSquares, int count)
{
    if(count == 0)
    {
        return 0.0;
    }

    double mean = sum / count;
    double variance = (sumSquares / count) - (mean * mean);

    if(variance < 0)
    {
        variance = 0;
    }

    return sqrt(variance);
}