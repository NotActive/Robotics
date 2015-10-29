/*

Function is to encapsulate a group of instructions that perform a specific task. For example, making right
turns, or left turns, avoid obstacle avoidance, etc.

Here are the skeleton of some functions:

*/
#defien LM motorA
#define RM motorB
#define TIRE_DIA 5.6
#define WHEELBASE 13.5


/* Sample code for goiong straight forward
   you will have a whole set of instructions to convert cm to encoder degrees
*/
void goForward(int distInCm)
{
  float target=cm/(PI*TIRE_DIA/360);
  nMotorEncoder[LM]=0;
  nMotorEncoder[RM]=0;

  nSyncedMotors=synchAB; // turn on motor feedback control to keep two motors in sync
                         // have motorA as master motor, motorB as slave motor
  nSyncedTurnRatio=100;  // keep output of motorB 100% of output of motorA
  nMotorEncoderTarget[LM]=target;  // set the encoder target # ... does NOT start motor!
  motor[LM]=30;                    // must NOT modify the slave motor. Motor feedback control algorithm
                                   // takes over modifying the slave motor.
  while(nMotorEncoder[LM]<target)
  {
    wait1Msec(10);
  }
  wait1Msec(500);
  motor[LM]=0;                      // as you see, you only stop the master motor.
  wait1Msec(10);
  nSyncedMotors=synchNone;          // turn off the motor feedback control
                                    // must un-sync
}

void goBackward(int distInCm)
{
  ...
}


void turnLeft(int botTurnDegrees)
{
  /* formula:
  encoder degrees = (float)botTurnDegrees * WHEELBASE / TIRE_DIA;
  */
  ...
}


void turnRight(float degrees)
{
  ...
}


void init()
{
  //   initialize all your sensors types here...
}

task main()
{
  init();
  goForward(50);
  goBackward(50);
  turnRight(90);
  turnLeft(90);
}
