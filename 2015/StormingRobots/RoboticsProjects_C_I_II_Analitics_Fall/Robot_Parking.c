/*
-----------------------------------------------
----------------Program made by----------------
-----------------Peter Romayev-----------------
-----------------------------------------------
*/

task main()
{
	//We tell it the sensors
	//this is the ultrasonic sensor. It is plugged into port four
	SensorType[S4] = sensorSONAR;
	//this is the touch sensor. It is plugged into port one
	SensorType[S1] = sensorTouch;
	//this is the light sensor. It is plugged into port three
	SensorType[S3] = sensorLightActive;

	//the integers.
	//dark is the black line. It's value is 45
	int dark = 45;
	//light is the white line. It's value is 73
	int light = 73;
	//thresh is the amount between AKA the average
	int thresh = (dark + light)/2;
	//this is the distence the ultrasonic sensor sees the wall
	int wall = 30;
	//this is the circumfrence of our robot
	int circ = 16*(360/(PI*3));
	while(SensorValue[S1] == 0){

		while(SensorValue[S4]< wall)
		{
			if (SensorValue[S3] < thresh)
			{
				motor[motorB] = 0;
				motor[motorC] = 100;
			}
			else
			{
				motor[motorB] = 100;
				motor[motorC] = 0;
			}

		}
		playSound(soundDownwardTones);

		nMotorEncoder[motorB] = 0;
		nMotorEncoder[motorC] = 0;

		while(SensorValue[S4]>wall)
		{
			if (SensorValue[S3] < thresh)
				{
				motor[motorB] = 0;
				motor[motorC] = 100;
			}
			else
			{
				motor[motorB] = 100;
				motor[motorC] = 0;
			}

		}
		if(nMotorEncoder[motorB]>circ){

			nMotorEncoder[motorB] = 0;
			nMotorEncoder[motorC] = 0;

			playSound(soundDownwardTones);

			motor[motorB] = 0;
			motor[motorC] = -50;
			wait1Msec(2000);

			while(SensorValue[S1] == 0){
				motor[motorC] = -50;
				motor[motorB] = -50;
			}
		}
	}
}
