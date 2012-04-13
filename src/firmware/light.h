#ifndef LIGHT_H
#define LIGHT_H

class light{
	public:
		void attach(int lightPin);
		void LightOn(float amp);
		void LightOff();
	private:
		int pin;
};

void light::attach(int lightPin){
	pin=lightPin;
        pinMode(lightPin,OUTPUT);
}

void light::LightOn(float amp){
        Serial.println(amp);
	//### should judge if the pin is analogWrite() enabled;
	//analogWrite(pin, constrain(amp,0,255));
	digitalWrite(pin,HIGH);
}
void light::LightOff(){
	digitalWrite(pin, LOW);
}




#endif
