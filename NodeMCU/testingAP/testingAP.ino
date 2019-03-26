#include <ESP8266WiFi.h>
#include <WiFiClient.h>


// Include the Wi-Fi library
#ifndef APSSID
#define APSSID "ESP8266_R1"
#define APPSK  "123456789"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

//ESP8266WebServer server(80);
WiFiServer server(80);              // launches the server

IPAddress local_ip(192, 168, 11, 40);      // fix IP of the server
IPAddress gateway(192, 168, 0, 1);  // WiFi router's IP
IPAddress subnet(255, 255, 255, 0);

void setup() {
  ESP.eraseConfig();

  pinMode(2, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  //WiFi.mode(WIFI_STA);
  WiFi.softAPConfig(local_ip, gateway, subnet);
    //Serial.println("Before: "+ WiFi.localIP().toString());
  WiFi.softAP(ssid, password);

  while (WiFi.localIP().toString() == "0.0.0.0") {
    delay(500);
    Serial.print(".");
  }
   //Serial.println("Before: "+ WiFi.localIP().toString());
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());// Start the access point
  // Send the IP address of the ESP8266 to the computer

  server.begin();
  digitalWrite(2, LOW);

  Serial.println(WiFi.softAPgetStationNum());
  
}

void loop() {




  Serial.println(WiFi.softAPgetStationNum());
  delay(200);

  recieveDataFromClient();
//  WiFiClient client = server.available();
//  if (!client) {
//    return;
//  }
//  Serial.println(F("sending data....."));
//  client.print("data receieved thanku");
}


//-****************************Function**************************************

void recieveDataFromClient() {
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
  blnk(3);
  
//  String reqcode = req.substring(0, 2);
  //  req.remove(0, 2);

  //  //response according to reqcode
  //  if (reqcode.equals(protocal[0])) {// this is for message receieved
  //    Serial.println(F("00 request: "));
  //    Serial.println(req);
  //    Serial.println(client.remoteIP().toString().c_str());
  //    blnk(3);
  //  } else if (reqcode.equals(protocal[1])) {// this is for sending message
  //    Serial.println(F("01 request: "));
  //    Serial.println(req);
  //  }
  
    Serial.println(F("sending data....."));
  client.print("data receieved thanku");
}

void blnk(int a) {
  for (int x = 0; x < a; x++) {
    digitalWrite(2, HIGH);
    delay(300);
    digitalWrite(2, LOW);
    delay(300);
  }
}




