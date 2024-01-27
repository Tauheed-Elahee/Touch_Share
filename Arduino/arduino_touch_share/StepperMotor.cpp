#include "Arduino.h"
#include "StepperMotor.hpp"

StepperMotor::StepperMotor(int pin1, int pin2, int pin3, int pin4, int delay) {
	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);
	pinMode(pin3, OUTPUT);
	pinMode(pin4, OUTPUT);
	this->delay = delay;
	this->dir = true;
};

// Public Functions

void StepperMotor::step(int steps) {
  int steps_abs = abs(steps);
  int count_step = 0;
	this->dir = (steps > 0)? true:false;
  do {
    int step_num = count_step%4;
    if(this->dir){
    switch(step_num){
      case 0:
        digitalWrite(this->pin1, HIGH);
        digitalWrite(this->pin2, LOW);
        digitalWrite(this->pin3, LOW);
        digitalWrite(this->pin4, LOW);
        break;
      case 1:
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, HIGH);
        digitalWrite(this->pin3, LOW);
        digitalWrite(this->pin4, LOW);
        break;
      case 2:
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, LOW);
        digitalWrite(this->pin3, HIGH);
        digitalWrite(this->pin4, LOW);
        break;
      case 3:
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, LOW);
        digitalWrite(this->pin3, LOW);
        digitalWrite(this->pin4, HIGH);
        break;


    }
  } else {
    switch(step_num){
      case 0:
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, LOW);
        digitalWrite(this->pin3, LOW);
        digitalWrite(this->pin4, HIGH);
        break;
      case 1:
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, LOW);
        digitalWrite(this->pin3, HIGH);
        digitalWrite(this->pin4, LOW);
        break;
      case 2:
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, HIGH);
        digitalWrite(this->pin3, LOW);
        digitalWrite(this->pin4, LOW);
        break;
      case 3:
        digitalWrite(this->pin1, HIGH);
        digitalWrite(this->pin2, LOW);
        digitalWrite(this->pin3, LOW);
        digitalWrite(this->pin4, LOW);
        break;
      } 
    };
    //delay(this->delay);
    count_step++;
  } while (count_step < steps_abs);
}

void StepperMotor::setDir(bool dir) {
	this->dir = dir;
}