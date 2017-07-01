#include "YMZ294.h"

const byte ws = 17;
const byte cs = 18;
const byte a0 = 19;
const byte ic = 22;
byte d[] = {32, 33, 25, 26, 27, 14, 12, 13};
#define toggle true
#define pi 3.14159265359

YMZ294 chip1(ws, cs, a0, ic, d, toggle);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  chip1.reset();
  chip1.setMixer(0, 1);
  chip1.setMixer(1, 1);
  chip1.setMixer(2, 1);
  //  chip1.setVolume(0,15);
  //  chip1.setVolume(1, 15);
  //  chip1.setVolume(2, 15);
  //  chip1.setToneFrequency(0, 0);
  //  chip1.setToneFrequency(1, 0);
  //  chip1.setToneFrequency(2, 0);
  delay(100);

  //  chip1.setRegister(0x08, 0b00011111);
  //  chip1.setRegister(0x0B, 0b01101010);
  //  chip1.setRegister(0x0C, 0b00011000);
  //  chip1.setRegister(0x0D, 0b00001101);
  //  chip1.setToneFrequency(0,440);
  //  delay(2000);
  //  chip1.setRegister(0x0B, 0b00000001);
  //  chip1.setRegister(0x0C, 0b00001001);
  //  chip1.setRegister(0x0D, 0b00001010);
}

void loop() {
  // put your main code here, to run repeatedly:
  chip1.setVolume(0, 15);
  chip1.setEnvelope(0, 1);
  Serial.println(chip1.getVolume(), BIN);
  chip1.setEnvelope(0, 0);
  chip1.setVolume(0, 18);
  Serial.println(chip1.getVolume(), BIN);
  delay(1000);
  Serial.printf("a\n");
}


//void arrayRead(){
//  int Rd;
//  Rd = digitalRead(ws);
//  Serial.printf("ws = %d\n",Rd);
//  Rd = digitalRead(cs);
//  Serial.printf("cs = %d\n",Rd);
//  Rd = digitalRead(a0);
//  Serial.printf("a0 = %d\n",Rd);
//  Rd = digitalRead(ic);
//  Serial.printf("ic = %d\n",Rd);
//  for(int i = 0;i < 8; i++){
//    Rd =digitalRead(d[i]);
//    Serial.printf("d[%d] = %d\n",i, Rd);
//  }
//  delay(1000);
//}

