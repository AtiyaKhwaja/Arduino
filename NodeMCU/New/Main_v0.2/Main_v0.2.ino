/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
//
//#ifndef STASSID
//#define STASSID "ESP8266_R1"
//#define STAPSK  "123456789"
//#endif

//const char* ssid     = STASSID;
//const char* password = STAPSK;
const String ssid     = "ESP8266_R1";
const String password = "123456789";

const char* host = "192.168.11.5";
const uint16_t port = 80;

WiFiServer server(80);              // launches the server

IPAddress local_ip(192, 168, 11, 10);      //**********NEEDS TO BE CHANGED PER NODE***************
IPAddress gateway(192, 168, 0, 1);  // WiFi router's IP
IPAddress subnet(255, 255, 255, 0);


void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.mode(WIFI_AP_STA);

  ConAP();

}



void loop() {
  recieveDataClient();
  int t = 0;
  t = Serial.read();
  if (t > 0) {
    sendD();
    t = 0;
  }

}
//***************************************************************************************************************************
void recieveDataClient() {
  delay(50);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(1000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');

  Serial.println(F("request: "));
  Serial.println(req);

  Serial.println(F("sending data....."));
  client.print("ACK: data receieved thanku");
  Serial.println();
  Serial.println("closing connection");
  client.stop();
  blnk(3, 200);
}
//***************************************************************************************************************************
void sendD() {
  ConSTA();
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    client.println("hello from ESP8266 Client NaChaNachi");
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  //  delay(300000); // execute once every 5 minutes, don't flood remote service
}
//***************************************************************************************************************************
void ConAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP("ESP8266_R2", "123456789");


  Serial.println(WiFi.status());
  Serial.print("Access Point \"");
  Serial.print("ESP8266_R2");
  Serial.println("\" started");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());// Start the access point
  // Send the IP address of the ESP8266 to the computer
  server.begin();
}
//***************************************************************************************************************************
void ConSTA() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
//***************************************************************************************************************************
void blnk(int a, int t) {
  for (int x = 0; x < a; x++) {
    digitalWrite(2, HIGH);
    delay(t);
    digitalWrite(2, LOW);
    delay(t);
  }
}
