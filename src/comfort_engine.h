#pragma once 

#include "processing.h"

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

float calculateSensoryContribution(float currentValue, Trend trend, bool spikeDetected); 
float calculateOverallComfortScore(float lightContribution, float soundContribution, float temperatureContribution);
ComfortLevel sensoryComfortLevel(float overallComfortScore);
void updateComfortContribution();