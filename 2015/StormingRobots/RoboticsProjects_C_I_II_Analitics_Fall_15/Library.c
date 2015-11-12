#include "common.h"

#define MAX_FILE_SIZE  5000  //maximum file size in bytes

//logging
int currentFileSize = 0; // in bytes

#if defined(NXT)
TFileHandle fp;              // to store file handler
TFileIOResult result;        // to store status
#else
long fp;
#endif

#define resetMotorEncoder(m)  motor[m] = 0

void InitalizeLogger()
{
	// Reset NXT time
	clearTimer(T1);
	time1(T1) = 0;

	// create a file name based on the current System time
	char fileName[15];
	sprintf(fileName,"log.txt");
	//	sprintf(fileName,"log%d.txt", nSysTime/1000);

#if defined(NXT)
	Delete(fileName, result);
	short fileSize = MAX_FILE_SIZE;
	OpenWrite(fp, result, fileName, fileSize);
#else
	fp = fileOpenWrite(fileName);
#endif
}

void LogMessage(string message)
{
	// Am I allowed to write, i.e. below max file size?
  // if not, just return
  currentFileSize = currentFileSize + 17 * sizeof(char);
  if (currentFileSize >= MAX_FILE_SIZE) {
  	return;
  }

	// write message
#if defined(NXT)
	WriteText(fp, result, message);
#else
	fileWriteData(fp, message, messagelen(message));
#endif
}


void CloseFile()
{
	// close file
#if defined(NXT)
	Close(fp, result);
#else
	fileClose(fp);
#endif
}

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
	InitalizeLogger();
	string message;

	MotorEncoderReset();

	const float OuterCircleDiameter = (RobotBase*2.0) + InnerCircleDiameter;
	const float InnerMotorSpeed = (InnerCircleDiameter/OuterCircleDiameter)*Speed;
	const float InnerMotorEnc = (InnerCircleDiameter/2.0)*EncPerCm;
	const float OuterMotorEnc = (OuterCircleDiameter/2.0)*EncPerCm;

	sprintf(message, "RobotBase: %.2f \r\n", RobotBase);
	LogMessage(message);
	sprintf(message, "InnerDia: %.2f \r\n", InnerCircleDiameter);
	LogMessage(message);
	sprintf(message, "Outer D: %.2f \r\n", OuterCircleDiameter);
	LogMessage(message);
	sprintf(message, "Enc / Cm: %.2f \r\n", EncPerCm);
	LogMessage(message);
	sprintf(message, "IE: %.2f \r\n", InnerMotorEnc);
	LogMessage(message);
	sprintf(message, "OE: %.2f \r\n", OuterMotorEnc);
	LogMessage(message);

	//nMotorEncoder[motorB] = (int)OuterMotorEnc;
	//nMotorEncoder[motorC] = (int)InnerMotorEnc;

	setMotorTarget(Rm, OuterMotorEnc, Speed);
	setMotorTarget(Lm, InnerMotorEnc, InnerMotorSpeed);

	while ( (nMotorRunState[Lm] != runStateIdle)  &&  (nMotorRunState[Rm] != runStateIdle) ) {
		sleep(100);
		sprintf(message, "L: %.1f R: %.1f \r\n\n", nMotorEncoder[Lm], nMotorEncoder[Rm]);
		LogMessage(message);
	}
	wait1Msec(100);

	//motor[motorB] = (int)Speed;
	//motor[motorC] = (int)InnerMotorSpeed;

	CloseFile();
}
