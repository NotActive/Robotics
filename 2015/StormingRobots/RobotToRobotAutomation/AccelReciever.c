const int UltrasonicSensor = S4;
const int Shooter = motorA;
const int LeftMotor = motorB;
const int RightMotor = motorC;

#include "AccelCommon.h"

bool DetectWall(){
	int v = SensorValue[UltrasonicSensor];
	if(v <= 25){
		return true;
	}else{
		return false;
	}
}

//FIXME: Fix name
void Shoot(){
	motor[Shooter] = 100;
}

void checkFoRightMotorove(){
	nxtDisplayTextLine(2,"%d",cCmdMessageGetSize(mailbox));

	if (cCmdMessageGetSize(mailbox)>0)
	{
		ubyte udata[MessageArraySize];
		cCmdMessageRead(udata, MessageArraySize, mailbox);

		byte data[MessageArraySize];

		data[0] = (byte) udata[0];
		data[1] = (byte) udata[1];
		data[2] = (byte) udata[2];
		data[3] = (byte) udata[3];

		if(data[0] == 1){
			Shoot();
		}

		motor[LeftMotor] = (-data[1]) + data[2];
		motor[RightMotor] = (-data[1]) - data[3];

		nxtDisplayTextLine(5, "%d    %d", ((-data[1]) + data[2]), ((-data[1]) - data[3]));
	}
}

task main(){
	SensorType[UltrasonicSensor] = sensorSONAR;
	while(true){
		checkFoRightMotorove();
		if(DetectWall()){
			ubyte data[1];
			data[0] = 1;
			cCmdMessageWriteToBluetooth(data, 1, mailbox);
		}
	}
}
