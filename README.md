# Health Challenge Sensory Solution: Environmental Monitoring System

## Overview
This project was developed as a sample solution for the Pearl Sullivan Engineering IDEAS Clinic Health Innovation Challenge. 

The Environmental Monitoring System collects data from light, sound, and temperature sensors and performs calculations to process the data. The processed values are displayed on a dashboard shows an overall comfort assessment as both a percentage and a descriptive comfort level as well as individual sensor cards with levels, trends, and spike detections. 

This solution addresses the Sensory subproblem (4.3 Recognizing and Responding to Sensory Discomfort) as it acts as a bridge between an elderly person with sensory sensitivities and their caretaker. The caretaker is able to use the dashboard to get an assessment of the environment and make adjustments to improve the comfort of the elderly person. Additionally, if the elderly person has trouble communicating their discomfort, the monitoring system provides a general gauge of the environment and provides a visual alerts to the caretaker. 

## Components 
### Hardware
- ESP32-S3
- Grove Light Sensor 
- Grove Sound Sensor 
- Grove Temperature Sensor 

### Software 
- Visual Studio Code 
- PlatformIO 
- Arduino Framework 
- LittleFS
- ESP32 WebServer Library 

## System Diagram 
![System Diagram](images/system_diagram.svg)

Data is continously collected from light, sound, and temperature sensors connected to an ESP32. The sensor readings are processed to determine comfort score, level, trend, and spikes before they are sent through the ESP32 web server and displayed on a real-time dashboard accessible over WiFi. 

## Features 
### Sensor Processing 
- Real-time enviornmental monitoring using light, sound, and temperature sensors 
- Temperature sensor value validation and disconnection visual alert 
- Sensor data smoothing with moving values 
- Trend detection with comparing moving averages (Increasing, Stable, Decreasing)
- Spike detection for sudden environemntal changes

### Comfort Assessment 
- Overall and invdividual comfort score calculation and level classification
- Environment adjustment recommendation 

### Dashboard 
- Real-time ESP32 web dashboard
- Adpative dashboard layout for desktop and mobile devices 
- WiFi access from any device on the same network

## Design Decisions 
- The temperature sensor is the only one with validation as it is the only sensor which gave readings during testing that were not possible. The light and sound sensor both gave possible readings so if those values were ruled out, actual readings could have been ruled out. When the temperature sensor is disconnected, temperature is excluded from comfort calculations while light and sound monitoring continue to function. Additionally, when the sensor is disconnected, "Not Connected" is displayed on the dashboard and the border and text colour changes to black for a visual alert. 
- The thresholds were determined after research deciding what was considered sensitive for elderly people. For light, over 1000 lux was too bright and an average lighting condition would be around 500 lux. For sound, 70 dB is considered too loud and 30-50 dB is the standard sound conditions. Temperature should stay between 20-24 degrees Celsius. The resources for these thresholds are under references below. 
- The current value for light and sound are not displayed as the Grove sensors read the ADC value (not lux or dB) which would not be useful for a caretaker to read so only the level, trend, and spike detection is displayed. Since the temperature reading is converted to Celsius, the current value is displayed as well. 
- Trend detection compares rolling averages rather than individual sensor readings to reduce the impact of short-term fluctuations. The trend detection also uses a trend decider number which determines between increasing and decreasing and to be a more definitive decider rather than constant fluctuations. The trend detection was included as it would help caretakers see if there was a gradual change in environmental conditions as that can slowly irritate someone. 
- Spike detection compares previous and following values against a threshold to determine if a difference in values is considered a spike. It was included as sudden spikes can irritate an elderly person as it is jarring. 
- The moving-average smoothing was implemented as it would average the readings to get a more accurate and stable number and get more decisive and reliable trends and spikes rather than little sensor irregularities.
- The sound sensor averages 32 ADC readings before processing. Since the sensor measures a fluctuating waveform, averaging multiple samples provides a more stable representation of the environmental noise level. 
- The colours are used as a visual alert and indication of the sensory statuses. 
- The dashboard is hosted directly on the ESP32 using LittleFS and the ESP32 WebServer library. This allows the dashboard to be accessed by any device connected to the same Wi‑Fi network without requiring external servers or cloud infrastructure.
- An adaptive dashboard layout was implemented to allow monitoring from both desktop and mobile devices. 

## Setup

## Screenshots 

## Future Improvments

## References
### Light Sensor
https://wiki.seeedstudio.com/Grove-Light_Sensor/
https://www.hackster.io/ingo-lohs/grove-introduction-in-a-light-sensor-a55efd 

### Sound Sensor
https://wiki.seeedstudio.com/Grove-Sound_Sensor/

### Temperature Sensor
https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/

These links is from where I pulled test code to test all of the sensors. 
