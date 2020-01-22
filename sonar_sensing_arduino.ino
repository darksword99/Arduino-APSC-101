
#include <NewPing.h>   // include the NewPing library for this program

#define VCC_PIN 13

#define TRIGGER_PIN 12 // sonar trigger pin will be attached to Arduino pin 12

#define ECHO_PIN 11 // sonar echo pint will be attached to Arduino pin 11

#define GROUND_PIN 10

#define MAX_DISTANCE 200 // fmaximum distance set to 200 cm

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // initialize NewPing

// Lights // 

#define LED_PROXIMITY 1 

#define LED_TIMER 2 

// DISTANCE DEFINITIONS // 

#define DISTANCE_FOR_PROXIMITY_LED 15



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
  
}


void loop() // do the following things forever


{

  delay(100); // wait for this number of milliseconds

  int DISTANCE_IN_CM = sonar.ping_cm(); // read the sonar sensor, using a variable

  Serial.print("Ping: "); //print “Ping:" on the computer display

  Serial.print(DISTANCE_IN_CM); //print the value of the variable next

  Serial.println("cm"); //print "cm" after that, then go to next line
  
  distanceCheck(DISTANCE_FOR_PROXIMITY_LED);

}




//INPUT THE DURATION IN SECONDS//
void timer(int duration){
 int counter = 0;
  
  for(counter = 0 ; counter < duration ; counter++){
  digitalWrite(LED_TIMER, HIGH); // Turns on the LED 
  delay(200);
  digitalWrite(LED_TIMER,LOW); // Turns off the LED for a flicker effect 
  delay(800);
  distanceCheck(DISTANCE_FOR_PROXIMITY_LED); // Checks if it's within the proximity distance
 }
 
  void distanceCheck(int distance){
      
    if(DISTANCE_IN_CM >= distance){ // if the sonar is withing 20 cm, turn on PROXIMITY LED
    digitalWrite(LED_PROXIMITY, HIGH); // turn on led when it is in within proximity
  }
  else{
    digitalWrite(LED_PROXIMITY,LOW); // turn off the led when it's not within proximity
  }
}

  
}
