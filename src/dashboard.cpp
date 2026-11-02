#include "dashboard.h"

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Carina's iPhone";
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

    server.begin();
    Serial.println("HTTP server started");
}

void updateDashboard(SensorData light, SensorData sound, SensorData temperature, ComfortContribution comfort) {
    

}