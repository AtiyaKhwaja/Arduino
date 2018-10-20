/*
   Speedometer using Sonar sensor

*/
const int trigPin = 36;
const int echoPin = 37;

long duration;
float distance1, distance2,  distanceInch;
float t1 = 0.1, Speed = 0.0;
float rSpeed = 50.00; // NEEDS TO BE CHANGED***********
void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

int Trigger(int pin) {

  int AnalogValue;
  AnalogValue = analogRead(pin);

  if (AnalogValue < 100) {
    return 1;
  } else {
    return 0;
  }

}

void loop() {

  int tRD = Trigger(1);

  if (tRD == 1) {
    delay(20);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    //First pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance1 = (duration * 0.034 / 2);

    delay(t1 * 1000);

    //Second pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance2 = (duration * 0.034 / 2);


    //distanceInch = duration*0.0133/2;
    //Serial.print(distanceInch);
    //Serial.print("in, ");

    // Calculating the Speed

    Speed = abs((distance1 - distance2) / t1);


    if ((Speed > 25) && (Speed < 120)) {
      if (Speed > rSpeed) {
        Serial.print("Beshi: ");
        Serial.println(Speed);
        delay(500);
        //return 1;
      } else {
        Serial.print("kom: ");
        Serial.println(Speed);
        delay(500);
        //return 0;
      }
    } else {
      return -1;
    }

  }
  delay(250);




}
