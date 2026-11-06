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

void loop()
{
    float lightValue = readLight();
    float soundValue = readSound();
    float temperatureValue = readTemperature();

    bool temperatureConnected = checkTemperature(temperatureValue);
    if (checkTemperature(temperatureValue)) {
    addSensorData(lightValue, soundValue, temperatureValue);
    }
    else {
    addSensorData(lightValue, soundValue, temperature.currentValue);
    }

    updateSensorData();
    updateComfortContribution(light, sound, temperature);
    updateDashboard();
}