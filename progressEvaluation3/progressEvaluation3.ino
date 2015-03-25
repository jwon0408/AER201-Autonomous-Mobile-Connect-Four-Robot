//getDistance Settings
//0:front, 1:back, 2:bottom left, 3:bottom right, 4:top left, 5:top right 
int const distanceTrigPins[6] = {27, 23, 25, 50, 29, 52};
int const distanceEchoPins[6] = {26, 22, 24, 51, 28, 53};
long distance[6];

//controlServoMotion Settings 
#include <Servo.h> 
Servo leftServo, rightServo;
#define leftServoPin 6 
#define rightServoPin 5
long const stdSpd = 250;

//followBall Settings 
long curError;
long prevError = 0;   
long derivative;
long const kP = 4;
long const kD = 0.03;
long startTime = 0;

//controlBall Settings 
#define retrieveServoPin 13
#define liftServoPin 3
#define deliverServoPin 4 
Servo retrieveServo, liftServo, deliverServo;
int middleAngle = 87; 
int initialAngle = middleAngle-12; 
int relAngle[7] = {-71, -48, -21, 3, 30, 58, 80};

//Moving Forward and Turning Settings
int c0TurnR_LStop = 40;  
int c1FllwRWall_FStop = 40;
int c2TurnL_BStop = 150;
int c3FllwRWall_FStop = 150;
int c4TurnL_BStop = 130;
int c11FllwLWall_FStop = 40;
int c12TurnR_LStop = 50;
int c13FllwLWall_FStop = 40;
int c14TurnR_BStop = 150; 
int c17FllwLWall_FStop = 420;

//Hopper Settings 
int atLegFind = 0; 
int passedLegFind = 0; 
int doneAligning = 0;  
int retrieveState = 0; 
int atLegTurn = 0;
int passedLegTurn = 0;

//detectBoard Settings 
int col = 0;
int stopDistanceBack = 61;
int stopDistanceFront[] = {65, 60, 55, 51, 47, 43};
#include <Wire.h>
#define pinClockA 40
#define pinClockB 42
#define pinClockC 44
#define pinDataA 34
#define pinDataB 36
#define pinDataC 38
#define VCNL4000_ADDRESS 0x13
#define COMMAND_0 0x80  
#define PRODUCT_ID 0x81 
#define IR_CURRENT 0x83  
#define AMBIENT_PARAMETER 0x84  
#define AMBIENT_RESULT_MSB 0x85  
#define AMBIENT_RESULT_LSB 0x86  
#define PROXIMITY_RESULT_MSB 0x87  
#define PROXIMITY_RESULT_LSB 0x88  
#define PROXIMITY_FREQ 0x89  
#define PROXIMITY_MOD 0x8A
int waitStartTime;
int ambientValue, proximityValue, proxEmptyAvg, ambEmptyAvg;
int const whiteProxThreshold = 100;
int const blackAmbThreshold = 200; 
int curDistance, curSensor;  

//decideNextPlay settings 
typedef struct 
{
	int meBC; 
	int oppoBC; 
	int meNBLC[5]; 
	int oppoNBLC[5];  
} hScoreInfo;
char const me = 'w'; 
char const oppo = 'b'; 
char board[6*7]; 
int topOfColumn[] = {6, 6, 6, 6, 6, 6, 6};
hScoreInfo myhScoreInfo;
int const initialDepth = 3; 
int const relativeSpd = 1;

int state = 4;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  
  for (int i=0; i<6; i++) 
  {
    pinMode(distanceTrigPins[i], OUTPUT);
    pinMode(distanceEchoPins[i], INPUT);
  } 
  
  initializeBoard(); 
  initializehScoreInfo();
  
  /*manuallyUpdateBoard();
  updateTopOfColumn();
  updateBC(); 
  updateNBLC_col();
  updateNBLC_row();
  updateNBLC_diag();*/
}

