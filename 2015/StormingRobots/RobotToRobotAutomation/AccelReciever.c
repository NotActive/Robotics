#pragma config(Sensor, S4,     wallSensor,     sensorSONAR)
#pragma config(Motor,  motorA,          claw,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorNXT, PIDControl, driveRight, encoder)

int clawm = motorA;
int lm = motorB;
int rm = motorC;

bool detectsWall(){
	int v = SensorValue[S4];
	if(v <= 25){
		return true;
	}else{
		return false;
	}
}

void moveClaw(){
	motor[clawm] = 100;
	wait1Msec(250);
	motor[clawm] = -100;
	wait1Msec(300);
}

void checkForMove(){
	nxtDisplayTextLine(2,"%d",cCmdMessageGetSize(mailbox19));

	if (cCmdMessageGetSize(mailbox19)>0)
	{
		ubyte udata[4];
		cCmdMessageRead(udata, 4, mailbox19);

		byte data[4];

		data[0] = (byte) udata[0];
		data[1] = (byte) udata[1];
		data[2] = (byte) udata[2];
		data[3] = (byte) udata[3];

		if(data[0] == 1){
			moveClaw();
		}

		nxtDisplayTextLine(3, "%d %d %d %d", data[0], data[1], data[2], data[3]);
		nxtDisplayTextLine(1, "%d", data[0]);

		motor[leftMotor] = (-data[1]) + data[2];
		motor[rightMotor] = (-data[1]) - data[3];

		nxtDisplayTextLine(5, "%d    %d", ((-data[1]) + data[2]), ((-data[1]) - data[3]));
	}
}

task main(){
	SensorType[S4] = sensorSONAR;
	while(true){
		checkForMove();
		if(detectsWall()){
			ubyte data[1];
			data[0] = 1;
			cCmdMessageWriteToBluetooth(data, 1, mailbox19);
		}
	}
}
