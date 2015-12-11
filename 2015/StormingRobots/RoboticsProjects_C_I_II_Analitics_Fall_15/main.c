#include "Library.c"

void runEnc( int enc)
{
	int speed = 90;
	MotorEncoderReset();

	const float outerCircleDiameter = (RobotBase*2.0)+innerDiameter;

	const float outerMotorEnc = ((outerCircleDiameter*PI)/2)*EncPerCm;
	const float innerMotorSpeed = (innerDiameter/outerCircleDiameter)*speed;
	const float innerMotorEnc = ((innerDiameter*PI)/2)*EncPerCm;

	// Which motor is the master: true -> outer, false -> inner
	bool outerMotorMaster = true;

	tMotor master;
	int targetEncoders;
  string message;
		
		master = Rm;
		targetEncoders = enc;
		nSyncedMotors = syncRmLm;
		nSyncedTurnRatio = 100.0 * innerDiameter / outerCircleDiameter;
		
	delay(2000);
		
	nMotorEncoderTarget[master] = targetEncoders;
	motor[master] = speed;

	//while(nMotorEncoder[master] < targetEncoders)
	//{
	//	wait1Msec(10);
	//}
	while ( stillRunning(Rm) )
		sleep(100);
	wait1Msec(10);
	nSyncedMotors = synchNone;          // turn off the motor feedback control

	wait1Msec(100);
}

task main()
{
	string message;
	//while (true)
	{

		MakeSTurn(20.0);

		displayTextLine(2, "Lenc:%d", nMotorEncoder[Lm]);
		displayTextLine(3, "Renc: %d", nMotorEncoder[Rm]);
		runEnc(528);
		delay(50000);

	}
}
