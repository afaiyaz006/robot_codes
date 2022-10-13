#include <AFMotor.h>    //Adafruit Motor Shield Library. First you must download and install AFMotor library
#include <QTRSensors.h> //Pololu QTR Sensor Library. First you must download and install QTRSensors library
  
AF_DCMotor motor1(1); //create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2(4); //create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
  
QTRSensors qtr;
const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];
float Kp =0.102; 
float Ki =0;
float Kd =0;
int P;
int I;
int D;
int lastError = 0;

const uint8_t maxspeeda = 150;
const uint8_t maxspeedb = 150;
const uint8_t basespeeda = 80;
const uint8_t basespeedb = 80;



void forward_brake(int posa, int posb) {
    motor1.setSpeed(posa);
    motor2.setSpeed(posb);
    motor1.run(FORWARD);
    motor2.run(BACKWARD);

}
void PID_control() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  int error = 2500 - position;
  Serial.print(position);
  Serial.print(' ');

  
  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  //int motorspeed = P*Kp + I*Ki 
  int motorspeed = P*Kp + D*Kd; 
  //Serial.print("Position:");
  //Serial.print(position);
  //Serial.print("P:");
  //Serial.print(P);
  //Serial.print("I:");
  //Serial.print(I);
  //Serial.print("D:");
  //Serial.println(D);
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
  Serial.print(motorspeeda);
  Serial.print(' ');
  Serial.print(motorspeedb);
  Serial.print(' ');
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print(' ');
  }
  Serial.println();
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
  qtr.setSensorPins((const uint8_t[]){A0,A1,A2,A3,A4,A5}, SensorCount);
  pinMode(LED_BUILTIN, OUTPUT);
  calibration(); 
  forward_brake(0, 0);
}



void loop() {
    PID_control();
}
