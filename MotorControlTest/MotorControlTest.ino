//-------------------------------------
// Engine 1 
//-------------------------------------
int GSM1 = 6;
int in1  = 2 ;
int in2  = 3;
//-------------------------------------
// Engine 2
//-------------------------------------
int GSM2 = 10;
int in3  = 4;
int in4  = 5;
//-------------------------------------
void setup(){
  pinMode(GSM1, OUTPUT);
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(115200);
}
void loop(){

  digitalWrite(in1, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, LOW);
    Serial.print("Motor 1 ON");

  digitalWrite(in3, HIGH);  // Motor 1 beginnt zu rotieren
  digitalWrite(in4, LOW);
      Serial.print("Motor 2 ON");
/*
  analogWrite(GSM1, 200);   // Motor 1 soll mit der Geschwindigkeit"200" (max. 255) rotieren
  analogWrite(GSM2, 50);
  delay(2000);
  analogWrite(GSM1, 100);
  analogWrite(GSM2, 200);
  delay(2000);
  analogWrite(GSM1, 50); 
  analogWrite(GSM2, 250);
  delay(2000);
  */
int delay_x = 5;
  for(int i=50;i<255;i++){
    analogWrite(GSM2, i);
    delay(15);
    delay_x++;
    Serial.print(i);
    Serial.print("\n");
  }
    for(int i=255;i<50;i--){
    analogWrite(GSM2, i);
    delay(15);
    Serial.print(i);
    Serial.print("\n");
  }
/*
 // digitalWrite(in3, HIGH);  // Motor 2 beginnt zu rotieren
 // digitalWrite(in4, LOW);

  //analogWrite(GSM2, 200);   // Motor 2 soll ebenfalls mit derGeschwindigkeit "200" (max. 255) rotieren
 // delay(2000);

  digitalWrite(in1, LOW);   // Durch die Veränderung von HIGH auf LOW(bzw. LOW auf HIGH) wird die Richtung der Rotation verändert.
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2000);

  digitalWrite(in1, LOW);   // Anschließend sollen die Motoren 2Sekunden ruhen.
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(2000);
*/
}
