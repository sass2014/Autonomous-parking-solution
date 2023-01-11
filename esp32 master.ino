//Lab report 1 UoN
// Department of Electrical and Electronic Engineering
// ESP32 master code
// UoN EEEBot 2022
// student id: 20363161

#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04

const int trigPin = 5;  //hc sr04 sensor
const int echoPin = 18;
#define SOUND_SPEED 0.034 // 0.034 metre per millisecond
#define CM_TO_INCH 0.393701  //1cm = 0.393701 inches
long duration;
float distanceCm;
int flag;

int16_t leftMotor_speed = 0;
int16_t rightMotor_speed = 0;
int16_t servoAngle = 0;

void setup() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input

  Wire.beginTransmission(I2C_SLAVE_ADDR);  // transmit to device #4
  //drive forwards for 1 second
  int16_t leftMotor_speed = 230;
  int16_t rightMotor_speed = 230;
  int16_t servoAngle = 90;
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor_speed & 0x000000FF));
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor_speed & 0x000000FF));
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(servoAngle & 0x000000FF));
  delay(1000);
  leftMotor_speed = 0;  //stop after 1 second
  rightMotor_speed = 0;
  servoAngle = 90;
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor_speed & 0x000000FF));
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor_speed & 0x000000FF));
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(servoAngle & 0x000000FF));
  delay(500);
  // turn 180 degrees
  leftMotor_speed = 200;   //turn a 180 degrees but left motor slower
  rightMotor_speed = 255;  //than right motor
  servoAngle = 180;
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor_speed & 0x000000FF));
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor_speed & 0x000000FF));
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(servoAngle & 0x000000FF));
  delay(1000);
  // reverse until obstacle is 10cm away
  leftMotor_speed = -230;
  rightMotor_speed = -230;
  servoAngle = 90;
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor_speed & 0x000000FF));
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor_speed & 0x000000FF));
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(servoAngle & 0x000000FF));
 //if obstacle is 10cm away, then stop
  if (flag == 1); 
  {
    leftMotor_speed = 0;
    rightMotor_speed = 0;
    servoAngle = 90;
    Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
    Wire.write((byte)(leftMotor_speed & 0x000000FF));
    Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
    Wire.write((byte)(rightMotor_speed & 0x000000FF));
    Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
    Wire.write((byte)(servoAngle & 0x000000FF));
    delay(1000);
  }
  //turn 90 degrees clockwise
  leftMotor_speed = 255;  //left motor speed more than right to turn clockwise
  rightMotor_speed = 200;
  servoAngle = 0;  //90 degrees clockwise from the previous 90 degrees
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor_speed & 0x000000FF));
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor_speed & 0x000000FF));
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(servoAngle & 0x000000FF));
  delay(1000);
  //reverse until obstacle is 10cm away
  leftMotor_speed = -230;
  rightMotor_speed = -230;
  servoAngle = 90;
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(leftMotor_speed & 0x000000FF));
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
  Wire.write((byte)(rightMotor_speed & 0x000000FF));
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
  Wire.write((byte)(servoAngle & 0x000000FF));
  //stop when obstacle is 10cm away
  if (flag ==1)
  {
    leftMotor_speed = 0;
    rightMotor_speed = 0;
    servoAngle = 90;
    Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));
    Wire.write((byte)(leftMotor_speed & 0x000000FF));
    Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));
    Wire.write((byte)(rightMotor_speed & 0x000000FF));
    Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));
    Wire.write((byte)(servoAngle & 0x000000FF));
    delay(1000);
  }
  Wire.endTransmission();
  delay(100);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  if (distanceCm == 10)
    flag = 1;
  else
    flag = 0;
}