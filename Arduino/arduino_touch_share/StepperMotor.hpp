#ifndef STEPPERMOTOR_HPP
#define STEPPERMOTOR_HPP

#include "Arduino.h"

class StepperMotor
{
private:
  // Pin assignment
	int pin1;
	int pin2;
	int pin3;
	int pin4;

  // step delay
	int step_delay;

  // direction TODO: to be removed and create local variable in functions instead
	bool dir;

  // 
public:
	StepperMotor(int pin1, int pin2, int pin3, int pin4, int step_delay);
	void step(int steps);
	void setDir(bool dir);
  void Print(void);
};

#endif //STEPPERMOTOR_HPP