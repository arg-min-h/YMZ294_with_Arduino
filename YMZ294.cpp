#include "Arduino.h"
#include "YMZ294.h"
#define fsc 2000000

// コンストラクタ
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
}

// コンストラクタ（リセットピンのトグル）
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
}

// リセット
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
  for(byte i = 0; i < 3; i++){
    setMixer(i, 0);
    setMixer(i + 3, 0);
    setVolume(i, 0);
  }
}

// レジスタへの書き込み
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

// トーンの周波数設定
void YMZ294::setToneFrequency(byte ch, int freq) {
  int TP = 0;
  if (freq != 0) {
    TP = fsc / (16 * freq);
  }
  if (TP > 4095) {
    TP = 0;
  }
  TP &= 0x0fff;
  setRegister(0x00 + (ch * 2), TP & 0xff);
  setRegister(0x01 + (ch * 2), (TP >> 8) & 0xff);
}

// トーンの周波数設定
void YMZ294::setToneFrequency(byte ch, float freq) {
  float floatTP = 0;
  if (freq != 0 | floatTP < 4096) {
    floatTP = fsc / (16 * freq);
  }
  int TP = 0;
  TP = (int)floatTP;
  if (TP > 4095) {
    TP = 0;
  }
  TP &= 0x0fff;
  setRegister(0x00 + (ch * 2), TP & 0xff);
  setRegister(0x01 + (ch * 2), (TP >> 8) & 0xff);
}

// ノイズの周波数設定
void YMZ294::setNoiseFrequency(int freq) {
  int NP = 0;
  if (freq != 0) {
    NP = fsc / (16 * freq);
  }
  if (NP > 31) {
    NP = 0;
  }
  NP &= 0x1f;
  setRegister(0x06, NP);
}

// ノイズの周波数設定
void YMZ294::setNoiseFrequency(float freq) {
  float floatNP = 0;
  if (freq != 0) {
    floatNP = fsc / (16 * freq);
  }
  int NP = 0;
  NP = (int)floatNP;
  if (NP > 31) {
    NP = 0;
  }
  NP &= 0x001f;
  setRegister(0x06, NP);
}

// ミキサーの設定
void YMZ294::setMixer(byte ch, bool mixSW) {
  bitWrite(_mix, ch, !mixSW);
  setRegister(0x07, _mix);
}

// _mixを取得（デバッグ用）
//byte YMZ294::getMixer() {
//  byte mix = _mix;
//  return mix;
//}

// ボリュームの設定
void YMZ294::setVolume(byte ch, byte vol) {
  byte env = _vol[ch];
  vol &= 0x0f;
  env &=  0xf0;
  _vol[ch] = env + vol;
  setRegister(0x08 + ch, _vol[ch]);
}

// _volの取得（デバッグ用）
//byte YMZ294::getVolume(byte ch) {
//  byte vol = _vol[ch];
//  return vol;
//}

// ボリュームとエンベロープの切り替え
void YMZ294::setEnvelope(byte ch, bool envSW) {
  bitWrite(_vol[ch], 4, envSW);
  setRegister(0x08 + ch, _vol[ch]);
}

// エンベロープの周波数の設定
void YMZ294::setEnvelopeFrequency(int freq) {
  int EP = 0;
  if (freq != 0) {
    EP = fsc / (256 * freq);
  }
  EP &= 0xffff;
  setRegister(0x0B, EP & 0xff);
  setRegister(0x0C, (EP >> 8) & 0xff);
}

// エンベロープの周波数の設定
void YMZ294::setEnvelopeFrequency(float freq) {
  float floatEP = 0;
  if (freq != 0) {
    floatEP = fsc / (256 * freq);
  }
  int EP = 0;
  EP = (int)floatEP;
  EP &= 0xffff;
  setRegister(0x0B, EP & 0xff);
  setRegister(0x0C, (EP >> 8) & 0xff);
}

// エンベロープの形状設定
void YMZ294::setEnvelopeShape(bool cont, bool att, bool alt, bool hold) {
  bitWrite(_shape, 3, cont);
  bitWrite(_shape, 2, att);
  bitWrite(_shape, 1, alt);
  bitWrite(_shape, 0, hold);
  setRegister(0x0d, _shape & 0x0f);
}

