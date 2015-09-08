// Creates sensors
// S1 - left sensor: go left
// S2 - right sensor: go right
// both pressed: go forward
#pragma config(Sensor, S1, left,  sensorTouch)
#pragma config(Sensor, S2, right, sensorTouch)

int getBitwiseControls(){
	int bo = SensorValue[S1] << 2;
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
	int bth = SensorValue[S2] << 0;
	int mth;

	return (bo | bt | bth | bl | br);
}

void writeData(){
	// Get user input, i.e., which sensor(s) is pressed
	ubyte data[1] = getBitwiseControls();
	// TODO: Figure out why are we using mailbox19? Try using default or mailbox1
	// FIXME: Can we create a constant for mailbox?
	// Send user input to bluetooth receiver
	cCmdMessageWriteToBluetooth(data, 1, mailbox19);
}

// Checks for wall. If the ultrasonic sensor gets close to the wall, it will display a messege on the screen.
void checkForWall(){
	ubyte data[1];
	// Do we have a message?
	if(cCmdMessageGetSize(mailbox19) > 0){
		// We do, let's read it
		cCmdMessageRead(data, 1, mailbox19);
		// FIXME: Create a constant for "1", which means robot is close to the wall
		// Print a warning messge
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
	// FIXME: Do we need this here? Test and remove if non needed
	// SensorType[S1] = sensorTouch;
	// SensorType[S2] = sensorTouch;
	while(true){
		writeData();
		checkForWall();
		wait10Msec(1);
		eraseDisplay();
	}
}
