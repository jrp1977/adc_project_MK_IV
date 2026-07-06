#include "adc.h"

double rawToVoltage(uint16_t raw)
{
    return (raw / ADC_MAX_VALUE) * ADC_REF_VOLTAGE;
}

double rawToTemperature(int16_t rawTemperature)
{
    return rawTemperature / 10.0;
}

int isOverVoltage(double voltage)
{
    return voltage > 3.0;
}

int isUnderVoltage(double voltage)
{
    return voltage < 0.3;
}

int hasSensorFault(uint8_t flags)
{
    return (flags & SENSOR_FAULT_FLAG) != 0;
}

int hasOutOfRange(uint8_t flags)
{
    return (flags & OUT_OF_RANGE_FLAG) != 0;
}