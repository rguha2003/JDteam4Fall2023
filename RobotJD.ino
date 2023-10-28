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

  Crane.write(90);

  Serial.begin(9600);
  
}

void loop() {
  // Read the joystick values
 ps2x.read_gamepad();

  int Lim1State = digitalRead(Lim1);
  int Lim2State = digitalRead(Lim2);

  // Get the values of the left analog stick (X and Y)
  //int leftStickX = ps2x.Analog(PSS_LX);
  int leftStickY = ps2x.Analog(PSS_LY);

  // Get the values of the right analog stick (X)
  //int rightStickX = ps2x.Analog(PSS_RX);
  int rightStickY = ps2x.Analog(PSS_RY);

  // Map the joystick values to motor speeds
  int motorSpeedLeft = map(leftStickY, 0, 255, 0, 180);
  int motorSpeedRight = map(rightStickY, 0, 255, 180, 0);

  // gripper int values Defined
  int GripIn = ps2x.Button(PSB_R1);
  int GripOut = ps2x.Button(PSB_R2);

  //Crane int Values Defined
  int CraneUp = ps2x.Button(PSB_L1);
  int CraneDown = ps2x.Button(PSB_L2);




//Gripper Controls
  if (GripIn == 1 && GripOut == 0) {
    
    Gripper.write(GripperForward);
    Serial.println("Gripper moving forward");
    
  }
  else if(GripOut == 1 && GripIn == 0){
   
    Gripper.write(GripperBack);
    Serial.println("Gripper moving back");
    
  }
  else{
    Gripper.write(90);
  };

  // Monitoring Window
int deadZoneMin = 80;
int deadZoneMax = 200;
int joystickValRight;
int joystickValLeft;
if(joystickValLeft >= deadZoneMin && joystickValLeft <= deadZoneMax ){
  DriveL.write(90);
}
else{
  DriveL.write(motorSpeedLeft);
 Serial.print("Left Motor Speed: ");
 Serial.println(motorSpeedLeft);
};
if(joystickValRight >= deadZoneMin && joystickValRight <= deadZoneMax){
  DriveR.write(90);
}
else{
 DriveR.write(motorSpeedRight);
 Serial.print("Right Motor Speed: ");
 Serial.println( motorSpeedRight);
}
  //Crane Contols-------------------------------------------------------
 if (CraneDown == 0 && CraneUp == 1){
  
  Serial.println("Crane going up");
  digitalWrite(CraneDirectionPin, HIGH);
  analogWrite(CraneSpeedPin, CraneUpSpeed);
  craneMoving = true;

  if(Lim2State == LOW){
    analogWrite(CraneSpeedPin, 0);
    craneMoving = false;
  }
 }
 else if(CraneDown == 1 && CraneUp == 0){
  Serial.println("Crane going Down");
  analogWrite(CraneSpeedPin, CraneDownSpeed);
  digitalWrite(CraneDirectionPin, LOW);
  craneMoving = true;

  if(Lim1State == LOW){
    analogWrite(CraneSpeedPin, 0);
    craneMoving = false;
  }

 }
 else{
  analogWrite(CraneSpeedPin, 0);
  craneMoving = false;
 }
 //if statement to control if crane is moving then shut off everything else
 if(craneMoving == true){
  Gripper.write(90);
  DriveL.write(90);
  DriveR.write(90);
 }
}





