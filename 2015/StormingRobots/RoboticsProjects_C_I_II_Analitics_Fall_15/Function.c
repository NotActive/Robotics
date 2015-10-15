#include "common.h"

void MotorEncoderReset()
{
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}

void TurnHalfCircle ()
{
	float OuterCircleDiameter = InnerCircleDiameter+(RobotBase*2.0);
	float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*OuterMotorSpeed;
	float InnerMotorEnc = (InnerCircleDiameter/2.0)*EncPerCm;
	float OuterMotorEnc = (OuterCircleDiameter/2.0)*EncPerCm;

	MotorEncoderReset();

	nMotorEncoder[motorB] = (int)OuterMotorEnc;
	nMotorEncoder[motorC] = (int)InnerMotorEnc;
	motor[motorB] = (int)OuterMotorSpeed;
	motor[motorC] = (int)InnerMotorSpeed;
}
