/************************************************************************

  Speed
  >> 0=full speed, 1-255 slower to faster

*************************************************************************/

#include <EEPROM.h>
#include "UF_uArm.h"

int s = 0, h = 0, r = 0;
int armState = true;

int  heightTemp  = 0, stretchTemp = 0, rotationTemp = 0, handRotTemp = 0;
char stateMachine = 0, counter = 0;
char dataBuf[9] = {0};

UF_uArm uarm;           // initialize the uArm library

void setup()
{

  analogReference(EXTERNAL);
  Serial.begin(9600);

  uarm.init();          // initialize the uArm position
  delay(500);

  /*uarm.setServoSpeed(SERVO_R, 50);  // 0=full speed, 1-255 slower to faster
    uarm.setServoSpeed(SERVO_L, 50);  // 0=full speed, 1-255 slower to faster
    uarm.setServoSpeed(SERVO_ROT, 50); // 0=full speed, 1-255 slower to faster
  */

  Serial.println("uArm : Begin");
  //uarm.setPosition(0, 0, 0, 0);
  delay(1000);
  uarm.alert(2, 50, 100);
  uarm.calibration();
}


void loop() {

  uarm.recordingMode(50);

  if (!digitalRead(LIMIT_SW)) {
    if (armState == true) {
      uarm.detachArm();
      armState = false;
    } else {
      uarm.attachArm();
      armState = true;
    }
    uarm.alert(3, 200, 200);
  }
}


void m() {

  if (!digitalRead(BTN_D4)) {
    uarm.alert(2, 50, 100);
    delay(500);
    /*s += 5;
      uarm.setPosition(s, h, r, 0);
      printArmData(s, h , r);
      delay(100);*/

  } else if (!digitalRead(BTN_D7)) {
    uarm.alert(2, 50, 100);
    delay(500);
    /*h += 5;
      uarm.setPosition(s, h, r, 0);
      printArmData(s, h , r);
      delay(100);*/

  } else if (!digitalRead(LIMIT_SW)) {
    if (armState == true) {
      uarm.detachArm();
      armState = false;
    } else {
      uarm.attachArm();
      armState = true;
    }
    uarm.alert(3, 200, 200);
  }

  delay(50);
}


void printArmData(int s, int h, int r) {

  Serial.print(" stretch: ");
  Serial.print(s);
  Serial.print(" height: ");
  Serial.print(h);
  Serial.print(" rotation: ");
  Serial.println(r);
}

void readVoltages() {

  Serial.print(" Left: ");
  Serial.print(analogRead(0));
  Serial.print(" Right: ");
  Serial.print(analogRead(1));
  Serial.print(" Rotation: ");
  Serial.println(analogRead(2));


}


