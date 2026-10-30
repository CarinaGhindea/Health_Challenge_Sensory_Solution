#include "comfort_engine.h"
#include <math.h>

ComfortContribution comfort;

float calculateRawSensoryContribution(float currentValue, float lowThreshold, float highThreshold) {
    float rawContribution = 0.0f;
    float middleThreshold = (lowThreshold + highThreshold) / 2.0f;
    if (currentValue < lowThreshold) {
        rawContribution = abs(lowThreshold - currentValue) / middleThreshold * 100.0f;
    }
    else if (currentValue > highThreshold) {
        rawContribution = abs(currentValue - highThreshold) / middleThreshold * 100.0f;
    }
    return rawContribution;
}

float calculateSensoryContribution(float currentValue, float lowThreshold, float highThreshold, Trend trend, bool spikeDetected) {
    float sensoryContribution = 0; 
    if (currentValue < lowThreshold) {
        sensoryContribution = calculateRawSensoryContribution(currentValue, lowThreshold, highThreshold);
        if (trend == DECREASING) {
            sensoryContribution += 5; 
        }
    } else if (currentValue > highThreshold) {
         sensoryContribution = calculateRawSensoryContribution(currentValue, lowThreshold, highThreshold);
         if (trend == INCREASING) {
            sensoryContribution += 5;
         }
    }
    if (spikeDetected) {
        sensoryContribution += 5; 
    }
    return sensoryContribution;
}

float calculateOverallComfortScore(float lightContribution, float soundContribution, float temperatureContribution) {
    float overallComfortScore = 100.0f - lightContribution - soundContribution - temperatureContribution;
    if (overallComfortScore < 0.0f) {
        overallComfortScore = 0.0f; 
    }
    return overallComfortScore;
}

ComfortLevel sensoryComfortLevel(float individualSensoryContribution) {
    if (individualSensoryContribution < 5.0f) {
        return GOOD;
    } else if (individualSensoryContribution < 10.0f) {
        return MODERATE;
    } else if (individualSensoryContribution < 25.0f) {
        return ELEVATED;
    } else {
        return SEVERE;
    }
}

const char* recommendation(FlaggedSensor sensor, ComfortLevel level) {
    if (sensor == LIGHT && (level == ELEVATED || level == SEVERE)) {
        return "Reduce environmental brightness";
    }
    else if (sensor == SOUND && (level == ELEVATED || level == SEVERE)) {
        return "Reduce environmental noise level";
    }
    else if (sensor == TEMPERATURE && (level == ELEVATED || level == SEVERE)) {
        return "Adjust environmental temperature";
    }
    else if (level == MODERATE) {
        return "Monitor environmental conditions";
    }
    else {
        return "Environmental conditions are within acceptable limits";
    }
}

void updateComfortContribution(SensorData light, SensorData sound, SensorData temperature) {
    comfort.lightContribution = calculateSensoryContribution(light.currentValue, LOW_LIGHT_THRESHOLD, HIGH_LIGHT_THRESHOLD, light.trend, light.spikeDetected);
    comfort.soundContribution = calculateSensoryContribution(sound.currentValue, LOW_SOUND_THRESHOLD, HIGH_SOUND_THRESHOLD, sound.trend, sound.spikeDetected);
    comfort.temperatureContribution = calculateSensoryContribution(temperature.currentValue, LOW_TEMPERATURE_THRESHOLD, HIGH_TEMPERATURE_THRESHOLD, temperature.trend, temperature.spikeDetected);
    comfort.overallComfortScore = calculateOverallComfortScore(comfort.lightContribution, comfort.soundContribution, comfort.temperatureContribution);
}