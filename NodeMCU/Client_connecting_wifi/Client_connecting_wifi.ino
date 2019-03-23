#include <ESP8266WiFi.h>
// Include the Wi-Fi library
const char* ssid = "TP-LINK_TAS-93F26A";
const char* password = "Rat#kn0ws";
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);
  // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); 
  Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

Serial.println('\n');
Serial.println("Connection established!");
Serial.print("IP address:\t");
Serial.println(WiFi.localIP());
// Send the IP address of the ESP8266 to the computer
}

void loop() { 
  digitalWrite(2, LOW); 
  delay(1000);                    
  digitalWrite(2, HIGH);
  delay(1000);

  
  }
