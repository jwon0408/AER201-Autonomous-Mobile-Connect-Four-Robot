void turnAwayFromHopper(int willBeOnTheRight)
{
  if (willBeOnTheRight) 
  { 
    int curDistToHopper = distance[2]/10; 
    
    if (curDistToHopper < 10)
    { 
      atLegTurn++;
    }
  
    if (atLegTurn > 3 && curDistToHopper > 25 && curDistToHopper < 35) 
    {
      passedLegTurn++; 
    }
  
    if (passedLegTurn > 1) 
    {
      leftServo.detach();
      rightServo.detach();
      
      //state++;   
    }
  }
  
  else if (!willBeOnTheRight) 
  {
    int curDistToHopper = distance[3]/10; 
    
    if (curDistToHopper < 10)
    {
      atLegTurn++;
    }
  
    if (atLegTurn > 3 && curDistToHopper > 25 && curDistToHopper < 35) 
    {
      passedLegTurn++; 
    }
  
    if (passedLegTurn > 1) 
    {
      leftServo.detach();
      rightServo.detach(); 
      
      //state++;
    }
  }  
}
