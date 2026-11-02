#include "dashboard.h"

#include <WiFi.h>
#include <WebServer.h>

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

    server.begin();
    Serial.println("HTTP server started");
}

void updateDashboard() {
    server.handleClient();
}

void handleRoot() {
    server.send(200, "text/html", "<html><body><h1>Welcome to the Dashboard</h1></body></html>");
}