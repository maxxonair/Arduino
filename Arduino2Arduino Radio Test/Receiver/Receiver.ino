#include <Servo.h>
#include <SPI.h>
#include "RF24.h"

//Servo myservo;
const int green = 6;
//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//int msg[1];
int Joystick[2];

void setup(){
//myservo.attach(9);
radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();
//pinMode(green, OUTPUT);
Serial.begin(115200); 
}
void GREENLOW(){
  digitalWrite(green, LOW);
}
void GREENHIGH(){
  digitalWrite(green, HIGH);
 // delay(20);
 // digitalWrite(green, LOW);
}

void loop(){
//GREENLOW();
if (radio.available()){
    while (radio.available()){
      //radio.read(msg, 1);
      radio.read(&Joystick, sizeof(Joystick));
      Serial.print(Joystick[0]);
      Serial.print(" -- ");
      Serial.print(Joystick[1]);
      Serial.print("\n");
      //Serial.print("\t");
      //Serial.print(msg[1]);
     // Serial.print("\n");
      //myservo.write (msg[0]);
      /*
      if(msg[0]>0){
        double val = msg[0];
        //double val2 = msg[1];
        //double t = val/8;
        GREENHIGH();
        Serial.print("lights ON");
        Serial.print("\n");
      } else {
        GREENLOW();
        Serial.print("lights OFF");
        Serial.print("\n");
      }
      */
    }
} else {
  //Serial.print("No Radio");
 // Serial.print("\n");
}
delay(10);

}
