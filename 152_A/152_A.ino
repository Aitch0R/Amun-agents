#include <Writer.h>
Writer writer;
#define writer Serial
#include <LiquidCrystal.h>
#include <LCD.h>
#include <IRRCV.h>

LiquidCrystal lc(2, 4, 5, 6, 7, 8);
LCD lcd(2, &lc,9);
IRRCV irrcv (3);
int gcurrent=0;
int glast=0;

void setup() {

  Serial.begin(1000000);
  Serial.print("j");
  delay(2000);
  lc.begin(16, 2);
  delay(1000);
  lc.setCursor(0, 1);
  delay(1000);
  lc.print("hello, world!");
  attachInterrupt(digitalPinToInterrupt(3), regist, CHANGE);
}

void loop() {
  if (Serial.available() > 0) {
    String cmd=Serial.readStringUntil('\n');
    split(cmd);
  }

  
}

void process(String splitted[]){
  switch(splitted[1].toInt()){
    case 1:
    lcd.process(splitted);
      break;
    case 2:

      break;
    case 3:

      Serial.println("msg set");
      break;
    case 5:
      
      Serial.println("msg set");
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
    if(sp==-1){break;}
  }
  process(splitted);
}

void regist(){
  irrcv.debounce();
}


