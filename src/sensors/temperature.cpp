#include "temperature.h"
#include <math.h>

const int TEMPERATURE_PIN = A2; // Define the pin for the temperature sensor - pin 3 on the ESP32 board

// consts referenced from 
// https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
// and sensor data sheet 
// https://www.berrybase.de/en/product-datasheet/019234a46c1b7364bfdac53da78c407c/create?srsltid=AYCX9vKbi2MFV9sZ_Fe6tFQbCHUPTxSl9p8s2eyOSe_w5k3Rx5OC1KhK
const int B = 4250;             // B value of the thermistor in Kelvin 
const int R0 = 100000;          // R0 = 100k

bool temperatureConnected = true;

void initTemperature() {
    pinMode(TEMPERATURE_PIN, INPUT); // set the temperature sensor pin as input
}

float readTemperature() {
    int analogValue = analogRead(TEMPERATURE_PIN);
    // cacluations referenced from https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
    float resistance = (4095.0/analogValue - 1) * R0; // calculating resistance of thermistor 
    float temperatureValue = 1.0 / (log(resistance / R0) / B + 1.0 / 298.15) - 273.15; // calculating temperature in Celsius
    return temperatureValue;
}

bool checkTemperature(float temperatureValue) {
    // values were determined from testing that they would reflect an unrealistic environment and the sensor requires attention
    temperatureConnected = (temperatureValue > -25 && temperatureValue < 40);
    return temperatureConnected; 
}