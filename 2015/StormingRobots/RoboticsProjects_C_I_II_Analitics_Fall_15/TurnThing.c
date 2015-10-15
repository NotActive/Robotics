//What the Wheel Diameter and Robot Base is.
const float Wdia = 5.6;
const float Rbase = 12.25;

//Encoder conversion tables.
const float EncPerCm = 360.0/(Wdia*PI);
const float CmPerEnc = Wdia*PI/360.0;
const float EncPerDeg = Rbase/Wdia;
const float OuterMotor = 100.0;
const float InnerCircle = 20.0;
const float OuterCircle = 50.0;
const float InnerOuter = InnerCircle/OuterCircle;
const float InnerMotor = OuterMotor*InnerOuter;

float CalcCost(float enc);


task main()
{

}
