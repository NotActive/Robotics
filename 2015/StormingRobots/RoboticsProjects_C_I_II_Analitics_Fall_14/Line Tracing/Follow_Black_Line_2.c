task main()
{

	SensorType[S3] = sensorLightActive;

	int black = 36;
	int white = 64;
	int threshold = (white + black) / 2;
	int motorSpeed = 50;

	motor[motorB] = motorSpeed;
	motor[motorC] = motorSpeed;

	while (true) {

		int sensorValue = SensorValue[S3];
		int sensorChange = sensorValue - black;
		float percentChange = ( float) sensorChange / black;
		float motorSpeedChange = motorSpeed * percentChange;
		int newMotorSpeedC = motorSpeed - motorSpeedChange;
		int newMotorSpeedB = motorSpeed + motorSpeedChange;

		motor[motorC] = newMotorSpeedC;
		motor[motorB] = newMotorSpeedB;
	}
}
