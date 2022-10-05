#include <AFMotor.h>    //Adafruit Motor Shield Library. First you must download and install AFMotor library
#include <QTRSensors.h> //Pololu QTR Sensor Library. First you must download and install QTRSensors library
  
AF_DCMotor motor1(2); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2(3); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
  
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
float Kp =0; 
float Ki =0;
float Kd =0;
int P;
int I;
int D;
int lastError = 0;
boolean onoff = false;

const uint8_t maxspeeda = 250;
const uint8_t maxspeedb = 250;
const uint8_t basespeeda = 0;
const uint8_t basespeedb = 0;


=
void forward_brake(int posa, int posb) {
    motor1.setSpeed(posa);
    motor2.setSpeed(posb);
    motor1.run(FORWARD);
    motor2.run(FORWARD);

}
void PID_control() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  int error = 2300 - position;
  Serial.println(position);
  
  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  //int motorspeed = P*Kp + I*Ki 
  int motorspeed = P*Kp + D*Kd; ;
  
  int motorspeeda = basespeeda + motorspeed;
  int motorspeedb = basespeedb - motorspeed;
  
  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = 0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  } 
  forward_brake(motorspeeda, motorspeedb);
}
void calibration() {
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
}
void setup() {
  
  Serial.begin(9600);
  delay(1000);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A5,A4,A3,A2,A1,A0}, SensorCount);
  pinMode(LED_BUILTIN, OUTPUT);
  calibration(); 
  forward_brake(0, 0);
}



void loop() {
    Serial.print("WORKING");
    PID_control();
    forward_brake(0,0);
  
}
