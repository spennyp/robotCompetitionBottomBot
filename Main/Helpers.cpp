// Helpers.cpp

#include "Helpers.h" 
#include "Globals.h"

// Sensors
bool clawTriggered(){
    return digitalRead(stopPin);
}
bool foundCliff(){
    return (analogRead(leftCliffQRD) > cliffThreshold.value);
}

    


// RunHelpers
// Reset constants
const int bridgeServoResetPosition = 90;

// Deploy constants
const int bridgeServoDeployPosition = 150;

void deployBridge()
{
    bottomServo.write(bridgeServoDeployPosition);
}

void resetBridge() {
    bottomServo.write(bridgeServoResetPosition);
}


//Sensors
bool bridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value && analogRead(leftBridgeQRD) < alignmentThreshold.value);
}


bool leftBridgeAligned() {
    return (analogRead(leftBridgeQRD) < alignmentThreshold.value);
}


bool rightBridgeAligned() {
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value);
}

