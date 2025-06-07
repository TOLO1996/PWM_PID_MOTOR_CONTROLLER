#include "Arduino.h"
#include <TimerOne.h>

#define IN1 6
#define IN2 7
#define PWM_IN 10
#define LimitPin 12
#define ENCA 2 // YELLOW
#define ENCB 3 // WHITE

volatile int posi = 0;
void motor_read();
void motor_set(int PWM);
void motor_homing();
void motor_set_pos(int pos);
void motor_init(){
 // Serial.begin(115200);
//konfiguracja enkodera obrotowego
pinMode(ENCA,INPUT);
pinMode(ENCB,INPUT);
attachInterrupt(digitalPinToInterrupt(ENCA),motor_read,RISING);
//konfiguracja pinow sterowania silnikiem
//pinMode(PWM_IN,OUTPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
//konfiguracja krancowki
pinMode(LimitPin, INPUT);
//konfiguracja PWM
//Timer1.initialize(2500);  // 40 us = 25 kHz
//Timer1.pwm(PWM_IN, 0);
//stan poczatkowy
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
}
void motor_set(int PWM){
  if (PWM>0) {
    //Timer1.setPwmDuty(PWM_IN, PWM);
    analogWrite(PWM_IN,PWM);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
  }
  else if (PWM<0) {
  //Timer1.setPwmDuty(PWM_IN, abs(PWM));
  analogWrite(PWM_IN,abs(PWM));
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  }
  else {
    //Timer1.setPwmDuty(PWM_IN, 0);
    analogWrite(PWM_IN,0);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
}
}

void motor_read(){
  noInterrupts(); // disable interrupts temporarily while reading
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
  interrupts(); // turn interrupts back on
}
void motor_homing(){
  Serial.println("HOMING"); //print action
  while(digitalRead(LimitPin) == HIGH){
  motor_set(80);
  }
   motor_set(0);
  posi =0;
  //isRunning();
  Serial.println("Homing Completed");
}
int motor_get(){
  return posi;
}
void motor_set_pos(int pos){
  posi = pos;
}