#define  LM         motorA
#define  RM         motorB
#define  SYNC_RM    synchBA  // B as the master motor, A as the secondary motor
#define  SYNC_LM    synchAB  // B as the master motor, A as the secondary motor

#define  DIA    5.6
#define  WBASE  17.5
#define  GEAR_RATIO 5/3     // motor gear = 24, tire gear= 40
float degPerCM = 360.0*GEAR_RATIO/(PI*DIA);
int kPwr = 50;

void leftTurn(int chassisTurnDeg)
{
  float target;

  target = (float)(chassisTurnDeg/360) * WBASE*PI*degPerCM; // convert cm to encoder value with gear ratio 1:1

  nxtDisplayTextLine(0, "      Left  Right");
  nxtDisplayTextLine(1, "      ====  ====");
  nxtDisplayTextLine(3, "Target:%4d  %4d", (int)-target, (int)target);

  nMotorEncoder[LM] = nMotorEncoder[RM]=0; //must reset
  nMotorEncoderTarget[RM] = target;
  nSyncedMotors= SYNC_RM;               //active motor feedback control, and
                                           //    determine which is the master motor

  nSyncedTurnRatio=-100;                    //secondary motor's power level is 100% of the master motor's
  motor[RM]=60;                         //start the motor at power 60

  while (nMotorRunState[RM] != runStateIdle)
  {
    wait1Msec(10);                      //small delay to avoid over-hauling the cpu
  }
  motor[RM] = 0;
  nSyncedMotors= synchNone;                //deactive motor feedback control
}


void rightTurn(int chassisTurnDeg)
{
  float target;

  target = (float)(chassisTurnDeg/360) * WBASE*PI*degPerCM; // convert cm to encoder value with gear ratio 1:1

  nxtDisplayTextLine(0, "      Left  Right");
  nxtDisplayTextLine(1, "      ====  ====");
  nxtDisplayTextLine(3, "Target:%4d  %4d", (int)-target, (int)target);

  nMotorEncoder[LM] = nMotorEncoder[RM]=0; //must reset
  nMotorEncoderTarget[RM] = target;
  nSyncedMotors= SYNC_LM;               //active motor feedback control, and
                                           //    determine which is the master motor

  nSyncedTurnRatio=-100;                    //secondary motor's power level is 100% of the master motor's
  motor[LM]=60;                         //start the motor at power 60

  while (nMotorRunState[LM] != runStateIdle)
  {
    wait1Msec(10);                      //small delay to avoid over-hauling the cpu
  }
  nSyncedMotors= synchNone;                //deactive motor feedback control
}

// cm :  the distance cm.   '+' == forward   '-' == backward
void goStraight(float cm)
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
  if (cm>0)
    motor[RM]=60;                         //start the motor at power 60
  else
    motor[RM]=-60;
    // while(nMotorEncoder[RM]<target-5) use this method as there used to be a bug in the motor state
  while (nMotorRunState[RM] != runStateIdle)
  {
    wait1Msec(10);                      //small delay to avoid over-hauling the cpu
  }
  wait1Msec(1000);                      // give the motor feedback control stop the motor
  nSyncedMotors= synchNone;             //deactive motor feedback control
}
