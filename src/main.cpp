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
#define RunLED 10 // Tracking in progress
#define RewLED 11 // Rewind the Tracker

// Set the button pins
#define TrackBtn 5 // Start/Stop tracking
#define RewBtn 6 // Rewind the Tracker

// Set the safety swich pins
#define MaxOpen 13  // Barndoor mount reached max open point
#define MinOpen 14  // Mount is fully closed

#define interval 5000

//bool Toggle=LOW;
unsigned long prevMill = 0;

boolean isTracking=false;
boolean isRewinding=false;

int goTracking = 1;
int goRewind = 1;

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
  pinMode(TrackBtn,INPUT_PULLUP);
  pinMode(RewBtn,INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  
  
  // if (currentMillis - previousMillis >= interval) {
  //   previousMillis = currentMillis;
  //   if (Toggle) {
  //     Toggle = !Toggle;
  //     RunFwd();
  //   } else {
  //     Toggle = !Toggle;
  //     RunRew();
  //   }

  // }

  goTracking = digitalRead(TrackBtn);
  goRewind = digitalRead(RewBtn);

  if (goTracking==LOW){
    isTracking = !isTracking;
    RunFwd();
  }

  if (goRewind==LOW){
    isRewinding = !isRewinding;
    isTracking = false;
    RunRew();
    AccStep.runSpeed();
  }

  if (isTracking) {
    AccStep.runSpeed();
  }
}

