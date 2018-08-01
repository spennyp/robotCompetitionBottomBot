// Sensors.cpp

#include "Sensors.h"
#include "Globals.h"
#include <Arduino.h>
#include "Menu.h"

bool clawTriggered() {
	return digitalRead(stopPin);
}

bool foundCliff() {
	return (analogRead(cliffQRD) > cliffThreshold.value);
}

bool bridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold && analogRead(leftBridgeQRD) < alignmentThreshold);
}


bool leftBridgeAligned() {
    return (analogRead(leftBridgeQRD) < alignmentThreshold);
}


bool rightBridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold);
}





