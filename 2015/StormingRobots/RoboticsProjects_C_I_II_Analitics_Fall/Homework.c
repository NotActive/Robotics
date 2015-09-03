/*
-----------------------------------------------
----------------Program made by----------------
-----------------Peter Romayev-----------------
-----------------------------------------------
*/

#include "move.c"


task main()
{

	float dist = 30.0;
	float deg = 90.0;

	GoForward(dist);
	wait1Msec(1000);
	GoBackward(dist);
	wait1Msec(1000);
	TurnLeft(deg);
	wait1Msec(1000);
	TurnRight(deg);
}
