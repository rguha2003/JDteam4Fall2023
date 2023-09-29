#include <PS2X_lib.h>
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
#define CranePin 9
//Limit Switches
#define LIM1 10
#define LIM2 11
#define LIM3 12
#define LIM4 13
//MotorSpeeds(will change as testing progresses)
#define CraneUpSpeed 120
#define CraneDownSpeed 70
#define GripperForward 120
#define GripperBack 70

   
  const int Lim1 = LIM1;
  const int Lim2 = LIM2;
  const int Lim3 = LIM3;
  const int Lim4 = LIM4;

PS2X ps2x;

void setup() {

 ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);

  DriveL.attach(DriveLpin);
  DriveR.attach(DriveRpin);
  Gripper.attach(GripperPin);
  Crane.attach(CranePin);

  pinMode(Lim1, INPUT_PULLUP);
  pinMode(Lim2, INPUT_PULLUP);
  pinMode(Lim3, INPUT_PULLUP);
  pinMode(Lim4, INPUT_PULLUP);

  Serial.begin(9600);
  
}

void loop() {
  // Read the joystick values
 ps2x.read_gamepad();

  int Lim1State = digitalRead(Lim1);
  int Lim2State = digitalRead(Lim2);
  int Lim3State = digitalRead(Lim3);
  int Lim4State = digitalRead(Lim4);

  // Get the values of the left analog stick (X and Y)
  int leftStickX = ps2x.Analog(PSS_LX);
  int leftStickY = ps2x.Analog(PSS_LY);

  // Get the values of the right analog stick (X)
  int rightStickX = ps2x.Analog(PSS_RX);
  int rightStickY = ps2x.Analog(PSS_RY);

  // Map the joystick values to motor speeds
  int motorSpeedLeft = map(leftStickY, 0, 255, 0, 180);
  int motorSpeedRight = map(rightStickX, 0, 255, 0, 180);

  // gripper int values Defined
  int GripIn = ps2x.Button(PSB_R1);
  int GripOut = ps2x.Button(PSB_R2);

  //Crane int Values Defined
  int CraneUp = ps2x.Button(PSB_L1);
  int CraneDown = ps2x.Button(PSB_L2);

//Gripper Controls
  if (GripIn == 1 && GripOut == 0) {
    
    if(Lim1State == LOW){
      Gripper.write(90);
    }
    else {
    Gripper.write(GripperForward);
    Serial.println("Gripper moving forward");
    }
  }
  else if(GripOut == 1 && GripIn == 0){
   
    if(Lim2State == LOW){
      Gripper.write(90);
    }
    else{
    Gripper.write(GripperBack);
    Serial.println("Gripper moving back");
    }
  }
  else{
    Gripper.write(90);
  };

  // Monitoring Window
 Serial.print("Left Motor Speed: ");
 Serial.println(motorSpeedLeft);
 Serial.print("Right Motor Speed: ");
 Serial.println( motorSpeedRight);
 //Driving Motors according to Joystick values
 DriveL.write(motorSpeedLeft);
 DriveR.write(motorSpeedRight);

  //Crane Contols
 if (CraneUp == 1 && CraneDown == 0){
  if(Lim3State == LOW){
    Crane.write(90);
  }
  else{
  Crane.write(CraneUpSpeed);
  Serial.println("Crane going up");
  }
 }
 else if(CraneDown == 1 && CraneUp == 0){
  if(Lim4State == LOW){
    Crane.write(90);
  }
  else{
  Crane.write(CraneDownSpeed);
  Serial.println("Crane going Down");
  }
 }
 else{
  Crane.write(90);

 };
}




