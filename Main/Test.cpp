// Test.cpp

#include "Test.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"

MotorWheel testMotorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));


// Diagnostics

void systemDiagnostics() {
    LCD.clear(); LCD.print("Diagnostics"); 
    LCD.setCursor(0,1); LCD.print("Exit -> HoldStop");
    while(true) {
        Serial.println("");
        Serial.print("Far QRD: "); Serial.println(analogRead(farTapeFollowQRD));
        Serial.print("Near QRD: "); Serial.println(analogRead(nearTapeFollowQRD)); 
        Serial.print("Left Cliff QRD: "); Serial.println(analogRead(leftCliffQRD)); 
        Serial.print("Right Cliff QRD: "); Serial.println(analogRead(rightCliffQRD)); 
		Serial.print("L Bridge QRD: "); Serial.println(analogRead(leftBridgeQRD)); 
		Serial.print("R Bridge QRD: "); Serial.println(analogRead(rightBridgeQRD));

        delay(500);

        if (stopbutton()) {
			delay(100);
			if (stopbutton()) {
				LCD.clear(); LCD.print("Leaving diagnositcs");
				delay(1000);
				return;
			}
		}
    }
}


// Sensor Test's

int cliffAlignCount = 0;

void sensorTest() {
    LCD.clear(); LCD.print("PID QRD's"); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
    while (!startbutton()){
        testPIDQRD();
        delay(100);
    }
    LCD.clear(); LCD.print("Cliff QRD's"); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
    while (!startbutton()){
        testCliffQRD();
        delay(100);
    }

    LCD.clear(); LCD.print("Output pin"); delay(1000);
    while(!startbutton()) {
        testCommunicationOut();
    }

    LCD.clear(); LCD.print("birdge QRD"); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
    while (!startbutton()) {
        testBridgeQRD();
        delay(100);
    }

    LCD.clear(); LCD.print("Bridge Touch"); delay(1000);
    while(!startbutton()) {
        testBridgeTouch();
    }

    LCD.clear(); LCD.print("Leaving Sensor"); LCD.setCursor(0, 1); LCD.print("testing"); delay(1000);
}

void testPIDQRD() {
	LCD.clear(); LCD.print("FarQRD: "); LCD.print(analogRead(farTapeFollowQRD));
	LCD.setCursor(0,1); LCD.print("NearQRD: "); LCD.print(analogRead(nearTapeFollowQRD));
}

void testCliffQRD() {
	LCD.clear(); LCD.print("LCliffQRD: "); LCD.print(analogRead(leftCliffQRD));
    LCD.setCursor(0, 1); LCD.print("RCliffQRD: "); LCD.print(analogRead(rightCliffQRD));
}

void testBridgeQRD() {
    LCD.clear(); LCD.print("LBridgeQRD: "); LCD.print(analogRead(leftBridgeQRD));
    LCD.setCursor(0,1); LCD.print("RBridgeQRD: "); LCD.print(analogRead(rightBridgeQRD));
}

void testCommunicationOut() {
    LCD.clear(); LCD.print("High");
    digitalWrite(5, HIGH);
    delay(2000);
    if(startbutton()) { return; }
    LCD.clear(); LCD.print("Low");
    digitalWrite(5, LOW);
    delay(2000);
}

void testBridgeTouch() {
    LCD.clear(); LCD.print("L Touch: "); LCD.print(leftBridgeTouchTriggered());
    LCD.setCursor(0, 1); LCD.print("R Touch: "); LCD.print(rightBridgeTouchTriggered());
    delay(100);
}


// System Test

void systemTest() {
    LCD.clear(); LCD.print("Caution, motors"); LCD.setCursor(0, 1); LCD.print("on in 3"); delay(3000);

    LCD.clear(); LCD.print("Testing turning"); LCD.setCursor(0, 1); delay(1000);
	while(!startbutton()) {
		testTurning();
	}

    LCD.clear(); LCD.print("Test Cliff align"); delay(1000);
    while(!startbutton()) {
        testCliffAlign();
    }
    testMotorWheel.stop();

    LCD.clear(); LCD.print("Testing Bridge"); delay(1000);
    while (!startbutton()){
        testBridge();
    }

    LCD.clear(); LCD.print("IR bridge"); LCD.setCursor(0, 1); LCD.print("QRD follow"); delay(1000);
    while(!startbutton()) {
        testBridgeQRDFollow();
    }
    testMotorWheel.stop();

    LCD.clear(); LCD.print("Touch sensor"); LCD.setCursor(0, 1); LCD.print("align"); delay(1000);
    while(!startbutton()) {
        testBridgeTouchSensorAlign();
    }
    testMotorWheel.stop();

    LCD.clear(); LCD.print("Leaving System"); LCD.setCursor(0, 1); LCD.print("Testing"); delay(1000);
}

void testTurning() {
	testMotorWheel.turnRight(90);
	delay(1000);
	if(startbutton()) { return; }
	testMotorWheel.turnLeft(90);
	delay(1000);
}

void testCliffAlign() {
    if(alignCliffQRDs(testMotorWheel)) {
		delay(100);
		testMotorWheel.reverse(75);
		while(foundLeftCliff() && foundRightCliff()) {}
		testMotorWheel.stop();
        cliffAlignCount ++;
        if(cliffAlignCount == 5) {
            cliffAlignCount = 0;
            delay(5000);
        }
    }
    delay(10);
}

void testBridge() {
    LCD.clear(); LCD.print("Let Go"); 
    deployBridge();
    delay(1000);
    if(startbutton()) { return ;}
    LCD.clear(); LCD.print("Hold");
    resetBridge();
    delay(1000);
}

void testBridgeQRDFollow() {
    followBridgeQRDs(testMotorWheel);
    delay(10);
}

void testBridgeTouchSensorAlign() {
    alignTouchSensors(testMotorWheel);
    delay(10);
}





