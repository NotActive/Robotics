   task main()
{

	SensorType[S3] = sensorLightActive;

	int black = 36;
	int white = 64;
	int threshold = (white + black) / 2;

	while (true) {

		if (SensorValue[S3] > threshold) {
			motor[motorB] = 100;
			motor[motorC] = 0;
		}
		else {
			motor[motorB] = 0;
			motor[motorC] = 100;
		}
	}
}
