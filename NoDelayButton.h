#include <arduino.h>

#ifndef NoDelayButton_H
#define NoDelayButton_H

class NoDelayButton {
public:
  // Konstruktor untuk menggunakan pin digital biasa dengan karakter keluaran
  NoDelayButton(uint8_t pins[], char buttonChars[], uint8_t buttonCount, uint8_t expectedButtonCount);
  bool begin();
  uint8_t scanValue();
  uint8_t scanValueRepeat();
  void clear();
  void lockButton();
  String scanString();
  char convertChar(int8_t index);

private:
  uint8_t buttonPins[10];
  uint8_t buttonChars[10];
  uint8_t buttonCount;
  uint8_t expectedButtonCount;
  bool isLocked;
  uint8_t pressedButtonIndex;
};

#endif