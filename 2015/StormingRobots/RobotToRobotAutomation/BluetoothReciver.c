#include "BluetoothCommon.h"

int wallSensor = S4;
int Shooter = motorA;
int Lm = motorB;
int Rm = motorC;

//this is how the robot moves. 4 means right touch sensor is pressed, 1 is left, etc, etc
const int TurnRight = 4;
const int TurnLeft = 1;

const int MoveForward = 5;
const int MoveBackward = 2;
const int UseShooter = 8;

const int StopMoving = 0;

//this is where it says if it detects wall
bool DetectWall(){
	int SonarSensorValue = SensorValue[wallSensor];
	if(SonarSensorValue <= 25){
		return true;
		}else{
		return false;
	}
}

//this is where it configures the move functions
void moveShooter(){
	motor[Shooter] = 100;
}

void moveLeft(){
	motor[Lm] = 100;
	motor[Rm] = -100;
}

void moveRight(){
	motor[Rm] = 100;
	motor[Lm] = -100;
}

void stopLeft(){
	motor[Lm] = 0;
}

void stopRight(){
	motor[Rm] = 0;
}

void moveF(){
	motor[Lm] = 100;
	motor[Rm] = 100;
}

void stopF(){
	motor[Lm] = 0;
	motor[Rm] = 0;
}

void moveBack(){
	motor[Lm] = -100;
	motor[Rm] = -100;
}

void stopBack(){
	motor[Lm] = 0;
	motor[Rm] = 0;
}

void stopAll(){
	stopBack();
	stopF();
	stopLeft();
	stopRight();
	motor[Shooter] = 0;
}

void CheckForMove(){
	nxtDisplayTextLine(2,"%d",cCmdMessageGetSize(mailbox));

	// If message size is > 0, there is a message
	if (cCmdMessageGetSize(mailbox)>0)
	{
		// Declare an array of size 1, which contains unsighed bytes
		ubyte data[MessegeArraySize];
		cCmdMessageRead(data, MessegeArraySize, mailbox);

		switch(data[0]){
		case TurnRight:
			moveRight();
			break;
		case TurnLeft:
			moveLeft();
			break;
		case MoveForward:
			moveF();
			break;
		case MoveBackward:
			moveBack();
			break;
		case UseShooter:
			moveShooter();
			break;
		case StopMoving:
			stopAll();
			break;
		default:
			stopAll();
			break;
		}
	}
}

task main(){
	SensorType[wallSensor] = sensorSONAR;

	while(true){
		//This checks if it should move or not.
		CheckForMove();
		//if it detects the wall, send data.
		if(DetectWall()){
			ubyte data[MessegeArraySize];
			data[0] = WallDetected;
			cCmdMessageWriteToBluetooth(data, MessegeArraySize, mailbox);
		}
	}
}
