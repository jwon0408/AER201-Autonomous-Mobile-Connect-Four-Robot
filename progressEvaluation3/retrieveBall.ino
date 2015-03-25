void retrieveBall()
{
	//Serial.println("retrieveBall started");
                
        //Initialize Values 
        int distToMiddleLegIn1 = 60; //Check this first  
        int distToMiddleLegOut = 210; 
        int distToMiddleLegIn2 = 120;
	
        switch (retrieveState) {    
        case 0: //Not done driving back 
        
        if (distance[0] < distToMiddleLegOut) 
        {
          leftServo.attach(leftServoPin);
          rightServo.attach(rightServoPin);
          
          controlServoMotion(0, -stdSpd);
          controlServoMotion(1, -stdSpd);
        }
        
        else 
        {
          leftServo.detach();
          rightServo.detach();
          
          delay(1000);
          retrieveState++;
        }
        
        break;
       
        case 1: //Done driving back
         
        retrieveServo.write(150);
        delay(1000);
        retrieveState++;
        
        break;  
          
        case 2: //Not done retrieving
        
        if (distance[0] > distToMiddleLegIn1) 
        { 
          leftServo.attach(leftServoPin);
          rightServo.attach(rightServoPin);
             
           //Drive in 
           controlServoMotion(0, stdSpd);
           controlServoMotion(1, stdSpd);
        }
        
        else 
        {
          leftServo.detach();
          rightServo.detach();
          
          delay(1000);
          retrieveState++; 
        }
        
        break; 
          
        case 3: //Done retrieving 
        
        if (distance[0] < distToMiddleLegOut) 
        {    
          leftServo.attach(leftServoPin);
          rightServo.attach(rightServoPin);
            
          //Drive out
          controlServoMotion(0, -stdSpd);
          controlServoMotion(1, -stdSpd);
        }
            
        else if (distance[0] > distToMiddleLegOut) 
        {
          leftServo.detach();
          rightServo.detach();
          
          delay(1000);
            
          retrieveServo.write(0);
          delay(1000);
            
          retrieveServo.detach(); 
          retrieveState++;
        }
         
        break;
       
        case 4://Drive back into align with wall   
        if (distance[0] > distToMiddleLegIn2) 
        { 
          leftServo.attach(leftServoPin);
          rightServo.attach(rightServoPin);
             
           //Drive in 
           controlServoMotion(0, stdSpd);
           controlServoMotion(1, stdSpd);
        }
        
        else 
        {
          leftServo.detach();
          rightServo.detach();
          state++; 
        }
        
        break; 
        }
        
	//Decrement the numBalls of the hopper
	  
	//Serial.println("retrieveBall finished");
}
