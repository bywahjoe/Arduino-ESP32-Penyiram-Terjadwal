#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

bool repeatMin=false;
String tempMin;
String jadwal[]={
  //Tanggal 08 Jam 22:03
  //"08+AUTO",
  "08+22:38",
  "08+22:39",
  
};
int total=(sizeof(jadwal) / sizeof(jadwal[0]));
void setup() {
  rtc.begin();
  Serial.begin(115200);
  Serial2.begin(115200);

  //tahun,bulan,tanggal,jam,menit,detik
  //rtc.adjust(DateTime(2021, 6, 8, 20, 56, 30));

}
void loop() {
  // put your main code here, to run repeatedly:
  //Serial2.write('a');
  //delay(3000);
  String waktu,pecah,omin;
  delay(5000);
  char format[] = "DD+hh:mm:ss";
  char onlyDate []= "DD";
  char onlyMin[]="mm";
  
  DateTime now = rtc.now();  

  waktu=now.toString(format);
  pecah=now.toString(onlyDate);
  omin=now.toString(onlyMin);

////  Serial.println(pecah);
////  Serial.println(waktu);
//
  for (int i = 0; i < (sizeof(jadwal) / sizeof(jadwal[0])); i++) {
    if(jadwal[i].startsWith(pecah) && jadwal[i].endsWith("AUTO")){
      //Detect AUTO
      Serial.println("Detect AUTO");
      Serial2.write('a');
      //if(!repeatMin){Serial2.write('a');repeatMin=true;}
      break;  
    }  
    else if (waktu.startsWith(jadwal[i]))
    {
      //Detect Scheduler
      if(!repeatMin){
        Serial.print("Detect Scheduler:");Serial.println(jadwal[i]);
        Serial2.write('n');repeatMin=true;tempMin=omin;
      }
      break;
    }else if(i==total-1){repeatMin=false;}
 }
  if(omin!=tempMin){repeatMin=false;}
// Serial.println(total);
}
