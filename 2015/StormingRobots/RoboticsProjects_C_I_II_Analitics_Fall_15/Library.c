#include "common.h"

float speed = 20.0;

#define resetMotorEncoder(m)  motor[m] = 0

void MotorEncoderReset()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}

#define setMotorTarget(m, enc, s)   { nMotorEncoderTarget[m] = enc; motor[m] = s;}

//void GoForward(float dist)
//{
//	MotorEncoderReset();
//	int total = dist * EncPerCm;
//	setMotorTarget(Lm, total, speed);
//	setMotorTarget(Rm, total, speed);
//	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
//		sleep(100);
//	wait1Msec(100);
//}

void goForward(float distInCm)
{
  float target=distInCm/(PI*Wdia/360);
  nMotorEncoder[Lm]=0;
  nMotorEncoder[Rm]=0;

  nSyncedMotors=synchBC; // turn on motor feedback control to keep two motors in sync
                         // have motorA as master motor, motorB as slave motor
  nSyncedTurnRatio=100;  // keep output of motorB 100% of output of motorA
  nMotorEncoderTarget[Lm]=target;  // set the encoder target # ... does NOT start motor!
  motor[Lm]=30;                    // must NOT modify the slave motor. Motor feedback control algorithm
                                   // takes over modifying the slave motor.
  while(nMotorEncoder[Lm]<target)
  {
    wait1Msec(10);
  }
  wait1Msec(500);
  motor[Lm]=0;                      // as you see, you only stop the master motor.
  wait1Msec(10);
  nSyncedMotors=synchNone;          // turn off the motor feedback control
                                    // must un-sync
}

void GoBackward(float dist)
{
	MotorEncoderReset();
	int total = dist * EncPerCm;
	setMotorTarget(Lm, total, -speed);
	setMotorTarget(Rm, total, -speed);
	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
		sleep(100);
}

void TurnLeft(float deg)
{
	MotorEncoderReset();
	int total = deg * EncPerDeg;
	setMotorTarget(Lm, total, -speed);
	setMotorTarget(Rm, total, speed);
	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
		sleep(100);
	wait1Msec(100);
}

void TurnRight(float deg)
{
	MotorEncoderReset();
	int total = deg * EncPerDeg;
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, -speed);
	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
		sleep(100);
	wait1Msec(100);
}

void MakeSTurn( float innerDiameter)
{
	int speed = 100;
	MotorEncoderReset();

	const float outerCircleDiameter = (RobotBase*2.0)+innerDiameter;
	const float outerMotorEnc = ((outerCircleDiameter*PI)/2)*EncPerCm;
	const float innerMotorSpeed = (innerDiameter/outerCircleDiameter)*speed;
	const float innerMotorEnc = ((innerDiameter*PI)/2)*EncPerCm;

  // Which motor is the master: true -> outer, false -> inner
  bool outerMotorMaster = true;

	tMotor master;
	float targetEncoders;

  if (outerMotorMaster ==  true)
  {
  	master = Rm;
  	targetEncoders = outerMotorEnc;
    nSyncedMotors = synchCB;
    nSyncedTurnRatio = 100.0 * innerDiameter / outerCircleDiameter;
  }
  else
  {
  	master = Lm;
  	targetEncoders = innerMotorEnc;
    nSyncedMotors = synchBC;
    nSyncedTurnRatio = 100.0 * outerCircleDiameter / innerDiameter; // > 100% !!!
  }

  nMotorEncoderTarget[master] = targetEncoders;
  motor[master] = speed;

  while(nMotorEncoder[master] < targetEncoders)
  {
    wait1Msec(10);
  }
  wait1Msec(500);
  motor[master] = 0;                      // as you see, you only stop the master motor.
  wait1Msec(10);
  nSyncedMotors = synchNone;          // turn off the motor feedback control

	//setMotorTarget(Rm, outerMotorEnc, speed);
	//setMotorTarget(Lm, innerMotorEnc, innerMotorSpeed);

	//while    lm stop  running   &&  rm stop running

	// while ( nMotorRunState[Lm] != runStateIdle  ||  	nMotorRunState[Lm] != runStateIdle )

	//while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )

	//while ( nMotorRunState[Lm] != runStateIdle  || nMotorRunState[Rm] != runStateIdle ) {
	//	sleep(100);
	//}
	//displayTextLine(6, "T-I:%.2f", innerMotorEnc);
	//displayTextLine(7, "T-O:%.2f", outerMotorEnc);

	wait1Msec(100);

}
