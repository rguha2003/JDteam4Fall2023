#include "Setup.h"

#include <Servo.h>

#include <PsxControllerBitBang.h>
#include <PsxControllerHwSpi.h>
#include <PsxNewLib.h>

//Nathan's code
void setup() {
  
  serial.begin(115200);

  //Outputs
 pinMode(DriveM1,OUTPUT);
 pinMode(DriveM2,OUTPUT);
 pinMode(CraneM,OUTPUT);
 pinMode(GripperM,OUTPUT);

 //function defined in setup its all the .attach and digitalwrites 
setupMotors();

}

void loop() {
  // put your main code here, to run repeatedly:

}
