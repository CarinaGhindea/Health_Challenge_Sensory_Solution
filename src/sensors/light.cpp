#include "light.h"

const int LIGHT_PIN = A0; // Define the pin for the light sensor

void initLight() {
    pinMode(LIGHT_PIN, INPUT); // Set the light sensor pin as input
}

int readLight() {
    int lightValue = analogRead(LIGHT_PIN); // Read the analog value from the light sensor
    return lightValue; 
}