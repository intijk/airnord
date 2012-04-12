#ifndef RP5_H
#define RP5_H
#include <Arduino.h>

class RP5{
public:

  //Require: MotorLeftPin1 and MotorRightPin1 must be pins which support analogWrite() .
  RP5(int MotorLeftPin1, 
      int MotorLeftPin2, 
      int MotorRightPin1, 
      int MotorRightPin2
      );
  RP5(int MotorLeftPin1, 
      int MotorLeftPin2, 
      int MotorRightPin1, 
      int MotorRightPin2,
      int LeftBound, 
      int RightBound);
      
  
  void Stop();
  void MoveForward();
  void MoveBackward();
  void MoveLeft();
  void MoveRight();
  void RotateLeft();
  void RotateRight();
  void Rotate(int Direction);
  void MoveAngle(int angle, float amp);

private:
  //pl1= Pin Left 1
  //pr1= Pin Right 1
  //lb = Left Bound
  int pl1,pl2,pr1,pr2,lb,rb;
  
  //Output the pins value, treat l1 and r1 as analog pins, l2 and r2 as digital pins.
  void output(int l1,int l2,int r1,int r2);
  
  //Necessory Init tasks.
  void Init();
};



RP5::RP5(int MotorLeftPin1, int MotorLeftPin2, int MotorRightPin1, int MotorRightPin2){
  pl1=MotorLeftPin1;
  pl2=MotorLeftPin2;
  pr1=MotorRightPin1;
  pr2=MotorRightPin2;
  lb=90;
  rb=90;

  Init();
}
RP5::RP5(int MotorLeftPin1, int MotorLeftPin2, int MotorRightPin1, int MotorRightPin2, int LeftBound, int RightBound){
  pl1=MotorLeftPin1;
  pl2=MotorLeftPin2;
  pr1=MotorRightPin1;
  pr2=MotorRightPin2;
  lb=LeftBound;
  rb=RightBound;

  Init();
}
void RP5::Init(){
  pinMode(pl1, OUTPUT);
  pinMode(pl2, OUTPUT);
  pinMode(pr1, OUTPUT);
  pinMode(pr2, OUTPUT);
}
void RP5:: RP5::Stop(){
  output(0,0,0,0);
}
void RP5:: MoveForward(){
  output(255,0,255,0);
}
void RP5:: MoveBackward(){
  output(0,1,0,1);
}
void RP5:: MoveLeft(){
  RotateLeft();
}
void RP5:: MoveRight(){
  RotateRight();
}
void RP5:: RotateLeft(){
  output(0,1,255,0);
}
void RP5:: RotateRight(){
  output(255,0,0,1);
}
void RP5:: Rotate(int Direction){
  if(Direction==0){//counter clockwise
    output(0,1,255,0);
  }
  else if(Direction==1){//clockwise
    output(255,0,0,1);
  }
}
void RP5:: MoveAngle(int Angle, float amp){
  //angle -180 ~ 180
  //amplitude  0 ~ 1

  double angle=(Angle+360)%360;
  double rad=angle*PI/180;
  double l,r;
  int l1,l2,r1,r2;

  if(angle>=180){
    angle-=360;
  }

  Serial.print("angle=");
  Serial.println(angle);
  Serial.print("rad=");
  Serial.println(rad);
  if(0 <= angle && angle < 90){
    l=1;
    r=-cos(2*rad);
  }
  else if(90 <= angle && angle <=180 ){
    l=-cos(2*rad);
    r=1;
  }
  else if(-180 <= angle && angle < -90){
    l=-1;
    r=cos(2*rad);
  }
  else if(-90 <= angle && angle <0){
    l=cos(2*rad);
    r=-1;

  }
  Serial.println(l);
  Serial.println(r);
  Serial.println(amp);
  l=l*255*amp;
  r=r*255*amp;
  Serial.print("l=");
  Serial.println(l);
  Serial.print("r=");
  Serial.println(r);
  if(abs(l)<lb){
    l=0;
  }
  if(abs(r)<rb){
    r=0;
  }
  if(l>=0.0){
    l1=int(l);
    l2=0;
  }
  else{
    l1=255+int(l);
    l2=1;
  }

  if(r>=0.0){
    r1=int(r);
    r2=0;
  }
  else{
    r1=255+int(r);
    r2=1;
  }
  Serial.println(l1);
  Serial.println(l2);
  Serial.println(r1);
  Serial.println(r2);
  output(l1,l2,r1,r2);
}
void RP5:: output(int l1,int l2, int r1,int r2){
  Serial.print("l1=");
  Serial.println(l1);
  Serial.print("pl1=");
  Serial.println(pl1);
  analogWrite(pl1,l1);
  digitalWrite(pl2,l2);
  Serial.print("pr1=");
  Serial.println(pr1);
  Serial.print("r1=");
  Serial.println(r1);
  analogWrite(pr1,r1);
  digitalWrite(pr2,r2);
}

#endif

