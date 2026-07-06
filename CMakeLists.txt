cmake_minimum_required(VERSION 4.2)
project(adc_project_MK_IV C)

set(CMAKE_C_STANDARD 99)

add_executable(adc_project_MK_IV main.c
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
        fault.h)

target_link_libraries(adc_project_MK_IV m)
