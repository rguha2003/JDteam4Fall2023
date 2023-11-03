#include "SemiAutomaticFunctions.h"
#include <PS2X_lib.h>
#include <Servo.h>



PS2X ps2x;


void setup() {


 ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);

  DriveL.attach(DriveLpin);
  DriveR.attach(DriveRpin);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Gripper.attach(GripperPin);
  pinMode(CraneDirectionPin, OUTPUT);
  pinMode(CraneSpeedPin, OUTPUT);
  pinMode(Lim1, INPUT_PULLUP);
  pinMode(Lim2, INPUT_PULLUP);

  craneMoving = false;

  Crane.write(95);

  Serial.begin(9600);
  
}

void loop() {
  // Read the joystick values
 ps2x.read_gamepad();

  int Lim1State = digitalRead(Lim1);
  int Lim2State = digitalRead(Lim2);

  int leftStickY = ps2x.Analog(PSS_LY);
  int rightStickY = ps2x.Analog(PSS_RY);

  // Map the joystick values to motor speeds
  int motorSpeedLeft = mapJoystickToServoL(leftStickY);
  int motorSpeedRight = mapJoystickToServoR(rightStickY);
  // gripper int values Defined
  int GripIn = ps2x.Button(PSB_PAD_LEFT);
  int GripOut = ps2x.Button(PSB_PAD_RIGHT);

  //Crane int Values Defined
  int CraneUp = ps2x.Button(PSB_L2);
  int CraneDown = ps2x.Button(PSB_L1);//---------------------------------------------temporary change

//Gripper Controls
  if (GripIn == 1 && GripOut == 0) {
    Gripper.write(GripperForward);
  }
  else if(GripOut == 1 && GripIn == 0){
    Gripper.write(GripperBack);
  }
  else{
    Gripper.write(gripperDead);
  };

int joystickValRight = rightStickY;
int joystickValLeft = leftStickY;



if(joystickValLeft >= deadZoneMin & joystickValLeft <= deadZoneMax ){
  DriveL.write(driveLDead);
}
else{
  DriveL.write(motorSpeedLeft);
 Serial.print("Left Motor Speed: ");
 Serial.println(motorSpeedLeft);
};
if(joystickValRight >= deadZoneMin & joystickValRight <= deadZoneMax){
  DriveR.write(driveRDead);
}
else{
 DriveR.write(motorSpeedRight);
 Serial.print("Right Motor Speed: ");
 Serial.println( motorSpeedRight);
}

  //Crane Contols-------------------------------------------------------
 if(CraneDown == 0 && CraneUp == 0){
 
  analogWrite(CraneSpeedPin, 0);
  craneMoving = false;
 
 }
 else if(CraneDown == 0 && CraneUp == 1){
  Serial.println("Crane going up");
  digitalWrite(CraneDirectionPin, LOW);
  analogWrite(CraneSpeedPin, CraneUpSpeed);
  craneMoving = true;
  
 }
 else if(CraneDown == 1 && CraneUp == 0){
  Serial.println("Crane going Down");
  digitalWrite(CraneSpeedPin, HIGH);
  analogWrite(CraneDirectionPin, CraneDownSpeed);
  craneMoving = true;
 }



 //if statement to control if crane is moving then shut off everything else
 
 if(craneMoving == true){
  Gripper.write(95);
  DriveL.write(95);
  DriveR.write(95);
 }
}


