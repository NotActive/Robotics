task main()

{

 int stations = 0;

 float cost = 0;

 // forward until it sess a station

 while(stations<3)
 {
  while (SensorValue[S4] == 10)

  {
   motor[motorB] = speed;
   motor[motorC] = speed;
  }
 CalcCost(enc);
 }
}
