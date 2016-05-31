//                                    //
//  Title:   I2C_Master_ReadWrite     //
//  Author:  J Hedges                 //
//  Date:    31/05/2016               //
//  Board:   mega2560                 //
//                                    //

//  Library Declarations  //
#include <Wire.h>

//  Global Variable Declarations  //
byte DataPacket[2];   //  Size 2 BYTE array, note zero index when called
int c = 0;    //  Full data converted back from individual packets

//  Startup Code - executes once  //
void setup()
{
  Wire.begin();   //  Join I2C bus as master (no address)
  Serial.begin(9600);   //  Start serial communiation
  pinMode(13, OUTPUT);    // Set user LED as digital output
}

//  Main Program Loop   //
void loop() 
{
  digitalWrite(13, HIGH);   //  Used to show program is working
  
  Wire.requestFrom(3, 2);   //  Request 2 BYTES from slave writer 3
  
  while (Wire.available())  //  Reads all bytes at port
  {
    DataPacket[0] = Wire.read();   //  Receive first byte
    DataPacket[1] = Wire.read();   //  Recieve second byte
    
    c = DataPacket[0];    //  Set first byte as integer in variable c
    c = (DataPacket[0] << 8) | DataPacket[1];   //  shift c by 8 BITS to correct transmission formatting and OR it with the second BYTE
    
    Serial.print("Data Recieved ");    //  Print the result to the serial com port for debug
    Serial.print(c);
    Serial.print("\n");   //  Add carriage return to each line to allow for easy reading in com port
  }

  Wire.beginTransmission(8);    //  Transmit to slave device at address 8
  Wire.write(DataPacket,2);   //  Send DataPacket, size 2 BYTES
  Wire.endTransmission();   // End transmission to slave at address 8
  
  Serial.print("Packet one = ");    //Print both data packets to the serial com port for debug
  Serial.print(DataPacket[0]);
  Serial.print(", Packet two = ");
  Serial.print(DataPacket[1]);
  Serial.print("\n");   //  Add carriage return to each line to allow for easy reading in com port
  
  delay(1000);   // Stop software running too quick and stressing CPU, can be used as sofware timing
  
  digitalWrite(13, LOW);    //  Used to show program is working
  delay(500);
}

//                //
//  END OF FILE   //
//                //
