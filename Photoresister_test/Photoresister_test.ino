
const int ledpin = 2;
const int ldrpin = A0;
double treshold = 600;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledpin, OUTPUT);
pinMode(ldrpin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrStatus = analogRead(ldrpin);
      Serial.println(ldrStatus);
  delay(100);
  if(ldrStatus<=treshold){
    digitalWrite(ledpin, HIGH);
    Serial.println("on");
  } else {
    digitalWrite(ledpin, LOW);
    Serial.println("off");
  }
}
