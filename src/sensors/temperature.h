#pragma once 

#include <Arduino.h>

extern bool temperatureConnected; // used as a flag for temperature validation 

void initTemperature();

float readTemperature();

bool checkTemperature(float temperatureValue); 