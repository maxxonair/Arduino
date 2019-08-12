#include <Servo.h>
#include <SPI.h>
#include "RF24.h"

//Servo myservo;
//const int green = 6;
//SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 7//CE -> 8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//int msg[1];
int xSpeed=0;

//-------------------------------------
// Engine 1 
//-------------------------------------
int GSM1 = A3;
int in1  = 4 ;
int in2  = 5;
//-------------------------------------
// Engine 2
//-------------------------------------
//int GSM2 = 10;
//int in3  = 8;
//int in4  = 9;
//-------------------------------------
int servoPin = 9; 
Servo Servo1; 
//-------------------------------------
int Joystick[2];


void setup(){

radio.begin();
radio.openReadingPipe(1,pipe);
radio.startListening();

  pinMode(GSM1, OUTPUT);
  //pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  Servo1.attach(servoPin); 
  
  Serial.begin(115200); 
}

void MotorControl_01(int THROTTLE, boolean forward){
  if(forward){
   digitalWrite(in1, HIGH);  
   digitalWrite(in2, LOW);
  } else {
   digitalWrite(in1, LOW);  
   digitalWrite(in2, HIGH);
  }
   analogWrite(GSM1, THROTTLE);
}
/*
void MotorControl_02(int THROTTLE, boolean forward){
    if(forward){
   digitalWrite(in3, HIGH);  
   digitalWrite(in4, LOW);
  } else {
   digitalWrite(in3, LOW);  
   digitalWrite(in4, HIGH);
  }
   digitalWrite(in3, HIGH);  // Motor 1 beginnt zu rotieren
   digitalWrite(in4, LOW);
   analogWrite(GSM2, THROTTLE);
}
*/
void loop(){
   /*
   // Servo Demo
   Servo1.write(0); 
   delay(1000);  
   Servo1.write(90); 
   delay(1000); 
   Servo1.write(180); 
   delay(1000); 
   */

if (radio.available()){
    while (radio.available()){
      
      radio.read(&Joystick, sizeof(Joystick));
      int AxisX = Joystick[0];
      int AxisY = Joystick[1];
       Serial.print(AxisX);
       Serial.print(" -- " );
       Serial.print(AxisY);
       Serial.print("\n");
     
      if( AxisX >= 0 && AxisX <= 255 ){
        int val = AxisX;
        boolean forward = true;
            if(val>128){
            val = map(val, 128, 255, 20, 255);
            xSpeed=map(val, 25, 255, 0, 100);
            forward = false; 
            } else {
            val = map(val, 128, 0, 20, 255); 
            xSpeed=map(val, 25, 255, 0, 100);
            xSpeed = -xSpeed;
            forward = true;
            }
        MotorControl_01(val, forward);
        Serial.print(xSpeed);
        Serial.print("\n");
      } else { }
      
        int val2=AxisY-128;;
        int SteeringValue = map(val2, -128, 128, 0, 180);
        Serial.print(SteeringValue);
        Serial.print("\n");
        Servo1.write(SteeringValue);
    
    
    }
} else {
  //Serial.print("No Radio");
  //Serial.print("\n");
}
delay(10);

}
