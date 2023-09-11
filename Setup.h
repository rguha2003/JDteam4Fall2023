#include <Servo.h>

#include <PsxControllerBitBang.h>
#include <PsxControllerHwSpi.h>
#include <PsxNewLib.h>

#define DriveM1 6
#define DriveM2 9

#define CraneM 10
#define GripperM 11

int rightstickRY = (PsxNewLib.Analog(PSS_RY));
int rightstickRX = (PsxNewLib.Analog(PSS_RX));
int leftstickLX = (PsxNewLib.Analog(PSS_LX));
int leftstickLY = (PsxNewLib.Analog(PSS_LY));
