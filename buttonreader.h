#ifndef BUTTONREADER_H
#define BUTTONREADER_H
#include <Arduino.h>

class ButtonReader {
public:
  ButtonReader(int pinNumber) : m_isPressed(false), m_pinNumber(pinNumber), m_numberOfPresses(0) {};
  void setup() {pinMode(m_pinNumber, INPUT);};
  void update() {
    if (digitalRead(m_pinNumber) == HIGH) {
      if (!m_isPressed) {
        m_numberOfPresses++;
      }
      m_isPressed = true;
    } else {
      m_isPressed = false;
    }
  }
  int numberOfPresses() const {return m_numberOfPresses;}
private:
  bool m_isPressed;
  int m_numberOfPresses;
  const int m_pinNumber;
};

#endif
