/*
  Connected to esp8266
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int v=0;
RF24 radio(D4, D8); // CE, CSN

//const byte address[][6] = {"00001", "00002"};
const uint64_t pipe = 0xE6E6E6E6E6E6;

void setup() {
  Serial.println(v++); 
  Serial.begin(115200);

  radio.openReadingPipe(1, pipe);
  //radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  pinMode(2, OUTPUT);
   Serial.println(v++); 
     //radio.begin();
}

void loop() {


  //  radio.startListening();
  //  if (radio.available()) {
  //    char text[32] = "";
  //    radio.read(&text, sizeof(text));
  //    Serial.println(text);
  //
  //  }
  Serial.println(v++);
  digitalWrite(2, LOW); 
  Serial.println(radio.isChipConnected());
  delay(500);
  radio.stopListening();

  const char text[] = "Hello From esp8266";
  radio.write(&text, sizeof(text));
  digitalWrite(2, HIGH);
 
}



