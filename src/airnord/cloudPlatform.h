#ifndef CLOUDPLATFORM_H
#define CLOUDPLATFORM_H


class cloudPlatform{
	public:
		cloudPlatform();
                void attach(int VerticalPin,int HerizontalPin); 
		void HAngle(int angle);
		void VAngle(int angle);
		void HStep(int step);
		void VStep(int step);
		void Vector(int vAngle,int hAngle);
		void StepVector(int vStepAngle, int hStepAngle);
		int getVAngle();
		int getHAngle();
	private:
                Servo vServo,hServo;
		int vPin,hPin,vValue,hValue;
		int vLB,vUB,hLB,hUB;
};

cloudPlatform::cloudPlatform(){
	vValue=90;
	hValue=90;
	vLB=10;
	vUB=179;
	hLB=10;
	hUB=179;
        
}

void cloudPlatform::attach(int VerticalPin,int HerizontalPin){  
        vPin=VerticalPin;
        hPin=HerizontalPin;
        pinMode(VerticalPin,OUTPUT);
        pinMode(HerizontalPin,OUTPUT);
	vServo.attach(vPin);
	hServo.attach(hPin);
	HAngle(0);
        VAngle(0);
}

void cloudPlatform::HAngle(int angle){
	angle+=90;
	hValue=constrain(angle,hLB,hUB);
	hServo.write(hValue);	
}
void cloudPlatform::VAngle(int angle){
	angle+=90;
	vValue=constrain(angle,vLB,vUB);
	vServo.write(vValue);
}

void cloudPlatform::HStep(int stepAngle){
	hValue=constrain(hValue+stepAngle,hLB,hUB);
	hServo.write(hValue);
}
void cloudPlatform::VStep(int stepAngle){
	vValue=constrain(vValue+stepAngle,vLB,vUB);
	vServo.write(vValue);
}
void cloudPlatform::Vector(int vAngle,int hAngle){
	vValue=constrain(vAngle+90,vLB,vUB);
	hValue=constrain(hAngle+90,hLB,hUB);	
	vServo.write(vValue);
	hServo.write(hValue);
}
void cloudPlatform::StepVector(int vStep,int hStep){
	vValue=constrain(vValue+vStep,vLB,vUB);
	hValue=constrain(hValue+hStep,hLB,hUB);
	vServo.write(vValue);
	hServo.write(hValue);
}
int cloudPlatform::getVAngle(){
	return vValue;
}
int cloudPlatform::getHAngle(){
	return hValue;
}

#endif
