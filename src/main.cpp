#include <Arduino.h>
#include <AccelStepper.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define TrackRPM 5 // RPM for Tracking
#define RewRPM 20 // RPM for Rewind

// Microstepping muss extern geschaltet und mit der angegebenen grösse übereinstimmen
#define MICROSTEPS 8

// All the wires needed for full functionality
#define DIR 2
#define STEP 3

////////////////////////////////////////////
// ATTENTION pin numbering not definitive //
////////////////////////////////////////////

// Set the LED pins for operation mode
#define TrkLED 10 // Tracking in progress
#define RewLED 11 // Rewind the Tracker

// Set the button pins
#define TrkBtn 5 // Start/Stop tracking
#define RewBtn 6 // Rewind the Tracker

// Set the safety swich pins NOT IMPLEMENTED YET
#define MaxOpen 13  // Barndoor mount reached max open point
#define MinOpen 14  // Mount is fully closed

// Define the run varables
boolean isTracking = false;
boolean isRewinding = false;

// Define the run check variables
boolean goTracking = true;
boolean goRewind = true;
boolean lastGoRewind = true;

// 2-wire basic config, microstepping is hardwired on the driver
AccelStepper AccStep = AccelStepper(1,STEP,DIR);

void RunFwd(){
  Serial.println("Jetzt gehts vorwärts");
  delay(500);
  AccStep.setSpeed(100);
}

void RunRew(){
  Serial.println("Jetzt gehts rückwärts");
  delay(500);
  AccStep.setSpeed(-500);
}

void setup() {
  AccStep.setMaxSpeed(2000);
  //AccStep.setAcceleration(20);

  // Setting button pins
  pinMode(TrkBtn,INPUT_PULLUP);
  pinMode(RewBtn,INPUT_PULLUP);
  
  // Setting LED pins
  pinMode(TrkLED,OUTPUT);
  pinMode(RewLED,OUTPUT);

  // Setting initial LED states
  digitalWrite(TrkLED,LOW);
  digitalWrite(RewLED,LOW);

  Serial.begin(9600);
}

void loop() {
  // Set state change check for rewinding
  lastGoRewind = goRewind;

  // Read the button states
  goTracking = digitalRead(TrkBtn);
  goRewind = digitalRead(RewBtn);

  // Check tracking button
  if (goTracking == LOW and !isRewinding){
    // Toggle run variable for tracking
    isTracking = !isTracking;
    
    // Toggle the tracking LED
    digitalWrite(TrkLED, !digitalRead(TrkLED));
    Serial.println("TrkLED ist: "+String(digitalRead(TrkLED)));
    RunFwd();
  }

  if (goRewind != lastGoRewind){
    // Toggle run variable for rewinding
    isRewinding = !isRewinding;
    isTracking = false;

    // Toggle rewind LED and reset tracking LED
    digitalWrite(RewLED, !digitalRead(RewLED));
    digitalWrite(TrkLED, LOW);
    Serial.println("RewLED ist: "+String(digitalRead(RewLED)));
    Serial.println("TrkLED ist: "+String(digitalRead(TrkLED)));
    RunRew();
  }

  if (isTracking or isRewinding) {
    AccStep.runSpeed();
  }
}

