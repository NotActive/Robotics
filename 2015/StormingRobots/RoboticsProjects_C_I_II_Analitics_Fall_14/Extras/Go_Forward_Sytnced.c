const int Lm = motorB;
const int Rm = motorC;
const float speed = 50.0;
const float Wdia = 5.6;
const float EncPerCm = 360.0/(Wdia*PI);
const float CmPerEnc = Wdia*PI/360.0;


void MotorEncoderReset()
{
	resetMotorEncoder(Lm);
	resetMotorEncoder(Rm);
}

void GoForward(float dist)
{
	int total = dist * EncPerCm;
	setMotorTarget(Lm, total, speed);
	waitUntilMotorStop(Lm);
}

void GoBackward(float dist)
{
	int total = -dist * EncPerCm;
	setMotorTarget(Lm, total, speed);
	nSyncedMotors = synchBC;
	waitUntilMotorStop(Lm);
}

task main()
{

	float dist = 50.0;


	MotorEncoderReset();
	GoForward(dist);
	MotorEncoderReset();
	GoBackward(dist);
}
