const int ledpin = 2;
const int ldrpin = A0;
double treshold = 25;

const double T_const = 0.04408817635;

int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ledpin, OUTPUT);
pinMode(ldrpin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int ldrStatus = analogRead(ldrpin);
  double temperature = T_const * ldrStatus; 
    Vo = analogRead(ldrpin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
      Serial.println(temperature);
      Serial.println(Tc);

  delay(500);
  if(temperature<=treshold){
    digitalWrite(ledpin, HIGH);
    //Serial.println("on");
  } else {
    digitalWrite(ledpin, LOW);
    //Serial.println("off");
  }
}
