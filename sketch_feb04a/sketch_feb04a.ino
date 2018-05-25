#include <LiquidCrystal.h>

//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(2, 4, 5, 6, 7, 8);      // put your pin numbers here
int pin=9;
void setup()
  {
      pinMode(pin,OUTPUT);
  digitalWrite(pin, HIGH);
  delay(5000);
  lcd.begin(16, 2);                          // put your LCD parameters here
  lcd.print("hello, world!");
  //lcd.setCursor(0,1);
 // lcd.print("it works!");
  }

void loop()
  {
  }
