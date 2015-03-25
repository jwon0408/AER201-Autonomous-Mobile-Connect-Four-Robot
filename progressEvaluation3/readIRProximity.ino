unsigned int readProximity()
{
  unsigned int data;
  byte temp;
  
  temp = readByte(COMMAND_0);
  Serial.print("temp: ");
  Serial.println(temp);
  
  writeByte(COMMAND_0, temp | 0x08);  // command the sensor to perform a proximity measure
  Serial.println("done writing");
  
  while(!(readByte(COMMAND_0)&0x20)) 
   ;  // Wait for the proximity data ready bit to be set
    
  Serial.println("passed while");  
  
  data = readByte(PROXIMITY_RESULT_MSB) << 8;
  data |= readByte(PROXIMITY_RESULT_LSB);
  
  Serial.print("data: ");
  Serial.println(data);
  
  return data;
}

// readAmbient() returns a 16-bit value from the VCNL4000's ambient light data registers
unsigned int readAmbient()
{
  unsigned int data;
  byte temp;
  
  temp = readByte(COMMAND_0);
  Serial.println(temp);
  writeByte(COMMAND_0, temp | 0x10);  // command the sensor to perform ambient measure
  Serial.println("done writing");
  
  while(!(readByte(COMMAND_0)&0x40)) 
  ;  // wait for the proximity data ready bit to be set
  Serial.println("passed while");
  
  data = readByte(AMBIENT_RESULT_MSB) << 8;
  data |= readByte(AMBIENT_RESULT_LSB);
  
  Serial.println(data);
  
  return data;
}

// writeByte(address, data) writes a single byte of data to address
void writeByte(byte address, byte data)
{
  Wire.beginTransmission(VCNL4000_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}

// readByte(address) reads a single byte of data from address
byte readByte(byte address)
{
  byte data;
  
  Wire.beginTransmission(VCNL4000_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(VCNL4000_ADDRESS, 1);
  waitStartTime = millis(); 
  while(!Wire.available())
  {
    if (millis()-waitStartTime > 10) 
    {
      return 0;
    }
  }
  data = Wire.read();

  return data;
}
