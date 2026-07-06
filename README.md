# ADC Sensor Log Analysis System

## Student Information

**Student:** James Pierce

**Student ID:** xxxxxxxxx

**Module:** UFMFGT-15-1 Programming for Engineers

**Coursework:** Resit Coursework

**University:** University of the West of England (UWE)

---

# Project Description

This program analyses a binary ADC sensor log file.

The program:

- Reads the binary ADC file
- Validates the file header
- Loads all ADC samples into memory
- Converts raw ADC values into voltages
- Calculates statistics for each ADC channel
- Detects overvoltage and undervoltage faults
- Detects sensor status flag faults
- Detects sequence number gaps
- Generates a detailed results report
- Generates a fault report

---

# Project Files

```
main.c
adc.c
adc.h
io.c
io.h
stats.c
stats.h
analysis.c
analysis.h
report.c
report.h
fault.c
fault.h
CMakeLists.txt
adc_sensor_log.bin
```

---

# Building with CLion

1. Open the ADC_Project_MK_IV folder in CLion.

2. Wait for CMake to finish loading.

3. Copy:

```
adc_sensor_log.bin
```

into

```
cmake-build-debug
```

4. Press **Run**.

The program will generate:

```
results.txt
fault_report.txt
```

---

# Building using GCC

Compile using:

```bash
gcc main.c adc.c io.c stats.c analysis.c report.c fault.c -o adc_project -lm
```

Run using:

```bash
./adc_project
```

Windows:

```bash
adc_project.exe
```

---

# GitHub Repository

https://github.com/jrp1977/adc_project_MK_IV

---

# Author

James Pierce

University of the West of England

Programming for Engineers

2026
