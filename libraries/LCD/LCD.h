//#include <LiquidCrystal.h>

class LCD{
public:
LiquidCrystal* lcdb;
int blPin; //backlight
int blState;
unsigned long blOnTime=0;
unsigned long blOnPeriod=10000;

String address;

	LCD (int add, LiquidCrystal* lcdr, int bl){
		lcdb=lcdr;
		blPin=bl;
		pinMode(blPin,OUTPUT);
		address=String(add)+",";
	}

	void process(String inc[]){
		switch (inc[2].toInt()){
			case 0:
				lcdb->clear();
				lcdb->print(inc[3]);
				lcdb->setCursor(0, 1);
				lcdb->print(inc[4]);
      				break;
			case 1:
				bkLight(inc[3].toInt());
      				break;
			case 2:
      				break;
		}
	}


	void setCursor(int c, int r){
		lcdb->setCursor(c,r);
	}

	void begin(int c, int r){
		lcdb->begin(c,r);
	}
	
	void print(String txt){
		lcdb->print(txt);
	}

	void bkLight(int state){
		digitalWrite(blPin,state);
		blState=state;
		if (blState==1){
			blOnTime=millis();
		}
	}

	void loop(){
		if (blState==1){
			if (millis()>=blOnTime+blOnPeriod){
				bkLight(0);
			}
		}
	}

	void status(){
		writer.print(address+"roger");
	}

};
