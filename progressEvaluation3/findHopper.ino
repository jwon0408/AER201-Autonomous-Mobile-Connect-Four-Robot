void findHopper(int isOnTheRight)
{
  if (!isOnTheRight) 
  { 
    int curDistToHopper = distance[2]/10;    
    
    if (curDistToHopper < 10)
    { 
      atLegFind++;
    }
  
    if (atLegFind > 3 && curDistToHopper > 25 && curDistToHopper < 35) 
    {
      passedLegFind++; 
    }
  
    if (passedLegFind > 25) 
    {
      leftServo.detach();
      rightServo.detach();
    
      //state++;   
    }
  }
  
  else if (isOnTheRight) 
  {
    int curDistToHopper = distance[3]/10; //[cm]
    
    if (curDistToHopper < 10)
    { 
      atLegFind++;
    }
  
    if (atLegFind > 3 && curDistToHopper > 25 && curDistToHopper < 35) 
    {
      passedLegFind++; 
    }
  
    if (passedLegFind > 25) 
    {
      leftServo.detach();
      rightServo.detach(); 
      
      //state++; 
    }
  }  
}
