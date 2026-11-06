#include "temperature.h"
#include <math.h>

const int TEMPERATURE_PIN = A2; // Define the pin for the temperature sensor - pin 3 on the ESP32 board
const int B = 4250;            // B value of the thermistor in Kelvin 
const int R0 = 100000;            // R0 = 100k

bool temperatureConnected = true;

void initTemperature() {
    pinMode(TEMPERATURE_PIN, INPUT); // Set the temperature sensor pin as input
}

float readTemperature() {
    int analogValue = analogRead(TEMPERATURE_PIN); // Read the analog value from the temperature sensor
    float resistance = (4095.0/analogValue - 1) * R0; // Calculate the resistance of the thermistor
    float temperatureValue = 1.0 / (log(resistance / R0) / B + 1.0 / 298.15) - 273.15; // Calculate the temperature in Celsius
    return temperatureValue;
}

bool checkTemperature(float temperatureValue) {
    temperatureConnected = (temperatureValue > -25 && temperatureValue < 40);
    return temperatureConnected; 
}