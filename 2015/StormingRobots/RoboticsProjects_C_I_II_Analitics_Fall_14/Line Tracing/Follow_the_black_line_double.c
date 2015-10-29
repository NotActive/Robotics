/*
-----------------------------------------------
----------------Program made by----------------
-----------------Peter Romayev-----------------
-----------------------------------------------
*/

//specifies some varibles instead of needing to write motorB/#/S1 aLW the time
//motors
const int Lm = motorB;
const int Rm = motorC;
//sensors
const int LColor = S1;
const int RColor = S2;
const int Gyro = S3;
const int Eye = S4;
//sensor value
//LW = Left White, LB = Left Black, RW = Right White, RB = Right Black
const int LW = 9;
const int LB = 6;
const int RW = 54;
const int RB = 18;
const int silver = 83;
//speed
const float speed = 50.0;
//mesurments and calculations
const float Wdia = 4.1;
const float WBase = 13.5;
const float EncPerCm = 360.0/(Wdia*PI);
const float CmPerEnc = Wdia*PI/360.0;
const float EncPerDeg = WBase/Wdia;
const int LThresh = (LB + LW)/2;
const int RThresh = (RW + RB)/2;

//functions
void MotorEncoderReset()
{
	//resets both motors MotorEncoder values
	resetMotorEncoder(Lm);
	resetMotorEncoder(Rm);
}

void GoForward(float dist)
{
	//Resets MotorEncoder
	MotorEncoderReset();
	//Calculates Total Distance to travel
	int total = dist * EncPerCm;
	//Tells the motors to run
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, speed);
	//Waits until motors stop
	waitUntilMotorStop(Lm);
	waitUntilMotorStop(Rm);
	//Waits a little bit. If it doesn't wait it does too sharp of a movement
	wait1Msec(500);
}

void GoBackwaRB(float dist)
{
	//Resets MotorEncoder
	MotorEncoderReset();
	//Calculates Total Distance to travel
	int total = -dist * EncPerCm;
	//Tells the motors to run
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, total, speed);
	//Waits until both motors stop
	waitUntilMotorStop(Lm);
	waitUntilMotorStop(Rm);
	//Waits a little bit. If it doesn't wait it does too sharp of a movement
	wait1Msec(500);
}

void TurnLeft(float deg)
{
	//Resets MotorEncoder
	MotorEncoderReset();
	//Calculates Total Distance to turn
	int total = deg * EncPerDeg;
	//Tells the motors to run
	setMotorTarget(Lm, -total, speed);
	setMotorTarget(Rm, total, speed);
	//Waits until motors stop
	waitUntilMotorStop(Lm);
	waitUntilMotorStop(Rm);
	//Waits a little bit. If it doesn't wait it does too sharp of a movement
	wait1Msec(500);
}

void TurnRight(float deg)
{
	//Resets MotorEncoder
	MotorEncoderReset();
	//Calculates Total Distance to turn
	int total = deg * EncPerDeg;
	//Tells the motors to run
	setMotorTarget(Lm, total, speed);
	setMotorTarget(Rm, -total, speed);
	//Waits until motors stop
	waitUntilMotorStop(Lm);
	waitUntilMotorStop(Rm);
	//Waits a little bit. If it doesn't wait it does too sharp of a movement
	wait1Msec(500);
}

task main()
{
	//Specifies which sensors are which
	SensorType[LColor] = sensorEV3_Color;
	SensorType[LColor] = sensorEV3_Color;
	SensorType[Gyro] = sensorEV3_Gyro;
	SensorType[Eye] = sensorEV3_Ultrasonic;

	//specifies distance and degrees
	float dist = 15.0;
	float deg = 90;

	while(true)
	{
		// Only do this when the light sensor does not see silver
		while(SensorValue[Eye]<5)
		{
			// If light sensor sees black, go right
			if(SensorValue[RColor] < RThresh)
			{
				TurnRight(deg);
			}
			else
			{
				// If color sensor sees black, go right
				if(SensorValue[LColor] < LThresh)
				{
					TurnLeft(deg);
				}
				else
				{
					GoForward(dist);
				}
			}
		}

		TurnLeft(deg);
		GoForward(dist/2);
		TurnRight(deg);
		GoForward(dist);
		TurnRight(deg);
		GoForward(dist/2);

	}

}
