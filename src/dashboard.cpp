#include "sensors/light.h"
#include "sensors/sound.h"
#include "sensors/temperature.h"

#include "processing.h"
#include "comfort_engine.h"
#include "dashboard.h"

#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

// replace WiFi name and password to network where ESP32 will be connected 
// device displaying dashboard also needs to be connected to that WiFi
// would recommend using hotspot as eduroam cannot be used like this 
const char* ssid = "YOUR_WIFI_NAME"; 
const char* password = "YOUR_WIFI_PASSWORD";

// creates WebServer object on port 80
WebServer server(80); 

void initDashboard() {
    // Connect to Wi-Fi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); // IP which can be used to access dashboard 

    // associates URLs with functions that return their content 
    server.on("/", handleRoot); 
    server.on("/dashboard.css", handleCSS); 
    server.on("/dashboard.js", handleJS); 
    server.on("/data", handleData); 

    // starts server 
    server.begin(); 
    Serial.println("HTTP server started");
}

void updateDashboard() {
    // checks for incoming broswer requests 
    // and calls corresponding route handler function 
    server.handleClient();
}

void handleRoot() {
    File file = LittleFS.open("/dashboard.html"); // opens HTML file 
    if(!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    // sends files content from LittleFS to browser
    server.streamFile(file, "text/html"); 

    file.close();
}

void handleCSS() {
    File file = LittleFS.open("/dashboard.css"); // opens CSS file 
    if(!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    // sends files content from LittleFS to browser
    server.streamFile(file, "text/css"); 

    file.close();
}

void handleJS() {
    File file = LittleFS.open("/dashboard.js"); // opens JS file
    if(!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    // sends files content from LittleFS to browser
    server.streamFile(file, "text/javascript"); 

    file.close();
}

// Dashboard.js requests this information every second using fetch('/data')
// creating JSON string which holds dashboard information 
void handleData() {
    // ToString functions convert enums to strings so they can be appended 
    // .c_str() returns C-style string equivalent so it can be appended 
    // String(...) converts number to JSON string 
    String json = "{";
    json += "\"overallComfort\":\""; 
    json += comfortLevelToString(comfort.overallComfortLevel).c_str();
    json += "\",";
    json += "\"recommendation\":\"";
    json += comfort.recommendation.c_str();
    json += "\",";
    json += "\"comfortBreakdown\":";
    json += String(comfort.overallComfortScore);
    json += ",";
    json += "\"lightBreakdown\":"; 
    json += String(comfort.lightContribution);
    json += ",";
    json += "\"soundBreakdown\":"; 
    json += String(comfort.soundContribution);
    json += ",";

    // if temperature is not connected displays "Not Connected"
    // rather than inaccurate value 
    if (!temperatureConnected) {
        json += "\"temperatureBreakdown\":\"Not Connected\",";
    }
    else {
        json += "\"temperatureBreakdown\":";
        json += String(comfort.temperatureContribution);
        json += ",";
    }

    json += "\"lightLevel\":\""; 
    json += comfortLevelToString(comfort.lightLevel).c_str();
    json += "\",";
    json += "\"lightTrend\":\""; 
    json += trendToString(light.trend).c_str();
    json += "\",";
    json += "\"lightSpike\":\""; 
    json += spikeDetectedToString(light.spikeDetected).c_str(); 
    json += "\",";
    json += "\"soundLevel\":\""; 
    json += comfortLevelToString(comfort.soundLevel).c_str();
    json += "\",";
    json += "\"soundTrend\":\""; 
    json += trendToString(sound.trend).c_str();
    json += "\",";
    json += "\"soundSpike\":\""; 
    json += spikeDetectedToString(sound.spikeDetected).c_str();
    json += "\",";

    // if temperature is not connected displays "Not Connected"
    // rather than inaccurate value 
    if (!temperatureConnected) {
        json += "\"temperatureCurrent\":\"Not Connected\",";
        json += "\"temperatureLevel\":\"Not Connected\",";
        json += "\"temperatureTrend\":\"Not Connected\",";
        json += "\"temperatureSpike\":\"Not Connected\"";
    }
    else {
        json += "\"temperatureCurrent\":"; 
        json += String(temperature.currentValue); 
        json += ",";
        json += "\"temperatureLevel\":\""; 
        json += comfortLevelToString(comfort.temperatureLevel).c_str();
        json += "\",";
        json += "\"temperatureTrend\":\""; 
        json += trendToString(temperature.trend).c_str();
        json += "\",";
        json += "\"temperatureSpike\":\""; 
        json += spikeDetectedToString(temperature.spikeDetected).c_str();
        json += "\"";
    }

    json += "}";
    server.send(200, "application/json",json); // sends information to browser 
}