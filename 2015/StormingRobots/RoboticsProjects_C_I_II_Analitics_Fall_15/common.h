const float GR = 3.0/5.0;
const float Wdia = 3.5;
const float RobotBase = 15.6;
const float EncPerCm = (360.0*GR)/(Wdia*PI);
const float EncPerDeg = RobotBase*GR/Wdia;

const tMotor Lm = motorB;
const tMotor Rm = motorC;
const TSynchedMotors syncRmLm = synchCB;
const TSynchedMotors syncLmRm = synchBC;
