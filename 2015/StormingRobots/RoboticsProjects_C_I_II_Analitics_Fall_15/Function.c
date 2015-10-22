#include "common.h"

void MotorEncoderReset()
{
	nMotorEncoder[Lm] = 0;
	nMotorEncoder[Rm] = 0;
}

//void TurnHalfCircle ()
//{
//	float OuterCircleDiameter = InnerCircleDiameter+(RobotBase*2.0);
//	float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*Speed;
//	float InnerMotorEnc = (InnerCircleDiameter/2.0)*EncPerCm;
//	float OuterMotorEnc = (OuterCircleDiameter/2.0)*EncPerCm;
//	MotorEncoderReset();
//	nMotorEncoder[motorB] = (int)OuterMotorEnc;
//	nMotorEncoder[motorC] = (int)InnerMotorEnc;
//	motor[motorB] = (int)Speed;
//	motor[motorC] = (int)InnerMotorSpeed;
//}

void GoForward()
{
	MotorEncoderReset();

	while(nMotorEncoder[motorB]>Dist){
		motor[motorB] = Speed;
		motor[motorC] = Speed;
	}
	motor[Lm] = 0;
	motor[Rm] = 0;
}

void GoBackward()
{
	MotorEncoderReset();

	while(nMotorEncoder[motorB]>Dist){
		motor[motorB] = -Speed;
		motor[motorC] = -Speed;
	}
	motor[Lm] = 0;
	motor[Rm] = 0;
}

void TurnLeft()
{
	MotorEncoderReset();

	while(nMotorEncoder[motorB]>Deg){
		motor[Lm] = -Speed;
		motor[Rm] = Speed;
	}
	motor[Lm] = 0;
	motor[Rm] = 0;
}

void TurnRight()
{
	MotorEncoderReset();

	while(nMotorEncoder[motorB]>Deg){
		motor[Lm] = Speed;
		motor[Rm] = -Speed;
	}
	motor[Lm] = 0;
	motor[Rm] = 0;
}

void GoInASquare()
{
	int i = 0;
	while(i<4)
	{
		GoForward();
		TurnLeft();
		i++;
	}
}

//void GoForward(float Dist)
//{
//	MotorEncoderReset();
//	int total = Dist * EncPerCm;
//	setMotorTarget(Lm, total, Speed);
//	setMotorTarget(Rm, total, Speed);
//	waitUntilMotorStop(Rm);
//	wait1Msec(100);
//}

//void GoBackward(float Dist)
//{
//	MotorEncoderReset();
//	int total = -Dist * EncPerCm;
//	setMotorTarget(Lm, total, Speed);
//	setMotorTarget(Rm, total, Speed);
//	waitUntilMotorStop(Lm);
//}

//void TurnLeft(float Deg)
//{
//	MotorEncoderReset();
//	int total = Deg * EncPerDeg;
//	setMotorTarget(Lm, total, -Speed);
//	setMotorTarget(Rm, total, Speed);
//	waitUntilMotorStop(Rm);
//	wait1Msec(100);
//}

//void TurnRight(float Deg)
//{
//	MotorEncoderReset();
//	int total = Deg * EncPerDeg;
//	setMotorTarget(Lm, total, Speed);
//	setMotorTarget(Rm, total, -Speed);
//	waitUntilMotorStop(Rm);
//	wait1Msec(100);
//}
