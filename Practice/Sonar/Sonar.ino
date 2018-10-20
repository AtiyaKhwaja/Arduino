/*
  Ultrasonic Sensor HC-SR04 and Arduino Tutorial

  by Dejan Nedelkovski,
  www.HowToMechatronics.com

*/


const int trigPin = 7;
const int echoPin = 8;

long duration;
int distanceCm, distanceInch;

void setup() {


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceInch = duration * 0.0133 / 2;

  //Serial.print(distanceInch);
  //Serial.print("in, ");
  Serial.println();
  delay(1000);
  Serial.print(distanceCm);
  Serial.print("cm, ");
  Serial.println();
  delay(1000);
}
