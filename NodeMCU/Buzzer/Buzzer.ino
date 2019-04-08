//int buzzer = D6; //buzzer to arduino pin 9
int led = 2;   //buzzer to arduino pin 7
int smoke = A0;

int sensorThreshold = 400;  //change threshold as per need

void setup() {
Serial.begin(9600);
//  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(led, OUTPUT);   // Set led - pin 7 as an output
   pinMode(smoke, INPUT);
}
int analogSensor = 100;
void loop() {
   analogSensor = analogRead(smoke);
  //  if(analogSensor > sensorThreshold){
  ////    buzz();
  //  }else{
  //    noTone(buzzer);
  //    digitalWrite(led, LOW);
  //  }
  //  delay(200);


  Serial.println(analogSensor);
  delay(200);

}

void buzz() {
  tone(buzzer, 1000);            // Send 1KHz sound signal...
  delay(200);                   // ...for 1 sec
  noTone(buzzer);              // Stop sound...
  //   delay(200);                 // ...for 1 sec
  digitalWrite(led, HIGH);   //led on
  delay(200);               // ...for 1 sec
  digitalWrite(led, LOW);  //led off
  delay(200);             // ...for 1 sec
}


