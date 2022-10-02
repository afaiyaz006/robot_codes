#include <AFMotor.h>
enum multipurpose{ testing_mode=0,manual_control=1,null_mode=-1};
multipurpose mp;
AF_DCMotor motor_1(2);///M2 RIGHT
AF_DCMotor motor_2(3);///M3  LEFT
int incomingByte = 0; // for incoming serial data
uint8_t i=0;

///IMPORTANT BACKWARD IS FORWARD
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
void rc_control(){
    incomingByte = Serial.read();
    //Serial.print("I received: ");
    //Serial.println(incomingByte);
    
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
    else if(incomingByte=='X'){
       Serial.print("nullmode\n");
       mp=null_mode;
    }
    else{
      brake();
      
      incomingByte='*';
    }
}
void testing(){
  
  incomingByte = Serial.read();
  
  if(incomingByte=='X'){
    Serial.print("nullmode");
    mp=null_mode;
  }
  else if(incomingByte=='m'){
    motor_1.run(BACKWARD);
    motor_2.run(BACKWARD);
    // increase speed from zero to max
    for (i=0; i<=100; i++) 
    {
      Serial.print("speed:");
      Serial.println(i);
      motor_1.setSpeed(i);  
      motor_2.setSpeed(i);  
      delay(10);
    }
    motor_1.run(RELEASE);
    motor_2.run(RELEASE);
    delay(1000);
    motor_1.run(FORWARD);
    motor_2.run(FORWARD);
    // Decelerate from maximum speed to zero
    for (i=100; i!=0; i--) 
    {
      Serial.print("speed:");
      Serial.println(i);
      motor_1.setSpeed(i);  
      motor_2.setSpeed(i);  
      delay(10);
  
    }
    motor_1.run(RELEASE);
    motor_2.run(RELEASE);
    delay(1000);
    mp=null_mode;
    Serial.print("nullmode\n");
  }
  
}
void stay_still(){
    motor_1.setSpeed(0);
    motor_2.setSpeed(0);
    motor_1.run(RELEASE);
    motor_2.run(RELEASE);
}
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  motor_1.setSpeed(100);
  motor_1.run(RELEASE);
  motor_2.setSpeed(100);
  motor_2.run(RELEASE);
  mp=null_mode;
}

void loop() {
  uint8_t i;
  motor_1.setSpeed(100);
  motor_2.setSpeed(100);
  if (Serial.available() > 0) {
    // read the incoming byte:
    if(mp==null_mode){
      incomingByte=Serial.read();
      if(incomingByte=='r'){
        Serial.println("manualmode\n");
        mp=manual_control;
      }
      else if(incomingByte=='t'){
        Serial.println("testingmode\n");
        mp=testing_mode;
       
        
      }
      else{
        mp=null_mode;
      }
    }
    else if(mp==manual_control){
      
        rc_control();
    }
    else if(mp==testing_mode){
        testing();
    }
    else if(mp==null_mode){
        stay_still();
    }
    
    
    
    
    
  }

  

  
  
}
