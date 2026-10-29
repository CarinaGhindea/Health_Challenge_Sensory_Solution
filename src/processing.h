#pragma once 

const int HISTORY_SIZE = 10;
const int COMPARISON_AVERAGE_WINDOW = 3;
const int TREND_DECIDER = 2;

const float LIGHT_TREND_THRESHOLD = 50.0f;
const float SOUND_TREND_THRESHOLD = 25.0f;
const float TEMPERATURE_TREND_THRESHOLD = 0.5f;

const float LIGHT_SPIKE_THRESHOLD = 300.0f;
const float SOUND_SPIKE_THRESHOLD = 300.0f;
const float TEMPERATURE_SPIKE_THRESHOLD = 2.0f;

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
float calculateComparisonAverage(const float history[], int startIndex);
Trend getTrend(const float history[], int size, float threshold);
bool detectSpike(const float history[], int size, float threshold);
void updateSensorData();