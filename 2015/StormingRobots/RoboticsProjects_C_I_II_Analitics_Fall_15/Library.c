#include "common.h"

float speed = 100.0;

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
	while ( stillRunning(Lm) && stillRunning(Rm) )
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

void MakeSTurn( float innerDiameter)
{
	int speed = 100;
	MotorEncoderReset();

	clearDebugStream();
	writeDebugStreamLine("Opower Ipower | OEnc   IEnc ");
	writeDebugStreamLine("============================");

	const float outerCircleDiameter = (RobotBase*2.0)+innerDiameter;

	float ratio = outerCircleDiameter/innerDiameter;
	
	const float innerMotorSpeed = ratio*speed;
	//const float innerMotorEnc = 1234;//((innerDiameter*PI)/2)*EncPerCm;
	//const float outerMotorEnc = 3159.04//((outerCircleDiameter*PI)/2)*EncPerCm;
	const float innerMotorEnc = (innerDiameter*PI)/2 * EncPerCm  * ratio;
	const float outerMotorEnc = (outerCircleDiameter*PI) / 2 * EncPerCm * ratio;

	writeDebugStreamLine("%f %f | %d %d ", speed, innerMotorSpeed, outerMotorEnc,  innerMotorEnc );

	setMotorTarget(Rm, outerMotorEnc, speed);
	setMotorTarget(Lm, innerMotorEnc, innerMotorSpeed);
	


	//while    lm stop  running   &&  rm stop running

	// while ( nMotorRunState[Lm] != runStateIdle  ||  	nMotorRunState[Lm] != runStateIdle )

	//while ( stillRunning(Lm) && stillRunning(Rm) )

	while ( !( nMotorRunState[Lm] == runStateIdle  &&  	nMotorRunState[Rm] == runStateIdle) )
  while (stillRunning(Rm) || stillRunning(Lm))
		sleep(100);

	wait1Msec(100);

}
