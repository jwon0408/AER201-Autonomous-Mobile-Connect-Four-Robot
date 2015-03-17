#define leftTrigPin 47
#define leftEchoPin 46
#define rightTrigPin 52
#define rightEchoPin 53

#include <Servo.h> 
Servo leftServo, rightServo;

#define leftServoPin 13
#define rightServoPin 12

long tempDistance, curDistance;  
long curError, prevError;  
long integral = 0; 
long derivative;
long const kP = 3.75;
long const kI = 0;
long const kD = 0.02;
long spdAdjust, spdAdjustLeft, spdAdjustRight;

long const targetDistance = 200;
long startTime = 0; 
long timeDiff;
long const stdSpeed = 250;

long getDistance(int trigPin, int echoPin);
void controlServoMotion(int isRightMotor, long motorSpeed);

void setup()
{
  Serial.begin(9600);
  
  pinMode(leftTrigPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightTrigPin, OUTPUT);
  pinMode(rightEchoPin, INPUT);
  
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
}

void loop() 
{
  //Follow left wall 
  curDistance = getDistance(leftTrigPin, leftEchoPin);
  
  //Follow right wall 
  //curDistance = getDistance(rightTrigPin, rightEchoPin);
  
  /*if (abs(tempDistance-curDistance) > changeThreshold) 
  {
    curDistance = tempDistance; 
  }*/
  
  Serial.print("curDistance: ");
  Serial.println(curDistance);
  
  timeDiff = startTime - millis();
  
  /*PID*/ 
  curError = curDistance - targetDistance; 
  
  
  integral += curError*timeDiff; 
  
  derivative = (curError - prevError)/timeDiff; 

  spdAdjust = curError*kP + integral*kI + derivative*kD;

  if (spdAdjust > 500) 
  {
    spdAdjust = 250; 
  } 
  
  else 
  {
    spdAdjust = spdAdjust % 250; 
  } 
  
  //Follow left wall
  controlServoMotion(0, stdSpeed);
  controlServoMotion(1, stdSpeed + spdAdjust);
  
  //Follow right wall
  //controlServoMotion(0, stdSpeed + spdAdjust);
  //controlServoMotion(1, stdSpeed);
  
  startTime = millis();   
  prevError = curError; 
}
