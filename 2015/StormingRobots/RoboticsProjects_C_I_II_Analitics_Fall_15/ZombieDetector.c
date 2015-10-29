#define MAX_FILE_SIZE  5000  //maximum file size in bytes

task main()
{
	const int Lm = motorB;
	const int Rm = motorC;
	const int SonarSensor = S4;

	const float WheelDia = 3.25;
	const float GR = 12.0/20.0;
	const float Dist = 100.0;
	const float Speed = 50.0;
	const float EncPerCm = 360.0*GR/(WheelDia*PI);

	nMotorEncoder[Lm] = 0;
	SensorType[SonarSensor] = sensorSONAR;

	//logging
	int bytes = 0;
	char fileName[15];

#if defined(NXT)
	TFileHandle fp;              // to store file handler
	TFileIOResult result;        // to store status
#else
	long fp;
#endif

	// Reset NXT time
	clearTimer(T1);
	time1(T1) = 0;

	// create a file name based on the current System time
	sprintf(fileName,"log%d.txt", nSysTime/1000);

	// create or open file
#if defined(NXT)
	Delete(fileName, result);
	short fileSize = MAX_FILE_SIZE;
	OpenWrite(fp, result, fileName, fileSize);
#else
	fp = fileOpenWrite(fileName);
#endif

	while(nMotorEncoder[Lm] <= Dist*EncPerCm)
	{
		motor[Lm] = Speed;
		motor[Rm] = Speed;

		// create message
		string message;
		sprintf(message, "%d\t%d\r\n", nMotorEncoder[Lm], SensorValue[SonarSensor]);

		// write message
#if defined(NXT)
		WriteText(fp, result, message);
#else
		fileWriteData(fp, message, messagelen(message));
#endif
	}

	// close file
#if defined(NXT)
	Close(fp, result);
#else
	fileClose(fp);
#endif
}
