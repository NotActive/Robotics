/*
-----------------------------------------------
----------------Program made by----------------
-----------------Peter Romayev-----------------
-----------------------------------------------
*/

const int ZOMBIEN = 4;
const int SPEED = 50;
const int MAXMATCHES = 12;
const int MINWHITE = 69;
const int MAXWHITE = 72;
const int MINGREEN = 26;
const int MAXGREEN = 37;
const int MINSILVER = 64;
const int MAXSILVER = 92;
const float DIAMETER = 3.0;
const float TICS_TO_CM_MULT = DIAMETER*PI/360;

bool isWhite(int value)
{
	if (value >= MINWHITE && value <= MAXWHITE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isGreen(int value)
{
	if (value >= MINGREEN && value <= MAXGREEN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isSilver(int value)
{
	//if (isWhite(value))
	//{
	//	return false;
	//}
	if (isGreen(value))
	{
		return false;
	}
	if (value >= MINSILVER && value <= MAXSILVER)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int numberOfMatches;

task main()
{
	// Configuration
	SensorType[S1] = sensorLightActive;
	SensorType[S4] = sensorSONAR;

	// Initialize the loop
	int zombieX[ZOMBIEN];
	int zombieY[ZOMBIEN];
	int loopN = 0;
	numberOfMatches = 0;
	bool readyToRecord = true;
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;

	// Move forward
	motor[motorB] = SPEED;
	motor[motorC] = SPEED;

	string out = "";
	while (loopN < ZOMBIEN)
	{
		displaySensorValues(line5,S1);
		// If I see silver
		if (isSilver(SensorValue[S1]))
		{
			strcat(out, "s");
			writeDebugStreamLine("s:");
			//false reading
			numberOfMatches = 0;
			if (readyToRecord == true)
			{
				// Record
				int x = nMotorEncoder[motorB]*TICS_TO_CM_MULT;
				zombieX[loopN] = x;
				zombieY[loopN] = SensorValue[S4];
				playSoundFile("! StartUp.rso");
				// I'm making a recording, not ready to record until I see the field again
				readyToRecord = false;
				// Increment number of recorded zombies
				loopN++;
			}
		}
		// If I see the field, I'm ready to record again
		else
		{
			strcat(out, "f");
						writeDebugStreamLine("f:");
			numberOfMatches++;

			if (numberOfMatches >= MAXMATCHES)
			{
				readyToRecord = true;
				numberOfMatches = 0;
			}
		}
	}

	// Stop moving
	motor[motorB] = 0;
	motor[motorC] = 0;

	//debug

	displayTextLine(3, out);

	//displayTextLine(3,"X value");
	//displayTextLine(4,"%d %d %d %d", zombieX[0], zombieX[1], zombieX[2], zombieX[3]);
	//displayTextLine(5,"Y value");
	//displayTextLine(6,"%d %d %d %d", zombieY[0], zombieY[1], zombieY[2], zombieY[3]);

	//display
	for (int i = 0; i < ZOMBIEN; i++)
	{
		//drawRect(zombieX[i], zombieY[i], zombieX[i]+5, zombieY[i]+10);
	}
	wait1Msec(99999999999);
}
