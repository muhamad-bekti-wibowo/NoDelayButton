#include "NoDelayButton.h"

NoDelayButton::NoDelayButton(uint8_t pins[], char _buttonChars[], uint8_t _buttonCount, uint8_t _expectedButtonCount)
    : buttonCount(_buttonCount),
      expectedButtonCount(_expectedButtonCount)
{
  for (uint8_t i = 0; i < buttonCount; i++)
  {
    buttonChars[i] = _buttonChars[i];
    buttonPins[i] = pins[i];
  }
}


uint8_t NoDelayButton::scanValue()
{
  uint8_t activeCount = 0;
  for (uint8_t i = 0; i < buttonCount; i++)
  {
    if (!digitalRead(buttonPins[i]))
    {
      if (!isLocked)
        pressedButtonIndex = 1 + i;
    }
    else
    {
      activeCount++;
    }
  }
  if (activeCount == buttonCount)
    pressedButtonIndex = 255;
  if (pressedButtonIndex == 255)
    isLocked = false;
  else if (isLocked)
    pressedButtonIndex = 254;
  if (pressedButtonIndex > 0 && pressedButtonIndex < 255)
    if (!isLocked)
      isLocked = true;

  return pressedButtonIndex;
}

String NoDelayButton::scanString()
{
  uint8_t activeCount = 0;
  String pinPressed;

  for (uint8_t i = 0; i < buttonCount; i++)
  {
    if (!digitalRead(buttonPins[i]))
    {
      pinPressed += char(buttonChars[i]);
    }
    else
    {
      activeCount++;
    }
  }
  if (pinPressed.length() == expectedButtonCount && activeCount != 1)
  {
    return pinPressed;
  }
  return "";
}

void NoDelayButton::clear()
{
  isLocked = false;
}

void NoDelayButton::lockButton()
{
  isLocked = true;
}

uint8_t NoDelayButton::scanValueRepeat()
{
  clear();
  return scanValue();
}

bool NoDelayButton::begin()
{
  if (scanValue() == 255)
    return true;
  return false;
}

char NoDelayButton::convertChar(int8_t index)
{
  return buttonChars[index];
}