#include "Library.c"

task main()
{
	float dist = 50.0;
	float deg = 90.0;

	
	MakeSTurn(20.0);

	displayTextLine(2, "Lenc:%d", nMotorEncoder[Lm]);
	displayTextLine(3, "Renc: %d", nMotorEncoder[Rm]);
	delay(50000);
}
