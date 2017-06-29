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
  chip1.setRegister(0x07, 0b00111000);
  chip1.setRegister(0x08, 0);
  chip1.setRegister(0x09, 0);
  chip1.setRegister(0x0a, 0);
  //  chip1.setToneFrequency(0, 0);
  //  chip1.setToneFrequency(1, 0);
  //  chip1.setToneFrequency(2, 0);


  delay(100);
  chip1.setNoiseFrequency(0);
  //  chip1.setToneFrequency(0, 440);
  chip1.setRegister(0x08, 15);
  chip1.setRegister(0x09, 15);
  chip1.setRegister(0x0A, 15);
}

void loop() {
  // put your main code here, to run repeatedly:
//  chip1.setToneFrequency(0, 500);
  delay(500);
//  chip1.setToneFrequency(0, 0);
  delay(500);
}

//void SetFrequency(int ch, word freq) {
//  word cal_freqency = 0;
//  if (freq != 0) {
//    cal_freqency = 125000 / freq;
//  }
//  cal_freqency &= 0b0000111111111111;
//  chip1.setRegister(0x00 + (ch * 2), cal_freqency & 0xff);
//  chip1.setRegister(0x01 + (ch * 2), (cal_freqency >> 8) & 0xff);
//}

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

