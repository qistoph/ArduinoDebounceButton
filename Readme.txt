DebounceButton library

-= INDEX =-
- SHORT INTRODUCTION
- USAGE
- VERSION HISTORY
- COPYRIGHT & LICENSE

-= SHORT INTRODUCTION =-
Working with the Arduino I was looking for a library that had all the button
functionality I need already in place.
Unfortunately there was no library available that had everything I wanted. So I
wrote my own.

This DebounceButton library currently has
- Debouncing
- Event-like interface (onPress, onRelease, onClick, onHold)
- Interval events for hold buttons
- Supports 3 types of buttons: pull down, pull-up and internal pull-up using the
  Arduino internal pull-up resistor
- Single call for updating all buttons

-= USAGE =-
The included example shows how to use the DebounceButton, but here's a short
description anyway.

Define a DebounceButton with the arguments that you want:
DebounceButton(buttonPin, type, debounceDelay, holdDelay, holdInterval)

buttonPin      the pin on which the button is connected
type           one of the three types (optional, default: DBTN_PULLDOWN)
debounceDelay  the time to allow the button to bounce, in ms
               (optional, default: 50)
holdDelay      how long to wait before sending the hold event, in ms
               (optional, default: 0 = disabled)
holdInterval   after how much time the hold event should be sent again, in ms
               (optional, default: 0 = disabled)

The type of the button can be one of these three
DBTN_PULLDOWN          A button with (external) pull-down resistor
DBTN_PULLUP            A button with (external) pull-up resistor
DBTN_PULLUP_INTERNAL   A button with internal pull-up resistor enabled

An example:
  DebounceButton button1 = DebounceButton(8, DBTN_PULLUP_INTERNAL, 50, 1000, 500);

This creates a button for pin 8, using the internal pull-up resistor.
It allows the button to bounce for 50ms. The onHold event is fired after
1 sec (1000ms) and will repeat twice a second (500ms).

In the setup() you can add the listeners to the events, like this

  button1.onPress = onPressGreen;
  button1.onRelease = onReleaseGreen;
  button1.onClick = onClickGreen;

All events are function that have one DebounceButton* as argument, and
return void.
There are 4 events available
onPress    fires when the button is pressed
onRelease  fires when the button is released
onClick    fires when the button is released without holding
onHold     fires when the button is held down

You should call the update method of the buttons every once in a while.
To call the update of all created buttons in only one line, you can use
DebounceButton::updateAll();

For a complete example, have a look at the included DebounceButton example.

-= VERSION HISTORY =-
Version 0.3 (03-02-2010)
Removed some Serial.print lines that accidentally ended up in the release
Added down time information
Removed &'s from the event setting
Added click event

Version 0.2 (01-02-2010)
Included hold-interval functionality
Released on Arduino forums (http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1265043477)

Version 0.1
Personal archive

-= COPYRIGHT & LICENSE =-
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

