void controlServoMotion(int isRightServo, long targetSpeed)
{  
  if (!isRightServo) 
  {
    leftServo.writeMicroseconds(1500 + targetSpeed);
  }
    
  else  
  {
    rightServo.writeMicroseconds(1500 - targetSpeed);
  }
}