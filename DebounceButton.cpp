/*
  DebounceButton.cpp - DebounceButton library
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

#include "DebounceButton.h"

DebounceButton::DebounceButton(byte buttonPin, byte type, unsigned long debounceDelay, unsigned long holdDelay, unsigned long holdInterval) {
  this->id = buttonId++;
  this->pin = buttonPin;
  this->holdDelay = holdDelay;
  this->holdInterval = holdInterval;
  DebounceButton::buttons[this->id] = this;

  setType(type);

  // some defaults
  lastDebounceTime = 0;
  this->debounceDelay = debounceDelay;
  updated = false;
  holdSent = false;
  onPress = NULL;
  onRelease = NULL;
}

DebounceButton::~DebounceButton() {
  for(int i=this->id; i<buttonId; ++i) {
    buttons[i] = buttons[i+1];
    //TODO: update the ID of the moved buttons
  }
  buttonId--;
}

// This function does not (yet) take into account the overflow of millis() after 2^32-1 ms (aprox 50 days)
boolean DebounceButton::update() {
  int reading = digitalRead(pin);
  unsigned long now = millis();

  if(reading != lastButtonState) {
    lastDebounceTime = now;
  }

  updated = false;

  if((now - lastDebounceTime) > debounceDelay) {
    // Switched from unpressed to pressed or vica versa
    if(stableButtonState != reading) {
      stableButtonState = reading;
      updated = true;
      holdSent = 0;

      if(stableButtonState == pressedValue && onPress != NULL) {
        onPress(this);
      }

      if(stableButtonState != pressedValue) {
        if(onRelease != NULL) {
          onRelease(this);
        }
        if((downTime < holdDelay || onHold == NULL) && onClick != NULL) {
          onClick(this);
        }
      }

    } else if(stableButtonState == pressedValue) {
      downTime = now - lastDebounceTime - debounceDelay;

      if(holdDelay > 0 && // The owner wants hold events, and
        ((!holdSent || holdInterval > 0) && (now - holdSent) > holdInterval) && // we haven't sent the event yet or it's time for another, and
        downTime > holdDelay && // we have waited long enough, and
        onHold != NULL) { // someone is actually listening
          onHold(this);
          holdSent = now;
      }
    }
  }

  lastButtonState = reading;

  return (stableButtonState == pressedValue);
}

boolean DebounceButton::isPressed() {
  return stableButtonState == pressedValue;
}

boolean DebounceButton::justPressed() {
  return updated && (stableButtonState == pressedValue);
}

boolean DebounceButton::justReleased() {
  return updated && (stableButtonState != pressedValue);
}

void DebounceButton::setType(byte type) {
  pinMode(pin, INPUT);
  // enable internal pull up
  if(type == DBTN_PULLUP_INTERNAL) digitalWrite(pin, HIGH);
  else digitalWrite(pin, LOW);

  switch(type) {
    case DBTN_PULLDOWN:
      pressedValue = HIGH;
      lastButtonState = stableButtonState = LOW;
      break;
    case DBTN_PULLUP:
    case DBTN_PULLUP_INTERNAL:
      pressedValue = LOW;
      lastButtonState = stableButtonState = HIGH;
      break;
  }
}

unsigned long DebounceButton::getDownTime() {
  return downTime;
}

DebounceButton *DebounceButton::buttons[DBTN_MAX_BUTTONS];
byte DebounceButton::buttonId = 0;

void DebounceButton::updateAll() {
  for(int i=0; i<buttonId; ++i) {
    buttons[i]->update();
  }
}