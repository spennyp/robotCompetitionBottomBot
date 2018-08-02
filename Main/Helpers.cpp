// Helpers.cpp

#include "Helpers.h"
#include "Globals.h"

const int bridgeDropDelay = 2000;
const int bridgeDriveDelay = 3000;

int cliffCount = 0;

// Sensors
bool clawTriggered()
{
    return digitalRead(stopPin);
}
bool foundCliff()
{
    return (analogRead(leftCliffQRD) > cliffThreshold.value);
}

// Reset constants
const int bridgeServoResetPosition = 90;

// Deploy constants
const int bridgeServoDeployPosition = 150;

void deployBridge()
{
    bottomServo.write(bridgeServoDeployPosition);
}

void resetBridge()
{
    bottomServo.write(bridgeServoResetPosition);
}

//Sensors
bool bridgeAligned()
{
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value && analogRead(leftBridgeQRD) < alignmentThreshold.value);
}

bool leftBridgeAligned()
{
    return (analogRead(leftBridgeQRD) < alignmentThreshold.value);
}

bool rightBridgeAligned()
{
    return (analogRead(rightBridgeQRD) < alignmentThreshold.value);
}

//Performs maneuvers necessary to navigate cliffs.
void checkCliffs(MotorWheel motorWheel)
{
    bool foundCliffs = foundCliff();
    if (foundCliffs && cliffCount == 0)
    {
        motorWheel.stop();
        motorWheel.reverse(100);
        delay(50);
        motorWheel.turnLeft(90, 100, false);
        motorWheel.runWithPID = true;
        cliffCount++;
    }
    else if (foundCliffs && cliffCount == 1)
    {
        motorWheel.reverse(100);
        delay(20);
        deployBridge();
        cliffCount++;
        delay(bridgeDropDelay);
        motorWheel.forward(150);
        delay(bridgeDriveDelay);
        motorWheel.runWithPID = true;
    }
    return;
}

void alignBridgeQRDS(MotorWheel motorWheel)
{
    bool isLeftBridgeAligned = leftBridgeAligned();
    bool isRightBridgeAligned = rightBridgeAligned();
    if (cliffCount == 2 && isLeftBridgeAligned && isRightBridgeAligned)
    {
        motorWheel.stop();
        digitalWrite(detachPin, HIGH);
        while (true)
        {
            delay(5000);
        }
    }
    else if (cliffCount == 2 && isLeftBridgeAligned && !isRightBridgeAligned)
    {
        motor.speed(leftMotor, -75);
        motor.speed(rightMotor, 100);
    }
    else if (cliffCount == 2 && !isLeftBridgeAligned && isRightBridgeAligned)
    {
        motor.speed(leftMotor, 100);
        motor.speed(rightMotor, -75);
    }
}