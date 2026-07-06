#include <float.h>

#include "analysis.h"
#include "adc.h"

void initialiseAnalysisResults(AnalysisResults *results)
{
    for(int ch = 0; ch < CHANNELS; ch++)
    {
        results->sum[ch] = 0.0;
        results->sumSquares[ch] = 0.0;

        results->minVoltage[ch] = DBL_MAX;
        results->maxVoltage[ch] = 0.0;

        results->tempSum[ch] = 0.0;
        results->minTemp[ch] = 1000.0;
        results->maxTemp[ch] = -1000.0;

        results->count[ch] = 0;

        results->overVoltage[ch] = 0;
        results->underVoltage[ch] = 0;
        results->sensorFault[ch] = 0;
        results->outOfRange[ch] = 0;

        for(int b = 0; b < HISTOGRAM_BINS; b++)
        {
            results->histogram[ch][b] = 0;
        }
    }

    results->sequenceGaps = 0;
}

void analyseRecords(const ADCSample *records,
                    unsigned int recordCount,
                    AnalysisResults *results)
{
    for(unsigned int i = 0; i < recordCount; i++)
    {
        const ADCSample *sample = records + i;

        int ch = sample->channel_id;
        double voltage = rawToVoltage(sample->raw_value);
        double temperature = rawToTemperature(sample->temperature);

        if(ch >= 0 && ch < CHANNELS)
        {
            results->sum[ch] += voltage;
            results->sumSquares[ch] += voltage * voltage;
            results->count[ch]++;

            results->tempSum[ch] += temperature;

            if(voltage < results->minVoltage[ch])
            {
                results->minVoltage[ch] = voltage;
            }

            if(voltage > results->maxVoltage[ch])
            {
                results->maxVoltage[ch] = voltage;
            }

            if(temperature < results->minTemp[ch])
            {
                results->minTemp[ch] = temperature;
            }

            if(temperature > results->maxTemp[ch])
            {
                results->maxTemp[ch] = temperature;
            }

            int bin = (int)((voltage / ADC_REF_VOLTAGE) * HISTOGRAM_BINS);

            if(bin >= HISTOGRAM_BINS)
            {
                bin = HISTOGRAM_BINS - 1;
            }

            if(bin < 0)
            {
                bin = 0;
            }

            results->histogram[ch][bin]++;

            if(isOverVoltage(voltage))
            {
                results->overVoltage[ch]++;
            }

            if(isUnderVoltage(voltage))
            {
                results->underVoltage[ch]++;
            }

            if(hasSensorFault(sample->status_flags))
            {
                results->sensorFault[ch]++;
            }

            if(hasOutOfRange(sample->status_flags))
            {
                results->outOfRange[ch]++;
            }
        }

        if(i > 0)
        {
            const ADCSample *previous = records + (i - 1);

            if(sample->sequence_number != previous->sequence_number + 1)
            {
                results->sequenceGaps++;
            }
        }
    }
}