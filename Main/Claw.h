// Claw.h

#ifndef _CLAW_h
#define _CLAW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Claw {
    private:
        void raise();
        void lower();
        bool hasObject();
        void dump();
        void open();
        int homeLimitSwitch;
        int numberOfTeddies;
        bool raising;
        bool switchingBots;
    public:
        Claw();
        void grab();
        void switchToTopBot();
        bool poll();
};

#endif



