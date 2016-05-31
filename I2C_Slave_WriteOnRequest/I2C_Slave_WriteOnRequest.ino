//                                    //
//  Title:   I2C_Master_ReadRequest   //
//  Author:  J Hedges                 //
//  Date:    29/05/2016               //
//  Board:   Uno                      //
//                                    //

//  Library Declarations  //
#include <Wire.h>

//  Global Variable Declarations  //
int Data = 0;   //  ADC Value as 16bit signed integer
byte DataPacket[2];   //  Size 2 BYTE array, note zero index when called

//  Startup Code - executes once  //
void setup() 
{
  Wire.begin(3);    //  Join I2C bus as slave with address 3
  Wire.onRequest(requestEvent);   //  Register event for data request
  Serial.begin(9600);   //  Start serial communication
  pinMode(13, OUTPUT);
}

//   Main Program Loop  //
void loop() 
{
  digitalWrite(13, HIGH);    //  Used to show program is working
  
  Data = analogRead(A0);  //  Read Analogue pin A0
  
  Serial.print("Data Sent ");    //  Print the result to the serial com port for debug
  Serial.print(Data); 
  Serial.print("\n");   //  Add carriage return to com port so data is readable
  
  DataPacket[0] = (Data >> 8) & 0xFF;    //  Shift number down by 8BITS and mask with 0xFF to remove other bits, place in array 0
  DataPacket[1] = Data & 0xFF;   //  Format lower part by masking with 0xFF 8BIT to remove any other bits, place in array 1
  
  delay(1000);   // Stop software running too quick and stressing CPU, can be used as sofware timing
  digitalWrite(13, LOW);    //  Used to show program is working
  delay(500);
}

// This function is registered as an event and is executing when 'called' by the master
void requestEvent() 
{
  Wire.write(DataPacket, 2);   //  Send array of data that is 2 BYTES in size
}

//                //
//  END OF FILE   //
//                //
