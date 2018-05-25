
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

#include <Logger.h>
Logger logger(1);
#include <IRsend.h>
#include <Light.h>
#include <Lightsensor.h>
#include <Thermostat.h>

#define ssid "RNNVH"
#define pass "JXF810HJ"

const uint16_t port = 151;
const char * host = "192.168.0.10"; // ip or dns
String obj;
String argu;
String code;
unsigned long lon;

//Light (int LightPin, String adrs, WiFiClient cl)
Light light1(13);
Light rgb1(12);
Light rgb2(14);
Light rgb3(16);
Lightsensor lightsensor(1);
IRsend irsend(5);
Thermostat thermo(4,2);

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  delay(10);
  connecttowifi();
  connecttoserver();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connected()) {
      String cmd = client.readStringUntil('\n');
      if (cmd!=NULL){
        split(cmd);
      }
    }else{
      connecttoserver();
    }
  }else{
    connecttowifi();
  }
//irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), 40);
}

void connecttowifi (){
  Serial.print("Wait for WiFi... ");
  WiFiMulti.addAP(ssid, pass);
  while(WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void connecttoserver (){
    Serial.print("connecting to ");
    Serial.println(host);
  while (!client.connect(host, port)) {
        Serial.println(host);
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
    }
    Serial.println("connected");
    //client.println("connected");
    }

void process(String splitted[]){
  switch(splitted[0].toInt()){
    case 0:
      logger.set(splitted[1].toInt(),splitted[2].toInt());
    case 1:
      lightsensor.send();
      break;
    case 4:
      thermo.process(splitted);
      break;
    case 3:
      break;
    case 5:
      irsend.send(splitted[1],splitted[2],splitted[3]);
      break;
    case 12:
      rgb1.process(splitted);
      break;
    case 13:
      light1.process(splitted);
      break;
    case 14:
      rgb2.process(splitted);
      break;
    case 16:
      rgb3.process(splitted);
      break;
  }
}

void split(String inc){
  String splitted[5];
  int index=0;
  while (index<=5){
    int sp = inc.indexOf(',');
    if(sp!=NULL){
      Serial.println(String(sp));
      splitted[index] = inc.substring(0,sp);
      inc = inc.substring(sp+1);
      index +=1;
    }else{
      break;
    }
  }
  process(splitted);
}

    


