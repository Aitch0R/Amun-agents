#include <Test.h>
#include <Pru.h>
Test test (2);
Pru pru(2,&test);
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:

pru.foos();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  pru.foos();
}


