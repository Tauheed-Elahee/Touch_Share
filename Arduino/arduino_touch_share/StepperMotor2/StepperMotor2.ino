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
  pinMode(VAL1, INPUT);

  analogWrite(SCL, 127);
}

int valread = 0;
int valtarget = 0;
bool valchange = false;

void loop() {

  valread = pinRead(1);
  //Serial.print("Current: ");
  Serial.println(valread);

  //Serial.print("valchange: ");
  //Serial.println(valchange);

  if (Serial.available() > 0) valchange = true;

  //Serial.print("check valchange: ");
  //Serial.println(valchange);

  //Serial.println(Serial.readString())

  if (valchange) {
    //Serial.println("Changed!");
    valread = pinRead(1);
    valtarget = Serial.parseInt();
    //Serial.print("Target: ");
    //Serial.println(valtarget);
    delay(1000);
    pinMove(1, valtarget);
    valchange = false;
  }
  delay(100);
  
  /*
  // Call the readValues function
  readValues(values, valuesChanged);

  if (valuesChanged) {
    motorTransmit(values);
  }

  valuesChanged = false;
  */
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


void pinMove(int pinNum, int valNew) {
  //Serial.println("Here!");
  int valOld = pinRead(pinNum);
  
  while(abs(valNew - valOld) > 30) {
    //Serial.println("Loop!");
    if ((valNew - valOld) > 30) digitalWrite(DIR, HIGH);
    if ((valNew - valOld) < 30) digitalWrite(DIR, LOW);
    pinEN(pinNum, HIGH);
    delay(100);
    pinEN(pinNum, LOW);
    delay(500);
    valOld = analogRead(VAL1);
    //Serial.print("Current moving value: ");
    //Serial.println(valOld);
  }
}

void pinEN(uint8_t pinNum, uint8_t pinState) {
  switch(pinNum) {
    case 1:
      digitalWrite(EN1, pinState);
    case 2:
      digitalWrite(EN2, pinState);
    case 3:
      digitalWrite(EN3, pinState);
    case 4:
      digitalWrite(EN4, pinState);
  }
}

int pinRead(uint8_t pinNum) {
  switch(pinNum) {
    case 1:
      return analogRead(VAL1);
    case 2:
      return analogRead(VAL2);
    case 3:
      return analogRead(VAL3);
    case 4:
      return analogRead(VAL4);
  }
}