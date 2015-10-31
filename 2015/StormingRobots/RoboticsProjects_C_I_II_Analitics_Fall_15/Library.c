#include "common.h"

#define resetMotorEncoder(m)  motor[m] = 0

void MotorEncoderReset()
{
 resetMotorEncoder(motorB);
 resetMotorEncoder(motorC);
}

#define setMotorTarget(m, enc, s)   { nMotorEncoderTarget[m] = enc; motor[m] = s;}

void GoForward(float Dist)
{
 MotorEncoderReset();
 int total = Dist * EncPerCm;
 setMotorTarget(Lm, total, Speed);
 setMotorTarget(Rm, total, Speed);
 //getMotorTargetCompleted(Lm)   return 0 if not finished
 while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
  sleep(100);
 wait1Msec(100);
}

void GoBackward(float Dist)
{
 MotorEncoderReset();
 int total = Dist * EncPerCm;
 setMotorTarget(Lm, total, -Speed);
 setMotorTarget(Rm, total, -Speed);
 //waitUntilMotorStop(Lm);
 while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
  sleep(100);
}

void TurnLeft(float Deg)
{
 MotorEncoderReset();
 int total = Deg * EncPerDeg;
 setMotorTarget(Lm, total, -Speed);
 setMotorTarget(Rm, total, Speed);
 //waitUntilMotorStop(Rm);
 while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
  sleep(100);
 wait1Msec(100);
}

void TurnRight(float Deg)
{
 MotorEncoderReset();
 int total = Deg * EncPerDeg;
 setMotorTarget(Lm, total, Speed);
 setMotorTarget(Rm, total, -Speed);
 // waitUntilMotorStop(Rm);
 while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) )
  sleep(100);
 wait1Msec(100);
}

void TurnHalfCircle ()
{

 MotorEncoderReset();

 float OuterCircleDiameter = InnerCircleDiameter+(RobotBase*2.0);
 float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*Speed;
 float InnerMotorEnc = (InnerCircleDiameter/2.0)*EncPerCm;
 float OuterMotorEnc = (OuterCircleDiameter/2.0)*EncPerCm;

 nMotorEncoder[motorB] = (int)OuterMotorEnc;
 nMotorEncoder[motorC] = (int)InnerMotorEnc;

 motor[motorB] = (int)Speed;
 motor[motorC] = (int)InnerMotorSpeed;
}
