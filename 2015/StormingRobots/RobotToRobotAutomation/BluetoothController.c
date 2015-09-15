#include "BluetoothCommon.h"

// Creates sensors
// S1 - left sensor: go left
// S2 - right sensor: go right
// both pressed: go forward


int left = S1;
int right = S2;

int getBitwiseControls(){
	int bo = SensorValue[left] << 2;
	int mo;

	int bt;
	int mt;

	int bl;
	int ml;

	int br;
	int mr;
	if(nNxtButtonPressed == 3){
		bt = 1 << 1;
		}else{
		bt = 0 << 1;
	}
	if(nNxtButtonPressed == 1) {
		bl = 1 << 4;
		}else{
		bl = 0 << 4;
	}
	if(nNxtButtonPressed == 2) {
		br = 1 << 3;
		}else{
		br = 0 << 3;
	}
	int bth = SensorValue[right] << 0;
	int mth;

	return (bo | bt | bth | bl | br);
}

void writeData(){
	// Get user input, i.e., which sensor(s) is pressed
	ubyte data[MessegeArraySize] = getBitwiseControls();
	// TODO: Figure out why are we using mailbox19? Try using default or mailbox1
	// FIXME: Can we create a constant for mailbox?
	// Send user input to bluetooth receiver
	cCmdMessageWriteToBluetooth(data, MessegeArraySize, mailbox);
}

// Checks for wall. If the ultrasonic sensor gets close to the wall, it will display a messege on the screen.
void checkForWall(){
	ubyte data[MessegeArraySize];
	// Do we have a message?
	if(cCmdMessageGetSize(mailbox) > 0){
		// We do, let's read it
		cCmdMessageRead(data, MessegeArraySize, mailbox);
		// Print a warning messge
		if(data[0] == WallDetected){
			nxtDisplayTextLine(0, "    WARNING:");
			nxtDisplayTextLine(2, "   OBJECT SEEN");
		}
	}
}

task main(){

	SensorType[left] = sensorTouch;
	SensorType[right] = sensorTouch;
	while(true){
		writeData();
		checkForWall();
		wait10Msec(1);
		eraseDisplay();
	}
}
