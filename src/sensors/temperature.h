#pragma once 

#include <Arduino.h>

extern bool temperatureConnected; 

void initTemperature();

float readTemperature();

bool checkTemperature(float temperatureValue); 