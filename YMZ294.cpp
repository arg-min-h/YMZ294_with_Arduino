#include "Arduino.h"
#include "YMZ294.h"
#define fsc 2000000

YMZ294::YMZ294(byte WS, byte CS, byte A0, byte IC, byte* D) {
  _WS = WS;
  pinMode(_WS, OUTPUT);
  _CS = CS;
  pinMode(_CS, OUTPUT);
  _A0 = A0;
  pinMode(_A0, OUTPUT);
  _IC = IC;
  pinMode(_IC, OUTPUT);
  _D = D;
  for (int i = 0; i < 8; i++) {
    pinMode(_D[i], OUTPUT);
  }
  _mix = 0xff;
  _vol = 0;
}
YMZ294::YMZ294(byte WS, byte CS, byte A0, byte IC, byte* D, bool toggle) {
  _WS = WS;
  pinMode(_WS, OUTPUT);
  _CS = CS;
  pinMode(_CS, OUTPUT);
  _A0 = A0;
  pinMode(_A0, OUTPUT);
  _IC = IC;
  pinMode(_IC, OUTPUT);
  _D = D;
  for (int i = 0; i < 8; i++) {
    pinMode(_D[i], OUTPUT);
  }
  _toggle = toggle;
  _mix = 0xff;
  _vol = 0;
}

void YMZ294::reset() {
  if (_toggle == true) {
    digitalWrite(_WS, HIGH);
    digitalWrite(_CS, HIGH);
    digitalWrite(_IC, HIGH);
    delay(1);
    digitalWrite(_IC, LOW);
  } else {
    digitalWrite(_WS, HIGH);
    digitalWrite(_CS, HIGH);
    digitalWrite(_IC, LOW);
    delay(1);
    digitalWrite(_IC, HIGH);
  }
}

void YMZ294::setRegister(byte address, byte data) {
  //SSGLPにアドレスを書き込む
  digitalWrite(_A0, LOW);
  digitalWrite(_WS, LOW);
  digitalWrite(_CS, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(_D[i], bitRead(address, i));
  }
  digitalWrite(_CS, HIGH);
  digitalWrite(_WS, HIGH);

  //SSGLPにデータを書き込む
  digitalWrite(_A0, HIGH);
  digitalWrite(_WS, LOW);
  digitalWrite(_CS, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(_D[i], bitRead(data, i));
  }
  digitalWrite(_CS, HIGH);
  digitalWrite(_WS, HIGH);
}


void YMZ294::setToneFrequency(byte ch, int freq) {
  int TP = 0;
  if (freq != 0) {
    TP = fsc / (16 * freq);
  }
  TP &= 0x00ff;
  //  TP &= 0b0000111111111111;
  setRegister(0x00 + (ch * 2), TP & 0xff);
  setRegister(0x01 + (ch * 2), (TP >> 8) & 0xff);
}

void YMZ294::setToneFrequency(byte ch, float freq) {
  float floatTP = 0;
  if (freq != 0) {
    floatTP = fsc / (16 * freq);
  }
  int TP = 0;
  TP = (int)floatTP;
  TP &= 0x00ff;
  //  TP &= 0b0000111111111111;
  setRegister(0x00 + (ch * 2), TP & 0xff);
  setRegister(0x01 + (ch * 2), (TP >> 8) & 0xff);
}

void YMZ294::setNoiseFrequency(int freq) {
  int NP = 0;
  if (freq != 0) {
    NP = fsc / (16 * freq);
  }
  NP &= 0x00ff;
  //  NP &= 0b0000000011111111;
  setRegister(0x06, NP & 0xff);
}

void YMZ294::setNoiseFrequency(float freq) {
  float floatNP = 0;
  if (freq != 0) {
    floatNP = fsc / (16 * freq);
  }
  int NP = 0;
  NP = (int)floatNP;
  NP &= 0x00ff;
  //  NP &= 0b0000000011111111;
  setRegister(0x06, NP & 0xff);
}

void YMZ294::setMixer(byte ch, bool mixSW) {
  bitWrite(_mix, ch, !mixSW);
  setRegister(0x07, _mix);
}

byte YMZ294::getMixer() {
  byte mix = _mix;
  return mix;
}

void YMZ294::setVolume(byte ch, byte value) {
  value &= 0x0f;
  _vol &= 0xf0;
  _vol = _vol + value;
  setRegister(0x08 + ch, _vol);
}

byte YMZ294::getVolume(){
  byte vol = _vol;
  return vol;
}

void YMZ294::setEnvelope(byte ch, bool envSW) {
  bitWrite(_vol, 4, envSW);
  setRegister(0x08 + ch, _vol);
}

void YMZ294::setEnvelopeFrequency(int freq) {
  int EP = 0;
  if (freq != 0) {
    EP = fsc / (8192 * freq);
  }
  EP &= 0xffff;
  //  EP &= 0b1111111111111111;
  setRegister(0x0B, EP & 0xff);
  setRegister(0x0C, (EP >> 8) & 0xff);
}

void YMZ294::setEnvelopeFrequency(float freq) {
  float floatEP = 0;
  if (freq != 0) {
    floatEP = fsc / (8192 * freq);
  }
  int EP = 0;
  EP = (int)floatEP;
  EP &= 0xffff;
  //  EP &= 0b1111111111111111;
  setRegister(0x0B, EP & 0xff);
  setRegister(0x0C, (EP >> 8) & 0xff);
}

