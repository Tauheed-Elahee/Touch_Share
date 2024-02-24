uint32_t delayShift = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("Hello World!");
  digitalWrite(12, LOW);
  delay(delayShift);
  digitalWrite(13, HIGH);
  delay(delayShift);
  digitalWrite(12, HIGH);
  delay(delayShift);
  digitalWrite(13, LOW);
  delay(delayShift);
  digitalWrite(12, LOW);
  delay(delayShift);
  digitalWrite(12, HIGH);
  delay(delayShift);
  digitalWrite(12, LOW);
  delay(delayShift);
  digitalWrite(12, HIGH);
  delay(delayShift);
  digitalWrite(12, LOW);
  delay(delayShift);
  digitalWrite(12, HIGH);
  delay(delayShift);
}
