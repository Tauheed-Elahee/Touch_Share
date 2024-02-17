#include "Arduino.h"
#include "StepperMotor.hpp"

StepperMotor::StepperMotor(int pin1, int pin2, int pin3, int pin4, int step_delay) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pin3 = pin3;
  this->pin4 = pin4;
	this->step_delay = step_delay;
	this->dir = true;
	pinMode(this->pin1, OUTPUT);
	pinMode(this->pin2, OUTPUT);
	pinMode(this->pin3, OUTPUT);
	pinMode(this->pin4, OUTPUT);
};

// Public Functions

void StepperMotor::step(int steps) {
  int steps_abs = abs(steps);
  int count_step = 0;
	this->dir = (steps > 0);
  do {
    int step_num = count_step % 4;
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
    delay(this->step_delay);
    count_step++;
  } while (count_step < steps_abs);
}

void StepperMotor::Print(void) {
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(this->pin1);
  Serial.println(this->pin2);
  Serial.println(this->pin3);
  Serial.println(this->pin4);
  Serial.println(this->step_delay);
}

void StepperMotor::setDir(bool dir) {
	this->dir = dir;
}