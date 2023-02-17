#include<LiquidCrystal.h>
const int drainswitch=8;
const int watertank=9;
const int drainvalve=10;
const int washingmotor=11;
const int buzzer=12;
const int timesetting=A0;
const int rs=7,en=6,d4=5,d5=4,d6=3,d7=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
int timervalue;
void setup(){
  pinMode(drainswitch,INPUT);
  pinMode(watertank,INPUT);
  pinMode(drainvalve,INPUT);
  pinMode(washingmotor,OUTPUT);
  pinMode(buzzer,OUTPUT);
  lcd.begin(20,4);
  lcd.print(" Washing machine ");
  lcd.setCursor(3,1);
  lcd.print(" Controller ");
  lcd.setCursor(6,2);
  lcd.print(" Design ");
  delay(100);
}
void loop(){
  if(digitalRead(drainswitch)==HIGH){
    delay(3000);
    if(digitalRead(watertank)==HIGH){
      digitalWrite(drainvalve,LOW);
      lcd.clear();
      lcd.print(" Drain valve closed ");
      delay(1000);
      lcd.clear();
      lcd.print(" Set washing timer ");
      timervalue=analogRead(timesetting);
      timervalue=map(timervalue,0,1023,0,60);
      lcd.setCursor(0,1);
      lcd.print(timervalue);
      lcd.print(" mins ");
      delay(1000);
      lcd.clear();
      lcd.print(" Washing ");
      digitalWrite(washingmotor,HIGH);
      delay(timervalue*60000);
      digitalWrite(washingmotor,LOW);
      digitalWrite(drainvalve,HIGH);
      lcd.clear();
      lcd.print(" Drain valve opened ");
      delay(3000);
      while(digitalRead(drainswitch)==HIGH){
        digitalWrite(buzzer,HIGH);
        delay(500);
        digitalWrite(buzzer,LOW);
        delay(500);
      }
      digitalWrite(drainvalve,LOW);
      lcd.clear();
      lcd.print(" Washing completed ");
      digitalWrite(buzzer,HIGH);
      delay(1000);
      digitalWrite(buzzer,LOW);
    }
  }
}
