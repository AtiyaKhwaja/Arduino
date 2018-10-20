/*
  Connected to Uno
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[][6] = {"00001", "00002"};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address[0]);
  radio.openWritingPipe(address[1]);
  radio.setPALevel(RF24_PA_MIN);

}

void loop() {

  
  radio.startListening();
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    
  }


  delay(10);
  radio.stopListening();

  const char text[] = "Hello From UNO";
  radio.write(&text, sizeof(text));

}



