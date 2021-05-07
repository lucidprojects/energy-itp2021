// Sweep
// by BARRAGAN <http://barraganstudio.com>

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created

int pos = 0;    // variable to store the servo position
int incomingByte = 0;   // for incoming serial data

boolean bloomed = false;
boolean unbloomed = true;
int bloomTo;

int openVal;
int closeVal;

int degree;

int readCount = 0;
int analogValue = analogRead(A0);  //A3 on teensy
void setup()
{
  myservo.attach(9);  // attaches the servo on pin 20  //D2 on teensy
  Serial.begin(9600);
  //  myservo.write(0);
  //  myservo.write(92);
}


void loop()
{
  
    int analogValue = analogRead(A0);
//     myservo.write(110);
  if (bloomed == false) {
    openVal = analogRead(A0);
//    if (openVal > 500) open(); // daytime
    if (openVal > 230) open(); // nighttime

  }

  if (bloomed != false) {
    closeVal = analogRead(A0);
//    if (closeVal < 260) close(); //daytime
    if (closeVal < 100) close(); //nighttime
  }

  //    if (readCount == 0 ) lightReading(analogValue);
  //    readCount++;

  //}

  //send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    Serial.print("received: ");
    Serial.print (incomingByte);
    if (incomingByte == 114) { //ASCI r
      close();
      Serial.println(" sent 0 Stopped ");
    }
    if (incomingByte == 108) {  // ASCII l
      open();
      Serial.println(" sent 0 Stopped ");
    }
    if (incomingByte == 48) {
      Serial.println(" sent Stopped ");
      myservo.write(92);
    }

    if (incomingByte == 97) {
      lightReading(analogValue);
    }

    if (incomingByte == 111){ //ASCII o
      open();
    }
  }
}


void lightReading(int a) {

  Serial.print("Analog reading = ");
  Serial.print(a);   // the raw analog reading

  // We'll have a few threshholds, qualitatively determined
  if (a < 10) {
    Serial.println(" - Dark");
    close();
  } else if (a < 200) {
    Serial.println(" - Dim");
    close();
  } else if (a < 500) {
    Serial.println(" - Light");
    close();
  } else if (a < 800) {
    Serial.println(" - Bright");
    open();
  } else {
    Serial.println(" - Very bright");
    open();
  }



}

void open() {
  Serial.println(" sent 180 Rotaing CCW ");
  degree = 100;
  if (!bloomed) {
    openVal = analogRead(A0);
    Serial.print("Analog reading = ");
    Serial.print(openVal);   // the raw analog reading
    delay(50);
    myservo.write(180);

    for (pos = 0; pos <= 85; pos += 1)  { // goes from 0 degrees to 180 degrees
      //      Serial.println(pos);
      delay(20);                       // waits 15ms for the servo to reach the position

      if (pos >= 85)  myservo.write(92);
    }
  }
  bloomed = true;
  readCount = 0;
  openVal = 0;
}



void close() {
  Serial.println(" sent 0 Rotainlg CW ");
  degree = 60;
  if (bloomed) {
    closeVal = analogRead(A0);
    Serial.print("Analog reading = ");
    Serial.print(closeVal);   // the raw analog reading
    delay(50); 
    myservo.write(60);

    for (pos = 0; pos <= 85; pos += 1) { // goes from 0 degrees to 180 degrees
      //      Serial.println(pos);
      delay(20);                       // waits 15ms for the servo to reach the position
      if (pos == 85)  myservo.write(92);
    }
  }
  bloomed = false;
  readCount = 0;
  closeVal = 0;

}
