#include "Library.c"

task main()
{

MakeSTurn(20.0);
int i=0;
string message;
while (true)
{
	sprintf(message, "inner %d outer %d", nMotorEncoder[Lm], nMotorEncoder[Rm]);
	writeDebugStreamLine("%s", message);
	delay(2000);
}
	//float dist = 50.0;
	//float deg = 90.0;

	//int motorencoder = nMotorEncoder[Lm];

	////displayTextLine(2, "Lenc:%d", nMotorEncoder[Lm]);
	////displayTextLine(3, "Renc: %d", nMotorEncoder[Rm]);
	////displayTextLine(4, "Bat: %d", nAvgBatteryLevel);
	//delay(50000);
 }
