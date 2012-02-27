#include <DebounceButton.h>

DebounceButton buttonGreen = DebounceButton(8, DBTN_PULLUP_INTERNAL, 50, 1000, 500);
DebounceButton buttonRed = DebounceButton(9, DBTN_PULLUP_INTERNAL, 50, 1000);

void setup() {
  Serial.begin(9600);
  
  buttonGreen.onPress = onPressGreen;
  buttonGreen.onRelease = onReleaseGreen;
  buttonGreen.onClick = onClickGreen;
  buttonGreen.onHold = onHoldGreen;
  buttonRed.onPress = onPressRed;
  buttonRed.onRelease = onReleaseRed;
  buttonRed.onClick = onClickRed;
  buttonRed.onHold = onHoldRed;
}

void loop() {
  DebounceButton::updateAll();
}

void onPressGreen(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.println("Green pressed");
}

void onReleaseGreen(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Green released after ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onClickGreen(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Green clicked for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onHoldGreen(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Green hold for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onPressRed(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.println("Red pressed");
}

void onReleaseRed(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Red released after ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onClickRed(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Red clicked for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onHoldRed(DebounceButton* btn) {
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Red hold for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}