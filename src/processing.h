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

float smoothLight(const float lightHistory[], int size);
Trend trendLight(const float lightHistory[], int size);
bool spikeLight(const float lightHistory[], int size);

float smoothSound(const float soundHistory[], int size);
Trend trendSound(const float soundHistory[], int size);
bool spikeSound(const float soundHistory[], int size);

float smoothTemperature(const float temperatureHistory[], int size);
Trend trendTemperature(const float temperatureHistory[], int size);
bool spikeTemperature(const float temperatureHistory[], int size);