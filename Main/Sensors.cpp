// Sensors.cpp

#include "Sensors.h"
#include "Globals.h"
#include <Arduino.h>

const int cliffQRDThreshold = 200;


bool checkCodeRedSwitch() {
    return digitalRead(codeRedSwitch);
}

bool clawIRTriggered() {
	return digitalRead(clawIR);
}

bool topBotFoundCliff() {
	return (analogRead(bottomCliffQRD) > cliffQRDThreshold);
}

bool bottomBotFoundCliff() {
    return (analogRead(topCliffQRD) > cliffQRDThreshold);
}

extern bool leftPlankInPosition() {
    return digitalRead(leftPlankQRD);
}

extern bool rightPlankInPosition() {
    return digitalRead(rightPlankQRD);
}







