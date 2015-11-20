#include "common.h"

float speed = 50.0;

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

void MakeHalf Turn ()
{
	MotorEncoderReset();

	const float OuterCircleDiameter = (RobotBase*2.0)+InnerCircleDiameter;
	const float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*speed;
	const float InnerMotorEnc = ((InnerCircleDiameter*PI)/2)*EncPerCm;
	const float OuterMotorEnc = ((OuterCircleDiameter*PI)/2)*EncPerCm;

	setMotorTarget(Rm, OuterMotorEnc, speed);
	setMotorTarget(Lm, InnerMotorEnc, InnerMotorSpeed);

	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
		sleep(100);
	wait1Msec(100);
}

//void MakeRightSTurn ()
//{
//	MotorEncoderReset();

//	const float OuterCircleDiameter = (RobotBase*2.0)+InnerCircleDiameter;
//	const float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*speed;
//	const float InnerMotorEnc = ((InnerCircleDiameter*PI)/2)*EncPerCm;
//	const float OuterMotorEnc = ((OuterCircleDiameter*PI)/2)*EncPerCm;

//	setMotorTarget(Rm, OuterMotorEnc, speed);
//	setMotorTarget(Lm, InnerMotorEnc, InnerMotorSpeed);

//	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
//		sleep(100);
//	wait1Msec(100);

//	setMotorTarget(Lm, OuterMotorEnc, speed);
//	setMotorTarget(Rm, InnerMotorEnc, InnerMotorSpeed);

//	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
//		sleep(100);
//	wait1Msec(100);
//}

//void MakeLeftSTurn ()
//{
//	MotorEncoderReset();

//	const float OuterCircleDiameter = (RobotBase*2.0)+InnerCircleDiameter;
//	const float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*speed;
//	const float InnerMotorEnc = ((InnerCircleDiameter*PI)/2)*EncPerCm;
//	const float OuterMotorEnc = ((OuterCircleDiameter*PI)/2)*EncPerCm;

//	setMotorTarget(Lm, OuterMotorEnc, speed);
//	setMotorTarget(Rm, InnerMotorEnc, InnerMotorSpeed);

//	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
//		sleep(100);
//	wait1Msec(100);

//	setMotorTarget(Rm, OuterMotorEnc, speed);
//	setMotorTarget(Lm, InnerMotorEnc, InnerMotorSpeed);

//	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
//		sleep(100);
//	wait1Msec(100);
//}
