
void serialMode() {
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
