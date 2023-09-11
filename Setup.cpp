#include <Servo.h>

#include <PsxControllerBitBang.h>
#include <PsxControllerHwSpi.h>
#include <PsxNewLib.h>

//iclusion of setup.h file
#include "Setup.h"

void setupMotors() {
  //rest of void setup
  DriveM1.attach(6);
  DriveM2.attach(9);
  CraneM.attach(10);
  GripperM.attach(11);

  digitalWrite(DriveM1,0);
  digitalWrite(DriveM2,0);
  digitalWrite(CraneM,0);
  digitalWrite(GripperM,0);
}



