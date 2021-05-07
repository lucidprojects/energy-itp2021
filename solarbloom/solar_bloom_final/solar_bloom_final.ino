#include <Servo.h>
#include <Adafruit_SleepyDog.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
boolean bloomed = false;
//int oLightVal = 200;
//int cLightVal = 100;

int oLightVal = 150;
int cLightVal = 5;


int openVal;
int closeVal;
int degree;
int readCount = 0;
int analogValue = analogRead(A0);  //A3 on teensy
int rotateVal = 205;
int rotateCloseVal = 190;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 20  //D2 on teensy
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  delay(5000);
  digitalWrite(LED_BUILTIN, LOW);
  LowPowerDelay(25000);
  digitalWrite(LED_BUILTIN, HIGH);

  int analogValue = analogRead(A0);
  if (bloomed == false) {
    openVal = analogRead(A0);
    if (openVal > oLightVal) open();
  }

  if (bloomed != false) {
    closeVal = analogRead(A0);
    if (closeVal < cLightVal) close();
  }
}

void open() {
  degree = 100;
  if (!bloomed) {
    openVal = analogRead(A0);
    delay(50);
    myservo.write(60);
    for (pos = 0; pos <= rotateVal; pos += 1)  {        // goes from 0 degrees to rotateVal degrees
      delay(20);                                        // waits 20ms for the servo to reach the position
      if (pos >= rotateVal)  myservo.write(92);         //ascii to stop
    }
  }
  bloomed = true;
  readCount = 0;
  openVal = 0;
}

void close() {
  degree = 60;
  if (bloomed) {
    closeVal = analogRead(A0);
    delay(50);
    myservo.write(180);
    for (pos = 0; pos <= rotateCloseVal; pos += 1) {    // goes from 0 degrees to rotateCloseVal degrees
      delay(20);                                        // waits 20ms for the servo to reach the position
      if (pos >= rotateCloseVal)  myservo.write(92);    //ascii to stop
    }
  }
  bloomed = false;
  readCount = 0;
  closeVal = 0;
}

void LowPowerDelay( int ms)
{
  // if we’re in the first fifteen seconds, use regular delay
  // so we’re not locked out of USB re-programming
  if ( millis() < 15000) {
    delay(ms);
  } else {
    // otherwise, use super-low-power delay
    Watchdog.sleep(ms);
  }
}
