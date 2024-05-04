/**
 * @file screen.h
 * @date 2024-04-05
 * @author Matthieu et Tom
 */

#include <Wire.h>
#include "SSD1306Wire.h"
#include "sensors_data.h"

extern SSD1306Wire display;
extern void oledInit();

extern void oledErase();

extern void oledPrintData();