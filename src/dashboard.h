#pragma once 

#include "processing.h"
#include "comfort_engine.h"

void initDashboard();
void updateDashboard(SensorData light, SensorData sound, SensorData temperature, ComfortContribution comfort);