#include <Servo.h>

#include <PsxControllerBitBang.h>
#include <PsxControllerHwSpi.h>
#include <PsxNewLib.h>

#ifndef SETUP_H
#define SETUP_H

#define DriveM1 6
#define DriveM2 9

#define CraneM 10
#define GripperM 11

PSXNEWLIB psxnewlib;
int i = 0;
int k = 0;
int d = 100;
int d1 = 200;
int error = 0;
byte type = 0;
byte vibrate = 0;

int rightstickRY = (PsxNewLib.Analog(PSS_RY));
int rightstickRX = (PsxNewLib.Analog(PSS_RX));
int leftstickLX = (PsxNewLib.Analog(PSS_LX));
int leftstickLY = (PsxNewLib.Analog(PSS_LY));

void setupMotors();
void errorCheck();

#endif
