#pragma once 

const int HISTORY_SIZE = 10;

enum Trend {
    DECREASING,
    STABLE,
    INCREASING
};

struct SensorData {
    float currentValue; 
    Trend trend;
    bool spikeDetected;
};

float smoothData(const float history[], int size);
Trend getTrend(const float history[], int size, float threshold);
float calculateComparisonAverage(const float history[], int startIndex);
bool detectSpike(const float history[], int size);
void updateSensorData();