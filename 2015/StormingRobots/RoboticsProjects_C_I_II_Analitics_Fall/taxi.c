//most of this is temporarily, will get moved to other places.

#include "lib.c"



task main()
{
	float TotalCost = 0;
	int i = 0;

	while(i<3)
	{
		MoveUntilStation();
		float cost = CalcCost(nMotorEncoder[motorB]);
		displayBigTextLine(i, "%f", cost);
		TotalCost = TotalCost + cost;
		wait10Msec(500);
		MovePastStation();
		i++;
	}
	StopMotors();
	displayBig4TextLine(i, "%f", TotalCost);
	wait1Msec(10000);
}
