#include <stdio.h>
#include <stdlib.h>

#include "io.h"

#define MAGIC_NUMBER 0xADC1BEEF

int readHeader(FILE *fp, ADCHeader *header)
{
    return fread(header, sizeof(ADCHeader), 1, fp) == 1;
}

int readRecords(FILE *fp, ADCSample *records, uint32_t count)
{
    return fread(records, sizeof(ADCSample), count, fp) == count;
}

int loadADCFile(const char *filename,
                ADCHeader *header,
                ADCSample **records)
{
    FILE *fp = fopen(filename, "rb");

    if(fp == NULL)
    {
        printf("Cannot open %s\n", filename);
        return 0;
    }

    if(!readHeader(fp, header))
    {
        printf("Header read failed.\n");
        fclose(fp);
        return 0;
    }

    if(header->magic != MAGIC_NUMBER)
    {
        printf("Invalid magic number.\n");
        fclose(fp);
        return 0;
    }

    *records = malloc(header->record_count * sizeof(ADCSample));

    if(*records == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return 0;
    }

    if(!readRecords(fp, *records, header->record_count))
    {
        printf("Record read failed.\n");
        free(*records);
        fclose(fp);
        return 0;
    }

    fclose(fp);

    return 1;
}