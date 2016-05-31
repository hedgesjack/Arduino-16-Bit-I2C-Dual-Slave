//                                    //
//  Title:   I2C_Slave_Reader         //
//  Author:  J Hedges                 //
//  Date:    31/05/2016               //
//  Board:   Uno                      //
//                                    //

//  Library Declarations  //
#include <Wire.h>

//  Global Variable Declarations  //
byte DataPacket[2];   //  Size 2 BYTE array, note zero index when called
int c = 0;    //  Full data converted back from individual packets

//  Startup Code - executes once  //
void setup() 
{
  Wire.begin(8);    //  Join I2C bus as slave with address 8
  Wire.onReceive(receiveEvent);   //  Register event for data recieve
  Serial.begin(9600);   //  Start serial communication
  pinMode(13, OUTPUT);    // Set user LED as digital output
}

//   Main Program Loop  //
void loop() 
{
  digitalWrite(13, HIGH);   //  Used to show program is working
  delay(1000);   // Stop software running too quick and stressing CPU, can be used as sofware timing
  digitalWrite(13, LOW);   //  Used to show program is working
  delay(500);
}

// This function is registered as an event and is executing when 'called' by the master
void receiveEvent(int howMany) 
{
  while (Wire.available()) 
  { 
    DataPacket[0] = Wire.read();   //  Receive first byte
    DataPacket[1] = Wire.read();   //  Recieve second byte
    c = DataPacket[0];    //  Set first byte as integer in variable c
    c = (DataPacket[0] << 8) | DataPacket[1];   //  shift c by 8 BITS to correct transmission formatting and OR it with the second BYTE B
  }
  Serial.print("Data Recieved ");    //  Print the result to the serial com port for debug
  Serial.print(c);
  Serial.print("\n");   //  Add carriage return to each line to allow for easy reading in com port
}

//                //
//  END OF FILE   //
//                //
