#pragma once 

#include <Arduino.h>

void initTemperature();

float readTemperature();

enum TemperatureStatus {
    TEMPERATURE_OK,
    TEMPERATURE_INVALID
};

TemperatureStatus checkTemperature(float temperatureValue); 