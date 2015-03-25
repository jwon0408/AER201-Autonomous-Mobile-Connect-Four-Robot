void chooseClockChannel(int channelNum) 
{
  switch(channelNum) {  
  case 0: //chooseClockC0
  digitalWrite(pinClockC, LOW);
  digitalWrite(pinClockB, LOW);
  digitalWrite(pinClockA, LOW);
  break;

  case 1: //chooseClockC1 
  digitalWrite(pinClockC, LOW);
  digitalWrite(pinClockB, LOW);
  digitalWrite(pinClockA, HIGH);
  break;

  case 2: //chooseClockC2 
  digitalWrite(pinClockC, LOW);
  digitalWrite(pinClockB, HIGH);
  digitalWrite(pinClockA, LOW); 
  break;

  case 3: //chooseClockC3 
  digitalWrite(pinClockC, LOW);
  digitalWrite(pinClockB, HIGH);
  digitalWrite(pinClockA, HIGH);
  break;

  case 4: //chooseClockC4
  digitalWrite(pinClockC, HIGH);
  digitalWrite(pinClockB, LOW);
  digitalWrite(pinClockA, LOW);
  break;

  case 5: //chooseClockC5 
  digitalWrite(pinClockC, HIGH);
  digitalWrite(pinClockB, LOW);
  digitalWrite(pinClockA, HIGH);
  break;

  case 6: //chooseClockC6 
  digitalWrite(pinClockC, HIGH);
  digitalWrite(pinClockB, HIGH);
  digitalWrite(pinClockA, LOW);
  break;

  case 7: //chooseClockC7
  digitalWrite(pinClockC, HIGH);
  digitalWrite(pinClockB, HIGH);
  digitalWrite(pinClockA, HIGH);
  break;
  }
}

void chooseDataChannel(int channelNum) 
{
  switch (channelNum) {
  case 0: //chooseDataC0
  digitalWrite(pinClockC, LOW);
  digitalWrite(pinClockB, LOW);
  digitalWrite(pinClockA, LOW);
  break;

  case 1: //chooseDataC1 
  digitalWrite(pinDataC, LOW);
  digitalWrite(pinDataB, LOW);
  digitalWrite(pinDataA, HIGH);
  break;

  case 2: //chooseDataC2 
  digitalWrite(pinDataC, LOW);
  digitalWrite(pinDataB, HIGH);
  digitalWrite(pinDataA, LOW); 
  break;

  case 3: //chooseDataC3 
  digitalWrite(pinDataC, LOW);
  digitalWrite(pinDataB, HIGH);
  digitalWrite(pinDataA, HIGH);
  break;

  case 4: //chooseDataC4
  digitalWrite(pinDataC, HIGH);
  digitalWrite(pinDataB, LOW);
  digitalWrite(pinDataA, LOW);
  break;

  case 5: //chooseDataC5 
  digitalWrite(pinDataC, HIGH);
  digitalWrite(pinDataB, LOW);
  digitalWrite(pinDataA, HIGH);
  break;

  case 6: //chooseDataC6 
  digitalWrite(pinDataC, HIGH);
  digitalWrite(pinDataB, HIGH);
  digitalWrite(pinDataA, LOW);
  break;

  case 7: //chooseDataC7
  digitalWrite(pinDataC, HIGH);
  digitalWrite(pinDataB, HIGH);
  digitalWrite(pinDataA, HIGH);
  break;
  }
}
