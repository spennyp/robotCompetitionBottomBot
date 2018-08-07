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
        Serial.print("L Bridge Touch: "); Serial.println(leftBridgeTouchTriggered());
        Serial.print("R Bridge Touch: "); Serial.println(rightBridgeTouchTriggered());


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

    LCD.clear(); LCD.print("IR follow and"); LCD.setCursor(0, 1); LCD.print("touch align"); delay(1000);
    while(!startbutton()) {
        followBridgeQRDs(testMotorWheel, 100);
			if(leftBridgeTouchTriggered() || rightBridgeTouchTriggered()) {
				testMotorWheel.stop();
				delay(1000);
				int alignTouchStartTime = millis();
				while(!alignTouchSensors(testMotorWheel)) { 
					delay(100); 
					if(alignTouchStartTime >= 5000) { break; }
				} // Delay to stop oscilation
				testMotorWheel.stop();
				delay(1000);
				LCD.clear(); LCD.print("DETATCHED!!"); 
				break;
			}
    }


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
    // testMotorWheel.forward(140);
    // while(!foundLeftCliff() || !foundRightCliff()) {}
    // unsigned long cliffAlignStartTime = millis();
    // while((millis() - cliffAlignStartTime) <= 2000) { 
    //     alignCliffQRDs(testMotorWheel);
    //     delay(50); 
    // }
    // if(foundLeftCliff() || foundRightCliff()) {
    //     testMotorWheel.reverse(100);
    //     while(foundLeftCliff() && foundRightCliff()) {}
    // }
    // testMotorWheel.forward(200);
    // delay(50);
    // testMotorWheel.stop();

    // delay(1000);
    // deployBridge();
    // delay(100);
    // testMotorWheel.reverse(180);
	// delay(100);
	// testMotorWheel.stop();
    // delay(5000);
    // resetBridge();
    // delay(1000);

    testMotorWheel.forward(150);
	while(!foundLeftCliff() && !foundRightCliff()) { delay(10); } // Gets to the cliff
	testMotorWheel.stop();

    unsigned long cliffAlignStartTime = millis();
    while((millis() - cliffAlignStartTime) <= 2000) { 
        if(alignCliffQRDs(testMotorWheel)) {
            testMotorWheel.reverse(160);
            delay(100);
        }
        delay(10); 
    }

    if(foundLeftCliff() || foundRightCliff()) {
        testMotorWheel.reverse(160);
        while(foundLeftCliff() || foundRightCliff()) {}
        
    }
    testMotorWheel.reverse(160);
    delay(150);
    testMotorWheel.forward(200); // Hard stop
    delay(20);
    testMotorWheel.stop();

    delay(3000);
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
    followBridgeQRDs(testMotorWheel, 100);
    delay(10);
}

void testBridgeTouchSensorAlign() {
    alignTouchSensors(testMotorWheel);
    delay(10);
}





