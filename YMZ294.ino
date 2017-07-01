#include "YMZ294.h"

// マクロ
#define on 1 // オン
#define off 0 // オフ
#define chA 0 // チャンネルA
#define chB 1 // チャンネルB
#define chC 2 // チャンネルC
#define chAN 3 // チャンネルAのノイズ
#define chBN 4 // チャンネルBのノイズ
#define chCN 5 // チャンネルCのノイズ
#define toggle true //リセットピンの反転

const byte ws = 17; // /WSに接続するピン番号
const byte cs = 18; // /CSに接続するピン番号
const byte a0 = 19; // A0に接続するピン番号
const byte ic = 22; // /ICに接続するピン番号
byte d[] = {32, 33, 25, 26, 27, 14, 12, 13}; //D0...D7に接続するピン番号


// YMZ294のインスタンスの生成
YMZ294 chip1(ws, cs, a0, ic, d, toggle);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  chip1.reset(); // リセット
  chip1.setMixer(chA, on); // CH Aのトーンをオンに
  chip1.setMixer(chB, off); // CH Bのトーンをオフに
  chip1.setMixer(chC, off); // CH Cのトーンをオフに
  chip1.setMixer(chBN, on);

  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  toneFreqVerification();
  noiseFreqVerification();
}

float MIDI2Freq(int midiNoteNo) {
  float midiExp = ((float)midiNoteNo - 69) / 12;
  float freq = 440 * pow(2, midiExp);
  return freq;
}

void noiseFreqVerification() {
  chip1.setVolume(chB, 15);
  for (byte b = 0; b < 32 ; b++) {
    byte by = 31 - b;
    float freq = 2000000 / (16 * (float)by);
    chip1.setRegister(0x06, by);
    Serial.printf("by = %d, %f [Hz]\n", by, freq);
    delay(100);
  }
  delay(500);
  chip1.setVolume(chB, 0);
}

void toneFreqVerification() {
  chip1.setVolume(chA, 15);
  for (int i = 0; i < 128; i++) {
    float freq = MIDI2Freq(i);
    float floatTP = 0;
    if (freq != 0) {
      floatTP = 2000000 / (16 * freq);
    }
    int TP = (int)floatTP;
    chip1.setToneFrequency(chA, freq);
    if (TP > 4095) {
      Serial.printf("MIDI Note No. %d (%f Hz)\n (YMZ294 cannnot treat this frequency.)\n", i, freq);
    } else {
      Serial.printf("MIDI Note No. %d (%f Hz)\n", i, freq);
    }
    delay(100);
  }
  delay(500);
  chip1.setVolume(chA, 0);
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

