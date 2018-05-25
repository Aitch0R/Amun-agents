
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
#include <Logger.h>

Logger logger(1);
#include <Thermostat.h>

#define ssid "RNNVH"
#define pass "JXF810HJ"

const uint16_t port = 151;
const char * host = "192.168.0.10"; // ip or dns
String obj;
String argu;
String code;
unsigned long lon;

Thermostat thermo(2,4);

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
  if (splitted[0].equals("0")){
    thermo.process(splitted);
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

    


