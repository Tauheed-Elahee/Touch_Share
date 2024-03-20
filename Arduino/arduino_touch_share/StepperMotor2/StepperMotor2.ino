// Needed libraries
#include <CSV_Parser.h>

#include "pinmap.h"


// Global Variables
uint32_t delayShift = 1;
bool change = false;

int values[NUM_VALUES];     // Array to store the parsed integers
byte valueIndex = 0;        // Index to keep track of the current position in the array
boolean valuesChanged = false; // Flag to indicate if values array has changed


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

  analogWrite(SCL, 127);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Hello World!");
  //motorStep();
  
  /*
  change = !change;

  if (change) digitalWrite(DIR, HIGH);
  if (!change) digitalWrite(DIR, LOW);

  digitalWrite(EN1, HIGH);
  delay(1000);
  digitalWrite(EN1, LOW);
  delay(1000);
  */

  // Call the readValues function
  readValues(values, valuesChanged);

  if (valuesChanged) {
    motorTransmit(values);
  }

  valuesChanged = false;
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

void readValues(int (&valArray)[NUM_VALUES], bool &valChange) {
  int tempVals[4];
  if (Serial.available() > 0) {
    String valString = Serial.readString();
    
    char *val_str = valString.c_str();
    CSV_Parser cp(val_str, /*format*/ "udududud", /*has_header*/ false);
    cp << valString;
    
    uint16_t * val1 = (uint16_t*)cp[0];
    uint16_t * val2 = (uint16_t*)cp[1];
    uint16_t * val3 = (uint16_t*)cp[2];
    uint16_t * val4 = (uint16_t*)cp[3];

    int valNew[NUM_VALUES];
    valNew[0] = val1[0];
    valNew[1] = val2[0];
    valNew[2] = val3[0];
    valNew[3] = val4[0];

    for (int i=0; i<NUM_VALUES; i++) {
      if (valNew[i] != valArray[i]) valChange = true;
      valArray[i] = valNew[i];
    }
  }
}

void motorTransmit(int (&valArray) [NUM_VALUES]) {
  for (int i=0; i<NUM_VALUES; i++) {
    Serial.println(values[i]);
  }

  Serial.println();
}