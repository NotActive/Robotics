#define  LM         motorC
#define  RM         motorB
#define  SYNC_RM    synchBC  // B as the master motor, C as the secondary motor

#define  DIA    5.6
#define  WBASE  17.5
#define  GEAR_RATIO 1/1     // motor gear = 24, tire gear= 40
float degPerCM = 360.0*GEAR_RATIO/(PI*DIA);

void leftTurn(int chassisTurnDeg)
{
  float target;

  target = (float)(chassisTurnDeg/360) * WBASE*PI*degPerCM; // convert cm to encoder value with gear ratio 1:1

  displayTextLine(0, "      Left  Right");
  displayTextLine(1, "      ====  ====");
  displayTextLine(3, "Target:%4d  %4d", (int)-target, (int)target);

  nMotorEncoder[LM] = nMotorEncoder[RM]=0; //must reset
  nSyncedMotors= SYNC_RM;               //active motor feedback control, and
                                           //    determine which is the master motor
  nSyncedTurnRatio=-100;                    //secondary motor's power level is 100% of the master motor's
  motor[RM]=60;                         //start the motor at power 60

  while (nMotorEncoder[RM]<target)
  {
    wait1Msec(10);                      //small delay to avoid over-hauling the cpu
  }
  motor[RM] = 0;
  nSyncedMotors= synchNone;                //deactive motor feedback control
}

task main()
{
    leftTurn(90);
    wait1Msec(2000); // wait for complete stop
    nxtDisplayTextLine(4, "Actual:%4d  %4d", nMotorEncoder[LM],nMotorEncoder[RM]);
    wait1Msec(3000);
}
