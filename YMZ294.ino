#include "YMZ294.h"

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
YMZ294 ymz294(ws, cs, a0, ic, d, toggle);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ymz294.reset(); // リセット
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  toneFreqVerification(); // トーン周波数の動作テスト
  toneFreqMIDIVerification(); // MIDIノートNo.を用いたトーン周波数の動作テスト
  noiseFreqVerification(); // ノイズ周波数の動作テスト
  volumeVerification(); // ボリュームの動作テスト
  mixerVerification(); // ミキサーの動作テスト
  envVerification(); // エンベロープの動作テスト
}

// トーン周波数の動作テスト
void toneFreqVerification() {
  Serial.printf("\nTone function test\n");
  ymz294.setMixer(chA, on); // CH Aのミキサーをオンにする
  ymz294.setVolume(chA, 15); // CH Aの音量を15にする
  for (int i = 4095; i >= 0; i--) { // 繰り返し（TPをデクリメント）
    float freq = 2000000 / (16 * (float)i); // 周波数の計算
    ymz294.setToneFrequency(chA, freq); // CH Aの周波数を freqにする
    Serial.printf("TP = %d (%f Hz)\n", i, freq);
    delay(5);
  }
  delay(500);
  ymz294.setVolume(chA, 0); // CH Aのミキサーをオフにする
  ymz294.setMixer(chA, off); // CH Aの音量を0にする
}

// MIDIノートNo.を周波数に変換
float MIDI2Freq(int midiNoteNo) {
  float midiExp = ((float)midiNoteNo - 69) / 12;
  float freq = 440 * pow(2, midiExp);
  return freq;
}

// MIDIノートNo.を用いたトーン周波数の動作テスト
void toneFreqMIDIVerification() {
  Serial.printf("\nTone function test\n");
  ymz294.setMixer(chA, on); // CH Aのミキサーをオンにする
  ymz294.setVolume(chA, 15); // CH Aの音量を15にする
  for (int i = 0; i < 128; i++) { // 繰り返し（MIDIノートNo.をインクリメント）
    float freq = MIDI2Freq(i); // MIDIノートNo.から周波数を計算
    ymz294.setToneFrequency(chA, freq); // CH Aの周波数をfreqにする
    float floatTP = 0;
    if (freq != 0) {
      floatTP = 2000000 / (16 * freq); // 周波数からTPを計算
    }
    int TP = (int)floatTP; // TPを整数に変換する
    if (TP > 4095) {
      Serial.printf("MIDI Note No.= %d (%f Hz)\n (YMZ294 cannnot treat this frequency.)\n", i, freq);
    } else {
      Serial.printf("MIDI Note No.= %d (%f Hz)\n", i, freq);
    }
    delay(100);
  }
  delay(500);
  ymz294.setVolume(chA, 0); // CH Aの音量を0にする
  ymz294.setMixer(chA, off); // CH Aのミキサーをオフにする
}

// ノイズ周波数の動作テスト
void noiseFreqVerification() {
  Serial.printf("\nNoise function tets\n");
  ymz294.setMixer(chBN, on); // CH Bのミキサーをオンにする
  ymz294.setVolume(chB, 15); // CH Bの音量を15にする
  for (int i = 31; i >= 0 ; i--) { // 繰り返し（NPをデクリメント）
    float freq = 2000000 / (16 * (float)i); // ノイズ周波数を計算
    ymz294.setNoiseFrequency(freq); // 周波数をfreqにする
    Serial.printf("NP = %d,(%f Hz)\n", i, freq);
    delay(100);
  }
  delay(500);
  ymz294.setVolume(chB, 0); // CH Bの音量を0にする
  ymz294.setMixer(chBN, off); // CH Bのミキサーをオフにする
}

