


#include <Servo.h>

#define N1 6
#define N2 7
Servo Drive;


void setup() {
Drive.attach(7);


}

void loop() {
Drive.write(90);
delay(500);
Drive.write(96);
delay(500);
Drive.write(95);
delay(500);
  }



