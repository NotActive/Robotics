#include "move.h"

const int Lm = motorB;
const int Rm = motorC;
const float speed = 50.0;
const float Wdia = 4.1;
const float WBase = 13.4 ;
const float EncPerCm = 360.0/(Wdia*PI);
const float EncPerDeg = WBase/Wdia;

void MotorEncoderReset()
{
	resetMotorEncoder(Lm);
	resetMotorEncoder(Rm);
}

void Go(float dist)
{
	MotorEncoderReset();
	int total = dist * EncPerCm;
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, speed);
	waitUntilMotorStop(Rm);
	wait1Msec(100);
}

void Turn(float deg, bool isRight)
{
	MotorEncoderReset();
	int total = deg * EncPerDeg;

	if (isRight)
	{
		setMotorTarget(Lm, total, speed);
		setMotorTarget(Rm, -total, speed);
	}
	else
	{
		setMotorTarget(Lm, -total, speed);
		setMotorTarget(Rm, total, speed);
	}
	waitUntilMotorStop(Rm);
	wait1Msec(100);
}

void GoForward(float dist)
{
	Go(dist);
}

void GoBackward(float dist)
{
	Go(-dist);
}

void TurnLeft(float deg)
{
	Turn(deg, false);
}

void TurnRight(float deg)
{
	Turn(deg, true);
}
