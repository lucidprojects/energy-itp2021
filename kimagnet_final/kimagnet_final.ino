const int buttonPin = 10;    // the number of the toggle pin
int buttonState;         // the current reading from the input pin
int lastButtonState;     // the previous reading from the input pin
int driveVal;

// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>

// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
// the default pins listed are the ones used on the Redbot (ROB-12097) with
// the exception of STBY which the Redbot controls with a physical switch
#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup() {
  pinMode(buttonPin, INPUT);
  buttonState = 0;
  lastButtonState = 0;
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    motor1.brake();
    if (lastButtonState == 1) {
      Serial.println("Switch one is on");
      driveVal = -255;
    } else {
      Serial.println("Switch one is off");
      driveVal = 255;

    }
  }

  lastButtonState = reading;

//  Serial.print("lastButtonState = ");
//  Serial.println(lastButtonState);
//  Serial.print("driveVal = ");
//  Serial.println(driveVal);

  motor1.drive(driveVal);

}
