#ifndef SEMI_AUTOMATIC_FUNCTIONS_H
#define SEMI_AUTOMATIC_FUNCTIONS_H
#include <Servo.h>



//establishing Servos
Servo DriveL;
Servo DriveR;
Servo Gripper;
Servo Crane;

//Arduino Pins
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
#define CraneSpeedPin A0 //IN2

#define IN1 11 //Semi-permanent
#define IN2 12
//Limit Switches
#define LIM1 9
#define LIM2 10
//#define LIM3 12
//#define LIM4 13
//MotorSpeeds(will change as testing progresses)
#define CraneUpSpeed 128
#define CraneDownSpeed 128
#define GripperForward 120
#define GripperBack 70
bool direction = true;
bool slowMode = false;
   
const int Lim1 = LIM1;
const int Lim2 = LIM2;
int deadZoneMin = 88;
int deadZoneMax = 89;

 int gripperDead = 95;
 int craneDead = 0;
 int driveLDead = 90;
 int driveRDead = 94;

//--------------------------------------------------------------Crane Stuff ------------------------------------------------
const int numReadings = 2;  // Adjust this value based on your requirements

int xReadings[numReadings];
int yReadings[numReadings];
int index = 0;

void initReadings() {
    for (int i = 0; i < numReadings; ++i) {
        xReadings[i] = 128;
        yReadings[i] = 128;
    }
}

int smoothInput(int* readings, int inputValue) {
    int total = 0;

    // Shift the readings to make room for the new value
    for (int i = numReadings - 1; i > 0; --i) {
        readings[i] = readings[i - 1];
        total += readings[i];
    }

    // Add the new value
    readings[0] = inputValue;
    total += inputValue;

    // Calculate the average
    return total / numReadings;
}
void driveFunction(int xVal, int yVal, int maxL, int maxR, int turnL, int turnR){

    int smoothedX = smoothInput(xReadings, xVal);
    int smoothedY = smoothInput(yReadings, yVal);
    
    int neutralZone = 2;  // Adjust this value based on your joystick's sensitivity
    int releaseDelay = 50;

    delay(releaseDelay);

    // Check if joystick is in the neutral position
    if (abs(smoothedX - 128) < neutralZone && abs(smoothedY - 128) < neutralZone) {
        // Joystick is in the neutral position, stop the motors
        DriveL.write(94);
        DriveR.write(94);
        delay(10);
    } 
else {
if(xVal < 145 && xVal > 90){
if(yVal > 130){
  DriveL.write(maxL);
  DriveR.write(maxR);
  delay(10);
}
else if(yVal < 126){
  DriveL.write(maxR);
  DriveR.write(maxL);
  delay(10);
}

}

else if(xVal >= 145){
  DriveL.write(turnR);
  DriveR.write(turnR);
  //Serial.println(leftStickX);
  delay(10);
}
else if(xVal <= 90){
    DriveL.write(turnL);
  DriveR.write(turnL);
  //Serial.println(leftStickX);
  delay(10);
}
}}

//----------------------------------------------------------------Semi-----------------------------------------------------

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
    digitalWrite(CraneDirectionPin, HIGH);
    analogWrite(CraneSpeedPin, CraneUpSpeed);
  }
  else{

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