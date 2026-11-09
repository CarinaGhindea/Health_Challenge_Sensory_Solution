#pragma once 

#include <string>

const int HISTORY_SIZE = 10; // number of last values used to smooth data 
const int COMPARISON_AVERAGE_WINDOW = 3; // number of values averaged to compare to the next ones
const int TREND_DECIDER = 2; // threshold that trend type will have to pass to classify a trend 

// thresholds used to determine trends 
const float LIGHT_TREND_THRESHOLD = 50.0f;
const float SOUND_TREND_THRESHOLD = 25.0f;
const float TEMPERATURE_TREND_THRESHOLD = 0.5f;

// thresholds used to determine spikes 
const float LIGHT_SPIKE_THRESHOLD = 300.0f;
const float SOUND_SPIKE_THRESHOLD = 300.0f;
const float TEMPERATURE_SPIKE_THRESHOLD = 2.0f;

// trend types 
enum Trend {
    DECREASING,
    STABLE,
    INCREASING
};

// data for each sensor group together 
struct SensorData {
    float currentValue; 
    Trend trend;
    bool spikeDetected;
};

// made global so they can be referenced in other files 
extern SensorData light;
extern SensorData sound;
extern SensorData temperature;

float smoothData(const float history[], int size);
float calculateComparisonAverage(const float history[], int startIndex);
Trend getTrend(const float history[], int size, float threshold);
std::string trendToString(Trend trend);
bool detectSpike(const float history[], int size, float threshold);
std::string spikeDetectedToString(bool spikeDetected);
void addSensorData(float lightValue, float soundValue, float temperatureValue);
void updateSensorData();