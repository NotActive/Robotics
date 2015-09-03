/*
-----------------------------------------------
----------------Program made by----------------
-----------------Peter Romayev-----------------
-----------------------------------------------
*/

task main
{
	int x = 0;
	int y = 0;
	SensorType[S4] = sensorSONAR;
	nMotorEncoder[motorB] = 0;
	motor[motorB] = 10;
	motor[motorC] = 10;
	while (SensorValue[S4] > 240){
		motor[motorB] = 0;
		motor[motorC] = 0;
		x = SensorValue[S4];
		y = nMotorEncoder[motorB];
		displayTextLine(4, "%d", x);
		displayTextLine(5, "%d", y);
		wait1Msec(99999999999999999999999);
	}
}
