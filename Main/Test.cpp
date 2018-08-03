// Test.cpp

#include "Test.h"
#include "Helpers.h"
#include "Globals.h"
#include "Helpers.h"
#include <Arduino.h>
#include "Menu.h"


void systemDiagnostics() {
    LCD.clear(); LCD.print("Diagnostics"); 
    LCD.setCursor(0,1); LCD.print("Exit -> HoldStop");
    while(true) {
        Serial.println("");
        Serial.print("Far QRD: "); Serial.print(analogRead(farTapeFollowQRD)); Serial.print("  ");
        Serial.print("Near QRD: "); Serial.print(analogRead(nearTapeFollowQRD)); Serial.print("  ");
        Serial.print("Left Cliff QRD: "); Serial.print(analogRead(leftCliffQRD)); Serial.print("  ");
        Serial.print("Right Cliff QRD: "); Serial.print(analogRead(rightCliffQRD)); Serial.print("  ");
		Serial.print("L Bridge QRD: "); Serial.print(analogRead(leftBridgeQRD)); Serial.print("  ");
		Serial.print("R Bridge QRD: "); Serial.print(analogRead(rightBridgeQRD)); Serial.print("  ");

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
    LCD.clear(); LCD.print("Testing PID "); LCD.setCursor(0, 1); LCD.print("QRD's");
    delay(1000);
    while (!startbutton()){
        testPIDQRD();
        delay(100);
    }
    LCD.clear(); LCD.print("Testing Cliff "); LCD.setCursor(0, 1); LCD.print("QRD's");
    delay(1000);
    while (!startbutton()){
        testCliffQRD();
        delay(100);
    }
    LCD.clear(); LCD.print("Testing Servo");
    delay(1000);
    while (!startbutton()){
        testServo();
        delay(100);
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

void testServo() {
    LCD.clear(); LCD.print("Let Go"); 
    deployBridge();
    delay(1000);
    LCD.clear(); LCD.print("Hold");
    resetBridge();
    delay(1000);
}
