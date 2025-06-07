#include <PID_v1.h>


//Define Variables we'll be connecting to
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
//double kp = 5 , ki = 1 , kd = 0.01; 
double Kp=5, Ki=1, Kd=0.01;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
void pid_init(){


myPID.SetMode(AUTOMATIC);
myPID.SetOutputLimits(-255, 255); 
}