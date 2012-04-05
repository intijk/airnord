#include <aJSON.h>
#include <Usb.h>
#include <adk.h>
#include <Servo.h>
#include "rp5.h"
#include "cloudPlatform.h"
#include "light.h"

#define MAX_PACK_LEN 100
#define DEBUG 0



void getPacketStringFromSerial(char* str, int MaxLen){
  int i;
  char incomingByte;
  for(i=0;i<MaxLen-1;i++){
    while(Serial.available()<=0);
    incomingByte=Serial.read();
    if(incomingByte==0x03){
      break;
    }
    str[i]=incomingByte;
  }
  str[i]='\0';
}

aJsonObject* getNextPackFromSerial(){
        char pack_str[MAX_PACK_LEN];
        getPacketStringFromSerial(pack_str,MAX_PACK_LEN);
        
        aJsonObject* pack=aJson.parse(pack_str);

        if(DEBUG){
          aJsonObject* action=aJson.getObjectItem(pack,"action");
          char *packp=aJson.print(pack);
          Serial.println("===");
          Serial.println(pack_str);
          Serial.println("---");
          Serial.println(packp);
          Serial.println("...");
          Serial.println(action->valuestring);
          free(packp);
        }
        return pack;
}

int MotorLeftPin1 = 3;
int MotorLeftPin2 = 2;
int MotorRightPin1 = 9;
int MotorRightPin2 = 8;
int CloudPlatformPinV=5;
int CloudPlatformPinH=6;
int lightPin=7;

RP5 rp5(MotorLeftPin1, MotorLeftPin2, MotorRightPin1, MotorRightPin2);
cloudPlatform cp;
light lt;

USB Usb;
ADK adk(&Usb, "Google, Inc.",
              "DemoKit",
              "DemoKit Arduino Board",
              "1.0",
              "http://www.android.com",
              "0000000012345678");


void setup() {
  
        Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
        rp5.Stop();
        
        if(Usb.Init()==-1){
          Serial.println("Usb.Init() is not finish.");
          while(1); //Usb.Init()==-1 then stop.
        }
        
        cp.attach(CloudPlatformPinV,CloudPlatformPinH);
        
        lt.attach(lightPin);
        
}



aJsonObject* pack;
aJsonObject* action;
char* packp;
String str;
int angle,direct,vAngle,hAngle,vStepAngle,hStepAngle,V,H;
float amp;
uint8_t rcode;


void loop() {
/*
  uint8_t pack_str[MAX_PACK_LEN];
  uint16_t len=MAX_PACK_LEN;
  uint8_t rcode;
  
  Usb.Task();
  if( adk.isReady() == false ) {
     return;
  }
  rcode=adk.RcvData(&len,pack_str);
  
#ifdef DEBUG
  if(len>0){
    Serial.println("\n==========");
    Serial.print("rcode=");
    Serial.println(rcode,HEX);
    Serial.print("len=");
    Serial.println(len,DEC);
    int i;
    for(i=0;i<len-1;i++){
      Serial.print(pack_str[i],HEX);
      Serial.print(" ");
    }
    Serial.println(pack_str[i],DEC);
    
    if(pack_str[0]==2){
      rp5.MoveAngle(int(pack_str[2]/255.0*360),1);
    }else{
      rp5.Stop();
    }
  }
#endif
*/

 
  pack=getNextPackFromSerial();
  if(pack!=NULL){
    action=aJson.getObjectItem(pack,"action");
    str=action->valuestring;  
    angle=aJson.getObjectItem(pack,"angle") -> valueint;
    vAngle=aJson.getObjectItem(pack,"vAngle") -> valueint;
    hAngle=aJson.getObjectItem(pack,"hAngle") -> valueint;
    V=aJson.getObjectItem(pack,"V") -> valueint;
    H=aJson.getObjectItem(pack,"H") -> valueint;
    vStepAngle=aJson.getObjectItem(pack,"vStepAngle") -> valueint;
    hStepAngle=aJson.getObjectItem(pack,"hStepAngle") -> valueint;

   
    amp=aJson.getObjectItem(pack,"amp") -> valuefloat;  
    direct=aJson.getObjectItem(pack,"direct") -> valueint;
    Serial.println(str);
    
    if(str.equals("Stop")){
      rp5.Stop();
    }else if(str.equals("MoveForward")){
      rp5.MoveForward();
    }else if(str.equals("MoveBackward")){
      rp5.MoveBackward();
    }else if(str.equals("MoveLeft")){
      rp5.MoveLeft();
    }else if(str.equals("MoveRight")){
      rp5.MoveRight();
    }else if(str.equals("RotateLeft")){
      rp5.RotateLeft();
    }else if(str.equals("RotateRight")){
      rp5.RotateRight();
    }else if(str.equals("Rotate")){
      rp5.Rotate(direct);
    }else if(str.equals("MoveAngle")){
      rp5.MoveAngle(angle,amp);
    }else if(str.equals("TripodHAngle")){
      cp.HAngle(angle);
    }else if(str.equals("TripodVAngle")){
      cp.VAngle(angle);
    }else if(str.equals("TripodHStep")){
      cp.HStep(angle);
    }else if(str.equals("TripodVStep")){
      cp.VStep(angle);
    }else if(str.equals("TripodVector")){
      cp.Vector(V,H);
    }else if(str.equals("TripodStepVector")){
      cp.StepVector(V,H);
    }else if(str.equals("LightOn")){
      lt.LightOn(amp);
    }else if(str.equals("LightOff")){
      lt.LightOff();
    }
    
    
    
    free(packp);
    aJson.deleteItem(pack);
    
    delay(10);
  }
  
  
  /*
  int i;
  for(i=-90;i<90;i++){
    cp.HAngle(i);
    cp.VAngle(i);
    delay(15);
    lt.LightOn(1);
  }
  for(i=90;i>=-90;i--){
    cp.HAngle(i);
    cp.VAngle(i);
    delay(15);
    lt.LightOff();
  }
  
  */
  /*
  lt.LightOn(1);
  delay(1000);
  lt.LightOff();
  delay(1000);
  */
  
}
