#include <Servo.h>
#include "pinku.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7);//rx tx
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

//Sensor Tanah
int satas,sbawah;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
  mySerial.begin(115200);

  //Servo
  myservo.attach(pinServo);
  myservo.write(90);
  
  //relay
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEST: ");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  char recv;
  if(mySerial.available()){
    recv=mySerial.read();
    Serial.println(recv);
    if(recv=='a'){
      
    }else if(recv=='n'){
     pompaON();
     delay(5000); 
     pompaOFF(); 
    }else{
      
    }
  }
//  myservo.write(180);
//  pompaON();
//  delay(2000);
//  
//  myservo.write(90);
//  pompaOFF();
//  delay(2000);

//  satas=getTanahAtas();
//  sbawah=getTanahBawah();
//  lcd.clear();
//  lcd.setCursor(0, 0);
//  lcd.print("LEMBAB: ");
//  lcd.print(satas);
//  lcd.print("-");
//  lcd.print(sbawah);
//  delay(1000);
  
}

//PORTAL
void buka(){
  myservo.write(90);  
}
//PORTAL
void tutup(){
  myservo.write(180);  
}
void pompaON(){
  digitalWrite(relay,LOW);
}
void pompaOFF(){
  digitalWrite(relay,HIGH);
}
int reverseSensor(int value){
  value=82-value;
  return value;
}
int getTanahAtas(){
  int value=analogRead(sensorAtas);
  value=map(value, 0, 1023, 0, 75);
  value=reverseSensor(value);
  
  Serial.print("Sensor Tanah Atas:");Serial.println(value);
  return value;
}
int getTanahBawah(){
  int value=analogRead(sensorBawah);  
  value=map(value, 0, 1023, 0, 75);
  value=reverseSensor(value);  

  Serial.print("Sensor Tanah Bawah:");Serial.println(value);
  return value;
}
