
const int trigPin =10;
const int echoPin =9;

const int red = 4;
const int green = 2;

long duration;
int distance;
double SpeedOfSound =0.034; // cetimeters per microsecond

void setup() {
  // put your setup code here, to run once:
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(2, HIGH);
  // delay(10);
  // digitalWrite(2, LOW);
  // delay(9000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration*SpeedOfSound/2;

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.print("\n");
delay(25);
  if(distance<50){
    digitalWrite(green, LOW);
    delay(50);
    digitalWrite(red, HIGH);
  } else {
    digitalWrite(red,LOW);
    delay(50);
    digitalWrite(green,HIGH);
  }
}
