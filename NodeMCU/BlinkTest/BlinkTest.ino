/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/


int led = 2;
int l = 1;
void setup() {




  
  Serial.begin(115200);
  pinMode(led, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    Serial.print("LED_BUILTIN = ");
    Serial.print(led);
    
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(led, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(500);                      // Wait for a second
  digitalWrite(led, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(500);                      // Wait for two seconds (to demonstrate the active low LED)
      Serial.print("LED_BUILTIN = ");
    Serial.println(l);
    l++;
  
}
