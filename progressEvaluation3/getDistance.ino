long getDistance(int trigPin, int echoPin)
{
	long duration;

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	
	return duration/5.82;
}
