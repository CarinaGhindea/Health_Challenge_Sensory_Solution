#include <Arduino.h>
#include <WiFi.h>
#include "LittleFS.h"
#include "dashboard.h"

void setup()
{
    Serial.begin(115200);
    if(!LittleFS.begin(true)){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
    }

    initDashboard();
}

void loop()
{
    updateDashboard();
}