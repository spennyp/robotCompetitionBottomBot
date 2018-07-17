// Claw.cpp

#include "Claw.h"
#include "Globals.h"

// TODO: Figure out what these 6 values should be, also add them to the menu instead of here?
const int clawServoOpenAngle = 50;
const int clawServoGrabAngle = 0;
const int dumpServoNormalAngle = 0;
const int dumpServoDumpAngle = 180;
const int dumpServoDumpTime = 2000;
const int grabServoDumpReleaseTime = 1000;
const int winchSpeed = 255;


// API

Claw::Claw() {
    switchingBots = false;
    homeLimitSwitch = bottomLimitSwitch;
    raising = false;
}

void Claw::grab() {
    setServo(clawGrabServo, clawServoGrabAngle); 
    raise();
}

void Claw::switchToTopBot() {
    if(homeLimitSwitch != middleLimitSwitch) {
        homeLimitSwitch = middleLimitSwitch;
        switchingBots = true;
        raise();
    }
}


// Lifecycle

// returns true once starts to lower
bool Claw::poll() {
    bool topSwitch = digitalRead(topLimitSwitch);
    bool homeSwitch = digitalRead(homeLimitSwitch);
    bool hasObj = hasObject();
    if(topSwitch || homeSwitch || (!hasObj && !switchingBots && raising)) {
        motor.speed(winchMotor, 0);
        raising = false;
        if(topSwitch && hasObj) {
            dump();
            lower();
            return true;
        } else if(!homeSwitch) {
            lower();
            open();
            return true;
        } else if(homeSwitch && switchingBots) {
            switchingBots = false;
        }
    }
    return false;
}


// Helpers

void Claw::raise() {
    if (!digitalRead(topLimitSwitch)) {
        raising = true;
        motor.speed(winchMotor, winchSpeed);
    }
}

void Claw::lower() {
    if (!digitalRead(homeLimitSwitch)) {
        raising = false;
        motor.speed(winchMotor, -winchSpeed);
    }
}

bool Claw::hasObject() {
    // Check if the object is in the claw somehow, may not use
    return true;
}

void Claw::dump() {
    setServo(clawDumpServo, dumpServoDumpAngle);
    delay(dumpServoDumpTime);
    open();
    delay(grabServoDumpReleaseTime);
    setServo(clawDumpServo, dumpServoNormalAngle);
    delay(grabServoDumpReleaseTime); // TODO: Change this delay?
}

void Claw::open() {
    setServo(clawGrabServo, clawServoOpenAngle); 
}

