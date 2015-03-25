void alignWithHopper(int isCornerHopper, int isOnTheRight)
{
	//Serial.println("alignWithHopper started");
	
	//Initialize values
	int distTolerance;
        
	if (!isCornerHopper) distTolerance = 3; 
	else distTolerance = 3;
        
        //Initialize motors 
	//leftServo.attach(leftServoPin);
	//rightServo.attach(rightServoPin);
	
	if (!isCornerHopper && !isOnTheRight)
	{
		//Turn left
		if (!doneAligning && (distance[4]/10+distTolerance) != distance[5]/10)
		{
		  controlServoMotion(0, -stdSpd); //leftServo backward 
		  controlServoMotion(1, stdSpd); //rightServo forward 
		}
		
		else 
		{
		  leftServo.detach(); 
                  rightServo.detach();
                  doneAligning = 1; 
                  //state++; 
		}
	}
	
	/*else if (!isCornerHopper && isOnTheRight)
	{
		//Turn right 
		if (distance[4] != (distance[5]+distTolerance))
		{
			controlServoMotion(0, stdSpd); //leftServo forward 
			controlServoMotion(1, -stdSpd); //rightServo backward
		}
		
		else
		{
			leftServo.detach(); 
                        rightServo.detach();
		}
	}
	
	else if (isCornerHopper && !isOnTheRight)
	{
		//Turn left 
		if ((distance[4]+distTolerance) != distance[5])
		{
			controlServoMotion(0, -slowServoSpd); //leftServo backward 
			controlServoMotion(1, fastServoSpd); //rightServo forward 
		} 
		
		else
		{
			leftServo.detach(); 
                        rightServo.detach();
		}
	}
	
	else if (isCornerHopper && isOnTheRight)
	{
		//Turn right 
		if (distance[4] != (distance[5]+distTolerance))
		{
			controlServoMotion(0, fastServoSpd); //leftServo forward 
			controlServoMotion(1, -slowServoSpd); //rightServo backward
		}
		
		else
		{
			leftServo.detach(); 
                        rightServo.detach();
		}
         }*/
      
      //Serial.println("alignWithHopper finished");
}
