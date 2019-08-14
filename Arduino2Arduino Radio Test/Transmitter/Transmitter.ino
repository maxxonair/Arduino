
#include <SPI.h>
#include "RF24.h"

 //SCK -> 13
 //MISO -> 12
 //MOSI -> 11
 //CSN -> 7
 //CE -> 8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int xAxis_01 = A5;
int yAxis_01 = A6;
int xAxis_02 = A3;
int yAxis_02 = A4;
int valX1; 
int valY1;
int valX2; 
int valY2;
int Joystick[2];

void setup(void){
radio.begin();
radio.openWritingPipe(pipe);
pinMode(xAxis_01, INPUT);
pinMode(yAxis_01, INPUT);
pinMode(xAxis_02, INPUT);
pinMode(yAxis_02, INPUT);
Serial.begin(115200);
}

void loop(void){
valX1 = analogRead(xAxis_01);
valX1= map(valX1, 1023, 0, 255, 0);
valY1 = analogRead(yAxis_01);
valY1 = map(valY1, 1023, 0, 0, 255);
valX2 = analogRead(xAxis_02);
valX2 = map(valX2, 1023, 0, 0, 255);
valY2 = analogRead(yAxis_02);
valY2 = map(valY2, 1023, 0, 0, 255);
Joystick[0]=valX1;
Joystick[1]=valY2;
//msg[0]=valX;
//radio.write(msg, 1);
radio.write(&Joystick, sizeof(Joystick));
Serial.print(valX1);
Serial.print(" -- ");
Serial.print(valY1);
Serial.print(" -- ");
Serial.print(valX2);
Serial.print(" -- ");
Serial.print(valY2);
Serial.print("\n");
//radio.write(msg, 2);
delay(10);
}
