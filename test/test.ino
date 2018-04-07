/************************************************************************

  Speed
  >> 0=full speed, 1-255 slower to faster

*************************************************************************/

#include <EEPROM.h>
#include "UF_uArm.h"

UF_uArm uarm;           // initialize the uArm library

void setup()
{
  uarm.init();          // initialize the uArm position
  detachServo();

  uarm.rawWrite(SERVO_ROT, 20, 90);
  uarm.rawWrite(SERVO_L, 20, 90);
  uarm.rawWrite(SERVO_R, 20, 90);
}

void loop()
{
  //uarm.calibration();   // if corrected, you can remove it
}

void detachServo()
{
  uarm.detachServo(SERVO_L);
  uarm.detachServo(SERVO_R);
  uarm.detachServo(SERVO_ROT);
  uarm.detachServo(SERVO_HAND_ROT);
  uarm.detachServo(SERVO_HAND);
}
