#include "lib.h"

//local const

//Tells which motor is which
const int Lm = motorB;
const int Rm = motorC;
//Tell where all the sensors are
const int Lcol = S1;
const int Rcol = S2;
const int Gyro = S3;
const int Eye = S4;
//Speed
const float speed = 50.0;

//Values
const int LcolW = 40;
const int LcolB = 10;
const int LcolThresh = (LcolW + LcolB)/2;
const int RcolW = 35;
const int RcolB = 5;
const int RcolThresh = (RcolW + RcolB)/2;
const float Price = 0.05;

//Functions
//Resets MotorEncoder
void MotorEncoderReset()
{
	resetMotorEncoder(Lm);
	resetMotorEncoder(Rm);
}
//Forward
void GoForward(float Dist)
{
	//Reset MotorEncoder
	MotorEncoderReset();
	//How far you want to go forward
	int total = Dist * EncPerCm;
	//Tells the motors to go forward
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, speed);
	//Waits until motors stop before doing the next command
	waitUntilMotorStop(Rm);
	//Waits. If it doesn't wait then it will do too sharp of a turn/movement
	wait1Msec(100);
}

//Backwards
void GoBackward(float Dist)
{
	//Reset MotorEncoder
	MotorEncoderReset();
	//How far you want to go backwards
	int total = -Dist * EncPerCm;
	//Tells the motors to go backwards
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, speed);
	//Waits until motors stop before doing the next command
	waitUntilMotorStop(Rm);
	//Waits. If it doesn't wait then it will do too sharp of a turn/movement
	wait1Msec(100);
}
void TurnLeft(float Deg)
{
	//Reset MotorEncoder
	MotorEncoderReset();
	//How far you want to turn
	int total = Deg * EncPerDeg;
	//Tells the motors to turn left
	setMotorTarget(Lm, -total, speed);
	setMotorTarget(Rm, total, speed);
	//Waits until motors stop before doing the next command
	waitUntilMotorStop(Rm);
	//Waits. If it doesn't wait then it will do too sharp of a turn/movement
	wait1Msec(100);
}
void TurnRight(float Deg)
{
	//Reset MotorEncoder
	MotorEncoderReset();
	//How far you want to turn
	int total = Deg * EncPerDeg;
	//Tells the motors to turn right
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, -total, speed);
	//Waits until motors stop before doing the next command
	waitUntilMotorStop(Rm);
	//Waits. If it doesn't wait then it will do too sharp of a turn/movement
	wait1Msec(100);
}

float CalcCost(float enc)
{
	//converts enc to cm, then mutiplies it by the cost per cm, which is currently .50 cents
	float cost = (enc*CmPerEnc)*Price;
	return cost;
}

void MoveUntilStation()
{
	while(SensorValue[Eye] > 30)
	{
		motor[Lm] = 50;
		motor[Rm] = 50;
	}
	motor[Lm] = 0;
	motor[Rm] = 0;
}

void MovePastStation()
{
	while(SensorValue[S4] < 30)
	{
		motor[Lm] = 50;
		motor[Rm] = 50;
	}
	MotorEncoderReset();
}

void StopMotors()
{
	motor[Lm] = 0;
	motor[Rm] = 0;
}
