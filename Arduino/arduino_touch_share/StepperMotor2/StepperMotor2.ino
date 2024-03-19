#include "pinmap.h"

uint32_t delayShift = 1;

bool change = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SDA, OUTPUT);
  pinMode(SCL, OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, LOW);

  // Setup shift register
  motorSetup();
  pinMode(SDA, INPUT);

  // Enable pins
  pinMode(EN1, OUTPUT);
  digitalWrite(EN1, HIGH);

  analogWrite(SCL, 127);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Hello World!");
  //motorStep();
  delay(1000);

  change = !change;

  if (change) digitalWrite(DIR, HIGH);
  if (!change) digitalWrite(DIR, LOW);
}

void motorStep(void) {
  int count = 0;
  do {
    motorStepSingle();
    count ++;
  } while (count < 100);
}

void motorSetup(void) {
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SDA, HIGH);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
  digitalWrite(SDA, LOW);
  delay(delayShift);
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
}

// Single cycle of the shift register
void motorStepSingle(void) {
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
  digitalWrite(SCL, LOW);
  delay(delayShift);
  digitalWrite(SCL, HIGH);
  delay(delayShift);
  digitalWrite(SCL, LOW);
}