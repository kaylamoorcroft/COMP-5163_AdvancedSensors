// ******************************************************************
// Advanced Sensors Lab
// COMP 5163
// Acadia University
// Kayla Moorcroft (0301408m)
// 2026/10/23

// library for Arduino framework
#include <Arduino.h>
// 1-Wire sensor communication libary
#include <OneWire.h>
// DS18B20 sensor library
#include <DallasTemperature.h>
// Pin that the DS18B20 is connected to
const int oneWireBus = D3;
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);
DeviceAddress sensorAddress = { 0x28, 0xFF, 0x0A, 0x75, 0xA3, 0x15, 0x04, 0xBC };
bool programTerminated = false;

void setup() {
    Serial.begin(115200);
    Serial.println("Temperature Application");
    DS18B20.begin();

    // getAddress function returns true if address found
    if (DS18B20.getAddress(sensorAddress, 0)) { 
        Serial.println("Found DS18B20 sensor with address: 28FF0A75A31504BC");
    }
    else {
        Serial.println("No DS18B20 temperature sensors are installed!");
        programTerminated = true;
    }
}

void loop() {
    if (!programTerminated) 
    {
        float fTemp;
        DS18B20.requestTemperatures();
        // fetch the temperature. We only have 1 sensor, so the index is 0.
        fTemp = DS18B20.getTempCByIndex(0);

        Serial.print("Current temperature is: " + String(fTemp) + "˚C or ");

        if (fTemp < 10) {
            Serial.println("Cold!");
        }
        else if (fTemp < 15) {
            Serial.println("Cool");
        }
        else if (fTemp < 25) {
            Serial.println("Perfect");
        }
        else if (fTemp < 30) {
            Serial.println("Warm");
        }
        else if (fTemp < 35) {
            Serial.println("Hot");
        }
        else {
            Serial.println("Too Hot!");
        }
        delay(2000);
    }
}