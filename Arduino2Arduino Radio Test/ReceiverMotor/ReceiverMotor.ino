#include <Servo.h>
#include <SPI.h>
#include "RF24.h"

//SCK  -> 13
//MISO -> 12
//MOSI -> 11
//CSN  ->  7
//CE   ->  8
RF24 radio(8,7);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//int msg[1];
int xSpeed=0;
int xSpeed_Telemetry=0;
int SteeringAngle_Telemetry;
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
boolean forward = true;


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
  //-------------------------------
  // Come to life routine:
  //-------------------------------
  Servo1.write(0);  
  delay(1000);
  Servo1.write(180);
  delay(1000);
  Servo1.write(90);
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
if(radio.available())  {
    while (radio.available()){      
      radio.read(&Joystick, sizeof(Joystick));
      int AxisX = Joystick[0];
      int AxisY = Joystick[1];
//-------------------------------------------------------------------
//                  Car Speed Control
//-------------------------------------------------------------------
            if(AxisX>=128){
              xSpeed=map(AxisX, 128, 255, 0, 255);
              forward = false; 
            } else {
              xSpeed=map(AxisX, 0, 127, -255, 0);
              xSpeed=-xSpeed;
              forward = true;
            }
        MotorControl_01(xSpeed, forward); 
//-------------------------------------------------------------------
//                   Steering Control  
//-------------------------------------------------------------------        
        int SteeringValue = map(AxisY-128, -128, 128, 0, 180);
        Servo1.write(SteeringValue);  
        //------------------------------------------------------------
        if(forward){
                xSpeed_Telemetry=map(xSpeed, 0, 255, 0, 100);
                xSpeed_Telemetry=-xSpeed_Telemetry;
        } else {
                xSpeed_Telemetry=map(xSpeed, 0, 255, 0, 100);
        }
        SteeringAngle_Telemetry=map(SteeringValue, 0, 180, -90, 90);
        Serial.print(xSpeed_Telemetry); 
        Serial.print(" -- " );  
        Serial.print(SteeringAngle_Telemetry);
        Serial.print("\n");
    }
} else {
 Serial.print("0");
}
delay(10);
}
