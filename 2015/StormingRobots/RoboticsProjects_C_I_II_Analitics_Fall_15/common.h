const float GR = 3.0/5.0;
const float Wdia = 3.3;
const float RobotBase = 15.5;
const float EncPerCm = (360.0*GR)/(Wdia*PI);
const float EncPerDeg = RobotBase/Wdia;

const int Lm = motorB;
const int Rm = motorC;

float InnerCircleDiameter = 20.0;
