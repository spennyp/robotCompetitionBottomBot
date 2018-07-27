// Claw.cpp

#include "Claw.h"
#include "Globals.h"
#include "Sensors.h"

// TODO: Figure out what these 6 values should be, also add them to the menu instead of here?
const int clawServoOpenAngle = 50;
const int clawServoGrabAngle = 180;
const int dumpServoNormalAngle = 8;
const int dumpServoDumpAngle = 125;
const int dumpServoDumpTime = 2000;
const int grabServoDumpReleaseTime = 1000;

const int winchSpeed = 50; // TODO: Add to menu


// API

Claw::Claw() {
    switchingBots = false;
    homeLimitSwitch = bottomHall;
    raising = false;
}

void Claw::grab() {
    setServo(clawGrabServo, clawServoGrabAngle); 
    delay(500);
    raise();
}

void Claw::switchToTopBot() {
    if(homeLimitSwitch != middleHall) {
        homeLimitSwitch = middleHall;
        switchingBots = true;
        raise();
    }
}

void Claw::reset() {
    // homeLimitSwitch = bottomHall;
    homeLimitSwitch = middleHall;
    setServo(clawDumpServo, dumpServoNormalAngle);
    close();
    delay(0);
    // lower();
}


// Lifecycle

// Returns true once starts to lower
bool Claw::poll() {
    bool topSwitch = topHallPosition();
    bool homeSwitch = homeHallPosition(homeLimitSwitch);
    if(homeSwitch || topSwitch) {
        motor.speed(winchMotor, 0);
        if(homeSwitch) {
            open();
        } else {
            dump();
            lower();
            return true;
        }
    }
    return false;

    // if(topSwitch || homeSwitch || (!hasObj && !switchingBots && raising)) {
    //     motor.speed(winchMotor, 0);
    //     raising = false;
    //     if(topSwitch && hasObj) {
    //         dump();
    //         lower();
    //         return true;
    //     } else if(!homeSwitch) {
    //         lower();
    //         open();
    //         return true;
    //     } else if(homeSwitch && switchingBots) {
    //         switchingBots = false;
    //     } else if(homeSwitch) {
    //         claw.open();
    //     }
    // }
}


// Helpers

void Claw::raise() {
    if (!topHallPosition()) {
        raising = true;
        motor.speed(winchMotor, winchSpeed);
    }
}

void Claw::lower() {
    if (!homeHallPosition(homeLimitSwitch)) {
        raising = false;
        motor.speed(winchMotor, -winchSpeed);  
    }
}

void Claw::dump() {
    setServo(clawDumpServo, dumpServoDumpAngle);
    delay(dumpServoDumpTime);
    open();
    delay(grabServoDumpReleaseTime);
    setServo(clawDumpServo, dumpServoNormalAngle);
    close();
    delay(grabServoDumpReleaseTime); 
}

void Claw::open() {
    setServo(clawGrabServo, clawServoOpenAngle); 
}

void Claw::close() {
    setServo(clawGrabServo, clawServoGrabAngle); 
}

