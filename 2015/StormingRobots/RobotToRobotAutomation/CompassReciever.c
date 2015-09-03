#pragma config(Sensor, S4,     wallSensor,     sensorSONAR)
#pragma config(Motor,  motorA,          claw,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorNXT, PIDControl, driveRight, encoder)
#pragma config(Sensor, S3,     compass,        sensorI2CHiTechnicCompass)

int clawm = motorA;
int lm = motorB;
int rm = motorC;

int totalX = 0;
int totalY = 0;

bool move = false;

const int turnRight = 4;
const int turnLeft = 1;

const int moveForward = 5;
const int moveBackward = 2;

const int goBack = 8;

const int stopMoving = 0;

int encoder = nMotorEncoder[motorB];

int getCompassValue(){
	return SensorValue[S3];
}

bool detectsWall(){
	int v = SensorValue[S4];
	if(v <= 25){
		return true;
		}else{
		return false;
	}
}

void moveLeft(){
	motor[rm] = -100;
	motor[lm] = 100;
	nMotorEncoder[motorB] = 0;
}

void moveRight(){
	motor[rm] = 100;
	motor[lm] = -100;
	nMotorEncoder[motorB] = 0;
}

void stopLeft(){
	motor[lm] = 0;
}

void stopRight(){
	motor[rm] = 0;
}

void moveF(){
	if(!move){
		nMotorEncoder[motorB] = 0;
		move = true;
	}
	nxtDisplayTextLine(6, "%d", nMotorEncoder[motorB]);

	encoder = nMotorEncoder[motorB];

	motor[lm] = 100;
	motor[rm] = 100;
}

void stopF(){
	motor[lm] = 0;
	motor[rm] = 0;
}

void moveBack(){
	if(!move)
	{
		nMotorEncoder[motorB] = 0;
		move = true;
	}
	nxtDisplayTextLine(6, "%d", nMotorEncoder[motorB]);

	encoder = nMotorEncoder[motorB];

	motor[lm] = -100;
	motor[rm] = -100;
}

void stopBack(){
	motor[lm] = 0;
	motor[rm] = 0;
}

void comeBack(){
	if(totalY == 0) totalY = 1;
	if(totalX == 0) totalX = 1;

	float rot = atan2(totalX, totalY) * 180 / PI;

	if(rot < 0){
		rot = 359+rot;
	}

	nxtDisplayTextLine(2, "Rot: %f", rot);

	while(getCompassValue() < rot){
		motor[motorB] = 100;
		motor[motorC] = -100;
	}
	nMotorEncoder[motorB] = 0;

	float dist = sqrt(totalX*totalX + totalY*totalY);

	nxtDisplayTextLine(3, "Dist: %f", dist);

	while(nMotorEncoder[motorB] < dist){
		moveF();
	}

	totalX = 0;
	totalY = 0;
}

void stopAll(){
	if(move){
		float rot = getCompassValue();

		float x = sinDegrees(rot) * encoder;
		float y = cosDegrees(rot) * encoder;

		nxtDisplayTextLine(0, "%d  %d %d", rot, x, y);
		nxtDisplayTextLine(1, "%d", encoder);

		totalX+=x;
		totalY+=y;

		nMotorEncoder[motorB] = 0;
		move = false;
	}

	stopBack();
	stopF();
	stopLeft();
	stopRight();
	motor[clawm] = 0;
}

void checkForMove(ubyte data){
	switch(data){
	case turnRight:
		nxtDisplayTextLine(7, "RIGHT");
		moveRight();
		break;
	case turnLeft:
		nxtDisplayTextLine(7, "LEFT");
		moveLeft();
		break;
	case moveForward:
		nxtDisplayTextLine(7, "FORWARD");
		moveF();
		break;
	case moveBackward:
		nxtDisplayTextLine(7, "BACKWARD");
		moveBack();
		break;
	case goBack:
		comeBack();
		break;
	case stopMoving:
		nxtDisplayTextLine(7, "!!!!!!STOP!!!!!!!!");
		stopAll();
		break;
	default:
		stopAll();
		break;
	}
}

void checkForRecieve(){
	if (cCmdMessageGetSize(mailbox19) > 0)
	{
		ubyte data[1];
		cCmdMessageRead(data, 1, mailbox19);

		checkForMove(data[0]);
	}
}

task main(){
	SensorType[S4] = sensorSONAR;
	while(true){
		if(totalY == 0) totalY = 1;
		if(totalX == 0) totalX = 1;

		float rot = atan(totalX / totalY) * 180 / PI;
		if(rot < 0){
			rot = 359+rot;
		}
		nxtDisplayTextLine(2, "Rot: %f", rot);

		float dist = sqrt(totalX*totalX + totalY*totalY);
		nxtDisplayTextLine(3, "Dist: %f", dist);

		nxtDisplayTextLine(4, "TotalX: %f", totalX);
		nxtDisplayTextLine(5, "TotalY: %f", totalY);

		checkForRecieve();

		ubyte data[2];
		data[0] = detectsWall();
		data[1] = nMotorEncoder[motorB];
		cCmdMessageWriteToBluetooth(data, 2, mailbox19);
	}
}
