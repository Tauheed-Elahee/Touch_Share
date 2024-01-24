//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2000;
int pinPot = 0;
int valPot = 0;
int count = 0;

int valDesired; // for incoming serial data


// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 2,3,4,5);

void setup() {
  // Nothing to do (Stepper Library sets pins as outputs)
  Serial.begin(115200);
  valDesired = 0;
}

void loop() {

  if (Serial.available() > 0) {
    valDesired = Serial.parseInt();
    Serial.print("valDesired: ");
    Serial.println(valDesired, DEC);
  }

  if (abs(valDesired - valPot) > 25) {
    // Rotate CCW quickly at 10 RPM
    myStepper.setSpeed(10);
    myStepper.step(50);
    count ++;
  }
  delay(900);
  valPot = analogRead(0);
  Serial.print(valPot);
  Serial.print(" ");
  Serial.print(count);
  Serial.print("\n");
  delay(100);
}