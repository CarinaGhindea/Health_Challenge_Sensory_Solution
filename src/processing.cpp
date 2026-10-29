#include <iostream> 
#include "processing.h"

SensorData light; 
SensorData sound;
SensorData temperature;

float lightHistory[HISTORY_SIZE] = {0}; 
float soundHistory[HISTORY_SIZE] = {0};
float temperatureHistory[HISTORY_SIZE] = {0};

float smoothData(const float history[], int size) {
    float sum = 0; 
    for (int i = 0; i < size; i++) {
        sum += history[i];
    }
    return sum / size;
}

float calculateComparisonAverage(const float history[], int startIndex) {
    float sum = 0;
    for (int i = startIndex; i <= startIndex + 2; i++) {
        sum += history[i];
    }
    return sum / COMPARISON_AVERAGE_WINDOW;
}

Trend getTrend(const float history[], int size, float threshold) {
    int increasingCount = 0;
    int decreasingCount = 0;
    for (int i = 0; i < size - 6; i++) {
        float avg1 = calculateComparisonAverage(history, i);
        float avg2 = calculateComparisonAverage(history, i + 4);
        if (avg1 < avg2 - threshold) {
            increasingCount++;
        } else if (avg1 > avg2 + threshold) {
            decreasingCount++;
        }
    }
    if (increasingCount > TREND_DECIDER) {
        return INCREASING;
    } else if (decreasingCount > TREND_DECIDER) {
        return DECREASING;
    } else {
        return STABLE;
    }
}

bool detectSpike(const float history[], int size, float threshold) {
    for (int i = 1; i < size - 1; i++) {
        if ((history[i] > history[i + 1] + threshold && 
            history[i] > history[i - 1] + threshold) || 
            (history[i] < history[i + 1] - threshold && 
            history[i] < history[i - 1] - threshold)) {
            return true;
        }
    }
    return false;
}

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