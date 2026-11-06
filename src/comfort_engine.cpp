#include "sensors/temperature.h"
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
    float overallComfortScore = 100.0f;
    if (!temperatureConnected) {
        overallComfortScore -= (lightContribution + soundContribution); 
    }
    else {
        overallComfortScore -= (lightContribution + soundContribution + temperatureContribution);
    }
    if (overallComfortScore < 0.0f) {
        overallComfortScore = 0.0f; 
    }
    return overallComfortScore;
}

ComfortLevel sensoryComfortLevel(float contribution) {
    if (contribution < 5.0f) {
        return GOOD;
    } else if (contribution < 10.0f) {
        return MODERATE;
    } else if (contribution < 25.0f) {
        return POOR;
    } else {
        return SEVERE;
    }
}

std::string comfortLevelToString(ComfortLevel level) {
    switch (level) {
        case GOOD:
            return "Good";
        case MODERATE:
            return "Moderate";
        case POOR:
            return "Poor";
        case SEVERE:
            return "Severe";
        default:
            return "Unknown";
    }
}

std::string recommendation(ComfortLevel lightLevel, ComfortLevel soundLevel, ComfortLevel temperatureLevel) {
    std::string recommendation = "";
    if ((lightLevel == POOR || lightLevel == SEVERE)) {
        recommendation += "Adjust environmental brightness. ";
    }
    if ((soundLevel == POOR || soundLevel == SEVERE)) {
        recommendation += "Reduce environmental noise level. ";
    }
    if ((temperatureLevel == POOR || temperatureLevel == SEVERE)) {
        recommendation += "Adjust environmental temperature. ";
    }
    if (recommendation.empty() && (lightLevel == MODERATE || soundLevel == MODERATE || temperatureLevel == MODERATE)) {
        recommendation += "Monitor environmental conditions. ";
    }
    if (recommendation.empty()) {
        recommendation += "Environmental conditions are within acceptable limits. ";
    }
    return recommendation;
}

void updateComfortContribution(SensorData light, SensorData sound, SensorData temperature) {
    comfort.lightContribution = calculateSensoryContribution(light.currentValue, LOW_LIGHT_THRESHOLD, HIGH_LIGHT_THRESHOLD, light.trend, light.spikeDetected);
    comfort.soundContribution = calculateSensoryContribution(sound.currentValue, LOW_SOUND_THRESHOLD, HIGH_SOUND_THRESHOLD, sound.trend, sound.spikeDetected);
    comfort.temperatureContribution = calculateSensoryContribution(temperature.currentValue, LOW_TEMPERATURE_THRESHOLD, HIGH_TEMPERATURE_THRESHOLD, temperature.trend, temperature.spikeDetected);
    comfort.overallComfortScore = calculateOverallComfortScore(comfort.lightContribution, comfort.soundContribution, comfort.temperatureContribution);
    
    comfort.lightLevel = sensoryComfortLevel(comfort.lightContribution);
    comfort.soundLevel = sensoryComfortLevel(comfort.soundContribution);
    comfort.temperatureLevel = sensoryComfortLevel(comfort.temperatureContribution);
    comfort.overallComfortLevel = sensoryComfortLevel(100.0f - comfort.overallComfortScore);
    comfort.recommendation = recommendation(comfort.lightLevel, comfort.soundLevel, comfort.temperatureLevel);
}