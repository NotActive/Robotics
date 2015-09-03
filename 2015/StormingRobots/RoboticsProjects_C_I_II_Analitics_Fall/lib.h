//What the Wheel Diameter and Robot Base is.
const float Wdia = 5.6;
const float Rbase = 12.25;

//Encoder conversion tables.
const float EncPerCm = 360.0/(Wdia*PI);
const float CmPerEnc = Wdia*PI/360.0;
const float EncPerDeg = Rbase/Wdia;

float CalcCost(float enc);
