
#include <NewPing.h>   // include the NewPing library for this program

#include <Servo.h>

Servo myservo;

#define VCC_PIN 13

#define TRIGGER_PIN 12 // sonar trigger pin will be attached to Arduino pin 12

#define ECHO_PIN 11 // sonar echo pint will be attached to Arduino pin 11

#define GROUND_PIN 10

#define MAX_DISTANCE 200 // fmaximum distance set to 200 cm

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // initialize NewPing

// Lights // 

#define LED_TIMER_UNTIL_CLOSE 4 //

#define LED_PROXIMITY 3

#define LED_TIMER 2 

// DISTANCE DEFINITIONS // 

#define DISTANCE_FOR_PROXIMITY_LED 40 // *******


// SAIFS WORK 

#define MAX_DISTANCE 200 // fmaximum distance set to 200 cm 

#define THRESHOLD_DISTANCE 10  // distance at which claw starts closing ******

#define HOLD_TIME 5  // duration of time between open/close phases in which servo does nothing. ***** 




void servoAction(void);
void timer(int duration);

//

void setup() //do the following things once


{

  Serial. begin(9600);  // set data transmission rate to communicate with computer

  pinMode(ECHO_PIN, INPUT) ;  

  pinMode(TRIGGER_PIN, OUTPUT) ;

  pinMode(GROUND_PIN, OUTPUT);  // tell pin 10 it is going to be an output

  pinMode(VCC_PIN, OUTPUT);  // tell pin 13 it is going to be an output

  digitalWrite(GROUND_PIN,LOW); // tell pin 10 to output LOW (OV, or ground)

  digitalWrite(VCC_PIN, HIGH) ; // tell pin 13 to output HIGH (+5V)

  pinMode(LED_PROXIMITY, OUTPUT); // tell pin 1 it is going to be an output for the PROXIMITY LED
  
  pinMode(LED_TIMER, OUTPUT); // tell pin 2 it is going to be an output for the TIMER LED

  pinMode(8,INPUT_PULLUP); //pin 8 forced to HIGH when there is no external input

  pinMode(LED_TIMER_UNTIL_CLOSE, OUTPUT); // tell pin 4 that it will be an output

  
  myservo.attach(9); //attaches the servo on pin 9 to the servo object

  myservo.write(60); //tells servo to go to 60 degree position

 
}

 int FLAG = 0 ; 
void loop() // do the following things forever


{
 
  
  delay(300); // wait for this number of milliseconds

  int DISTANCE_IN_CM = sonar.ping_cm(); // read the sonar sensor, using a variable

  Serial.print("Ping: "); //print “Ping:" on the computer display

  Serial.print(DISTANCE_IN_CM); //print the value of the variable next

  Serial.println("cm"); //print "cm" after that, then go to next line

   if(DISTANCE_IN_CM <= DISTANCE_FOR_PROXIMITY_LED){ // if the sonar is withing 20 cm, turn on PROXIMITY LED
    digitalWrite(LED_PROXIMITY, HIGH); // turn on led when it is in within proximity
  }
  else{
    digitalWrite(LED_PROXIMITY,LOW); // turn off the led when it's not within proximity
  }

    if (DISTANCE_IN_CM <= THRESHOLD_DISTANCE && FLAG == 0 && DISTANCE_IN_CM > 0) {
    timerUntilClose(3);
    myservo.write(360);
    Serial.print("active"); //print the word "open"
    Serial.println(""); //print nothing, go to next line
    timer(4);
    FLAG = 1;
    }
    else if(DISTANCE_IN_CM <= THRESHOLD_DISTANCE && FLAG == 1 && DISTANCE_IN_CM > 0){
    myservo.write(0); //goes back to original position
    Serial.print("deactivated");
    Serial.println("");
    timer(3);
    FLAG = 0; 
    }
  }





//INPUT THE DURATION IN SECONDS//

void timer(int duration){
 int counter = 0;
  
  for(counter = 0 ; counter < duration ; counter++){
  digitalWrite(LED_TIMER, HIGH); // Turns on the LED 
  delay(200);
  digitalWrite(LED_TIMER,LOW); // Turns off the LED for a flicker effect 
  delay(800);
  
   }
}
 
void timerUntilClose(int duration){
 int counter = 0;
  
  for(counter = 0 ; counter < duration ; counter++){
  digitalWrite(LED_TIMER_UNTIL_CLOSE, HIGH); // Turns on the LED 
  delay(200);
  digitalWrite(LED_TIMER_UNTIL_CLOSE,LOW); // Turns off the LED for a flicker effect 
  delay(800);
  
   }
}


/*
void servoAction(void){
    myservo.write(180);
    Serial.print("active"); //print the word "open"
    Serial.println(""); //print nothing, go to next line

    timer(HOLD_TIME);

    myservo.write(60); //goes back to original position
    Serial.print("deactivated");
    Serial.println("");
  
}

*/
