//sensors and motors
// FIXME: Fix formatting!!! Please!!!
#pragma config(Sensor, S4,     wallSensor,     sensorSONAR)
#pragma config(Motor,  motorA,          claw,          tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorNXT, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorNXT, PIDControl, driveRight, encoder)

// FIXME: fix names: spelling and unreadable variable names
int clawm = motorA;
int lm = motorB;
int rm = motorC;

// FIXME: What is our naming convention for contstants!!!!!
//this is how the robot moves. 4 means right touch sensor is pressed, 1 is left, etc, etc
const int turnRight = 4;
const int turnLeft = 1;

const int moveForward = 5;
const int moveBackward = 2;
//FIXME: Do we need this semicolon here?
;
const int useClaw = 8;

const int stopMoving = 0;

//this is where it says if it detects wall
//FIXME: Change function to somthing more readable
bool detectsWall(){
	// FIXME: use sonar sensor by name
  // FIXME: change v to something people can understand and read
	int v = SensorValue[S4];
	if(v <= 25){
		return true;
		}else{
		return false;
	}
}

//this is where it configures the move functions
void moveClaw(){
	motor[clawm] = 100;
	wait1Msec(250);
	motor[clawm] = -100;
	wait1Msec(300);
}

void moveLeft(){
	motor[lm] = 100;
	motor[rm] = -100;
}

void moveRight(){
	motor[rm] = 100;
	motor[lm] = -100;
}

void stopLeft(){
	motor[lm] = 0;
}

void stopRight(){
	motor[rm] = 0;
}

void moveF(){
	motor[lm] = 100;
	motor[rm] = 100;
}

void stopF(){
	motor[lm] = 0;
	motor[rm] = 0;
}

void moveBack(){
	motor[lm] = -100;
	motor[rm] = -100;
}

void stopBack(){
	motor[lm] = 0;
	motor[rm] = 0;
}

void stopAll(){
	stopBack();
	stopF();
	stopLeft();
	stopRight();
	motor[clawm] = 0;
}

//TODO: Find out what this is
void checkForMove(){
	nxtDisplayTextLine(2,"%d",cCmdMessageGetSize(mailbox19));

	// If message size is > 0, there is a message
	if (cCmdMessageGetSize(mailbox19)>0)
	{
		// Declare an array of size 1, which contains unsighed bytes
		ubyte data[1];
		cCmdMessageRead(data, 1, mailbox19);

		switch(data[0]){
		case turnRight:
			moveRight();
			break;
		case turnLeft:
			moveLeft();
			break;
		case moveForward:
			moveF();
			break;
		case moveBackward:
			moveBack();
			break;
		case useClaw:
			moveClaw();
			break;
		case stopMoving:
			stopAll();
			break;
		default:
			stopAll();
			break;
		}
	}
}

task main(){
	//FIXME: Do we need this here?
	SensorType[S4] = sensorSONAR;
	while(true){
		//This checks if it should move or not.
		checkForMove();
		//if it detects the wall, send data.
		if(detectsWall()){
			// FIXME: Create a constant (same as in controller, see comment there)
			ubyte data[1];
			data[0] = 1;
			cCmdMessageWriteToBluetooth(data, 1, mailbox19);
		}
	}
}
