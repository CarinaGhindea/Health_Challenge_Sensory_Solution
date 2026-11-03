#include "dashboard.h"
#include "comfort_engine.h"
#include "processing.h"

#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

const char* ssid = "CarinaiPhone";
const char* password = "u6zr47zj5i0y";

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
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/dashboard.css", handleCSS);
    server.on("/dashboard.js", handleJS);
    server.on("/data", handleData);

    server.begin();
    Serial.println("HTTP server started");
}

void updateDashboard() {
    server.handleClient();
}

void handleRoot() {
    File file = LittleFS.open("/dashboard.html");
    if(!file){
    Serial.println("Failed to open file for reading");
    return;
    }

    server.streamFile(file, "text/html"); 

    file.close();
}

void handleCSS() {
    File file = LittleFS.open("/dashboard.css");
    if(!file){
    Serial.println("Failed to open file for reading");
    return;
    }

    server.streamFile(file, "text/css"); 

    file.close();
}

void handleJS() {
    File file = LittleFS.open("/dashboard.js");
    if(!file){
    Serial.println("Failed to open file for reading");
    return;
    }

    server.streamFile(file, "text/javascript"); 

    file.close();
}

void handleData() {
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
    json += "\"temperatureBreakdown\":"; 
    json += String(comfort.temperatureContribution);
    json += ",";
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
    json += "}";
    server.send(200, "application/json",json);
}