void loop() 
{
  for (int i=0; i<6; i++) 
  {
    distance[i] = getDistance(distanceTrigPins[i], distanceEchoPins[i]);
  }
  
  Serial.print("state ");
  Serial.println(state);
   
  switch (state){  
  
  /*case -1: //Drive forward a little 
  
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  controlServoMotion(0, stdSpd); 
  controlServoMotion(1, stdSpd);
  delay(200);
  leftServo.detach();
  rightServo.detach();
  state++;
  break; 
  
  case 0: //Turn right 
  
  if (distance[3] > c0TurnR_LStop)
  {
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    controlServoMotion(0, stdSpd); //left wheel forward
    controlServoMotion(1, -stdSpd); //right wheel backward 
  }

  else 
  {
    leftServo.detach(); 
    rightServo.detach();
    state++;
  } 
  
  break;   
  
  case 1: //Follow right wall
  
  if (distance[0] > c1FllwRWall_FStop) 
  {
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    followWall(1, 50); 
  }
  
  else 
  {
    leftServo.detach(); 
    rightServo.detach();
    state++;
  }
  
  break; 
  
  //TEST THIS!!!
  case 2: //Turn left (not corner hopper) 
  
  if (distance[1] > c2TurnL_BStop)
  {
    Serial.println("turning left");
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    controlServoMotion(0, stdSpd); //left wheel forward  
    controlServoMotion(0, -stdSpd); //right wheel backwards 
  }

  else 
  {
    leftServo.detach(); 
    rightServo.detach();
    state++;
  }
  
  break;  
  
  case 3: //Follow right wall 
  
  if (distance[0] > c3FllwRWall_FStop) 
  {
    followWall(1, 50);
  }
  
  else 
  {
    leftServo.detach();
    rightServo.detach();
    state++;
  }
  
  break;*/ 
  
  case 4: //Turn left (corner hopper) 
  
  if (distance[1] > c4TurnL_BStop) 
  {
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    controlServoMotion(0, -stdSpd); //left wheel backward 
    controlServoMotion(1, stdSpd); //right wheel forward 
  }
  
  else 
  {
    leftServo.detach();
    rightServo.detach();
    state++;
  }
  
  break;
  
  case 5: //Follow right wall and find the hopper on the left
  
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);  
  findHopper(0); 
  followWall(1, 200);
  
  break;
  
  case 6: //Align with the hopper (not corner) and the hopper on the left 
  
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  alignWithHopper(0, 0);
  
  break;
  
  //MAKE SURE THE DIRECTION AND THE DURATION IS RIGHT!!!
  case 7: //Lower the ball 
  
  liftServo.attach(liftServoPin);
  liftServo.writeMicroseconds(2000); 
          
  for (int duration=0; duration<68; duration++)
  {
      delay(125);
  }
          
  liftServo.detach(); 
  state++;
   
  case 8: //Retrieve Ball
  
  retrieveBall();
  
  break; 
  
  //MAKE SURE THE DIRECTION AND THE DURATION OS RIGHT!!!
  case 9: //Lift the ball 
 
  liftServo.attach(liftServoPin);
  liftServo.writeMicroseconds(1000); 
          
  for (int duration=0; duration<68; duration++)
  {
    delay(125);
  }
          
  liftServo.detach(); 
  state++;
  
  case 10: //Align with the wall(i.e. turn left)  
  
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);
  
  turnAwayFromHopper(1);
  
  controlServoMotion(0, -stdSpd); //left wheel backward 
  controlServoMotion(1, stdSpd); //right wheel forward 
  
  case 11: //Follow left wall
  
  if (distance[0] > c11FllwLWall_FStop) 
  {
    followWall(0, 200);
  }
  
  else 
  {
    leftServo.detach();
    rightServo.detach();
    state++;
  }
  
  break;
    
  case 12: //Turn right (corner hopper)
  
  if (distance[2] > c12TurnR_LStop) 
  {
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    
    controlServoMotion(0, stdSpd); //left forward  
    controlServoMotion(1, -stdSpd); //right wheel backward  
  }
  
  else 
  {
    leftServo.detach();
    rightServo.detach();
    state++;
  }
  
  break;
   
  case 13: //Follow left wall
  
  if (distance[0] > c13FllwLWall_FStop) 
  {
    followWall(0, 60);
  }
  
  else 
  {
    leftServo.detach();
    rightServo.detach();
    state++;
  }
  
  break;
  
  //CHECK THIS!!!  
  case 14: //Turn right (no corner hopper) 
  
  if (distance[1] > c14TurnR_BStop)
  {
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    
    controlServoMotion(0, stdSpd); //left wheel forward 
    controlServoMotion(0, -stdSpd); //right wheel backward 
  }

  else 
  {
    leftServo.detach(); 
    rightServo.detach();
    state++;
  }
  
  break; 
  
  case 15: //Follow left wall and align with the game detection board
  curDistance = distance[1]/10;
  
  Serial.println(curDistance);
  
  if (curDistance < stopDistanceBack)
  {
    leftServo.attach(leftServoPin);
    rightServo.attach(rightServoPin);
    followWall(0,45);
  }  
  
  else 
  {
    leftServo.detach(); 
    rightServo.detach();
   
    for (curSensor=0; curSensor<6; curSensor++) 
    {
      Serial.print("Sensor ");
      Serial.println(curSensor);
    
      chooseClockChannel(curSensor);
      chooseDataChannel(curSensor);
      Serial.println("passed multiplexer");
    
      byte temp = readByte(PRODUCT_ID);
      if (temp == 0) 
      {
        Serial.print("continue");
        continue;
      } 
      Serial.print("temp: ");
      Serial.println(temp);
    
      if (temp != 0x11)  // Product ID Should be 0x11
      {
        Serial.print("Something's wrong. Not reading correct ID: 0x");
        Serial.println(temp, HEX);
      }
    
      else
      Serial.println("VNCL4000 Online...");
    
      writeByte(AMBIENT_PARAMETER, 0x0F);  
      writeByte(IR_CURRENT, 20);  
      writeByte(PROXIMITY_FREQ, 2);  
      writeByte(PROXIMITY_MOD, 0x81);  

      if (col == 0 && curSensor == 0)   
      {
        initializeVal();
      }
     
      detectBall();      
    }
    
    delay(1000);
    col++;
    state++; 
  }
  
  break;
  
  case 16: //Passed the col 0
  
  curDistance = distance[0]/10;
  
  if (curDistance < stopDistanceFront[col] && curDistance > stopDistanceFront[col+1])
  {
    leftServo.detach(); 
    rightServo.detach();
   
    for (curSensor=0; curSensor<6; curSensor++) 
    {
      Serial.print("Sensor ");
      Serial.println(curSensor);
    
      chooseClockChannel(curSensor);
      chooseDataChannel(curSensor);
      Serial.println("passed multiplexer");
    
      byte temp = readByte(PRODUCT_ID);
      if (temp == 0) 
      {
        Serial.print("continue");
        continue;
      } 
      Serial.print("temp: ");
      Serial.println(temp);
    
      if (temp != 0x11)  // Product ID Should be 0x11
      {
        Serial.print("Something's wrong. Not reading correct ID: 0x");
        Serial.println(temp, HEX);
      }
    
      else
      Serial.println("VNCL4000 Online...");
    
      writeByte(AMBIENT_PARAMETER, 0x0F);  
      writeByte(IR_CURRENT, 20);  
      writeByte(PROXIMITY_FREQ, 2);  
      writeByte(PROXIMITY_MOD, 0x81);  

      if (col == 0 && curSensor == 0)   
      {
        initializeVal();
      }
     
      detectBall();      
    }
    
    delay(1000);
    col++;
    
    if (col != 6)
    { 
      leftServo.attach(leftServoPin);
      rightServo.attach(rightServoPin);
    }
   
    else 
    {
      //state++;
    } 
  }

  else 
  {
    followWall(0,45);
  }  
  
  break;
  
  case 17: //Move forward following the left wall to align with the game board 
  
  if (distance[0] > c17FllwLWall_FStop) 
  {
    followWall(0, 45);
  }
  
  else 
  {
    leftServo.detach();
    rightServo.detach();
    //state++;
  }
  
  break;
  
  case 18: //Align with the game board 
  
  controlServoMotion(0, 0); //left wheel stationary 
  controlServoMotion(1, -stdSpd); //right wheel backward
  for (int i=0; i<10; i++)
  {
  delay(500);
  }
  leftServo.detach();
  rightServo.detach();
  state++;
  break; 
  
  case 19: //Decide the next play and align the tube 
  
  int nextMoveCol = negamax_NA(-1, 1, initialDepth, relativeSpd, 1); 
  deliverBall(nextMoveCol);
  makeMove(nextMoveCol, me);
  printBoard(); 
  state++; 
  break; 
  }  
}


