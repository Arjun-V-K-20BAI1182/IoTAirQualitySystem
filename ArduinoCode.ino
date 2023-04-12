#include <LiquidCrystal.h>      //Header file for LCD
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2; //pins of LCD connected to Arduino
LiquidCrystal lcd(rs,en,d4,d5,d6,d7); //lcd function from LiquidCrystal

int buz = 8;  //buzzer connected to pin 8
int led = 9;  //led connected to pin 9

const int aqsensor = A0;  //output of mq135 connected to A0 pin of Arduino
int threshold = 350;      //Threshold level for Air Quality

void setup() {

  pinMode (buz,OUTPUT);     // buzzer is connected as Output from Arduino
  pinMode (led,OUTPUT);     // led is connected as output from Arduino
  pinMode (aqsensor,INPUT); // MQ135 is connected as INPUT to arduino

  Serial.begin (9600);      //begin serial communication with baud rate of 9600

  lcd.clear();              // clear lcd
  lcd.begin (16,2);         // consider 16,2 lcd
}

void loop() {

  int ppm = analogRead(aqsensor); //read MQ135 analog outputs at A0 and store it in ppm

  String quality = "";
  if (ppm < 181)
    quality = "Good        ";
  else if(ppm < 225)
    quality = "Poor        ";
  else if(ppm < 300)
    quality = "Very poor   ";
  else if(ppm < 350)
    quality = "Toxic       ";
  else
    quality = "Very Toxic  ";
  
  Serial.print("PPM in air: ");  //print message in serail monitor
  Serial.println(ppm);            //print value of ppm in serial monitor

  lcd.setCursor(0,0);             // set cursor of lcd to 1st row and 1st column
  lcd.print("PPM in air: ");      // print message on lcd
  lcd.print(ppm);                 // print value of MQ135

  lcd.setCursor(1, 1);
  lcd.print("AQ " + quality);
  Serial.println("AQ " + quality);  
  if (ppm > threshold)            // check is ppm is greater than threshold or not
    {
      tone(led,1000,200);         //blink led with turn on time 1000mS, turn off time 200mS
      digitalWrite(buz,HIGH);     //Turn ON Buzzer
    }
  else
    {
      digitalWrite(led,LOW);   //jump here if ppm is not greater than threshold and turn off LED
      digitalWrite(buz,LOW);   //Turn off Buzzer
    }  
  delay (500);
}
