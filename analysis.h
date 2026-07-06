#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "adc.h"

typedef struct
{
    double sum[CHANNELS];
    double sumSquares[CHANNELS];

    double minVoltage[CHANNELS];
    double maxVoltage[CHANNELS];

    double tempSum[CHANNELS];
    double minTemp[CHANNELS];
    double maxTemp[CHANNELS];

    int count[CHANNELS];

    int overVoltage[CHANNELS];
    int underVoltage[CHANNELS];
    int sensorFault[CHANNELS];
    int outOfRange[CHANNELS];

    int histogram[CHANNELS][HISTOGRAM_BINS];

    int sequenceGaps;

} AnalysisResults;

void initialiseAnalysisResults(AnalysisResults *results);

void analyseRecords(const ADCSample *records,
                    unsigned int recordCount,
                    AnalysisResults *results);

#endif