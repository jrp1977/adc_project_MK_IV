#include <stdio.h>
#include <time.h>

#include "report.h"
#include "stats.h"
#include "adc.h"

void writeResultsReport(const ADCHeader *header,
                        const AnalysisResults *results)
{
    FILE *out = fopen("log analysis results.txt", "w");

    if(out == NULL)
    {
        printf("Cannot create results.txt\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *current = localtime(&now);

    fprintf(out, "==============================================================\n");
    fprintf(out, "          ADC SENSOR LOG ANALYSIS REPORT\n");
    fprintf(out, "==============================================================\n\n");

    fprintf(out, "Project           : ADC Sensor Log Analysis System\n");
    fprintf(out, "Module            : UFMFGT-15-1 Programming for Engineers\n");
    fprintf(out, "Coursework        : Resit Coursework\n");
    fprintf(out, "Student           : James Pierce\n");
    fprintf(out, "Student ID        : 23034541\n");
    fprintf(out, "University        : University of the West of England (UWE)\n");
    fprintf(out, "File Analysed     : adc_sensor_log.bin\n");
    fprintf(out, "Report Version    : 1.0\n");

    fprintf(out, "--------------------------------------------------------------\n");

    if(current != NULL)
    {
        fprintf(out,
                "Generated on      : %02d/%02d/%04d\n",
                current->tm_mday,
                current->tm_mon + 1,
                current->tm_year + 1900);

        fprintf(out,
                "Generated at      : %02d:%02d:%02d\n",
                current->tm_hour,
                current->tm_min,
                current->tm_sec);
    }

    fprintf(out, "--------------------------------------------------------------\n\n");

    fprintf(out, "HEADER INFORMATION\n");
    fprintf(out, "------------------\n");
    fprintf(out, "Version           : %u\n", header->version);
    fprintf(out, "Channels          : %u\n", header->channel_count);
    fprintf(out, "Records           : %u\n", header->record_count);
    fprintf(out, "Sample Rate       : %u Hz\n\n", header->sample_rate);

    fprintf(out, "SEQUENCE INTEGRITY\n");
    fprintf(out, "------------------\n");
    fprintf(out, "Sequence Gaps     : %d\n\n", results->sequenceGaps);

    for(int ch = 0; ch < CHANNELS; ch++)
    {
        double mean = calculateMean(results->sum[ch],
                                    results->count[ch]);

        double rms = calculateRMS(results->sumSquares[ch],
                                  results->count[ch]);

        double stdDev = calculateStdDev(results->sum[ch],
                                        results->sumSquares[ch],
                                        results->count[ch]);

        double meanTemp = calculateMean(results->tempSum[ch],
                                        results->count[ch]);

        fprintf(out, "==============================================================\n");
        fprintf(out, "CHANNEL %d\n", ch);
        fprintf(out, "==============================================================\n\n");

        fprintf(out, "Voltage Statistics\n");
        fprintf(out, "------------------\n");
        fprintf(out, "Samples            : %d\n", results->count[ch]);
        fprintf(out, "Mean Voltage       : %.4f V\n", mean);
        fprintf(out, "RMS Voltage        : %.4f V\n", rms);
        fprintf(out, "Minimum Voltage    : %.4f V\n", results->minVoltage[ch]);
        fprintf(out, "Maximum Voltage    : %.4f V\n", results->maxVoltage[ch]);
        fprintf(out, "Std Deviation      : %.4f V\n\n", stdDev);

        fprintf(out, "Temperature Statistics\n");
        fprintf(out, "----------------------\n");
        fprintf(out, "Mean Temperature   : %.1f C\n", meanTemp);
        fprintf(out, "Minimum Temperature: %.1f C\n", results->minTemp[ch]);
        fprintf(out, "Maximum Temperature: %.1f C\n\n", results->maxTemp[ch]);

        fprintf(out, "Fault Summary\n");
        fprintf(out, "-------------\n");
        fprintf(out, "Overvoltage Events : %d\n", results->overVoltage[ch]);
        fprintf(out, "Undervoltage Events: %d\n", results->underVoltage[ch]);
        fprintf(out, "Sensor Fault Flags : %d\n", results->sensorFault[ch]);
        fprintf(out, "Out Of Range Flags : %d\n\n", results->outOfRange[ch]);

        fprintf(out, "Voltage Histogram\n");
        fprintf(out, "-----------------\n");

        for(int b = 0; b < HISTOGRAM_BINS; b++)
        {
            double low = (ADC_REF_VOLTAGE / HISTOGRAM_BINS) * b;
            double high = (ADC_REF_VOLTAGE / HISTOGRAM_BINS) * (b + 1);

            fprintf(out,
                    "%.2f - %.2f V : %d\n",
                    low,
                    high,
                    results->histogram[ch][b]);
        }

        fprintf(out, "\n");
    }

    fprintf(out, "==============================================================\n");
    fprintf(out, "END OF REPORT\n");
    fprintf(out, "==============================================================\n");

    fclose(out);
}