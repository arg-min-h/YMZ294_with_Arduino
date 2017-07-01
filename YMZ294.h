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
    void setNoiseFrequency(float);
    void setMixer(byte, bool);
    byte getMixer(); // デバッグ用
    void setVolume(byte, byte);
    byte getVolume(byte); // デバッグ用
    void setEnvelope(byte, bool);
    void setEnvelopeFrequency(int);
    void setEnvelopeFrequency(float);
    void setEnvelopeShape(byte);
  private:
    byte _WS, _CS, _A0, _IC;
    byte* _D;
    bool _toggle;
    byte _mix;
    //    byte _vol;
    byte _vol[3];
};
#endif // _YMZ294_H_
