// Sensors.cpp

#include "Sensors.h"
#include "Globals.h"
#include <Arduino.h>
#include "Menu.h"

bool clawTriggered() {
	return digitalRead(stopPin);
}

bool foundLeftCliff() {
	return (analogRead(leftCliffQRD) > cliffThreshold.value);
}

bool foundRightCliff() {
	return (analogRead(rightCliffQRD) > cliffThreshold.value);
}

bool bridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value && analogRead(leftBridgeQRD) < alignmentThreshold.value);
}


bool leftBridgeAligned() {
    return (analogRead(leftBridgeQRD) < alignmentThreshold.value);
}


bool rightBridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value);
}





