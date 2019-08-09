
int led = 6;
int led_green = 5;
boolean switcher = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  char text = Serial.read();
  int inttext = 0;


  if (text == '1' ){
    digitalWrite(led, HIGH);
  } 
  if (text == '3'){
    digitalWrite(led, LOW);
  } 
  /*
  if(inttext > 199 && inttext<801){
    digitalWrite(led, HIGH);
    delay(inttext);
    digitalWrite(led, LOW);
    delay(inttext);
  }
  */

}
