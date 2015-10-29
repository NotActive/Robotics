#include "common.h"

void MotorEncoderReset()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}

void TurnHalfCircle ()
{
	float OuterCircleDiameter = InnerCircleDiameter+(RobotBase*2.0);
	float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*Speed;
	float InnerMotorEnc = (InnerCircleDiameter/2.0)*EncPerCm;
	float OuterMotorEnc = (OuterCircleDiameter/2.0)*EncPerCm;
	MotorEncoderReset();
	nMotorEncoder[motorB] = (int)OuterMotorEnc;
	nMotorEncoder[motorC] = (int)InnerMotorEnc;
	motor[motorB] = (int)Speed;
	motor[motorC] = (int)InnerMotorSpeed;
}

void GoForward(float Dist)
{
	MotorEncoderReset();
	int total = Dist * EncPerCm;
	setMotorTarget(Lm, total, Speed);
	setMotorTarget(Rm, total, Speed);
	waitUntilMotorStop(Rm);
	wait1Msec(100);
}

void GoBackward(float Dist)
{
	MotorEncoderReset();
	int total = -Dist * EncPerCm;
	setMotorTarget(Lm, total, Speed);
	setMotorTarget(Rm, total, Speed);
	waitUntilMotorStop(Lm);
}

void TurnLeft(float Deg)
{
	MotorEncoderReset();
	int total = Deg * EncPerDeg;
	setMotorTarget(Lm, total, -Speed);
	setMotorTarget(Rm, total, Speed);
	waitUntilMotorStop(Rm);
	wait1Msec(100);
}

void TurnRight(float Deg)
{
	MotorEncoderReset();
	int total = Deg * EncPerDeg;
	setMotorTarget(Lm, total, Speed);
	setMotorTarget(Rm, total, -Speed);
	waitUntilMotorStop(Rm);
	wait1Msec(100);
}
