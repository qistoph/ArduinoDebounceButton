/*
  DebounceButton.h - DebounceButton library
  Copyright (c) 2010 Chris van Marle.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef DebounceButton_h
#define DebounceButton_h

#include "Arduino.h"

#define DBTN_MAX_BUTTONS    20

#define DBTN_PULLDOWN        0
#define DBTN_PULLUP          1
#define DBTN_PULLUP_INTERNAL 2

class DebounceButton {
  public:
    DebounceButton(byte buttonPin, byte type = DBTN_PULLDOWN, unsigned long debounceDelay = 50, unsigned long holdDelay = 0, unsigned long holdInterval = 0);
    ~DebounceButton();
    boolean update();
    boolean justPressed();
    boolean justReleased();
    boolean isPressed();

    void setType(byte type);
    unsigned long getDownTime();

    void (*onPress)(DebounceButton*);
    void (*onRelease)(DebounceButton*);    void (*onClick)(DebounceButton*);    void (*onHold)(DebounceButton*);

    static void updateAll();

  private:
    byte id;
    byte pin;
    byte pressedValue;
    byte stableButtonState;
    byte lastButtonState;
    boolean updated;
    unsigned long debounceDelay;
    unsigned long holdDelay;
    unsigned long holdInterval;
    unsigned long holdSent;
    unsigned long lastDebounceTime;
    unsigned long downTime;

    static DebounceButton *buttons[];
    static byte buttonId;
};

#endif
