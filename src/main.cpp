#include <Arduino.h>
#include <BasicStepperDriver.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 5

// Microstepping muss extern geschaltet und mit der angegebenen grösse übereinstimmen
#define MICROSTEPS 8

// All the wires needed for full functionality
#define DIR 2
#define STEP 3

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
  stepper.begin(RPM, MICROSTEPS);
  Serial.begin(9600);
}

void loop() {
  // Eine Umdrehung im Uhrzeigersinn
  Serial.println("Die Rotation beginn...");
  stepper.rotate(360);
  Serial.println("Die Rotation ist fertig...");

  Serial.println("Es rotiert wieder!");
  stepper.startRotate(360);
  Serial.println("Dies sollte vor dem Ende der Rotation angezeigt werden!");

  delay(2000);

  // Vier mal eine viertel Umdrehung zurück
  //for (int i = 0; i < 5; i++) {
  //  stepper.rotate(-90);
  //  delay(1000);
  //}
  
    
}