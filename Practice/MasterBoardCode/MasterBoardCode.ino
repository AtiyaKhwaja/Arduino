//code for the master board

//NRF configuring==================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[][6] = {"00001", "00002"};

int LCars = 0;
int RCars = 0;

//trigger point pin==================
int TrgRD = 1;
int TrgLD = 0;
int TrgRU = 2;

//lane selection pin==================
int tLaneRD = 24, eLaneRD = 25;
int tLaneRU = 26, eLaneRU = 27;
int tLaneLD = 28, eLaneLD = 29;

//speed monitoring pin==================
int tSpeedL = 34, eSpeedL = 35;
int tSpeedR = 36, eSpeedR = 37;


void setup() {
  Serial.begin(9600);
  //NRF
  radio.begin();
  radio.openReadingPipe(1, address[1]);
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);

  //lane
  pinMode(tLaneRD, OUTPUT); pinMode(eLaneRD, INPUT);
  pinMode(tLaneRU, OUTPUT); pinMode(eLaneRU, INPUT);
  pinMode(tLaneLD, OUTPUT); pinMode(eLaneLD, INPUT);

  //speed
  pinMode(tSpeedL, OUTPUT); pinMode(eSpeedL, INPUT);
  pinMode(tSpeedR, OUTPUT); pinMode(eSpeedR, INPUT);

}

void loop() {

  int tLD = Trigger(TrgLD);
  int tRD = Trigger(TrgRD);
  int tRU = Trigger(TrgRU);

  // FOR THE LOWER RIGHT BLOCK
  if (tRD == 1) {
    RCars++;

    int l = Lane(tLaneRD, eLaneRD);
    int s = 0;
    for (int i = 1; i < 30; i++) {
      int t = Speed(tSpeedR, eSpeedR);
      if (t >= 0) {
        s = t;
      }
    }
    int c = 0;
    if (LCars > 0) {
      c = 1;
    }

    int actCode = 1;
    actCode = (actCode * 10) + s;
    actCode = (actCode * 10) + l;
    actCode = (actCode * 10) + c;

    radio.stopListening();
    radio.write(&actCode, sizeof(actCode));


  }

  // FOR THE UPPER RIGHT BLOCK
  if (tRU == 1) {
    RCars--;

    int l = Lane(tLaneRD, eLaneRD);
    int s = 0;
    for (int i = 1; i < 30; i++) {
      int t = Speed(tSpeedR, eSpeedR);
      if (t >= 0) {
        s = t;
      }
    }

    int actCode = 200;
    radio.stopListening();
    radio.write(&actCode, sizeof(actCode));

  }

  // FOR THE LOWER LEFT BLOCK
  if (tLD == 1) {
    LCars++;

  }

}

//******************SpeedoMeter******************
int Speed(int trigPin, int echoPin) {
  long duration;
  float distance1, distance2,  distanceInch;
  float t1 = 0.1, Speed = 0.0;
  int rSpeed = 0; // NEEDS TO BE CHANGED***********

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

  // Calculating the Speed

  Speed = abs((distance1 - distance2) / t1);

  if ((Speed > 15) && (Speed < 120)) {
    if (Speed > rSpeed) {
            Serial.print("Beshi: ");
      Serial.println(Speed);
      delay(200);
      return 1;
    } else {
            Serial.print("kom: ");
      Serial.println(Speed);
         delay(200);
      return 0;
    }
  } else {
    return -1;
  }
}


//******************Lane detector******************
int Lane(int trigPin, int echoPin) {
  long duration;
  int distanceCm, distanceInch;
  int rLane = 0; // NEEDS TO BE CHANGED***********


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  //distanceInch = duration * 0.0133 / 2;
  if (distanceCm > rLane) {
    return 1;
  } else {
    return 0;
  }
}

//******************trigger point******************
int Trigger(int pin) {

  int AnalogValue;
  AnalogValue = analogRead(pin);

  if (AnalogValue < 100) {
    return 1;
  } else {
    return 0;
  }

}
