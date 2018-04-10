/************************************************************************

  Speed
  >> 0=full speed, 1-255 slower to faster

*************************************************************************/

#include <EEPROM.h>
#include "UF_uArm.h"

int  heightTemp  = 0, stretchTemp = 0, rotationTemp = 0, handRotTemp = 0;
char stateMachine = 0, counter = 0;
char dataBuf[9] = {0};

UF_uArm uarm;           // initialize the uArm library

void setup()
{
  Serial.begin(9600);

  uarm.init();          // initialize the uArm position
  //detachServo();

  uarm.setServoSpeed(SERVO_R, 50);  // 0=full speed, 1-255 slower to faster
  uarm.setServoSpeed(SERVO_L, 50);  // 0=full speed, 1-255 slower to faster
  uarm.setServoSpeed(SERVO_ROT, 50); // 0=full speed, 1-255 slower to faster
  delay(500);

  Serial.println("uArm : Begin");

  //uarm.rawWrite(SERVO_ROT, 20, 90);
  //uarm.rawWrite(SERVO_L, 20, 90);
  //uarm.rawWrite(SERVO_R, 20, 90);

  delay(3000);
  //detachServo();
  /*uarm.rawWrite(SERVO_ROT, 20, 0);
    uarm.rawWrite(SERVO_ROT, 20, 180);
  */
  Serial.println("uArm : 0,0,0,0");
  uarm.setPosition(0, 0, 0, 0);
}

int c = 0;

void loop()
{

  if (!digitalRead(BTN_D4)) {
    c += 5;
    uarm.setPosition(c, 0, 0, 0);

  } else if (!digitalRead(BTN_D7)) {
    detachServo();
  }

  delay(50);
}

void detachServo()
{
  detachArm();
}



