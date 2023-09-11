#include <Servo.h>

#include <PsxControllerBitBang.h>
#include <PsxControllerHwSpi.h>
#include <PsxNewLib.h>

#include "Setup.h"
#include "Drive.h"

void driveRobot() {
   if(error == 1)
  return;
  else {//DualShock Controller
PsxNewLib.read_gamepad(false, Vibrate); //Disabling the vibration of the controller


int rightstickRY = (PsxNewLib.Analog(PSS_RY));  //Right stick RY
int rightstickRX = (PsxNewLib.Analog(PSS_RX));  //Right stick RX
int leftstickLR = (PsxNewLib.Analog(PSS_LX));   //Left stick LX  (right/left turning)
int leftstickLL = (PsxNewLib.Analog(PSS_LY));
if (PsxNewLib.Button(leftstickLY<50))  //MOVE FORWARD
{
  digitalWrite(DriveM1,1);
  digitalWrite(DriveM2,1);
}
if (PsxNewLib.Button(leftstickLY>50))  //MOVE BACKWARDS
{
  digitalWrite(DriveM1,1);
  digitalWrite(DriveM2,1);
}
if (PsxNewLib.Button(rightstickRX<200))  //TURN LEFT
{
  digitalWrite(DriveM1,1);
  digitalWrite(DriveM2,0);
}
if (PsxNewLib.Button(rightstickRX>200))  //TURN RIGHT
{
  digitalWrite(DriveM1,0);
  digitalWrite(DriveM2,1);
}

}