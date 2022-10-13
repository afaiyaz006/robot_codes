#include <AFMotor.h>
AF_DCMotor motor_1(3);///M2 RIGHT
AF_DCMotor motor_2(2);///M3  LEFT
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  motor_1.setSpeed(100);
  motor_1.run(BACKWARD);
  motor_2.setSpeed(100);
  
  motor_2.run(BACKWARD);
}
