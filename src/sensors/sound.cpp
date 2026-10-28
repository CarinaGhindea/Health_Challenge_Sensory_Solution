#include "sound.h"

const int SOUND_PIN = A1; // Define the pin for the sound sensor
const int NUM_SAMPLES = 32; // Number of samples to average

void initSound() {
    pinMode(SOUND_PIN, INPUT); // Set the sound sensor pin as input
}

int readSound() {
    long sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += analogRead(SOUND_PIN); 
    }
    int soundValue = sum / NUM_SAMPLES; // Divide by NUM_SAMPLES to get the average value
    return soundValue;
}