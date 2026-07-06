#include <stdio.h>
#include <stdlib.h>

#include "adc.h"
#include "io.h"
#include "analysis.h"
#include "report.h"
#include "fault.h"

int main(void)
{
    ADCHeader header;
    ADCSample *records = NULL;

    if(!loadADCFile("adc_sensor_log.bin", &header, &records))
    {
        printf("Program stopped because the ADC file could not be loaded.\n");
        return 1;
    }

    AnalysisResults results;

    initialiseAnalysisResults(&results);
    analyseRecords(records, header.record_count, &results);

    writeResultsReport(&header, &results);
    writeFaultReport(records, header.record_count);

    free(records);

    printf("Analysis complete.\n");
    printf("Results saved to log analysis results.txt\n");
    printf("Fault report saved to fault_report.txt\n");

    return 0;
}