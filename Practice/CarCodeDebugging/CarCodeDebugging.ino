//****** car code******
#include <TFT.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//***************NRF Code*************

RF24 radio(7, 6); // CE, CSN

const byte address[][6] = {"00001", "00002"};
int actCode = 0;

String Car2[] = {"Path Clear", "Incomming car"}; //LSB
String Lane[] = {"Stay on Lane", "Change Lane"};
String Speed[] = {"Speed Ok", "Reduce your Speed"}; //MSB


//***************Display Code*************

#define cs   10
#define dc   9
#define rst  8

TFT screen = TFT(cs, dc, rst);

void setup() {

  //***************NRF Code*************
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address[0]);
  radio.openWritingPipe(address[1]);
  radio.setPALevel(RF24_PA_MIN);
  //***************Display Code*************
  // initialize the screen
  screen.begin();

  // make the background black
  screen.background(0, 0, 0);

  // set the text color to white
  screen.stroke(255, 255, 255);

  // write text to the screen in the top left corner
  screen.text("N/A", 60, 64);
}

void loop() {
  int temp = CarRx();

  if ((temp != actCode) && (temp > 999)) {
    actCode = temp;
    Serial.println(temp);
    temp = temp % 1000;

    char tm[200];
    Dot(temp);

    Car2[temp % 10].toCharArray(tm, 200);
    Serial.println(tm);
    screen.text(tm, 15, 24);
    temp = temp / 10;

    Lane[temp % 10].toCharArray(tm, 200);
    Serial.println(tm);
    screen.text(tm, 15, 60);
    temp = temp / 10;

    Speed[temp % 10].toCharArray(tm, 200);
    Serial.println(tm);
    screen.text(tm, 15, 100);
    temp = temp / 10;


  }

  if ((temp != actCode) && (temp == 200)) {
    actCode = temp;
    Serial.println(temp);
    Reported(temp);
    //char tm[200];
    screen.text("Reported", 56, 54);
    screen.text("!!!", 72, 69);

  }

//  if ((temp != actCode) && (temp == 300)) {
//    actCode = temp;
//    Serial.println(temp);
//    Reported(temp);
//    //char tm[200];
//    screen.text("OK", 72, 64);
//
//  }


//  const char text[] = "DHK-1245";
//  radio.write(&text, sizeof(text));

}
void Reported(int c) {
  screen.background(0, 0, 0);

  if(c == 200){
      screen.fill(0, 0, 127);  
    }else{
      screen.fill(0, 127, 0);
    }
  

  // draw a circle in the center of screen
  screen.circle(screen.width() / 2, screen.height() / 2, 35);
}

void Dot(int x) {
  screen.background(0, 0, 0);
  if (x % 10 == 0) {
    screen.fill(0, 255, 0);
    screen.circle(140, 27, 10);
  } else {
    screen.fill(0, 0, 255);
    screen.circle(140, 27, 10);
  }
  x = x / 10;
  //*********************
  if (x % 10 == 0) {
    screen.fill(0, 255, 0);
    screen.circle(140, 63, 10);
  } else {
    screen.fill(0, 0, 255);
    screen.circle(140, 63, 10);
  }
  x = x / 10;
  //**********************
  if (x % 10 == 0) {
    screen.fill(0, 255, 0);
    screen.circle(140, 103, 10);
  } else {
    screen.fill(0, 0, 255);
    screen.circle(140, 103, 10);
  }
  x = x / 10;

}





//****************this for receive actCode*********************
int CarRx() {
  int temp = 0;
  radio.startListening();
  if (radio.available()) {

    radio.read(&temp, sizeof(temp));
    //Serial.println(temp);

  }
  delay(10);
  radio.stopListening();
  return temp;
}


