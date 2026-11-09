#include <iostream> 
#include "processing.h"

SensorData light; 
SensorData sound;
SensorData temperature;

// arrays used to store the values 
float lightHistory[HISTORY_SIZE] = {0}; 
float soundHistory[HISTORY_SIZE] = {0};
float temperatureHistory[HISTORY_SIZE] = {0};

// smoothing data to make it more consistent and stable 
// and make more assured decisions based off of it 
float smoothData(const float history[], int size) {
    float sum = 0; 
    for (int i = 0; i < size; i++) {
        sum += history[i];
    }
    return sum / size;
}

// helper function for getTrend() 
// calculates average between 3 adjacent values 
// within the sensor history array
float calculateComparisonAverage(const float history[], int startIndex) {
    float sum = 0;
    for (int i = startIndex; i <= startIndex + 2; i++) {
        sum += history[i];
    }
    return sum / COMPARISON_AVERAGE_WINDOW;
}

// determines trend of sensor values (increaseing, decreasing, stable)
// by comparing adjacent rolling averages through the history array
Trend getTrend(const float history[], int size, float threshold) {
    int increasingCount = 0;
    int decreasingCount = 0;
    for (int i = 0; i < size - 6; i++) { // indexes set to not leave array
        float avg1 = calculateComparisonAverage(history, i); 
        float avg2 = calculateComparisonAverage(history, i + 4);
        // compares adjacent averages to the threshold 
        // and increases approriate count 
        if (avg1 < avg2 - threshold) { 
            increasingCount++;
        } else if (avg1 > avg2 + threshold) {
            decreasingCount++;
        }
    }
    // determines trend if trend type persisted more than the trend decider amount
    if (increasingCount > TREND_DECIDER) {
        return INCREASING;
    } else if (decreasingCount > TREND_DECIDER) {
        return DECREASING;
    } else {
        return STABLE;
    }
}

// returns enum values as strings so they can be displayed on the dashboard 
std::string trendToString(Trend trend) {
    switch (trend) {
        case DECREASING:
            return "Decreasing";
        case STABLE:
            return "Stable";
        case INCREASING:
            return "Increasing";
        default:
            return "Unknown";
    }
}

// detects sudden increase or decrease in sensor readings 
// that exceed spike thresholds 
bool detectSpike(const float history[], int size, float threshold) {
    for (int i = 1; i < size - 1; i++) {
        if ((history[i] > history[i + 1] + threshold && 
            history[i] > history[i - 1] + threshold) || 
            (history[i] < history[i + 1] - threshold && 
            history[i] < history[i - 1] - threshold)) {
            return true; // checking if adjacent values exceed threshold 
        }
    }
    return false;
}

// turns bool into strings so they can be displayed on the dashboard 
std::string spikeDetectedToString(bool spikeDetected) {
    if (spikeDetected) {
        return "Spike Detected";
    } else {
        return "No Spike Detected";
    }
}

// appends sensor values to history array
void addSensorData(float lightValue, float soundValue, float temperatureValue) {
    for (int i = 0; i < HISTORY_SIZE - 1; i++) {
        // shifting previous values to beginning of the array 
        // and makes space for new readings
        lightHistory[i] = lightHistory[i + 1];
        soundHistory[i] = soundHistory[i + 1];
        temperatureHistory[i] = temperatureHistory[i + 1];
    }
    lightHistory[HISTORY_SIZE - 1] = lightValue;
    soundHistory[HISTORY_SIZE - 1] = soundValue;
    temperatureHistory[HISTORY_SIZE - 1] = temperatureValue;
}

// updating smoothed values, trends, and spike detection for each sensor using stored history 
void updateSensorData() {
    light.currentValue = smoothData(lightHistory, HISTORY_SIZE);
    light.trend = getTrend(lightHistory, HISTORY_SIZE, LIGHT_TREND_THRESHOLD);
    light.spikeDetected = detectSpike(lightHistory, HISTORY_SIZE, LIGHT_SPIKE_THRESHOLD);

    sound.currentValue = smoothData(soundHistory, HISTORY_SIZE);
    sound.trend = getTrend(soundHistory, HISTORY_SIZE, SOUND_TREND_THRESHOLD);
    sound.spikeDetected = detectSpike(soundHistory, HISTORY_SIZE, SOUND_SPIKE_THRESHOLD);

    temperature.currentValue = smoothData(temperatureHistory, HISTORY_SIZE);
    temperature.trend = getTrend(temperatureHistory, HISTORY_SIZE, TEMPERATURE_TREND_THRESHOLD);
    temperature.spikeDetected = detectSpike(temperatureHistory, HISTORY_SIZE, TEMPERATURE_SPIKE_THRESHOLD);
}