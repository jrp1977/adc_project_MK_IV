#ifndef REPORT_H
#define REPORT_H

#include "adc.h"
#include "analysis.h"

void writeResultsReport(const ADCHeader *header,
                        const AnalysisResults *results);

#endif