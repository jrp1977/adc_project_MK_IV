#include <stdio.h>

#include "fault.h"
#include "adc.h"

void writeFaultReport(const ADCSample *records,
                      unsigned int recordCount)
{
    FILE *out = fopen("fault_report.txt", "w");

    if(out == NULL)
    {
        printf("Cannot create fault_report.txt\n");
        return;
    }

    fprintf(out, "=====================================================\n");
    fprintf(out, "        ADC SENSOR FAULT REPORT\n");
    fprintf(out, "=====================================================\n\n");

    for(unsigned int i = 0; i < recordCount; i++)
    {
        const ADCSample *sample = records + i;

        double voltage = rawToVoltage(sample->raw_value);

        if(isOverVoltage(voltage))
        {
            fprintf(out,
                    "OVERVOLTAGE | index=%u | time=%.4f s | channel=%u | voltage=%.4f V | sequence=%u\n",
                    i,
                    sample->timestamp,
                    sample->channel_id,
                    voltage,
                    sample->sequence_number);
        }

        if(isUnderVoltage(voltage))
        {
            fprintf(out,
                    "UNDERVOLTAGE | index=%u | time=%.4f s | channel=%u | voltage=%.4f V | sequence=%u\n",
                    i,
                    sample->timestamp,
                    sample->channel_id,
                    voltage,
                    sample->sequence_number);
        }

        if(hasSensorFault(sample->status_flags))
        {
            fprintf(out,
                    "SENSOR FAULT | index=%u | time=%.4f s | channel=%u | flags=0x%02X | sequence=%u\n",
                    i,
                    sample->timestamp,
                    sample->channel_id,
                    sample->status_flags,
                    sample->sequence_number);
        }

        if(hasOutOfRange(sample->status_flags))
        {
            fprintf(out,
                    "OUT OF RANGE | index=%u | time=%.4f s | channel=%u | flags=0x%02X | sequence=%u\n",
                    i,
                    sample->timestamp,
                    sample->channel_id,
                    sample->status_flags,
                    sample->sequence_number);
        }

        if(i > 0)
        {
            const ADCSample *previous = records + (i - 1);

            if(sample->sequence_number != previous->sequence_number + 1)
            {
                fprintf(out,
                        "SEQUENCE GAP | index=%u | expected=%u | found=%u\n",
                        i,
                        previous->sequence_number + 1,
                        sample->sequence_number);
            }
        }
    }

    fclose(out);
}