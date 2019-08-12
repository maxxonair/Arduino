
#include <SPI.h>
#include "RF24.h"

 //SCK -> 13
 //MISO -> 12
 //MOSI -> 11
 //CSN -> 7
 //CE -> 8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int xAxis = A6;
int yAxis = A5;
int valX; 
int valY;
int Joystick[2];

void setup(void){
radio.begin();
radio.openWritingPipe(pipe);
pinMode(xAxis, INPUT);
pinMode(yAxis, INPUT);
Serial.begin(115200);
}

void loop(void){
valX = analogRead(xAxis);
valX = map(valX, 1023, 0, 0, 255);
valY = analogRead(yAxis);
valY = map(valY, 1023, 0, 0, 255);
Joystick[0]=valX;
Joystick[1]=valY;
//msg[0]=valX;
//radio.write(msg, 1);
radio.write(&Joystick, sizeof(Joystick));
Serial.print(valX);
Serial.print(" -- ");
Serial.print(valY);
Serial.print("\n");
//radio.write(msg, 2);
delay(10);
}
