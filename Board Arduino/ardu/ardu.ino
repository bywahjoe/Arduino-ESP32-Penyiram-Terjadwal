#include <Servo.h>
#include "pinku.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7);//rx tx
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

//Flowsensor
byte sensorInt = 0; 
byte flowsensor = 2;

float konstanta = 4.5; //konstanta flow meter

volatile byte pulseCount;

float debit;
unsigned int flowmlt;
unsigned long totalmlt;
unsigned long oldTime;

//Sensor Tanah
int satas, sbawah;

//Milis Setting
const long interval = 1000;
unsigned long before = 0;
unsigned long beforeRelay = 0;

void pulseCounter()
{
// Increment the pulse counter
pulseCount++;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mySerial.begin(115200);

  Serial.begin(115200); 
  
  //Servo
  myservo.attach(pinServo);
  myservo.write(90);

  //relay
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("START");
  delay(1000);
  pinMode(flow, INPUT);
  digitalWrite(flow, HIGH);

  pulseCount = 0;
  debit = 0.0;
  flowmlt = 0;
  totalmlt = 0;
  oldTime = 0;

  attachInterrupt(sensorInt, pulseCounter, FALLING);
}

void loop() {
  if((millis() - oldTime) > 1000) 
{ 
detachInterrupt(sensorInt);
debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / konstanta;
oldTime = millis();
pulseCount = 0;

attachInterrupt(sensorInt, pulseCounter, FALLING);
}

  satas = getTanahAtas();
  sbawah = getTanahBawah();

  char recv;

  if (mySerial.available()) {
    recv = mySerial.read();
    Serial.println(recv);
    if (recv == 'a') {

    } else if (recv == 'n') {
      pompaON();
      beforeRelay=millis();
    } else {

    }
  }
  
  unsigned long now = millis();
  if (now - before >= interval) {
    tampil();
    before = now;
  }
  if(now - beforeRelay>=15000){
    pompaOFF();
  }
  
  //  buka();
  //  Serial.println("buka");
  //  delay(4000);
  //  tutup();
  //  delay(4000);

  if (satas > 45) {
    buka();
  } else {
    tutup();
  };

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
void tampil() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TANAH: ");
  lcd.print(satas);
  lcd.print("%");
  lcd.print("-");
  lcd.print(sbawah);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("DEBIT: ");
  lcd.print(debit);
  lcd.print("L/min");
}

//PORTAL
void buka() {
  myservo.write(90);
}
//PORTAL
void tutup() {
  myservo.write(180);
}
void pompaON() {
  digitalWrite(relay, LOW);
}
void pompaOFF() {
  digitalWrite(relay, HIGH);
}
int reverseSensor(int value) {
  value = 82 - value;
  return value;
}
int getTanahAtas() {
  int value = analogRead(sensorAtas);
  value = map(value, 0, 1023, 0, 75);
  value = reverseSensor(value);

  Serial.print("Sensor Tanah Atas:"); Serial.println(value);
  return value;
}
int getTanahBawah() {
  int value = analogRead(sensorBawah);
  value = map(value, 0, 1023, 0, 75);
  value = reverseSensor(value);

  Serial.print("Sensor Tanah Bawah:"); Serial.println(value);
  return value;
}
