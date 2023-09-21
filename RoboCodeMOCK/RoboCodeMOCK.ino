#include <PS2X_lib.h>
#include <servo.h>
Servo DriveL
Servo DriveR
Servo Gripper
Servo Crane
// Define the data pin and clock pin and Servos
#define PS2_DAT 2
#define PS2_CLK 3
#define CraneUp 120
#define CraneDown 70
#define GripperForward 120
#define GripperBack 70


PS2X ps2x;

// Motor control pins
int DriveL = 9;  // Motor 1 pin A
int DriveR = 10; // Motor 1 pin B
int Gripper = 5;  // Motor 2 pin A
int Crane = 6;  // Motor 2 pin B

void setup() {
  // Initialize the PS2 controller
  ps2x.config_gamepad(PS2_CLK, PS2_DAT);

  // Set motor control pins as outputs
  pinMode(DriveL, OUTPUT);
  pinMode(DriveR, OUTPUT);
  pinMode(Gripper, OUTPUT);
  pinMode(Crane, OUTPUT);
  
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
  int rightStickY = ps2x.Anaolog(PSS_RY);

  // Map the joystick values to motor speeds
  int motorSpeedLeft = map(leftStickY, 0, 180, 0, 255);
  int motorSpeedRight = map(rightStickX, 0, 180, 0, 255);

  // gripper int values Defined
  int Gripin = ps2x.button(PSB_R1);
  int GripOut = ps2x.button(PSB_R2);

  //Crane int Values Defined
  int CraneUp = ps2x.button(PSB_L1);
  int CraneDown = ps2x.button(PSB_L2);

//Gripper Controls
  if Gripin == 1 && GripOut == 0 {
    Gripper.write(Gripin);
  
  }
  else(GripOut == 1 && GripIn == 0){
    Gripper.write(GripOut);

  }
  else(Gripin == 1 && GripOut == 1){
    Gripper.write(90);

  }

  // Monitoring Window
 serial.Write("Left Motor Speed: ", motorSpeedLeft, "Right Motor Speed: ", motorSpeedRight);
}Servo.Write = (motorSpeedLeft);
 Servo.Write = (motorSpeedRight);

  //Crane Contols
  
 if CraneUp == 1 && CraneDown == 0{
  Crane.write(CraneUp);

 }
 else(CraneDown == 1 && CraneUp == 0){
  Crane.write(CraneDown);

 }
 else(CraneUp == 1 && CraneDown == 1){
  Crane.write(90);

 }




