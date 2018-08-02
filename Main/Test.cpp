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
        Serial.println("");
        Serial.print("Far QRD: "); Serial.println(analogRead(farTapeFollowQRD));
        Serial.print("Near QRD: "); Serial.println(analogRead(nearTapeFollowQRD));
        Serial.print("Left Cliff QRD: "); Serial.println(analogRead(leftCliffQRD));
		Serial.print("L Bridge QRD: "); Serial.println(analogRead(leftBridgeQRD));
		Serial.print("R Bridge QRD: "); Serial.println(analogRead(rightBridgeQRD));

        delay(4000);

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
	LCD.clear(); LCD.print("CliffQRD: "); LCD.print(analogRead(leftCliffQRD));
}

void testServo() {
    LCD.clear(); LCD.print("Let Go"); 
    deployBridge();
    LCD.clear(); LCD.print("Hold");
    resetBridge();
}



