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
  
  File file = LittleFS.open("/dashboard.html");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();

    initDashboard();
}

void loop()
{
    updateDashboard();
}