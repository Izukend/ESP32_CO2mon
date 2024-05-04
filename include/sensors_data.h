/**
 * @file sensors_data.h
 * @date 2024-04-05
 * @author Matthieu et Tom
 */

#include "MHZ19.h"
#include <Arduino.h>
#include "DHTesp.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include "SSD1306Wire.h"

extern MHZ19 myMHZ19;
extern SoftwareSerial mySerial;

extern int recoverCO2Data();
extern int recoverTemp();
extern int recoverHum();
extern String oledData();