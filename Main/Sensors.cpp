// Sensors.cpp

#include "Sensors.h"
#include "Globals.h"
#include <Arduino.h>
#include "Menu.h"

bool clawIRTriggered() {
	return digitalRead(clawIR);
}

bool foundCliff() {
	return (analogRead(cliffQRD) > cliffThreshold.value);
}

bool frontTouchSensorTriggered() {
    return digitalRead(frontTouchSensor);
}

bool topHallTriggered() {
    return !digitalRead(topHall);
}

bool bottomHallTriggered() {
    return !digitalRead(bottomHall);
}







