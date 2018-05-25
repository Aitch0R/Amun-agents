/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
// defines pins numbers
class WindowV{
public:
int dirPin;
int stepPin;
int enPin;
int servoPin;
int limitPin;
string address;
 
Window(int dir_pin, int stp_pin, int en_pin, int servo_pin, int limit_pin)
    stepPin = stppin;      #input
    dirPin = dirpin;       #input
    enPin=en_pin;
    servoPin=servo_pin;
    limitPin=limit_pin;
    address=;
 
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);

void move(int direction, int steps) {
    digitalWrite(dirPin,direction); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < steps; x++) {
        digitalWrite(stepPin,HIGH); 
        delayMicroseconds(stp_dly); 
        digitalWrite(stepPin,LOW); 
        delayMicroseconds(stp_dly); 
    }

void process(String inc[]){
    //enable stepper
    //retcact servo
    move(inc[3].toInt(),inc[4].toInt());
    //deploy seervo
    //delay (give time for prev step)
    //move stepper few steps
    //disable servo
    //disable stepper
}

void status(){
    writer.print(address+"roger");
}

};
