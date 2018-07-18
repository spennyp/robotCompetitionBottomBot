// Claw.cpp

#include "Claw.h"
#include "Globals.h"
#include "Sensors.h"

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

void Claw::reset() {
    homeLimitSwitch = bottomLimitSwitch;
    close();
    while(!lower()) {}
    open();
}


// Lifecycle

// Returns true once starts to lower
bool Claw::poll() {
    bool topSwitch = digitalRead(topLimitSwitch);
    bool homeSwitch = digitalRead(homeLimitSwitch);
    bool hasObj = clawHasObject();
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

bool Claw::lower() {
    if (!digitalRead(homeLimitSwitch)) {
        raising = false;
        motor.speed(winchMotor, -winchSpeed);  
        return false;
    }
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

void Claw::close() {
    setServo(clawGrabServo, clawServoGrabAngle); 
}

