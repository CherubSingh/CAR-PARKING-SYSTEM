#include <Servo.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

Servo myservo;

#define ir_enter 2
#define ir_back  4

#define ir_car1 5
#define ir_car2 6


int S1=0, S2=0;
int flag1=0, flag2=0; 
int slot = 2;  

void setup(){
Serial.begin(9600);

pinMode(ir_car1, INPUT);
pinMode(ir_car2, INPUT);


pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);
  
myservo.attach(3);
myservo.write(90);

lcd.begin(20, 4);  
lcd.setCursor (0,1);
Serial.println("    Car  parking  ");
lcd.setCursor (0,2);
Serial.println("       System     ");
delay (2000);
lcd.clear();   

Read_Sensor();

int total = S1+S2;
slot = slot-total; 
}

void loop(){

Read_Sensor();

lcd.setCursor (0,0);
Serial.println("   Have Slot: "); 
lcd.print(slot);
Serial.println("    ");  

lcd.setCursor (0,1);
if(S1==1){lcd.print("S1:Fill ");}
     else{lcd.print("S1:Empty");}

lcd.setCursor (10,1);
if(S2==1){lcd.print("S2:Fill ");}
     else{lcd.print("S2:Empty");}
  

if(digitalRead (ir_enter) == 0 && flag1==0){
if(slot>0){flag1=1;
if(flag2==0){myservo.write(180); slot = slot-1;}
}else{
lcd.setCursor (0,0);
Serial.println(" Sorry Parking Full ");  
delay(1500);
}   
}

if(digitalRead (ir_back) == 0 && flag2==0){flag2=1;
if(flag1==0){myservo.write(180); slot = slot+1;}
}

if(flag1==1 && flag2==1){
delay (1000);
myservo.write(90);
flag1=0, flag2=0;
}

delay(1);
}

void Read_Sensor(){
S1=0, S2=0;

if(digitalRead(ir_car1) == 0){S1=1;}
if(digitalRead(ir_car2) == 0){S2=1;} 
}
