
const int green = 5 ; 
void setup() {
  // put your setup code here, to run once:
pinMode(green, OUTPUT);

Serial.begin(115200);
}

void GREENLOW(){
  digitalWrite(green, LOW);
}
void GREENHIGH(){
  digitalWrite(green, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
GREENLOW();
delay(500);
GREENHIGH();
delay(500);
}
