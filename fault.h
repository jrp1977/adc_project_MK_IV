#ifndef FAULT_H
#define FAULT_H

#include "adc.h"

void writeFaultReport(const ADCSample *records,
                      unsigned int recordCount);

#endif