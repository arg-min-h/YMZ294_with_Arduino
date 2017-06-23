#include "YMZ294.h"

YMZ294 test;

int cppTest = 0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  cppTest = test.function(5);
  Serial.printf("test = %d\n",cppTest);
  delay(3000);
}
