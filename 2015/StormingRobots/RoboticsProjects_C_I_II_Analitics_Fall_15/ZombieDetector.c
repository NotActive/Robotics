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

	SensorType[SonarSensor] = sensorSONAR;

	nMotorEncoder[Lm] = 0;

	while(nMotorEncoder[Lm] <= Dist*EncPerCm)
	{
		motor[Lm] = Speed;
		motor[Rm] = Speed;
		displayTextLine(5, "%d", SensorValue[SonarSensor]);
		displayTextLine(4, "%d", nMotorEncoder[Lm]);
	}
}
