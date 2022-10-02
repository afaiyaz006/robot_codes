#include <AFMotor.h>

AF_DCMotor motor_1(2);
AF_DCMotor motor_2(3);
double GetTemp(void);
int incomingByte=0;

void setup() 
{
  
  Serial.begin(9600);
  //Set initial speed of the motor & stop
  motor_1.setSpeed(20);
  motor_1.run(RELEASE);
  motor_2.setSpeed(20);
  motor_2.run(RELEASE);
}


void loop() {
  // put your main code here, to run repeatedly:
    uint8_t i=0;
    i=0;
    Serial.write(0);
    //Serial.print(',');
    
   
    delay(100);
    //Serial.print(',');
    if (Serial.available()>0) {
     
      incomingByte=Serial.read();
      if(incomingByte=='x'){
         motor_1.run(BACKWARD);
         for (i=0; i<=230; i++) 
         {
            
            motor_1.setSpeed(i);
            Serial.write(i);
            //Serial.print(',');
            delay(100);
            //Serial.print(',');
            
         }
         for (i=230; i!=0; i--) 
         {
            
            motor_1.setSpeed(i);
            Serial.write(i);
            //Serial.print(',');
            delay(100);
            //Serial.print(',');
         }
         motor_1.run(RELEASE);

         incomingByte='*';
       }
       else if(incomingByte=='y'){
         motor_2.run(BACKWARD);
         for (i=0; i<=230; i++) 
         {
            
            motor_2.setSpeed(i);
            Serial.write(i);
            //Serial.print(',');
            delay(100);
            
         }
         for (i=230; i!=0; i--) 
         {
            
            motor_2.setSpeed(i);
            Serial.write(i);
            //Serial.print(',');
            delay(100);
            //Serial.print(',');
         }
         motor_2.run(RELEASE);
         incomingByte='*';
          
       }
       
    }
 
}
