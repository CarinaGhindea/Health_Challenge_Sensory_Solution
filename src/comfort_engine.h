#pragma once 

#include "processing.h"
#include <string>

// thresholds ranges representing comfortable environmental conditions 
// values outside these ranges contribute to discomfort 
const float LOW_LIGHT_THRESHOLD = 1500.0f; 
const float LOW_SOUND_THRESHOLD = 0.0f;
const float LOW_TEMPERATURE_THRESHOLD = 18.0f;

const float HIGH_LIGHT_THRESHOLD = 2200.0f;
const float HIGH_SOUND_THRESHOLD = 800.0f;
const float HIGH_TEMPERATURE_THRESHOLD = 24.0f;

// determined comfort levels from best to worst 
enum ComfortLevel {
    GOOD, 
    MODERATE,
    POOR,
    SEVERE
};

// stores all comofort and dashboard information 
struct ComfortContribution {
    float lightContribution;
    float soundContribution;
    float temperatureContribution;
    float overallComfortScore;

    ComfortLevel lightLevel; 
    ComfortLevel soundLevel; 
    ComfortLevel temperatureLevel; 
    ComfortLevel overallComfortLevel; 

    std::string recommendation; 
};

extern ComfortContribution comfort; // made global so it can be referenced in other files 

float calculateRawSensoryContribution(float currentValue, float lowThreshold, float highThreshold);
float calculateSensoryContribution(float currentValue, float lowThreshold, float highThreshold, Trend trend, bool spikeDetected);
float calculateOverallComfortScore(float lightContribution, float soundContribution, float temperatureContribution);
ComfortLevel sensoryComfortLevel(float contribution);
std::string comfortLevelToString(ComfortLevel level);
std::string recommendation(ComfortLevel lightLevel, ComfortLevel soundLevel, ComfortLevel temperatureLevel);
void updateComfortContribution(SensorData light, SensorData sound, SensorData temperature);