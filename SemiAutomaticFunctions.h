#ifndef SEMI_AUTOMATIC_FUNCTIONS_H
#define SEMI_AUTOMATIC_FUNCTIONS_H
#include <Servo.h>



//establishing Servos
Servo DriveL;
Servo DriveR;
Servo Gripper;
Servo Crane;

// Arduino Pins
#define PS2_DAT 2
#define PS2_CMD 3
#define PS2_SEL 4
#define PS2_CLK 5
//Motor Pins
#define DriveLpin 6
#define DriveRpin 7
#define GripperPin 8
//Crane motor driver no longer needs library
#define CraneDirectionPin 9
#define CraneSpeedPin A0
//Limit Switches
#define LIM1 10
#define LIM2 11
//#define LIM3 12
//#define LIM4 13
//MotorSpeeds(will change as testing progresses)
#define CraneUpSpeed 120
#define CraneDownSpeed 70
#define GripperForward 120
#define GripperBack 70
bool direction = true;

   
  const int Lim1 = LIM1;
  const int Lim2 = LIM2;

bool craneMoving;

void runServo(Servo servo, unsigned long time, int speed){
unsigned long startTime = millis();

while (millis() - startTime <= time){
  servo.write(speed);
}
servo.write(90);

}

void runCrane(unsigned long cTime, bool direction){
  unsigned long startTime = millis();

while (millis() - startTime <= cTime){
  if(direction){
     Serial.println("Crane going up");
    digitalWrite(CraneDirectionPin, HIGH);
    analogWrite(CraneSpeedPin, CraneUpSpeed);
  }
  else{
    Serial.println("Crane going down");
    digitalWrite(CraneDirectionPin, LOW);
    analogWrite(CraneSpeedPin, CraneDownSpeed);
  }
}
}

void craneGripperSemiUp(){
  runCrane(2000, direction);
  delay(2000);
  runServo(Gripper, 2000, GripperForward);
  delay(1000);
}
#endif