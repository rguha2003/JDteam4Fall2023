#include "SemiAutomaticFunctions.h"
#include <PS2X_lib.h>
#include <Servo.h>



PS2X ps2x;


void setup() {

delay(300);
 ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);

  DriveL.attach(DriveLpin);
  DriveR.attach(DriveRpin);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Gripper.attach(GripperPin);
  pinMode(CraneDirectionPin, OUTPUT);
  pinMode(CraneSpeedPin, OUTPUT);
  //pinMode(Lim1, INPUT_PULLUP);
  //pinMode(Lim2, INPUT_PULLUP);


  Crane.write(95);

  Serial.begin(9600);
  
}

void loop() {
  // Read the joystick values

 ps2x.read_gamepad();
  //just in case switches aren't working, explicitly pull them high
  digitalWrite(9, HIGH); //Note that activation occurs when reading high, since pressing them disconnects them from ground
  digitalWrite(10, HIGH);

  int STBY = 12;
  int Lim1State = digitalRead(Lim1);//1 if pressed
  int Lim2State = digitalRead(Lim2);//1 if pressed
  int L1;
  int L2;
  int leftStickY = ps2x.Analog(PSS_LY);
  int rightStickY = ps2x.Analog(PSS_RY);

 
  // gripper int values Defined
  int GripIn = ps2x.Button(PSB_PAD_LEFT);
  int GripOut = ps2x.Button(PSB_PAD_RIGHT);

  //Crane int Values Defined
  int CraneUp = ps2x.Button(PSB_L1);
  int CraneDown = ps2x.Button(PSB_L2);//---------------------------------------------temporary change



  L1 = Lim1State;
  L2 = Lim2State;
//----------------------------------------------------------------------------------Gripper Controls
  if (GripIn == 1 && GripOut == 0) {
    Gripper.write(GripperForward);
  }
  else if(GripOut == 1 && GripIn == 0){
    Gripper.write(GripperBack);
  }
  else{
    Gripper.write(gripperDead);
  };
//------------------------------------------------------------------------------------------------Drive
unsigned long debounceDelay = 50;  // Adjust as needed
unsigned long lastDebounceTime = 0;


//----------------------------------------------------------- Assuming joystickX and joystickY are your joystick readings

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

//-----------------------------------------------------------------------------------------------------Newer Crane Functions

if ((ps2x.Button(PSB_L1) & ps2x.Button(PSB_L2)) | (!ps2x.Button(PSB_L1) & !ps2x.Button(PSB_L2)) ){ //holding forward and reverse —> don’t move
digitalWrite(IN2,0);
digitalWrite(IN1,0);
}
  else if (ps2x.Button(PSB_L1)){ 
  //holding forward and limit 1 not reached
  if (L2 ){
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2,HIGH);
    }
  else{
    digitalWrite(IN1, HIGH); 
    digitalWrite(IN2, LOW);
    }
  
  if(ps2x.ButtonReleased(PSB_L1)){
   digitalWrite(IN1, LOW); 
   digitalWrite(IN2, LOW);
    }
  }
else if (ps2x.Button(PSB_L2)){ 
  //holding forward and limit 1 not reached
  if (L1){
    digitalWrite(IN2, HIGH); 
    digitalWrite(IN1,HIGH);
    }
  else{
    digitalWrite(IN1, LOW); 
    digitalWrite(IN2, HIGH);
    }
  
  
  if(ps2x.ButtonReleased(PSB_L2)){
   digitalWrite(IN1, LOW); 
   digitalWrite(IN2, LOW);
    }
  }
  

}



