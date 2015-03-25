void followWall(int isFollowingRightWall, int targetDistance)
{       
        Serial.println("following wall");
        
        long spdAdjust, spdAdjustLeft, spdAdjustRight;
  
	long timeDiff = startTime - millis();
  
	if (!isFollowingRightWall)
	curError = distance[2] - targetDistance;

	else if (isFollowingRightWall)
	curError = distance[3] - targetDistance;
	
	derivative = (curError - prevError)/timeDiff; 

	spdAdjust = curError*kP + derivative*kD;

	if (!isFollowingRightWall)
	{
		if (spdAdjust > 500) spdAdjustRight = 250;
		else if (spdAdjust > 0) spdAdjustRight = spdAdjust%250; 
		else if (spdAdjust < -500) spdAdjustLeft = 250;
		else if (spdAdjust < 0) spdAdjustLeft = abs(spdAdjust)%250; 
	}
	
	else if (isFollowingRightWall)
	{
		if (spdAdjust > 500) spdAdjustLeft = 250;
		else if (spdAdjust > 0) spdAdjustLeft = spdAdjust%250;
		else if (spdAdjust < -500) spdAdjustRight = 250;  
		else if (spdAdjust < 0) spdAdjustRight = abs(spdAdjust) % 250;
	}
  
  controlServoMotion(0, stdSpd + spdAdjustLeft);
  controlServoMotion(1, stdSpd + spdAdjustRight);
  
  startTime = millis();   
  prevError = curError; 
}
