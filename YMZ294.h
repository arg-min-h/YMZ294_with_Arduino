#ifndef _YMZ294_H_
#define _YMZ294_H_

class YMZ294 {
  public:
    YMZ294(byte WS, byte CS, byte A0, byte IC, byte* D);
    YMZ294(byte WS, byte CS, byte A0, byte IC, byte* D, bool toggle);
    void reset();
    void setRegister(byte, byte);
    void setToneFrequency(byte, int);
    void setToneFrequency(byte, float);
    void setNoiseFrequency(int);
//    void setMixer(
  private:
    byte _WS, _CS, _A0, _IC;
    byte* _D;
    bool _toggle;
};
#endif // _YMZ294_H_
