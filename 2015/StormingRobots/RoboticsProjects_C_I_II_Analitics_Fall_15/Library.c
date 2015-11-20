#include "common.h"

float speed = 100.0;

#define resetMotorEncoder(m)  motor[m] = 0

void MotorEncoderReset()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
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
	const float innerMotorSpeed = (innerDiameter/outerCircleDiameter)*speed;
	const float innerMotorEnc = ((innerDiameter*PI)/2)*EncPerCm;
	const float outerMotorEnc = ((outerCircleDiameter*PI)/2)*EncPerCm;

	setMotorTarget(Rm, outerMotorEnc, speed);
	setMotorTarget(Lm, innerMotorEnc, innerMotorSpeed);

	//while    lm stop  running   &&  rm stop running
	
 // while ( nMotorRunState[Lm] != runStateIdle  ||  	nMotorRunState[Lm] != runStateIdle )  
	
	//while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
	
  while ( !( nMotorRunState[Lm] == runStateIdle  &&  	nMotorRunState[Rm] == runStateIdle) ) 	
   	sleep(100);
   displayTextLine(6, "T-I:%.2f", innerMotorEnc);
  displayTextLine(7, "T-O:%.2f", outerMotorEnc);
 
	wait1Msec(100);

}
