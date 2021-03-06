#include <ESP8266WiFi.h>
#include <WiFiClient.h>


// Include the Wi-Fi library
//#ifndef APSSID
//#define APSSID "ESP8266_R2" //**********NEEDS TO BE CHANGED PER NODE***************
//#define APPSK  "123456789"
//#endif
//
//const char *ssidMy = APSSID;
//const char *password = APPSK;

const char *ssidMy = "ESP8266_R2";//**********NEEDS TO BE CHANGED PER NODE***************
const char *password = "123456789";
const uint16_t port = 80;
String ssid = "ESP8266_R";


WiFiServer server(80);              // launches the server

IPAddress local_ip(192, 168, 11, 10); //**********NEEDS TO BE CHANGED PER NODE***************
IPAddress gateway(192, 168, 0, 1);  // WiFi router's IP
IPAddress subnet(255, 255, 255, 0);

String IPtable[] = {"192.168.11.5",
                    "192.168.11.10",
                    "192.168.11.15",
                    "192.168.11.20",
                    "192.168.11.25"
                   };

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  //WiFi.mode(WIFI_AP);
   WiFi.softAPConfig(local_ip, gateway, subnet);
  //  WiFi.softAP(ssidMy, password);
  //
  //
  //  while (WiFi.localIP().toString() == "0.0.0.0") {
  //    delay(500);
  //    Serial.print(".");
  //  }
  //  Serial.print("Access Point \"");
  //  Serial.print(ssidMy);
  //  Serial.println("\" started");
  //  Serial.print("IP address:\t");
  //  Serial.println(WiFi.softAPIP());// Start the access point
  //  // Send the IP address of the ESP8266 to the computer
  //
  //  server.begin();
  StartAP();
}
int poi = 0;
void loop() {
  digitalWrite(2, LOW);


  sendMsg(1, "this is first msg from R2");
  delay(5000);
  //StartAP();
//  sendMsg(1, "this is Second msg from R2");
//  Serial.println("Send korsi.....");
//  delay(10000);

  //manageDataClient();

  //  int incomingByte = 0;
  //
  //  // send data only when you receive data:
  //  if (Serial.available() > 0) {
  //    // read the incoming byte:
  //    incomingByte = Serial.read() - 48;
  //    Serial.println("Send kortesi.....");
  //    // say what you got:
  //    sendMsg(incomingByte, "this is msg from Client");
  //    delay(1000);
  //    Serial.println("Delay ses.....");
  //    StartAP();
  //  }


}







//-****************************Function**************************************
void StartAP() {
  
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssidMy, password);

  while (WiFi.localIP().toString() == "0.0.0.0") {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.status());
  Serial.print("AP mode Begin:\t");
  Serial.println(WiFi.softAPIP());// Start the access point
  // Send the IP address of the ESP8266 to the computer
  blnk(1, 1000);
  server.begin();

}
////-----------------------------------------------------------------------
void sendMsg(int n, String msg) {
  String ssidTemp = ssid + n;
  Serial.println(ssidTemp);
//  WiFi.begin(ssidTemp, password);
WiFi.begin(ssidTemp);

  while (WiFi.localIP().toString() == "0.0.0.0") {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.status());
  //sending data to the connected AP.............
  WiFiClient client;

  Serial.println(IPtable[n - 1]);
  String host = IPtable[n - 1];
  //for (int g = 0; g < 10; g++) {
    if (!client.connect(host, port)) {
      Serial.print(".");
      delay(500);
      return;
    }
//    if (g == 9) {
//      return;
//    }
//  }


  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    client.println(msg);
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 10000) {
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


  blnk(3, 300);
}

//-----------------------------------------------------------------------
//void manageDataClient() {
//  delay(50);
//  WiFiClient client = server.available();
//  if (!client) {
//    return;
//  }
//  Serial.println(F("new client"));
//
//  client.setTimeout(1000); // default is 1000
//
//  // Read the first line of the request
//  String req = client.readStringUntil('\r');
//
//
//  Serial.println(req);
//  Serial.println(F("sending data....."));
//  client.print("data receieved thanku from R2");
//  Serial.println();
//  Serial.println("closing connection");
//  client.stop();
//  blnk(5, 100);
//}
//-----------------------------------------------------------------------
void blnk(int a, int t) {
  for (int x = 0; x < a; x++) {
    digitalWrite(2, HIGH);
    delay(t);
    digitalWrite(2, LOW);
    delay(t);
  }
}




