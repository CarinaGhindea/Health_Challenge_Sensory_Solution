/* Grove - Light Sensor demo v1.0
* 
* Signal wire to A0.
* By: http://www.seeedstudio.com
*/
/*
#include <Arduino.h>
#include <math.h>

#define LIGHT_SENSOR A0//Grove - Light Sensor is connected to A0 of Arduino
float Rsensor; //Resistance of sensor in K
void setup() 
{
    Serial.begin(115200);                //Start the Serial connection
}
void loop() 
{
    int sensorValue = analogRead(LIGHT_SENSOR); 
    Rsensor = (float)(1023-sensorValue)*10/sensorValue;
    Serial.println("the analog read data is ");
    Serial.println(sensorValue);
    Serial.println("the sensor resistance is ");
    Serial.println(Rsensor,DEC);//show the ligth intensity on the serial monitor;
    delay(1000); 
} */