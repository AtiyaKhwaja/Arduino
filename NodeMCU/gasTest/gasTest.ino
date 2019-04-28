int smoke = A0;
void setup() {
  // put your setup code here, to run once:
  pinMode(smoke, INPUT);
    Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogSensor = analogRead(smoke);
  Serial.println(analogSensor);
    delay(200);
}
