#include "light.h"

const int LIGHT_PIN = A0; // Define the pin for the light sensor - pin 1 on the ESP32 board

void initLight() {
    pinMode(LIGHT_PIN, INPUT); // Set the light sensor pin as input
}

int readLight() {
    int lightValue = analogRead(LIGHT_PIN); // Read the analog value from the light sensor
    return lightValue; 
}