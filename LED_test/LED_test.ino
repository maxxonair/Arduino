


const int green = 2;
const int red = 3;
const int white = 4;
const int blue =5; 
const int yellow = 6;

int activeLight = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);


  Serial.begin(9600);
}

void AllLOW(){
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  digitalWrite(white, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(yellow, LOW);
}

void Light(int light){
  digitalWrite(light, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(2, HIGH);
  // delay(10);
  // digitalWrite(2, LOW);
  // delay(9000);
  AllLOW();
  delay(10);
  Light(activeLight);
  Serial.println(activeLight);
  delay(100);
  activeLight++;
  if(activeLight==7){
    activeLight = 2;
  }
  

}
