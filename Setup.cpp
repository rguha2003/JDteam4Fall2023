#include <Servo.h>

#include <PsxControllerBitBang.h>
#include <PsxControllerHwSpi.h>
#include <PsxNewLib.h>

//iclusion of setup.h file
#include "Setup.h"

void setupMotors() {
  //rest of void setup to attach servos and set state
  DriveM1.attach(6);
  DriveM2.attach(9);
  CraneM.attach(10);
  GripperM.attach(11);

  digitalWrite(DriveM1,0);
  digitalWrite(DriveM2,0);
  digitalWrite(CraneM,0);
  digitalWrite(GripperM,0);
}

//ERROR CHECK ----------
void errorCheck(){
  if(error == 0){
    Serial.println("Found Controller, configured successful");
  }
   
  else if(error == 1)
    Serial.println("No controller found, check wiring or reset the Arduino");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands");
 
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it.");
 
 //Error in code might happen here, idk if this should be a seperate function---------------------
 type = PsxNewLib.readType();
  switch(type) {
 
  case 0:
    break;
  case 1:
    break;
  case 2:
    break;
  }
}
 




