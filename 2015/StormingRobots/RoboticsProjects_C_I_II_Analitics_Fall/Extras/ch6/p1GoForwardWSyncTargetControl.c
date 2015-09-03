#define  LM         motorC
#define  RM         motorB
#define  SYNC_RM    synchBC  // B as the master motor, A as the secondary motor
#define  DIA        5.6
#define  GEAR_RATIO 1/1     // motor gear = 24, tire gear= 40
float degPerCM = 360.0*GEAR_RATIO/(PI*DIA);

void goForward(float cm)
{
  float target;

  target = cm * degPerCM; // convert cm to encoder value with gear ratio 1:1

  nxtDisplayTextLine(0, "      Left  Right");
  nxtDisplayTextLine(1, "      ====  ====");
  nxtDisplayTextLine(4, "Actual:%4d  %4d", (int)target, (int)target);

  nMotorEncoder[LM] = nMotorEncoder[RM]=0; //must reset
  nSyncedMotors= SYNC_RM;               //active motor feedback control, and
                                        //    determine which is the master motor
  nSyncedTurnRatio=100;                 //secondary motor's power level is 100% of the master motor's
  nMotorEncoderTarget[RM]=target;       //set the target encoder. Note that motor
                                        //    is not running yet
  motor[RM]=100;                         //start the motor at power 60
  // while(nMotorEncoder[RM]<target-5) use this method as there used to be a bug in the motor state
  while (nMotorRunState[RM] != runStateIdle)
  {
    wait1Msec(10);                      //small delay to avoid over-hauling the cpu
  }
  wait1Msec(1000);                      // give the motor feedback control stop the motor
  nSyncedMotors= synchNone;             //deactive motor feedback control
}

task main()
{
    goForward(100);
    wait1Msec(2000); // wait for complete stop
    nxtDisplayTextLine(4, "Actual:%4d  %4d", nMotorEncoder[RM],nMotorEncoder[LM]);
    wait1Msec(3000);
}
