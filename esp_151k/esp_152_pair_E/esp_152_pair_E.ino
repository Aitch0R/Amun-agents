
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
WiFiClient dest=client;
#define writer client
//#include <Logger.h>
//Logger logger(1);


#define ssid "RNNVH"
#define pass "JXF810HJ"
int pin=2;
const uint16_t port = 152;
const char * host = "192.168.0.10"; // ip or dns
String obj;
String argu;
String code;
unsigned long lon;
String ser;

//Light (int LightPin, String adrs, WiFiClient cl)


void setup() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  WiFi.mode(WIFI_STA);
  Serial.begin(1000000);
  delay(10);
  connecttowifi();
  connecttoserver();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (dest.connected()) {
      String cmd = dest.readStringUntil('\n');
     // Serial.println(String(dest.getTimeout()));
      if (cmd!=NULL){
        split(cmd);
      }
      //Serial.print("check");
      while (Serial.available() > 0) {
    // get incoming byte:
    ser=Serial.readStringUntil('\n');
    ser.trim();
    dest.println(ser);
      }
      //Serial.println("checkend");
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
  digitalWrite(pin, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(pin, HIGH);  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
}

void connecttoserver (){
    Serial.print("connecting to ");
    Serial.println(host);
  while (!dest.connect(host, port)) {
        Serial.println(host);
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
    }
    Serial.println("connected");
    dest.println("connected");
    }

void process(String splitted[]){
  switch(splitted[0].toInt()){
    
    case 1:
      digitalWrite(pin, HIGH);
      break;
    case 2:
      digitalWrite(pin, LOW);
      break;
    case 3:
      break;
    case 5:
      break;
    case 12:
      break;
    case 13:
      
      break;
    case 14:
      
      break;
    case 16:
      
      break;
  }
}

void split(String inc){
  String splitted[5];
  String temp=inc;
  int index=0;
  while (index<=5){
    int sp = inc.indexOf(',');
      splitted[index] = inc.substring(0,sp);
      inc = inc.substring(sp+1);
      index +=1;
    if(sp+1==-1){break;}
    }
  
  if (splitted[0].equals("0")){
    Serial.print(temp);
    Serial.println("0");
    
  }else{
  
  process(splitted);
  }
}

    


