#include "common.h"

float speed = 20.0;

#define resetMotorEncoder(m)  motor[m] = 0
#define stillRunning(m)   (nMotorRunState[m]!=runStateIdle)

void MotorEncoderReset()
{
	resetMotorEncoder(Lm);
	resetMotorEncoder(Rm);
}

#define setMotorTarget(m, enc, s)   { nMotorEncoderTarget[m] = enc; motor[m] = s;}

void GoForward(float dist)
{
	MotorEncoderReset();
	int total = dist * EncPerCm;
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, speed);
	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
		sleep(100);
	wait1Msec(100);
}


void GoBackward(float dist)
{
	MotorEncoderReset();
	int total = dist * EncPerCm;
	setMotorTarget(Lm, total, -speed);
	setMotorTarget(Rm, total, -speed);

	while ( stillRunning(Lm)  && stillRunning(Rm) )
		sleep(100);
}

void TurnLeft(float deg)
{
	MotorEncoderReset();
	int total = deg * EncPerDeg;
	setMotorTarget(Lm, total, -speed);
	setMotorTarget(Rm, total, speed);
	while ( stillRunning(Lm) && stillRunning(Rm) )
		sleep(100);
	wait1Msec(100);
}

void TurnRight(float deg)
{
	MotorEncoderReset();
	int total = deg * EncPerDeg;
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, -speed);
	while ( stillRunning(Lm) && stillRunning(Rm) )
		sleep(100);
	wait1Msec(100);
}

//void MakeSTurn( float innerDiameter)
//{
//	int speed = 100;
//	MotorEncoderReset();

//	clearDebugStream();
//	writeDebugStreamLine("Opower Ipower | OEnc   IEnc ");
//	writeDebugStreamLine("============================");

//	const float outerCircleDiameter = (RobotBase*2.0)+innerDiameter;

//	float ratio = outerCircleDiameter/innerDiameter;

//	const float innerMotorSpeed = ratio*speed;
//	//const float innerMotorEnc = 1234;//((innerDiameter*PI)/2)*EncPerCm;
//	//const float outerMotorEnc = 3159.04//((outerCircleDiameter*PI)/2)*EncPerCm;
//	const float innerMotorEnc = (innerDiameter*PI)/2 * EncPerCm ;
//	const float outerMotorEnc = (outerCircleDiameter*PI) / 2 * EncPerCm * ratio;

//	writeDebugStreamLine("%f %f | %d %d ", speed, innerMotorSpeed, outerMotorEnc,  innerMotorEnc );

//	setMotorTarget(Rm, outerMotorEnc, speed);
//	setMotorTarget(Lm, innerMotorEnc, innerMotorSpeed);

//	//while    lm stop  running   &&  rm stop running

//	// while ( nMotorRunState[Lm] != runStateIdle  ||  	nMotorRunState[Lm] != runStateIdle )

//	//while ( stillRunning(Lm) && stillRunning(Rm) )nMotorRunState

//	while ( !( nMotorRunState[Lm] == runStateIdle  &&  	[Rm] == runStateIdle) )
//  while (stillRunning(Rm) || stillRunning(Lm))
//		sleep(100);

//	wait1Msec(100);
//}

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
	int targetEncoders;
  string message;
		
	if (outerMotorMaster ==  true)
	{
		master = Rm;
		targetEncoders = outerMotorEnc;
		nSyncedMotors = syncRmLm;
		nSyncedTurnRatio = 100.0 * innerDiameter / outerCircleDiameter;
		sprintf(message, "Target OEnc=%d", targetEncoders);
		}
	else
	{
		master = Lm;
		targetEncoders = innerMotorEnc;
		nSyncedMotors = syncLmRm;
		nSyncedTurnRatio = 100.0 * outerCircleDiameter / innerDiameter; // > 100% !!!
		sprintf(message, "Target IEnc = %d", targetEncoders);
	}
	writeDebugStreamLine("%s", message);
		
	delay(2000);
		
	nMotorEncoderTarget[master] = targetEncoders;
	motor[master] = speed;

	//while(nMotorEncoder[master] < targetEncoders)
	//{
	//	wait1Msec(10);
	//}
	while ( stillRunning(Rm) )
		sleep(100);
	wait1Msec(10);
	nSyncedMotors = synchNone;          // turn off the motor feedback control

	wait1Msec(100);
}
