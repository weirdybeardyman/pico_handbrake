/*
  PicoGamepad

  Turn a Raspberry Pico 2040 into an HID gamepad

  Supports:
  128 Buttons
  8 Analog axes
  4 Hat switches
  
  created 28 June 2021
  by Jake Wilkinson (RealRobots)

  This example code is in the public domain.

  https://www.gitlab.com/realrobots/PicoGamepad
*/

#include <PicoGamepad.h>

PicoGamepad gamepad;

const int minAxis = 540;
const int maxAxis = 630;
const int buttonCutoff = 555;
//max pot value 667 - min 528

// 16 bit integer for holding input values
int val;
bool buttonVal;
bool lastButtonState;

void setup() {  
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, true); 
  // X Potentiometer on pin 26
  pinMode(26, INPUT);

  //set initial button state
  lastButtonState = analogRead(26) > buttonCutoff;
  //gamepad.SetButton(0, lastButtonState); 
  //gamepad.send_update();
}

void loop() {

  // Get input value from Pico analog pin
  val = analogRead(26);
  // Map analog 0-1023 value from pin to max HID range -32767 - 32767
  //val = constrain(val, minAxis, maxAxis);
  //val = map(val, minAxis, maxAxis, -32767, 32767);//map(val, 0, 1023, -32767, 32767);

  // Send value to HID object
  //gamepad.SetX(val);


  // Simple toggle button that is on when handbrake is up and vice-versa
  //buttonVal = analogRead(26) > buttonCutoff;
  //gamepad.SetButton(0, buttonVal); 

  //Momentary button to toggle handbrake when it changes state
  buttonVal = val > buttonCutoff;
  gamepad.SetButton(0, buttonVal != lastButtonState); 
  lastButtonState = buttonVal;
    
  // Send all inputs via HID 
  // Nothing is send to your computer until this is called.
  gamepad.send_update();

  delay(100);
}
