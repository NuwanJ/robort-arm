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

  /*uarm.rawWrite(SERVO_ROT, 20, 90);
    uarm.rawWrite(SERVO_L, 20, 90);
    uarm.rawWrite(SERVO_R, 20, 90);
  */
  //detachServo();
  /*uarm.rawWrite(SERVO_ROT, 20, 0);
    uarm.rawWrite(SERVO_ROT, 20, 180);
  */
}

void loop()
{

  if (Serial.available())
  {
    byte rxBuf = Serial.read();
    if (stateMachine == 0)
    {
      stateMachine = rxBuf == 0xFF ? 1 : 0;
    }
    else if (stateMachine == 1)
    {
      stateMachine = rxBuf == 0xAA ? 2 : 0;
    }
    else if (stateMachine == 2)
    {
      dataBuf[counter++] = rxBuf;
      if (counter > 8) // receive 9 byte data
      {
        stateMachine = 0;
        counter = 0;
        *((char *)(&rotationTemp)  )  = dataBuf[1]; // recevive 1byte
        *((char *)(&rotationTemp) + 1)  = dataBuf[0];
        *((char *)(&stretchTemp )  )  = dataBuf[3];
        *((char *)(&stretchTemp ) + 1)  = dataBuf[2];
        *((char *)(&heightTemp  )  )  = dataBuf[5];
        *((char *)(&heightTemp  ) + 1)  = dataBuf[4];
        *((char *)(&handRotTemp )  )  = dataBuf[7];
        *((char *)(&handRotTemp ) + 1)  = dataBuf[6];
        uarm.setPosition(stretchTemp, heightTemp, rotationTemp, handRotTemp);
        /* pump action, Valve Stop. */
        if (dataBuf[8] & CATCH)   uarm.gripperCatch();
        /* pump stop, Valve action.
           Note: The air relief valve can not work for a long time,
           should be less than ten minutes. */
        if (dataBuf[8] & RELEASE) uarm.gripperRelease();
      }
    }
  }
  /*Serial.println(">> Loop");
    uarm.rawWrite(SERVO_L, 20, 70);
    delay(1000);
    uarm.rawWrite(SERVO_L, 20, 110);
    delay(1000);*/
  //uarm.calibration();   // if corrected, you can remove it


  /*motion();
    motionReturn();*/

}

void detachServo()
{
  uarm.detachServo(SERVO_L);
  uarm.detachServo(SERVO_R);
  uarm.detachServo(SERVO_ROT);
  uarm.detachServo(SERVO_HAND_ROT);
  uarm.detachServo(SERVO_HAND);
}






void motion()
{
  uarm.setPosition(60, 0, 0, 0);    // stretch out
  delay(400);
  uarm.setPosition(60, -45, 0, 0);  // down
  uarm.gripperCatch();               // catch
  delay(400);
  uarm.setPosition(60, 0, 0, 0);    // up
  delay(400);
  uarm.setPosition(60, 0, 25, 0);   // rotate
  delay(400);
  uarm.setPosition(60, -45, 25, 0); // down
  delay(400);
  uarm.gripperRelease();             // release
  delay(100);
  uarm.setPosition(60, 0, 25, 0);   // up
  delay(400);
  uarm.setPosition(0, 0, 25, 0);
  delay(400);
  uarm.gripperDirectDetach();        // direct detach
  delay(500);
}

void motionReturn()
{
  uarm.setPosition(60, 0, 25, 0);    // stretch out
  delay(400);
  uarm.setPosition(60, -45, 25, 0);  // down
  uarm.gripperCatch();                // catch
  delay(400);
  uarm.setPosition(60, 0, 25, 0);    // up
  delay(400);
  uarm.setPosition(60, 0, 0, 0);     // rotate
  delay(400);
  uarm.setPosition(60, -45, 0, 0);   // down
  delay(400);
  uarm.gripperRelease();              // release
  delay(100);
  uarm.setPosition(60, 0, 0, 0);     // up
  delay(400);
  uarm.setPosition(0, 0, 0, 0);       // original position
  delay(400);
  uarm.gripperDirectDetach();         // direct detach
  delay(500);
}
