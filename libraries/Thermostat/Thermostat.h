class Thermostat {
public:

int pin1;
int pin2;
int pinstat;
int thisStep=0;
String address;
String cmdid="0";

Thermostat (int pin_1, int pin_2){
	pin1 = pin_1;
	pin2 = pin_2;
	pinMode(pin1,OUTPUT);
	pinMode(pin2,OUTPUT);
	digitalWrite(pin1,LOW);
	digitalWrite(pin2,LOW);
	pinstat=0;
	address=String(pin1)+",";
}

int step(int dir){
	thisStep=thisStep+dir;
	if (thisStep==4){
		thisStep=0;
	}else if (thisStep==-1){
		thisStep=3;
	}
	switch (thisStep) {
		case 0:  // 01
			digitalWrite(pin1, LOW);
			digitalWrite(pin2, HIGH);
			break;
		case 1:  // 11
			digitalWrite(pin1, HIGH);
			digitalWrite(pin2, HIGH);
			break;
		case 2:  // 10
			digitalWrite(pin1, HIGH);
			digitalWrite(pin2, LOW);
			break;
		case 3:  // 00
			digitalWrite(pin1, LOW);
			digitalWrite(pin2, LOW);
			break;
	}
	return thisStep;
}

void turn(int direction, int steps){
	int dir=1;
	int currentStep;
	for (int i=1; i<=steps*2; i++){
		if (direction==1){
			dir=1;
		}else{
			dir=-1;
		}
		currentStep=step(dir);
		delay (50);
	}
	if (steps>=100){
		while (currentStep!=3){
			currentStep=step(dir);
		}
	}
}
	
void process (String incoming[]){
	cmdid=incoming[1].toInt();
	turn(incoming[2].toInt(), incoming[3].toInt());
	status();	
}

void status (){
	logger.m(address+cmdid);
}
};
