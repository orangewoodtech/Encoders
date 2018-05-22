#include <Arduino.h>
#include <Wire.h>

int encoderPin1 = 2; // GREEN
int encoderPin2 = 3; // WHITE

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;


void requestEvent()
{

static long data = 0x75BCD15;

data=encoderValue;

byte myArray[4];
myArray[0] = (data);
myArray[1] = (data>>8);
myArray[2] = (data>>16);
myArray[3] = (data>>24);

Wire.write(myArray, 4);
}

void setup()
{
Wire.begin(6); // join i2c with address 4
//Serial.begin(9600);
// call requestEvent function when there's a request
Wire.onRequest(requestEvent);

  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on

  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}

int rounds = 0;

void loop()
{  
//  rounds=encoderValue;
//  Wire.onRequest(requestEvent());
//  Serial.println(rounds);
  delay(10);
}


void updateEncoder()
{
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
