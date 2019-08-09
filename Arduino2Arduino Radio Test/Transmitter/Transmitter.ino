
#include <SPI.h>
#include "RF24.h"

int msg[1]; //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int potpin = 1;
int digipin = 4;
int val;


void setup(void){
radio.begin();
radio.openWritingPipe(pipe);
pinMode(digipin, INPUT);
}

void loop(void){
int digistate = digitalRead(digipin);
val = analogRead(potpin);
val = map(val, 0, 1023, 0, 100);
//msg[0] = val;
msg[0]=digistate;
//msg[1] = 2;
radio.write(msg, 1);
//radio.write(msg, 2);
delay(10);
}
