#include <AFMotor.h>
AF_DCMotor motor_1(2);///M2 RIGHT
AF_DCMotor motor_2(3);///M3  LEFT
int incomingByte = 0; // for incoming serial data
uint8_t i=0;
///FORWARD IS BACKWARD
void left(){
    motor_1.run(BACKWARD);
    motor_2.run(FORWARD);
    delay(10);
}
void right(){
    motor_2.run(BACKWARD);
    motor_1.run(FORWARD);
    delay(10);
}
void brake(){
    motor_1.run(RELEASE);
    motor_2.run(RELEASE);
    motor_1.setSpeed(0);
    motor_2.setSpeed(0);
    incomingByte='*';
  
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  motor_1.setSpeed(100);
  motor_1.run(RELEASE);
  motor_2.setSpeed(100);
  motor_2.run(RELEASE);


}

void loop() {
  // put your main code here, to run repeatedly:
   motor_1.setSpeed(100);
   motor_2.setSpeed(100);
   if (Serial.available() > 0) {
        incomingByte=Serial.read();
        if(incomingByte=='w'){
          motor_1.run(BACKWARD);
          motor_2.run(BACKWARD);
          delay(10);
          incomingByte='*';
       }
       else if(incomingByte=='s'){
          motor_1.run(FORWARD);
          motor_2.run(FORWARD);
          delay(10);
          incomingByte='*';
      
      }
      else if(incomingByte=='a'){
          left();
          incomingByte='*';
      }
      else if(incomingByte=='d'){
          right();
          incomingByte='*';
      }
      else{
        brake();
      
        incomingByte='*';
      }
   }
}
