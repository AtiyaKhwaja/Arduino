/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/
//#include <EEPROM.h>
#include <ESP8266WiFi.h>
int buzzer = D6;
int smoke = A0;
int sensorThreshold = 160;

int id = 1;                           //**********NEEDS TO BE CHANGED PER NODE***************
const char *ssidMy = "ESP8266_R1";    //**********NEEDS TO BE CHANGED PER NODE***************
String ssid     = "ESP8266_R";
const String password = "123456789";

//const char* host = "192.168.11.10";
const uint16_t port = 80;
boolean Flag[] = {false, false, false, false, false};
String IPtable[] = {"192.168.11.5",
                    "192.168.11.10",
                    "192.168.11.15",
                    "192.168.11.20",
                    "192.168.11.25"
                   };

WiFiServer server(80);              // launches the server

IPAddress local_ip(192, 168, 11, 5);  //**********NEEDS TO BE CHANGED PER NODE***************
IPAddress gateway(192, 168, 0, 1);  // WiFi router's IP
IPAddress subnet(255, 255, 255, 0);


void setup() {
  pinMode(2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smoke, INPUT);
  //EEPROM.begin(512);
  Serial.begin(115200);
  Serial.println();

  WiFi.mode(WIFI_AP_STA);

  ConAP();

}



void loop() {
  recieveDataClient();
  Checking();
  gas();
  int t = 0;
  t = Serial.read() - 48;
  if (t == 1) {
    Serial.println("******1st checkpoint******");
    codeDecipher("11111");
    t = 0;
  } else if (t == 2) {
    Serial.println("******1st checkpoint******");
    codeDecipher("11000");
    t = 0;
  }

}

//***************************************************************************************************************************
void Checking() {
  if (Flag[id - 1]) {
    broadcast("111");
    blnk(2, 100);
    buzz();
  }
}
//***************************************************************************************************************************
void broadcast(String C) {
  //Serial.println("******Dhuksi broadcast a checkpoint******");
  String sndcd = (String)id + "1" + C;
  //Serial.println(sndcd);

  for (int we = 1; we <= 3; we++) {
    if (we != id && !Flag[we - 1]) {
      sendD(we, sndcd);
      blnk(2, 100);
      buzz();
    }
  }
  Serial.print("Flag: ");
  for (int i = 0; i < 5; i = i + 1) {
    Serial.print(Flag[i]);
  }
  Serial.println();
}

//***************************************************************************************************************************
void codeDecipher(String code) {
  String rcvr = code.substring(0, 1);
  code.remove(0, 1);

  String UniBroad = code.substring(1, 2);
  code.remove(1, 1);
  //Serial.println("******2nd checkpoint katakati ses******");
  //Serial.println(code);

  if (code == "111") {
    Flag[id - 1] = true;
  }
  else if (code == "000") {
    Flag[id - 1] = false;
  }
  //Serial.println("******1Broadcast a dhuktesi checkpoint******");
  //Serial.println(UniBroad);

  for (int i = 0; i < 5; i = i + 1) {
    Serial.print(Flag[i]);
  }
  if (UniBroad == "1") {
    broadcast(code);
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

  Serial.print(F("request from R"));
  Serial.println(req.substring(0, 1));
  Serial.println(F("sending data....."));
  client.print("101");//ACK
  Serial.println();
  Serial.println("closing connection");
  client.stop();
  blnk(3, 200);

  codeDecipher(req);
}
//***************************************************************************************************************************
void sendD(int Rnum, String msg) {
  ConSTA(Rnum);
  String host = IPtable[Rnum - 1];

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(1000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    client.println(msg);
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(10000);
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


  String M =  msg.substring(2, 5);
  if (M == "111") {
    Flag[Rnum - 1] = true;
  } else if (M == "000") {
    Flag[Rnum - 1] = false;
  }



  //  delay(300000); // execute once every 5 minutes, don't flood remote service
}
//***************************************************************************************************************************
void ConAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(ssidMy, "123456789");


  Serial.println(WiFi.status());
  Serial.print("Access Point \"");
  Serial.print(ssidMy);
  Serial.println("\" started");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());// Start the access point
  // Send the IP address of the ESP8266 to the computer
  server.begin();
}
//***************************************************************************************************************************
void ConSTA(int Rnum) {
  String ssidTemp = ssid + Rnum;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidTemp, password);
  int hu = 1;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (hu == 10) {
      WiFi.mode(WIFI_AP);
      return;
    } else {
      hu++;
    }
  }

  Serial.println("*");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
//***************************************************************************************************************************
void gas() {
  int analogSensor = analogRead(smoke);
  Serial.print("Gas input: ");
  Serial.println(analogSensor);
  delay(200);
  if (analogSensor > sensorThreshold) {
    Flag[id - 1] = true;
  }
  delay(20);

}
//***************************************************************************************************************************
void blnk(int a, int t) {
  for (int x = 0; x < a; x++) {
    digitalWrite(2, LOW);
    delay(t);
    digitalWrite(2, HIGH);
    delay(t);
  }
}
//***************************************************************************************************************************
void buzz() {
  tone(buzzer, 1000);
  delay(200);
  noTone(buzzer);
  delay(200);
}
