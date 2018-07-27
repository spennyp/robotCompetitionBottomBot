// Sensors.cpp

#include "Sensors.h"
#include "Globals.h"
#include <Arduino.h>
#include "Menu.h"

const int cliffQRDThreshold = 300;


bool checkCodeRedSwitch() {
    return digitalRead(codeRedSwitch);
}

bool clawIRTriggered() {
	return digitalRead(clawIR);
}

bool topBotFoundCliff() {
	return (analogRead(topCliffQRD) > cliffThreshold.value);
}

bool bottomBotFoundCliff() {
    return (analogRead(bottomCliffQRD) > cliffThreshold.value);
}

bool leftPlankInPosition() {
    return digitalRead(leftPlankQRD);
}

bool rightPlankInPosition() {
    return digitalRead(rightPlankQRD);
}

bool endOfCourse() {
    return digitalRead(topBotFrontTouchSensor);
}

bool topHallPosition() {
    return !digitalRead(topHall);
}

bool homeHallPosition(int homeHallNumber) {
    return !digitalRead(homeHallNumber);
}







