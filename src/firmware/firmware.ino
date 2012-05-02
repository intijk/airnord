#include <aJSON.h>
#include <Usb.h>
#include <adk.h>
#include <Servo.h>
#include "rp5.h"
#include "cloudPlatform.h"
#include "light.h"

#define MAX_PACK_LEN 70
#define DEBUG 1



int MotorLeftPin1 = 3;
int MotorLeftPin2 = 2;
int MotorRightPin1 = 5; 
int MotorRightPin2 = 4;
int CloudPlatformPinV=6;
int CloudPlatformPinH=9;
int lightPin=7;

aJsonObject* pack;
aJsonObject* action;
char* packp;
String str;
int angle,direct,vAngle,hAngle,vStepAngle,hStepAngle,V,H;
float amp;
uint8_t rcode;

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

//Store packet string in buffer str
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


void getPacketStringFromADK(char *str, int MaxLen){
  int i=0;
  char incomingByte;
  uint16_t len=MaxLen-1;
  uint8_t rcode;
  uint8_t pack_str[MAX_PACK_LEN];
  
  Usb.Task();
  if( adk.isReady() == false ) {
     Serial.println("adk.isReady() == false");
     return;
  }
  
  rcode=adk.RcvData(&len,pack_str);
  Serial.print("adk.RcvData return len=");
  Serial.println(len);
  while(pack_str[i]!=0x03 && i<len){
    str[i]=pack_str[i];
    i++;
  }
  if(pack_str[i]!=0x03){
    //Did not finish at this read
    //Serial.println("getPacketStringFromADK failed");
    str[0]=0;
  }else{
    str[i]=0;
  }
}

aJsonObject* getNextPackFromADK(){
        char pack_str[MAX_PACK_LEN];
        
        getPacketStringFromADK(pack_str,MAX_PACK_LEN);        
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

void setup() {
        Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps      
        if(Usb.Init()==-1){
          Serial.println("Usb.Init() is not finish.");
          while(1); //Usb.Init()==-1 then stop.
        }
      rp5.Stop();        
      cp.attachPin(CloudPlatformPinV,CloudPlatformPinH);       
      lt.attach(lightPin); 
}

int i,j;
void loop() { 
  pack=getNextPackFromADK();
  
  //pack=getNextPackFromSerial();
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
    Serial.println(amp);
    
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
  }
  delay(200);
  
}
