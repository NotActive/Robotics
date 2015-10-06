/*
-----------------------------------------------
----------------Program made by----------------
-----------------Peter Romayev-----------------
-----------------------------------------------
*/

task main()
{

	//varibles!!!!!!!!
	int offset = 10;
	int noseOffset = 0;


	//draws a mouth
	drawRect(5 + offset,12,65 + offset,8);

	//
	//draws eyes
	//

	//left
	drawEllipse(10 + offset,50,20 + offset,35);
	//right
	drawEllipse(50 + offset,50,60 + offset,35);

	while (true)
	{
		if (noseOffset == 0)
		{
			noseOffset = 5;
		}
		else
		{
			noseOffset = 0;
		}

		//draws nose
		drawEllipse(30 + offset,30 + noseOffset,40 + offset,20 + noseOffset);

		wait1Msec(1000);

		eraseEllipse(30 + offset,30 + noseOffset,40 + offset,20 + noseOffset);

	}

}
