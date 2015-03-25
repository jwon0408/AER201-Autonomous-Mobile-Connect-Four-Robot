void deliverBall(int destCol)
{	 
	//Serial.println("deliverBall started");
       
        deliverServo.attach(deliverServoPin);
        
        //Position the tube
        deliverServo.write(middleAngle + relAngle[destCol]);
        delay(3000);
	
	//Move the tube back to the initial position 
        deliverServo.write(initialAngle);
        delay(2000);

        deliverServo.detach(); 
	//Serial.println("deliverBall finished");
}
