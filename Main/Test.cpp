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
    LCD.clear(); LCD.print("Low");
    digitalWrite(5, LOW);
    delay(2000);
}


// System Test

void systemTest() {
    LCD.clear(); LCD.print("Caution, motors"); LCD.setCursor(0, 1); LCD.print("will be on"); delay(1000);

    LCD.clear(); LCD.print("Testing Bridge"); delay(1000);
    while (!startbutton()){
        testBridge();
    }

    LCD.clear(); LCD.print("Test Bridge align"); delay(1000);
    while(!startbutton()) {
        testBridgeAlign();
    }
    testMotorWheel.stop();

    LCD.clear(); LCD.print("Test Cliff align"); delay(1000);
    while(!startbutton()) {
        testCliffAlign();
    }
    testMotorWheel.stop();

    LCD.clear(); LCD.print("Testing turning"); LCD.setCursor(0, 1); delay(1000);
	while(!startbutton()) {
		testTurning();
	}
}

void testBridge() {
    LCD.clear(); LCD.print("Let Go"); 
    deployBridge();
    delay(1000);
    if(startbutton()) { return; }
    LCD.clear(); LCD.print("Hold");
    resetBridge();
    delay(1000);
}

void testBridgeAlign() {
    if(alignBridgeQRDs(testMotorWheel)) {
        testMotorWheel.stop();
    }
    delay(10);
}

void testCliffAlign() {
    alignCliffQRDs(testMotorWheel);
    delay(10);
}

void testTurning() {
	testMotorWheel.turnRight(90);
	delay(1000);
	if(startbutton()) { return; }
	testMotorWheel.turnLeft(90);
	delay(1000);
}



