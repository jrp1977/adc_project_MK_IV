#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#define ADC_MAX_VALUE 4095.0
#define ADC_REF_VOLTAGE 3.3

#define CHANNELS 4
#define HISTOGRAM_BINS 10

#define SENSOR_FAULT_FLAG 0x01
#define OUT_OF_RANGE_FLAG 0x02

typedef struct __attribute__((packed))
{
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
    uint8_t reserved[2];
} ADCSample;

typedef struct __attribute__((packed))
{
    uint32_t magic;
    uint16_t version;
    uint16_t channel_count;
    uint32_t record_count;
    uint32_t sample_rate;
    uint8_t reserved[8];
} ADCHeader;

double rawToVoltage(uint16_t raw);
double rawToTemperature(int16_t rawTemperature);

int isOverVoltage(double voltage);
int isUnderVoltage(double voltage);
int hasSensorFault(uint8_t flags);
int hasOutOfRange(uint8_t flags);

#endif