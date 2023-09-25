#include <PS2X_lib.h>
#include <Servo.h>
Servo DriveL;
Servo DriveR;
Servo Gripper;
Servo Crane;
// Define the data pin and clock pin and Servos
#define PS2_DAT 2
#define PS2_CLK 3
#define CraneUpSpeed 120
#define CraneDownSpeed 70
#define GripperForward 120
#define GripperBack 70


PS2X ps2x;

void setup() {
  // Motor control pins
    // Initialize the PS2 controller
 ps2x.config_gamepad(PS2_CLK, PS2_DAT, false, false);

  DriveL.attach(9);  // Motor 1 pin A
  DriveR.attach(10); // Motor 1 pin B
  Gripper.attach(5);  // Motor 2 pin A
  Crane.attach(6);  // Motor 2 pin B



  // Set motor control pins as outputs
  //pinMode(DriveL, OUTPUT);
  //pinMode(DriveR, OUTPUT);
  //pinMode(Gripper, OUTPUT);
  //pinMode(Crane, OUTPUT);
  
  Serial.begin(9600);
  

}

void loop() {
  // Read the joystick values
  ps2x.read_gamepad();

  // Get the values of the left analog stick (X and Y)
  int leftStickX = ps2x.Analog(PSS_LX);
  int leftStickY = ps2x.Analog(PSS_LY);

  // Get the values of the right analog stick (X)
  int rightStickX = ps2x.Analog(PSS_RX);
  int rightStickY = ps2x.Analog(PSS_RY);

  // Map the joystick values to motor speeds
  int motorSpeedLeft = map(leftStickY, 0, 255, 0, 180);//Might be in reverse?
  int motorSpeedRight = map(rightStickX, 0, 255, 0, 180);//same thing?

  // gripper int values Defined
  int GripIn = ps2x.Button(PSB_R1);
  int GripOut = ps2x.Button(PSB_R2);

  //Crane int Values Defined
  int CraneUp = ps2x.Button(PSB_L1);
  int CraneDown = ps2x.Button(PSB_L2);

//Gripper Controls
  if (GripIn == 1 && GripOut == 0) {
    Gripper.write(GripperForward);
  
  }
  else if(GripOut == 1 && GripIn == 0){
    Gripper.write(GripperBack);

  }
  else{
    Gripper.write(90);

  };

  // Monitoring Window
 Serial.print("Left Motor Speed: ");
 Serial.print(motorSpeedLeft);
 Serial.print("Right Motor Speed: ");
 Serial.print( motorSpeedRight);
 
 DriveL.write(motorSpeedLeft);
 DriveR.write(motorSpeedRight);

  //Crane Contols
  
 if (CraneUp == 1 && CraneDown == 0){
  Crane.write(CraneUpSpeed);

 }
 else if(CraneDown == 1 && CraneUp == 0){
  Crane.write(CraneDownSpeed);

 }
 else{
  Crane.write(90);

 };
}




