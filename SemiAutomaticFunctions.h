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
#define DriveLpin 7
#define DriveRpin 6
#define GripperPin 8
//Crane motor driver no longer needs library
#define CraneDirectionPin 9  //IN1
#define CraneSpeedPin 13 //IN2
#define IN1 9 //Semi-permanent
#define IN2 13
//Limit Switches
#define LIM1 10
#define LIM2 11
//#define LIM3 12
//#define LIM4 13
//MotorSpeeds(will change as testing progresses)
#define CraneUpSpeed 128
#define CraneDownSpeed 128
#define GripperForward 120
#define GripperBack 70
bool direction = true;
   
const int Lim1 = LIM1;
const int Lim2 = LIM2;
int deadZoneMin = 80;
int deadZoneMax = 100;

 int gripperDead = 95;
 int craneDead = 0;
 int driveLDead = 90;
 int driveRDead = 94;

bool craneMoving;
bool craneMovingDown;
bool craneMovingUp;

int mapJoystickToServoL(int leftStickY) {
 
  // Calculate the mapped value using a quadratic function
  int mappedValue = 
  0.7200*leftStickY+3;
  return mappedValue;
};
int mapJoystickToServoR(int rightStickY) {
  // Define the mapping parameters
  int minInput = 0;      // Minimum joystick value
  int maxInput = 255;    // Maximum joystick value
  int minOutput = 180;   // Minimum servo speed
  int maxOutput = 0;    // Maximum servo speed

  int OppStick = maxInput - rightStickY;

    // Calculate the mapped value using a quadratic function
  int mappedValue = 
  0.7200*(OppStick)+3;
  return mappedValue;
}

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