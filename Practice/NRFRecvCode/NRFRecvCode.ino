/*
 * Connected to MEGA
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[][6] = {"00001", "00002"};
int tr = 26, ec = 27;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address[1]);
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);

    pinMode(tr, OUTPUT); pinMode(ec, INPUT);
 
}

int Lane(int trigPin, int echoPin) {
  long duration;
  int distanceCm, distanceInch;
  int rLane = 9; // NEEDS TO BE CHANGED***********


  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  //distanceInch = duration * 0.0133 / 2;
  if (distanceCm < rLane) {
    Serial.print("Wrong lane: ");
    Serial.println(distanceCm);
    return 1;
  } else {
    Serial.print("Right lane: ");
    Serial.println(distanceCm);
    return 0;
  }
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
  
  //radio.stopListening();
  
  //const char text[] = "Hello From Mega";
  //int actCode = 200;
 // radio.write(&actCode, sizeof(actCode));
int tRD = Trigger(2);
if(tRD == 1){
  delay(20);
  Lane(tr,ec);
  }
  delay(250); 



//  radio.startListening();
//    delay(10);
//    if (radio.available()) {
//    char text[32] = "";
//    radio.read(&text, sizeof(text));
//    Serial.println(text);
//    
//  }

}
