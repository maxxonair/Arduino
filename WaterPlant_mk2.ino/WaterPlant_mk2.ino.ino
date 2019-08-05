


//----------------------------------------------------------------------------------------------
//
//                                   Watering script Mark II 
//
//----------------------------------------------------------------------------------------------
#include <DS3231.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
Time t; 

const int button_plus  = 2;
const int button_minus = 3;
const int button_MenuForward  = 4;
const int button_MenuBackward = 5;


int val           = 0;
int menu          = 0;
int NR_menu       = 6;
int OnHour_01_old = 0;
int OnHour_02_old = 0;
int OnMin_01_old  = 0;
int OnMin_02_old  = 0;
int WateringTime_01_old=0;
int WateringTime_02_old=0;
int menu_old = 0; 

double lcd_time=0; 
 int OnHour_01 =  8;
 int OnHour_02 = 20;
 //int OnHour_03 = 15; 

 int OnMin_01 = 30; 
 int OnMin_02 = 30;

const int OnSec = 0;

int Relay = 6;

 int WateringTime_01 = 2; // [s]
 int WateringTime_02 = 2; // [s]

 const int delay_nominal = 1000;
const int delay_long    = 5000; 
 int delay_is      = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(button_plus, INPUT);
  pinMode(button_minus, INPUT);
  pinMode(button_MenuForward, INPUT);


  lcd.init();                      // initialize the lcd 

  rtc.begin();
}
void watering_morning(){
      digitalWrite(Relay,LOW);
      Serial.println("Pump: ON"); 
      delay(WateringTime_01*1000);
      digitalWrite(Relay,HIGH);
      Serial.println("Pump: OFF"); 
}
void watering_evening(){
      digitalWrite(Relay,LOW);
      Serial.println("Pump: ON"); 
      delay(WateringTime_02*1000);
      digitalWrite(Relay,HIGH);
      Serial.println("Pump: OFF"); 
}
void lcd_menu_00(){
   lcd.backlight();
   lcd.clear();
     lcd.setCursor(0,0);
   //Serial.print(rtc.getDOWStr());
  // lcd.print(" ");
  // Send date
  //lcd.print(rtc.getDateStr());
  // lcd.print("-");
  // Send time
 lcd.print(rtc.getTimeStr());
 lcd.setCursor(0,1);
  lcd.print("Garten Braun ");
}
void lcd_menu_hour_01(){
     lcd.backlight();
     lcd.clear();
     lcd.setCursor(0,0);
  lcd.print("Menu ");
  lcd.print(menu);
  lcd.setCursor(0,1);
  lcd.print("H morning: ");
  lcd.print(OnHour_01);
}
void lcd_menu_hour_02(){
       lcd.backlight();
       lcd.clear();
     lcd.setCursor(0,0);
       lcd.print("Menu ");
  lcd.print(menu);
  lcd.setCursor(0,1);
  lcd.print("H evening: ");
  lcd.print(OnHour_02);
}
void lcd_menu_minute_01(){
       lcd.backlight();
     lcd.setCursor(0,0);
       lcd.print("Menu ");
  lcd.print(menu);
  lcd.setCursor(0,1);
  lcd.print("Min morning: ");
  lcd.print(OnMin_01);
}
void lcd_menu_minute_02(){
       lcd.backlight();
       lcd.clear();
     lcd.setCursor(0,0);
       lcd.print("Menu ");
  lcd.print(menu);
  lcd.setCursor(0,1);
  lcd.print("Min evening: ");
  lcd.print(OnMin_02);
}
void lcd_menu_watertime_01(){
       lcd.backlight();
       lcd.clear();
     lcd.setCursor(0,0);
       lcd.print("Menu ");
  lcd.print(menu);
  lcd.setCursor(0,1);
  lcd.print("T morning: ");
  lcd.print(WateringTime_01);
}
void lcd_menu_watertime_02(){
       lcd.backlight();
       lcd.clear();
     lcd.setCursor(0,0);
            lcd.print("Menu ");
  lcd.print(menu);
       lcd.setCursor(0,1);
  lcd.print("T evening: ");
  lcd.print(WateringTime_02);
}
  boolean AnyVariableChange(){
  if(OnHour_01_old != OnHour_01 || OnHour_02_old != OnHour_02 ||  OnMin_01_old != OnMin_01 || OnMin_02_old != OnMin_01 || WateringTime_01_old != WateringTime_01 || WateringTime_02_old != WateringTime_02 || menu_old != menu){
  OnHour_01_old=OnHour_01;
  OnHour_02_old=OnHour_02;
  OnMin_01_old=OnMin_01;
  OnMin_02_old=OnMin_02;
  WateringTime_01_old=WateringTime_01;
  WateringTime_02_old=WateringTime_02;
  menu_old=menu; 
    return true;
  } else if(menu==0){
    return true;
    delay(500);
  } else {
    return false;
  }
}
void DisplayTimeout(double t_set){
  if(menu==menu_old){
    lcd_time=lcd_time+0.2;
  }else {
    lcd_time=0;
  }
  if(lcd_time>t_set){
    lcd.noBacklight();
  }
}
void UpDownSelect(){
   if(menu==1) {
          if(digitalRead(button_plus) == HIGH){OnHour_01++;delay(300);}
      else if(digitalRead(button_minus) == HIGH){OnHour_01--;delay(300);}
  } else if (menu == 2){
              if(digitalRead(button_plus) == HIGH){OnMin_01++;delay(300);}
      else if(digitalRead(button_minus) == HIGH){OnMin_01--;delay(300);}
  } else if (menu==3){
               if(digitalRead(button_plus) == HIGH){WateringTime_01++;delay(300);}
      else if(digitalRead(button_minus) == HIGH){WateringTime_01--;delay(300);}   
  } else if (menu==4){
              if(digitalRead(button_plus) == HIGH){OnHour_02++;delay(300);}
      else if(digitalRead(button_minus) == HIGH){OnHour_02--;delay(300);}
  } else if (menu==5){
                  if(digitalRead(button_plus) == HIGH){OnMin_02++;delay(300);}
      else if(digitalRead(button_minus) == HIGH){OnMin_02--;delay(300);}
  } else if (menu==6){
                   if(digitalRead(button_plus) == HIGH){WateringTime_02++;delay(300);}
      else if(digitalRead(button_minus) == HIGH){WateringTime_02--;delay(300);} 
  } 
//------------------------------------------------------------------
    // Menu frame condition (all variables):
      if(OnHour_01>24){OnHour_01=0;} else if(OnHour_01<0){OnHour_01=24;}
      if(OnHour_02>24){OnHour_02=0;} else if(OnHour_02<0){OnHour_02=24;}
      if(OnMin_01>60){OnMin_01=0;} else if(OnMin_01<0){OnMin_01=59;}
      if(OnMin_02>60){OnMin_02=0;} else if(OnMin_02<0){OnMin_02=59;}      
   if(menu>NR_menu){menu=0;} else if(menu<0){menu=NR_menu;}
}
void DisplayOutput(){
    if(AnyVariableChange()){
           if (menu==0) {lcd_menu_00();}
      else if (menu==1) {lcd_menu_hour_01();}
      else if (menu==2) {lcd_menu_minute_01();}
      else if (menu==3) {lcd_menu_watertime_01();}
      else if (menu==4) {lcd_menu_hour_02();}
      else if (menu==5) {lcd_menu_minute_02();}
      else if (menu==6) {lcd_menu_watertime_02();}
  }
}
void loop() {
    // Read selected menu from Menu Button: 
    if(digitalRead(button_MenuForward) == HIGH){menu++;delay(300);}
  else if(digitalRead(button_MenuBackward) == HIGH){menu--;delay(300);}
  // Read value input from plus/minus buttons: 
      UpDownSelect();

  // Display Backlight timeout after set seconds without change:
     DisplayTimeout(60);
 // Autoselect: Display output
     DisplayOutput();
  delay(200);
  
  // Convert time seconds to milliseconds!!
  // Watering and timer functions: 
   // t = rtc.getTime();
  
    if(t.hour == OnHour_01 && t.min == OnMin_01 && t.sec == OnSec){
    watering_morning();
    delay_is = delay_long; 
    } else if (t.hour == OnHour_02 && t.min == OnMin_02 && t.sec == OnSec){
    watering_evening();
    delay_is = delay_long; 
    } else {
    digitalWrite(Relay,HIGH);
    delay_is = delay_nominal;   
    }
}
