void initializeVal() 
{
        Serial.println("initializeVal started");
        
	int const numSample = 5; 
	
        long proxEmptyTotal = 0;
        long ambEmptyTotal = 0;
        
	for (int i=0; i<numSample; i++)
	{
		proxEmptyTotal += readProximity();
                ambEmptyTotal += readAmbient();
		delay(5);
	}
	
        proxEmptyAvg = proxEmptyTotal/numSample;
        ambEmptyAvg = ambEmptyTotal/numSample;
       
       Serial.println("initializeVal finished"); 
}

void detectBall() 
{ 
  ambientValue = readAmbient();
  proximityValue = readProximity();
  //Serial.print(ambientValue, DEC);
  //Serial.print("\t");
  //Serial.println(proximityValue, DEC);

  if (proximityValue > proxEmptyAvg + whiteProxThreshold) 
  {
    Serial.println("White");
    board[curSensor*7+col] = 'w'; 
  }
  
  else if (ambientValue < ambEmptyAvg - blackAmbThreshold) 
  { 
    Serial.println("Black");
    board[curSensor*7+col] = 'b'; 
  }
  
  else 
  {
    Serial.println("Empty");
  }
}
