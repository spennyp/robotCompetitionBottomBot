// Test.cpp

#include "Sensors.h"
#include "Globals.h"
#include <Arduino.h>
#include "Menu.h"

void systemDiagnostics()
{
    LCD.clear();
    LCD.print("Diagnostics");
    LCD.setCursor(0, 1);
    LCD.print("Exit -> HoldStop");
    while (true)
    {
        Serial.println("");
        Serial.print(" Left Cliff QRD: ");
        Serial.print(analogRead(leftCliffQRD));
        Serial.print(" Near QRD: ");
        Serial.print(analogRead(nearTapeFollowQRD));
        Serial.print("Far QRD: ");
        Serial.print(analogRead(farTapeFollowQRD));
        Serial.print(" L Bridge QRD: ");
        Serial.print(analogRead(leftBridgeQRD));
        Serial.print(" R Bridge QRD: ");
        Serial.print(analogRead(rightBridgeQRD));
        Serial.print(" R Cliff QRD: ");
        Serial.print(analogRead(rightCliffQRD));

        delay(100);

        if (stopbutton())
        {
            delay(100);
            if (stopbutton())
            {
                LCD.clear();
                LCD.print("Leaving diagnositcs");
                delay(1000);
                return;
            }
        }
    }
}

void testFullSystem()
{
}

void testQRDSensors()
{
}
