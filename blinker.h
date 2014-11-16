#ifndef BLNKER_H
#define BLINKER_H
#include <Arduino.h>

class Blinker {
public:
  Blinker(int pinNumber, int interval) : m_pinNumber(pinNumber), m_interval(interval),
                                         m_lastTimerStart(millis()), blinkStatus(LOW) {};
  void setup() {pinMode(m_pinNumber, OUTPUT);};
  void update() {
    if (m_interval ==  0) {digitalWrite(m_pinNumber, LOW); return;}
    if (millis() - m_lastTimerStart > m_interval) {
      blinkStatus = !blinkStatus;
      digitalWrite(m_pinNumber, blinkStatus);
      m_lastTimerStart = millis();
    }
  }
  void setInterval(int interval) {m_interval = interval;};
private:
  const int m_pinNumber;
  unsigned long m_interval;
  unsigned long m_lastTimerStart;
  bool blinkStatus;
};

#endif
