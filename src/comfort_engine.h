#pragma once 

#include "processing.h"

const float LOW_LIGHT_THRESHOLD = 1500.0f; 
const float LOW_SOUND_THRESHOLD = 0.0f;
const float LOW_TEMPERATURE_THRESHOLD = 18.0f;

const float HIGH_LIGHT_THRESHOLD = 2200.0f;
const float HIGH_SOUND_THRESHOLD = 800.0f;
const float HIGH_TEMPERATURE_THRESHOLD = 24.0f;

struct ComfortContribution {
    float lightContribution;
    float soundContribution;
    float temperatureContribution;
    float overallComfortScore;
};

enum ComfortLevel {
    GOOD, 
    MODERATE,
    ELEVATED,
    SEVERE
};

float calculateRawSensoryContribution(float currentValue, float lowThreshold, float highThreshold);
float calculateSensoryContribution(float currentValue, float lowThreshold, float highThreshold, Trend trend, bool spikeDetected); 
float calculateOverallComfortScore(float lightContribution, float soundContribution, float temperatureContribution);
ComfortLevel sensoryComfortLevel(float individualSensoryContribution);
void updateComfortContribution(SensorData light, SensorData sound, SensorData temperature);