// Test.cpp

#include "Test.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"

MotorWheel testMotorWheel(motorSpeed, PID(proportionalGain, derivativeGain, pidThreshold));

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

void testFullSystem() {
    LCD.clear(); LCD.print("Testing PID "); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
    while (!startbutton()){
        testPIDQRD();
        delay(100);
    }
    LCD.clear(); LCD.print("Testing Cliff "); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
    while (!startbutton()){
        testCliffQRD();
        delay(100);
    }
    LCD.clear(); LCD.print("Testing Bridge "); LCD.setCursor(0, 1); LCD.print("QRD's"); delay(1000);
    while (!startbutton()) {
        testBridgeQRD();
        delay(100);
    }
    LCD.clear(); LCD.print("Testing Servo");
    delay(1000);
    while (!startbutton()){
        testServo();
        delay(100);
    }

    LCD.clear(); LCD.print("Testing turning"); LCD.setCursor(0, 1); delay(1000);
	while(!startbutton()) {
		testTurning();
	}
}

void testPIDQRD() {
	LCD.clear(); LCD.print("FarQRD: "); LCD.print(analogRead(farTapeFollowQRD));
	LCD.setCursor(0,1); LCD.print("NearQRD: "); LCD.print(analogRead(nearTapeFollowQRD));
}

void testCliffQRD() {
	LCD.clear(); LCD.print("LCliffQRD: "); LCD.print(analogRead(leftCliffQRD));
    LCD.setCursor(0,1); LCD.print("RCliffQRD: "); LCD.print(analogRead(rightCliffQRD));
}

void testBridgeQRD() {
    LCD.clear(); LCD.print("LBridgeQRD: "); LCD.print(analogRead(leftBridgeQRD));
    LCD.setCursor(0,1); LCD.print("RBridgeQRD: "); LCD.print(analogRead(rightBridgeQRD));
}

void testServo() {
    LCD.clear(); LCD.print("Let Go"); 
    deployBridge();
    delay(1000);
    if(startbutton()) { return; }
    LCD.clear(); LCD.print("Hold");
    resetBridge();
    delay(1000);
}

void testTurning() {
	testMotorWheel.turnRight(90);
	delay(1000);
	if(startbutton()) { return; }
	testMotorWheel.turnLeft(90);
	delay(1000);
	if(startbutton()) { return; }
	testMotorWheel.turnRight(180);
	delay(1000);
	if(startbutton()) { return; }
	testMotorWheel.turnLeft(180);
	delay(1000);
}



