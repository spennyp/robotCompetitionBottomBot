// Test.cpp

#include "Sensors.h"
#include "Globals.h"
#include <Arduino.h>
#include "Menu.h"


void systemDiagnostics() {
    LCD.clear(); LCD.print("Diagnostics"); 
    LCD.setCursor(0,1); LCD.print("Exit -> HoldStop");
    while(true) {
        Serial.println("");
        Serial.println("");
        Serial.print("Top hall: "); Serial.println(topHallTriggered());
        Serial.print("Bottom hall: "); Serial.println(bottomHallTriggered());
        Serial.print("Front Touch: "); Serial.println(frontTouchSensorTriggered());
        Serial.print("Far QRD: "); Serial.println(analogRead(farTapeFollowQRD));
        Serial.print("Near QRD: "); Serial.println(analogRead(nearTapeFollowQRD));
        Serial.print("Cliff QRD: "); Serial.println(analogRead(cliffQRD));
        Serial.print("Claw IR: "); Serial.println(clawIRTriggered());
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

}

void testQRDSensors() {

}

void testDump() {
	// reset();
	// LCD.clear(); LCD.print("Reset");
	// delay(2000);
	// activateDumper();
	// LCD.clear(); LCD.print("Dump");
	// delay(2000);
}

void testClaw() {
	// bool triggered = clawIRTriggered();
	// LCD.clear(); LCD.print(triggered);
	// if(triggered) {
	// 	claw.grab();
	// 	delay(1000);
	// 	setServo(clawDumpServo, 8);
	// 	delay(1000);
	// 	setServo(clawGrabServo, 18); 
	// 	delay(1000);
	// 	setServo(clawDumpServo, 125);
	// 	delay(1000);
	// }
}



