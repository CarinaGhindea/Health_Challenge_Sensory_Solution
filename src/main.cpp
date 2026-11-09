#include <Arduino.h>
#include <WiFi.h>
#include "LittleFS.h"

#include "sensors/light.h"
#include "sensors/sound.h"
#include "sensors/temperature.h"

#include "processing.h"
#include "comfort_engine.h"
#include "dashboard.h"

void setup()
{
    Serial.begin(115200);
    
    if(!LittleFS.begin(true)) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    initLight(); 
    initSound();
    initTemperature();

    initDashboard();
}

// main program loop:
// 1. reads sensor values 
// 2. validates temperature sensor 
// 3. stores history of sensor data 
// 4. updates sensor data with smoothing, trend, and spike calculations 
// 5. calculates overall and invdividual comfort score and level 
// 6. updates dashboard to reflect data 

void loop()
{
    float lightValue = readLight();
    float soundValue = readSound();
    float temperatureValue = readTemperature();

    // if temperature sensor is not connected then uses most recent accurate smoothed temperature sensor value
    // to not affect calculations 
    bool temperatureConnected = checkTemperature(temperatureValue);
    if (temperatureConnected) {
        addSensorData(lightValue, soundValue, temperatureValue);
    }
    else {
        addSensorData(lightValue, soundValue, temperature.currentValue);
    }

    updateSensorData();
    updateComfortContribution(light, sound, temperature);
    updateDashboard();
}