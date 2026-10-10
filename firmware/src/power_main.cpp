#include "power_main.h"
#include <Arduino.h>
#include <digitalWriteFast.h>
#include "ThrusterControl.h"
#include "adc_sensors.h"

// ISR for when water is detected (executes instantly with zero-latency)
void water_detected(){
    // Immediate system kill switch and thruster shutdown
    digitalWriteFast(KS_PIN, HIGH);
}

void power_setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    
    pinMode(WATER_PIN, INPUT_PULLDOWN);
    
    // Configure KS pin as INPUT_PULLUP during initial boot check phase
    pinMode(KS_PIN, INPUT_PULLUP); 
    
    // Allow 5 seconds for system stabilization and safety checks
    delay(5000);
    
    // Reconfigure KS pin to OUTPUT and set to LOW (System Armed)
    pinMode(KS_PIN, OUTPUT);
    digitalWrite(KS_PIN, LOW);
    
    // Attach hardware interrupt for water leak detection on rising edge
    attachInterrupt(digitalPinToInterrupt(WATER_PIN), water_detected, RISING);
    
    // Initialize system thrusters
    initThrusters();
}

void setup() {
    power_setup();
}

void loop() {
    // Main execution loop for secondary tasks
}
