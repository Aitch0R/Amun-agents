class IRRCV{
public:
String address;
String msg;
int pin;
int len=0;
int sec[68];
long current=0;
long tcurrent=0;
long last=0;
long tlast=0;
long diff=0;
long tdiff=0;
boolean block=false;
String io="";


	IRRCV(int pin){		
		pinMode(pin,INPUT_PULLUP);
		address="0,"+String(pin)+",";
		
	}

	void debounce(){
		current=micros();
		diff=current-last;
		tdiff=-diff;
		diff=max(diff,tdiff);
		if (diff>300){
		regist();}
		last=current;
	}

	void reset(){
			memset(sec, 0, 67);
			len=0;	
	}

	void regist(){
		if (diff<10000){	
			sec[len]=diff;
			len+=1;
		}else{
			reset();
		}
		if (len == 67){
			binTrans();
			reset();		
		}
	}

	   void binTrans(){
                int i=3;
                io="";
                while (i < 67){
                        if (sec[i]<1000){
                                io=io+"0";
                        }else if (sec[i]>1000){
                                io=io+"1";
			}
                        i=i+2;
		}
	send();           
	}

	void send(){
		Serial.println(address+io);
	}
};
