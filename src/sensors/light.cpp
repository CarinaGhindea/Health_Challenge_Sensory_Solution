#include "light.h"

const int LIGHT_PIN = A0; // define the pin for the light sensor - pin 1 on the ESP32 board

void initLight() {
    pinMode(LIGHT_PIN, INPUT); 
}

int readLight() {
    // code referenced from
    // https://www.hackster.io/ingo-lohs/grove-introduction-in-a-light-sensor-a55efd
    int lightValue = analogRead(LIGHT_PIN); // read the current light sensor ADC reading 
    return lightValue; 
}