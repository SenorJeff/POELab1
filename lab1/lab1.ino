/*
  Button

 Turns on and off a light emitting diode(LED) connected to digital
 pin 13, when pressing a pushbutton attached to pin 2.


 The circuit:
 * LED attached from pin 13 to ground
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground

 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.


 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 8;     // the number of the pushbutton pin
const int green =  12;// the number of the LED pin
const int yellow = 11;
const int red = 10;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int LEDState = 0;
int previousButtonState = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // initialize Serial Communication
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if ((buttonState == HIGH) && (previousButtonState == LOW)) {
      //increment LEDState
      LEDState++;
      LEDState = LEDState % 5;
      Serial.println(LEDState);
  }

  bool greenOn = LEDState > 2;
  digitalWrite(green, greenOn);
  
  previousButtonState = buttonState;
  delay(100);
}
