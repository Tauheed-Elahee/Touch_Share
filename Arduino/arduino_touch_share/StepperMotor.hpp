#ifndef STEPPERMOTOR_HPP
#define STEPPERMOTOR_HPP

#include "Arduino.h"

class StepperMotor
{
private:
	int pin1;
	int pin2;
	int pin3;
	int pin4;
	int step_delay;
	bool dir;
public:
	StepperMotor(int pin1, int pin2, int pin3, int pin4, int step_delay);
	void step(int steps);
	void setDir(bool dir);
};

#endif //STEPPERMOTOR_HPP