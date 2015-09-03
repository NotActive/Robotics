#pragma config(Sensor, S1,     left,           sensorTouch)
#pragma config(Sensor, S2,     right,          sensorTouch)

#include "Accelerometer.h"

const tSensors Accel = S4;

int oldX, oldY, oldZ;

const int turnRange = 75;

int getForwardPower(){
	int xVal;
	int yVal;
	int zVal;

	#ifdef V3_5up
        if (getAccelReading(Accel, &xVal,&yVal,&zVal))
	#else
        if (getAccelReading(Accel, xVal,yVal,zVal))
	#endif

	oldX = xVal;
	oldY = yVal;
	oldZ = zVal;

	int returnVal;

	if(xVal > 100){
		returnVal = 100;
	}else if(xVal < -100){
		returnVal = -100;
	}else{
		returnVal = xVal;
	}

	return returnVal;
}

int getTurnPower(){
	int xVal;
	int yVal;
	int zVal;

	#ifdef V3_5up
        if (getAccelReading(Accel, &xVal,&yVal,&zVal))
	#else
        if (getAccelReading(Accel, xVal,yVal,zVal))
	#endif

	int returnVal;

	if(yVal > 100){
		nxtDisplayTextLine(6, "right");
		returnVal = 100;
	}else if(yVal < -100){
		returnVal = -100;
	}else{
		returnVal = yVal;
	}

	return returnVal;
}

int getClaw(){
	if(nNxtButtonPressed == 3){
		return 1;
	}else{
		return 0;
	}
}

int getLeft(int power){
	if(power < 0 && power >= -100){
		return power;
	}else if(power >= 0){
		return 0;
	}else{
		return -100;
	}
}

int getRight(int power){
	if(power > 0 && power <= 100){
		return power;
	}else if(power <= 0){
		return 0;
	}else{
		return 100;
	}
}

void writeData(){
	ubyte data[4];

	data[0] = getClaw();
	data[1] = getForwardPower();
	data[2] = getLeft(getTurnPower());
	data[3] = getRight(getTurnPower());

	//nxtDisplayTextLine(1, "%d %d %d %d", data[0], data[1], data[2], data[3]);

	cCmdMessageWriteToBluetooth(data, 4, mailbox19);
}

void checkForWall(){
	ubyte data[1];
	if(cCmdMessageGetSize(mailbox19) > 0){
		cCmdMessageRead(data, 1, mailbox19);
		if(data[0] == 1){
			nxtDisplayTextLine(0, "WARNING:");
			nxtDisplayTextLine(2, "Robot is very");
			nxtDisplayTextLine(3, "close to the wall.");
			nxtDisplayTextLine(4, "I suggest you");
			nxtDisplayTextLine(5, "TURN AROUND!!!");
		}
	}
}

task main(){
	accel_init(Accel);

	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorTouch;
	while(true){
		writeData();
		checkForWall();
	}
}
