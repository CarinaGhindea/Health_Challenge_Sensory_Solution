#include "sound.h"

const int SOUND_PIN = A1; // define the pin for the sound sensor - pin 2 on the ESP32 board
const int NUM_SAMPLES = 32; // number of ADC readings used to average sound value

void initSound() {
    pinMode(SOUND_PIN, INPUT); 
}

int readSound() {
    // ADC sampling code referenced from 
    // https://wiki.seeedstudio.com/Grove-Sound_Sensor/
    long sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += analogRead(SOUND_PIN); // accumulate ADC values 
    }
    int soundValue = sum / NUM_SAMPLES; // calculating average sound ADC value 
    return soundValue;
}