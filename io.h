#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdint.h>

#include "adc.h"

int readHeader(FILE *fp, ADCHeader *header);
int readRecords(FILE *fp, ADCSample *records, uint32_t count);

int loadADCFile(const char *filename,
                ADCHeader *header,
                ADCSample **records);

#endif