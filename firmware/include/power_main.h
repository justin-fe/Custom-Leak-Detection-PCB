#ifndef POWER_MAIN_H
#define POWER_MAIN_H

#include <Arduino.h>

// Pin Definitions
const int WATER_PIN = 2; // Connected to PCB leak sensor output
const int KS_PIN = 3;    // System Kill Switch line
const int LED_PIN = 13;  // Status LED

// Function Prototypes
void power_setup();
void water_detected();

#endif
