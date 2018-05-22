#include <Arduino.h>

#include <Wire.h>
int LED=13;
void setup(){
Wire.begin(); // join i2c as master
Serial.begin(9600);
pinMode(LED, OUPUT);
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

if (G=='00')
{LinearMove(X,Y,Xpast,Ypast,encoder1,encoder2,encoder3);
  Xpast=X;
  Ypast=Y;}
else if (G=='01')
{LinearCut(X,Y,Xpast,Ypast,encoder1,encoder2,encoder3);
  Xpast=X;
  Ypast=Y;}
else if(G=='02'||G=='03')
{ArcCut( X,Y,I,J,Xpast,Ypast,encoder1,encoder2,encoder3);
  Xpast=X;
  Ypast=Y;}
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

void LinearMove(int Xfinal,int Yfinal,int Xpast,int Ypast,int encoder1,int encoder2,int encoder3)
{ int EncoderXvalue=encoder1*5/1440 ;
  int EncoderYvalue=encoder2*5/1440;
  int EncoderZvalue=encoder3*5/1440;
  int Const= -1*Yfinal*(Xfinal-Xpast) + (Yfinal-Ypast)*Xfinal ;
  int error= -1*(Xfinal-Xpast)*EncoderYvalue + (Yfinal-Ypast)*EncoderXvalue + Const;
  if (abs(error)>.5)
    {Serial.println("I'm done");
    digitalWrite(LED,HIGH);
    } 
  }
  


{ int EncoderXvalue=encoder1*5/1440 ;
  int EncoderYvalue=encoder2*5/1440;
  int EncoderZvalue=encoder3*5/1440;
  int Const= -1*Yfinal*(Xfinal-Xpast) + (Yfinal-Ypast)*Xfinal ;
  int error= -1*(Xfinal-Xpast)*EncoderYvalue + (Yfinal-Ypast)*EncoderXvalue + Const;
  if (abs(error)>.5)
    {Serial.println("I'm done");
    digitalWrite(LED,HIGH);
    } 
  }
  

void ArcCut(int Xfinal,int Yfinal,int i,int j,int Xpast,int Ypast, int encoder1,int encoder2,int encoder3)
{ int EncoderXvalue=encoder1*5/1440 ;
  int EncoderYvalue=encoder2*5/1440;
  int EncoderZvalue=encoder3*5/1440;
  int Xcenter=i+Xpast;
  int Ycenter=j+Ypast;
  int SquareRadius= (Xcenter-Xfinal)^2+(Ycenter-Yfinal)^2;
  int error= (EncoderXvalue-Xcenter)^2 + (EncoderYvalue-Ycenter)^2 -SquareRadius;
  if (abs(error)>.5)
    {Serial.println("I'm done");
    digitalWrite(LED,HIGH);
    } 
  }
