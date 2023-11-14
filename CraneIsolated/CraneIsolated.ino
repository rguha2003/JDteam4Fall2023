#include <Servo.h>
#include <PS2X_lib.h>


// Arduino Pins
#define PS2_DAT 2
#define PS2_CMD 3
#define PS2_SEL 4
#define PS2_CLK 5

//Crane motor driver no longer needs library
#define CraneDirectionPin 9  //IN1
#define CraneSpeedPin A0 //IN2

bool slowMode = false;

PS2X ps2x;

Servo DriveL;
Servo DriveR;

const float alpha = 0.2;  // Adjust as needed

float smoothedX = 0;
float smoothedY = 0;
//--------------------------------------------------------DRIVE FUNCTION--can be put in the SemiAuto----------------------------------------------------------------------------------

void driveFunction(int xVal, int yVal, int maxL, int maxR, int turnL, int turnR){

if(xVal < 145 & xVal > 90){
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
else{
  DriveL.write(94);
  DriveR.write(94);
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
}
//----------------------------------------------------------------------------------------------------------------------------------------

void setup() {
 ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, false);

  DriveL.attach(7);
  DriveR.attach(6);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);



  Serial.begin(9600);
}
void loop(){
ps2x.read_gamepad();

unsigned long debounceDelay = 100;  // Adjust as needed
unsigned long lastDebounceTime = 0;


//----------------------------------------------------------- Assuming joystickX and joystickY are your joystick readings
if (millis() - lastDebounceTime > debounceDelay) {
    // Process joystick input
int leftStickY = ps2x.Analog(PSS_RY);
int leftStickX = ps2x.Analog(PSS_RX);



//----------------------------------------------------------------Function gets called, put this in the loop-----------------------------------------------------
if(ps2x.ButtonPressed(PSB_R3)){
  slowMode =true;
}
else if(ps2x.ButtonReleased(PSB_R3)){
  slowMode = false;
}

 if(slowMode){
  
 driveFunction(leftStickX, leftStickY, 100, 90, 98, 90);
 }
else{
driveFunction(leftStickX, leftStickY, 120, 60, 120, 60);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 lastDebounceTime = millis();
}
}
