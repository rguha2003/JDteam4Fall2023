
#include <PS2X_lib.h>
#include <Servo.h>



PS2X ps2x;


void setup() {

// Arduino Pins
#define PS2_DAT 2
#define PS2_CMD 3
#define PS2_SEL 4
#define PS2_CLK 5

 ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);



  Serial.begin(9600);
  
}

void loop(){
ps2x.read_gamepad();
int Read = ps2x.Analog(PSB_R2);

delay(800);
Serial.print(Read);

}