// ボリュームの動作テスト
void volumeVerification(){
  Serial.printf("\nVolume function test\n");
  ymz294.setMixer(chA, on); // CH Aのミキサーをオンにする
  ymz294.setToneFrequency(chA, 440);
  for (byte i = 0; i < 16; i++){ // 繰り返し（音量をインクリメント）
    ymz294.setVolume(chA, i); // CH Aの音量をiにする
    Serial.printf("Volume = %d\n", i);
    delay(500);
  }
  delay(1000);
}

// ミキサーの動作テスト
void mixerVerification(){
  Serial.printf("\nMixer function test");
  ymz294.setVolume(chA, 15); // CH Aのボリュームを15にする
  ymz294.setVolume(chB, 15); // CH Bのボリュームを15にする
  ymz294.setVolume(chC, 15); // CH Cのボリュームを15にする
  ymz294.setToneFrequency(chA, MIDI2Freq(60)); // CH Aの周波数を"ド"にする
  ymz294.setToneFrequency(chB, MIDI2Freq(64)); // CH Bの周波数を"ミ"にする
  ymz294.setToneFrequency(chC, MIDI2Freq(67)); // CH Cの周波数を"ソ"にする
  Serial.printf("CH A: off, CH B: off, CH C: off\n");
  delay(1000);
  ymz294.setMixer(chA, on); // CH Aのミキサーをオンにする
  Serial.printf("CH A: on, CH B: off, CH C: off\n");
  delay(1000);
  ymz294.setMixer(chB, on); // CH Bのミキサーをオンにする
  Serial.printf("CH A: on, CH B: on, CH C: off\n");
  delay(1000);
  ymz294.setMixer(chC, on); // CH Cのミキサーをオンにする
  Serial.printf("CH A: on, CH B: on, CH C: on\n");
  delay(1000);
  ymz294.setMixer(chA, off); // CH Aのミキサーをオフにする
  Serial.printf("CH A: off, CH B: on, CH C: on\n");
  delay(1000);
  ymz294.setMixer(chB, off); // CH Bのミキサーをオフにする
  Serial.printf("CH A: off, CH B: off, CH C: on\n");
  delay(1000);
  ymz294.setMixer(chC, off); // CH Cのミキサーをオフにする
  ymz294.setVolume(chA, 0); // CH Aのボリュームを0にする
  ymz294.setVolume(chB, 0); // CH Bのボリュームを0にする
  ymz294.setVolume(chC, 0); // CH Cのボリュームを0にする
}

// エンベロープの動作テスト
void envVerification() {
  Serial.printf("\nEnvelope function test\n");
  ymz294.setMixer(chC, on); // CH Cのミキサーをオンにする
  ymz294.setVolume(chC, 15);
  ymz294.setEnvelope(chC, on); // CH Cのエンベロープをオンにする
  for (int i = 0; i < 5; i++) {
    float envCycle = 250 * (float)i ; // エンベロープの周期 [ms]  float envFreq = 1000 / envCycle; // エンベロープの周波数 [Hz]
    Serial.printf("Cycle = %f ms \n", envCycle);
    ymz294.setEnvelopeFrequency(1000 / envCycle); // エンベロープ周波数を 1 / envCycle [Hz]にする
    ymz294.setToneFrequency(chC, 440); // CH Cの周波数を440 Hzにする
    for (int j = 0; j < 16; j++) {
      bool cont = bitRead(j, 3); // contの値をjの4ビット目にする
      bool att = bitRead(j, 2); // contの値をjの3ビット目にする
      bool alt = bitRead(j, 1); // contの値をjの2ビット目にする
      bool hold = bitRead(j, 0); // contの値をjの1ビット目にする
      Serial.printf("cont = %d, att = %d, alt = %d, hold = %d\n", cont, att, alt, hold);
      ymz294.setEnvelopeShape(cont, att, alt, hold); // エンベロープを設定する
      delay(1000);
    }
  }
  delay(1000);
  ymz294.setVolume(chC, 0); // CH Cの音量を0にする
  ymz294.setEnvelope(chC, off); // CH Aのミキサーをオフにする
  ymz294.setMixer(chC, off); // CH Cのエンベロープをオンにする
}
