#include "Arduino.h"
#include "YMZ294.h"

YMZ294::YMZ294(byte WS, byte CS, byte A0, byte IC, byte* D) {
  pinMode(_WS, OUTPUT);
  _WS = WS;
  pinMode(_CS, OUTPUT);
  _CS = CS;
  pinMode(_A0, OUTPUT);
  _A0 = A0;
  pinMode(_IC, OUTPUT);
  _IC = IC;
  for (int i = 0; i < 8; i++) {
    pinMode(_D[i], OUTPUT);
  }
  _D = D;
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
}

//void YMZ294::reset() {
//  digitalWrite(_WS, HIGH);
//  digitalWrite(_CS, HIGH);
//  digitalWrite(_IC, LOW);
//  delay(1);
//  digitalWrite(_IC, HIGH);
//}

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



