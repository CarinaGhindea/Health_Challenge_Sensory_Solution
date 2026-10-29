#include "processing.h"

SensorData light; 
SensorData sound;
SensorData temperature;

float lightHistory[HISTORY_SIZE] = {0}; 
float soundHistory[HISTORY_SIZE] = {0};
float temperatureHistory[HISTORY_SIZE] = {0};

const float lightThreshold;
const float soundThreshold;
const float temperatureThreshold;

float smoothData(const float history[], int size) {
    float sum = 0; 
    for (int i = 0; i < size - 1; i++) {
        sum += history[i];
    }
    return sum / size;
}

Trend getTrend(const float history[], int size, float threshold) {

}

float calculateComparisonAverage(const float history[], int startIndex) {

}

bool detectSpike(const float history[], int size) {

}

void updateSensorData() {

}