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
const int green =  11;// the number of the LED pin
const int yellow = 10;
const int red = 9;
const int sensorPin = A0;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int LEDState = 0;
int previousButtonState = 0;
int timer; 
int sensorValue;
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

void writeAll(bool redon, bool yellowon, bool greenon){
  analogWrite(red, 250-sensorValue/2);
  analogWrite(yellow, 250-sensorValue/2);
  analogWrite(green,250-sensorValue/2);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if ((buttonState == HIGH) && (previousButtonState == LOW)) {
      //increment LEDState
      LEDState++;
      LEDState = LEDState % 5;
      Serial.println(LEDState);
  }

  timer = millis()/500;
  if (LEDState == 0)
  {
    writeAll(HIGH, HIGH, HIGH);
  }
  else if(LEDState == 1)
  {
    writeAll(timer%2 > 0, timer%2 > 0, timer%2 > 0);
  }
  else if(LEDState == 2)
  {
    writeAll(timer%2 > 0,timer%4 > 1, timer%8 > 3);
  }
  else if(LEDState == 3)
  {
    writeAll(timer%3 == 0, timer%3 == 1, timer%3 == 2);
  }
  else if(LEDState == 4)
  {
    writeAll(LOW, LOW, LOW);
  }
  
  previousButtonState = buttonState;
  delay(100);
}
