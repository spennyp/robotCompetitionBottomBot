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
        void dump();
        void open();
        void close();
        int homeLimitSwitch;
        int numberOfTeddies;
        bool raising;
        bool switchingBots;
    public:
        Claw();
        void grab();
        void switchToTopBot();
        void reset();
        bool poll();
};

#endif



