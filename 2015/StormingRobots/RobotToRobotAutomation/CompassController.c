#pragma config(Sensor, S1,     left,           sensorTouch)
#pragma config(Sensor, S2,     right,          sensorTouch)

int getBitwiseControls(){
	int bo = SensorValue[S1] << 2;

	int bt;

	int bl;

	int br;

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

	return (bo | bt | bth | bl | br);
}

void writeData(){
	ubyte data[1];
	data[0] = getBitwiseControls();

	cCmdMessageWriteToBluetooth(data, 1, mailbox19);
}

void checkForWall(){
	ubyte data[2];
	if(cCmdMessageGetSize(mailbox19) > 0){
		cCmdMessageRead(data, 2, mailbox19);
		if(data[0] == 1){
			nxtDisplayTextLine(0, "WARNING:");
			nxtDisplayTextLine(2, "Robot is very");
			nxtDisplayTextLine(3, "close to the wall.");
			nxtDisplayTextLine(4, "I suggest you");
			nxtDisplayTextLine(5, "TURN AROUND!!!");
		}
	}
}

void checkMotors(){
	ubyte data[2];

	if(cCmdMessageGetSize(mailbox19) > 0){
		cCmdMessageRead(data, 2, mailbox19);
		nxtDisplayTextLine(1, "Encoders: %d", data[1]);
	}
}

task main(){
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorTouch;
	while(true){
		writeData();
		//checkForWall();
		checkMotors();
		wait10Msec(1);
	}
}
