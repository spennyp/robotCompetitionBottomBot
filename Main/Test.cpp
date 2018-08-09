// Test.cpp

#include "Test.h"
#include "Globals.h"
#include "Helpers.h"
#include "MotorWheel.h"

extern MotorWheel motorWheel;


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
        delay(2000);
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

	LCD.clear(); LCD.print("Test Cliff align"); delay(1000);
    while(!startbutton()) {
        int count = 0;
        while(count < 3) {
            testCliffAlign();
            count++;
        }
        delay(4000);
    }

    LCD.clear(); LCD.print("Testing turning"); LCD.setCursor(0, 1); delay(1000);
	while(!startbutton()) {
		testTurning();
	}

    motorWheel.stop();

    LCD.clear(); LCD.print("Testing Bridge"); delay(1000);
    while (!startbutton()){
        testBridge();
    }

    LCD.clear(); LCD.print("IR bridge"); LCD.setCursor(0, 1); LCD.print("QRD follow"); delay(1000);
    while(!startbutton()) {
        testBridgeQRDFollow();
    }
    motorWheel.stop();

    LCD.clear(); LCD.print("Touch sensor"); LCD.setCursor(0, 1); LCD.print("align"); delay(1000);
    while(!startbutton()) {
        testBridgeTouchSensorAlign();
    }
    motorWheel.stop();

    LCD.clear(); LCD.print("IR follow and"); LCD.setCursor(0, 1); LCD.print("touch align"); delay(1000);
    while(!startbutton()) {
        followBridgeQRDs(100);
			if(leftBridgeTouchTriggered() || rightBridgeTouchTriggered()) {
				motorWheel.stop();
				delay(1000);
				int alignTouchStartTime = millis();
				while(!alignTouchSensors()) { 
					delay(100); 
					if(alignTouchStartTime >= 5000) { break; }
				} // Delay to stop oscilation
				motorWheel.stop();
				delay(1000);
				LCD.clear(); LCD.print("DETATCHED!!"); 
				break;
			}
    }
    motorWheel.stop();


    LCD.clear(); LCD.print("Leaving System"); LCD.setCursor(0, 1); LCD.print("Testing"); delay(1000);
}

void testTurning() {
	motorWheel.turnRight(90);
	delay(1000);
	if(startbutton()) { return; }
	motorWheel.turnLeft(90);
	delay(1000);
}

// void testCliffAlign() {
//     motorWheel.forward(150);
// 	while(!foundLeftCliff() && !foundRightCliff()) { delay(10); } // Gets to the cliff
// 	motorWheel.stop();

//     unsigned long cliffAlignStartTime = millis();
//     while((millis() - cliffAlignStartTime) <= 2000) { 
//         if(alignCliffQRDs()) {
//             motorWheel.reverse(160);
//             delay(100);
//         }
//         delay(10); 
//     }

//     if(foundLeftCliff() || foundRightCliff()) {
//         motorWheel.reverse(160);
//         while(foundLeftCliff() || foundRightCliff()) {}
//     }
// 	motorWheel.hardStop();

// 	delay(5000);
//     // motorWheel.reverse(160);
//     // motorWheel.hardStop();

//     // delay(3000);
// }
void testCliffAlign() {
    LCD.clear(); LCD.print("Began");

    motorWheel.forward(150);
	while(!foundLeftCliff() && !foundRightCliff()) { delay(10); } // Gets to the cliff
	motorWheel.stop();

    if(foundLeftCliff()) {
        while(!foundRightCliff()) {
            if(!foundLeftCliff()) {
                motorWheel.forward(200);
            } else {
                motor.speed(leftMotor, -220);
                motor.speed(rightMotor, 180);
            }
            delay(10);
        }
        motor.speed(leftMotor, 200);
        motor.speed(rightMotor, -200);
        delay(30);
    } else { // Found right
        while(!foundLeftCliff()) {
            if(!foundRightCliff()) {
                motorWheel.forward(200);
            } else {
                motor.speed(leftMotor, 180);
                motor.speed(rightMotor, -220);
            }
            delay(10);
        }
        motor.speed(leftMotor, -200);
        motor.speed(rightMotor, 200);
        delay(30);
    }
    motorWheel.stop();
    delay(100);

    if(foundRightCliff() || foundLeftCliff()) {
        motorWheel.reverse(120);
        while(foundRightCliff() || foundLeftCliff()) { delay(10); }
        motorWheel.hardStop(false);
    }
    motorWheel.stop();

    LCD.clear(); LCD.print("Found");
}

void leftAdjust() {
    motor.speed(leftMotor, -220);
    motor.speed(rightMotor, 180);
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
    followBridgeQRDs(100);
    delay(10);
}

void testBridgeTouchSensorAlign() {
    alignTouchSensors();
    delay(10);
}





