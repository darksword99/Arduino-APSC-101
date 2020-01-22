// --------------------------------------------------------------------------------------

// APSC 101-January 2020

// Code for video Arduino 05

// Video located at:   https://www.youtube.com/watch?v=_DDtwvWsmNo

//

// VERSION 2

//

// This program uses an ultrasonic distance sensor (sonar)

// and shows its readings on the screen of an attached

// computer, via the Arduino Serial Monitor.

// IMPORTANT:  This Version 2 program uses the "NewPing" library, which can be installed

// by selecting “Sketch → Include Library → Manage Library and then adding NewPing

//  

//  Instructions here:  https://www.ardu-badge.com/NewPing

//

// --------------------------------------------------------------------------------------


#include <NewPing.h>   // include the NewPing library for this program

#define VCC_PIN 13

#define TRIGGER_PIN 12 // sonar trigger pin will be attached to Arduino pin 12

#define ECHO_PIN 11 // sonar echo pint will be attached to Arduino pin 11

#define GROUND_PIN 10

#define MAX_DISTANCE 200 // fmaximum distance set to 200 cm

#define THRESHOLD_DISTANCE 5  // distance at which claw starts closing

#define HOLD_TIME 5  // duration of time between open/close phases in which servo does nothing. 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // initialize NewPing

Servo myservo; //create servo object to control a servo



void setup() //do the following things once


{

  Serial. begin(9600);  // set data transmission rate to communicate with computer

  pinMode(ECHO_PIN, INPUT) ;  

  pinMode(TRIGGER_PIN, OUTPUT) ;

  pinMode(GROUND_PIN, OUTPUT);  // tell pin 10 it is going to be an output

  pinMode(VCC_PIN, OUTPUT);  // tell pin 13 it is going to be an output

  digitalWrite(GROUND_PIN,LOW); // tell pin 10 to output LOW (OV, or ground)

  digitalWrite(VCC_PIN, HIGH) ; // tell pin 13 to output HIGH (+5V)


//servo setup below

  pinMode(8,INPUT_PULLUP); //pin 8 forced to HIGH when there is no external input

  myservo.attach(9); //attaches the servo on pin 9 to the servo object

  myservo.write(60); //tells servo to go to 60 degree position

}


void loop() // do the following things forever


{

  delay(100); // wait for this number of milliseconds

  int DISTANCE_IN_CM = sonar.ping_cm(); // read the sonar sensor, using a variable

  Serial.print("Ping: "); //print “Ping:" on the computer display

  Serial.print(DISTANCE_IN_CM); //print the value of the variable next

  Serial.println("cm"); //print "cm" after that, then go to next line

  if (DISTANCE_IN_CM >= THRESHOLD_DISTANCE) {
    servoAction();
  }

  


}

void servoAction() 

{
    myservo.write(150);
    Serial.print("active"); //print the word "open"
    Serial.println(""); //print nothing, go to next line

    delay(HOLD_TIME);

    myservo.write(60); //goes back to original position
    Serial.print("deactivated");
    Serial.println("");
  
}
