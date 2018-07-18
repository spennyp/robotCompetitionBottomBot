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

// /// Checks if the bottom bot is in position to deploy top bot, and adjusts if not
// void bottomBotPlankCheck() {
// 	bool lPlankSensor = digitalRead(leftPlankQRD);
// 	bool rPlankSensor = digitalRead(rightPlankQRD);
// 	if(lPlankSensor && rPlankSensor) {
// 		switchToTopBot();
// 	} else if(lPlankSensor) {
// 		motorWheel.turnLeft(5);
// 	} else if(rPlankSensor) {
// 		motorWheel.turnRight(5);
// 	}
// }

