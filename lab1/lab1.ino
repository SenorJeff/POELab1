/*
  Lab1
  9/9/2016
  Jeff Pflueger and Eric Miller

  This code satisfies the requirements for Lab 1

  LEDs are hooked up to pins 9, 10, and 11
  A button is hooked up to pin 8
  An Infra-Red distance sensor is hooked up to pin A0

   The Button switches between 9 states for the LEDs:

   All On
   Blinking
   Counting forward in Binary
   Counting backward in Binary
   Move 1 LED forward
   Move 1 LED backward
   Move LED-Hole Forward
   Move LED-Hole Backward
   All Off

   The Infra red distance sensor changes the brightness
   of the LEDs when it senses something
   LEDs get dimmer the closer something gets.

   
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin = 8;   // the number of the pushbutton pin
const int green =  11;     // the number of the green LED pin
const int yellow = 10;     // the number of the yellow LED pin
const int red = 9;         // the number of the red LED pin
const int sensorPin = A0;  // the number of the IR sensor pin

// variables will change:
int buttonState = 0;       // variable for pushbutton status
int LEDState = 0;          // variable for LED state
int previousButtonState = 0; // previous button state variable
int timer;                 // timer variable
int sensorValue;           //value fo IR sensor

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
  //Sets LEDs to PWM signal between 0 and 255 based on IR sensor 
  analogWrite(red, redon ? (250-sensorValue/2) : 0);
  analogWrite(yellow, yellowon ? (250-sensorValue/2) : 0);
  analogWrite(green, greenon ? (250-sensorValue/2) : 0);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  sensorValue = analogRead(sensorPin);
  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if ((buttonState == HIGH) && (previousButtonState == LOW)) {
    
      //increment LEDState
      LEDState++;

      //LED State counts 0-8, 9 total states
      LEDState = LEDState % 9;

      //delays 2ms so button doesnt read
      //multiple times
      delay(2);
  }

  //times on half second intervals
  timer = millis()/500;

  //These set states for LEDs
  if (LEDState == 0) {
    //all LEDs On
    writeAll(HIGH, HIGH, HIGH);
    
  }
  else if(LEDState == 1) {
    //Blinking LEDs
    writeAll(timer%2 > 0, timer%2 > 0, timer%2 > 0);
    
  }
  else if(LEDState == 2) {
    //Counts forward in Binary
    writeAll(timer%2 > 0,timer%4 > 1, timer%8 > 3);
    
  }
  else if(LEDState == 3) {
    //Counts backward in Binary
    writeAll(!(timer%2 > 0),!(timer%4 > 1), !(timer%8 > 3)); 
    
  }
  else if(LEDState == 4) {
    //Blinks 1 LED forward
    //1-0-0 -> 0-1-0 -> 0-0-1
    writeAll(timer%3 == 0, timer%3 == 1, timer%3 == 2);   
    
  }
  else if(LEDState == 5) {
    //Blinks 1 LED backward
    //0-0-1 -> 0-1-0 -> 1-0-0
    writeAll(timer%3 == 2, timer%3 == 1, timer%3 == 0);
    
  }
  else if(LEDState == 6) {
    //Blinks LED hole forward
    //0-1-1 -> 1-0-1 -> 1-1-0
    writeAll(!(timer%3 == 0), !(timer%3 == 1), !(timer%3 == 2));
    
  }
  else if(LEDState == 7) {
    //Blinks LED hole backward
    //1-1-0 -> 1-0-1 -> 0-1-1
    writeAll(!(timer%3 == 2), !(timer%3 == 1), !(timer%3 == 0));
    
  }
  else {
    //All LEDs Off
    writeAll(LOW, LOW, LOW);
    
  }
  
  //Sets previous button state to current
  //button state for use in future loops
  previousButtonState = buttonState;
}
