
#define LeLEYE S1
#define REYE S3
#define  LM  motorA
#define  RM  motorB
#define USF  S4
#define USS  S2
#define Tilted (xVal > 50)

const int Base=17.5;
int LeftEyeWhite=45;
int LeftEyeBlack=36;
int RightEyeWhite=40;
int RightEyeBlack=37;
int SilverR=225;
int SilverL=225;
int SL=(2*SilverL+LeftEyeWhite)/3;
int SR=(2*SilverR+RightEyeWhite)/3;
int AvLeft=(LeftEyeBlack+LeftEyeWhite)/2;
int AvRight=(RightEyeBlack+RightEyeWhite)/2;
bool Tilted=false;
int xVal, yVal, zVal;

void init()
{
  SensorType[LEYE]=sensorLightActive;
  SensorType[REYE]=sensorLightActive;
  SensorType[USF]=sensorSONAR;
  SensorType[USS]=sensorSONAR;
}

void goFor(int cm)
{
  float target=cm/(PI*5.6/360);
  nMotorEncoder[LM]=0;
  nMotorEncoder[RM]=0;
  nSyncedMotors=synchAB;
  nSyncedTurnRatio=100;
  nMotorEncoderTarget[LM]=target;
  motor[LM]=30;
  target = target -10;
  while(nMotorEncoder[LM]<target)
  {
    wait1Msec(10);
  }
  wait1Msec(1000);
  motor[LM]=0;
  wait1Msec(10);
  nSyncedMotors=synchNone;
}

void goBack(int cm)
{
  float target=(float)cm/(PI*5.6/360);
  nMotorEncoder[LM]=0;
  nMotorEncoder[RM]=0;
  target=-1*target;
  nSyncedMotors=synchAB;
  nSyncedTurnRatio=100;
  nMotorEncoderTarget[LM]=target;
  motor[LM]=-30;
  target = target+10;
  while(nMotorEncoder[LM]>target)
  {
    wait1Msec(10);
  }
  wait1Msec(1000);
  motor[LM]=0;
  wait1Msec(10);
  nSyncedMotors=synchNone;
}

void leftTurn(int body)
{
  // pad 5 degrees due to the encodertarget bug
  float turntarget=(float)body*Base/5.6+10;
  nMotorEncoder[RM]=0;
  nSyncedMotors=synchBA;
  nSyncedTurnRatio=-100;
  nMotorEncoderTarget[RM]=turntarget;
  motor[RM]=30;
  turntarget = turntarget- 10;
  while(nMotorEncoder[RM]<turntarget)
  {
    wait1Msec(10);
  }
  wait1Msec(1000);
  motor[RM]=0;
  wait1Msec(10);
  nSyncedMotors=synchNone;
}

void rightTurn(int body)
{
  float turntarget=(float)body*Base/5.6+10;
  nMotorEncoder[LM]=0;
  nSyncedMotors=synchAB;
  nSyncedTurnRatio=-100;
  nMotorEncoderTarget[LM]=turntarget;
  motor[LM]=30;
  turntarget = turntarget -10;
  while(nMotorEncoder[LM]<turntarget)
  {
    wait1Msec(10);
  }
  wait1Msec(1000);
  motor[LM]=0;
  wait1Msec(10);
  nSyncedMotors=synchNone;
}

void MissionImpossible()
{
  //        100 = Tempo
  //          6 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  880,    7); wait1Msec(  75);  // Note(D, Duration(32th))
  PlayTone(  933,    7); wait1Msec(  75);  // Note(D#, Duration(32th))
  PlayTone(  988,    7); wait1Msec(  75);  // Note(E, Duration(32th))
  PlayTone( 1047,    7); wait1Msec(  75);  // Note(F, Duration(32th))
  PlayTone( 1109,    7); wait1Msec(  75);  // Note(F#, Duration(32th))
  PlayTone( 1175,    7); wait1Msec(  75);  // Note(G, Duration(32th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(    0,   27); wait1Msec( 300);  // Note(Rest, Duration(Eighth))
  PlayTone( 1047,   14); wait1Msec( 150);  // Note(F, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1109,   14); wait1Msec( 150);  // Note(F#, Duration(16th))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  880,  108); wait1Msec(1200);  // Note(D, Duration(Half))
  PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  831,  108); wait1Msec(1200);  // Note(C#, Duration(Half))
  PlayTone(    0,    7); wait1Msec(  75);  // Note(Rest, Duration(32th))
  PlayTone( 1398,   14); wait1Msec( 150);  // Note(A#, Duration(16th))
  PlayTone( 1175,   14); wait1Msec( 150);  // Note(G, Duration(16th))
  PlayTone(  784,  108); wait1Msec(1200);  // Note(C, Duration(Half))
  PlayTone(    0,   14); wait1Msec( 150);  // Note(Rest, Duration(16th))
  PlayTone(  932,   14); wait1Msec( 150);  // Note(A#5, Duration(16th))
  PlayTone(  784,   14); wait1Msec( 150);  // Note(C, Duration(16th))
  return;
}



void headL()
{
  nMotorEncoder[motorC]=0;

  while(nMotorEncoder[motorC]>-2100)
  {
    motor[motorC]=-100;
  }
  motor[motorC]=0;
}

void headR()
{
  nMotorEncoder[motorC]=0;
  while(nMotorEncoder[motorC]<2100)
  {
    motor[motorC]=100;
  }
  motor[motorC]=0;
}

#endif
