#include <Arduino.h>

#include <Wire.h>
void setup(){
Wire.begin(); // join i2c as master
Serial.begin(9600);
}
float Xpast,Ypast=0;
float X,Y,I,J;
char G;
void loop(){
float  encoder1=RecieveData(4);
  Serial.print(encoder1);
  Serial.print("\t");
  
float  encoder2=RecieveData(5);
  Serial.print(encoder2);
  Serial.print("\t");
  
float  encoder3=RecieveData(6);
  Serial.println(encoder3);
   delay(10); 

}

float RecieveData(int address)
{ float output;
  Wire.requestFrom(address,4); // request 2 bytes from address 4
  byte a,b,c,d;
  a = Wire.read();  
  b = Wire.read();
  c = Wire.read();
  d = Wire.read();

  long val = 0;
  val += d << 24;
  val += c << 16;
  val += b << 8;
  val += a;
  return val ;
}


