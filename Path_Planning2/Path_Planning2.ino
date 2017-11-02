/*
The maximum acceleration (180deg/s^2) and the acceleration duration (0.5seconds), is predefined in the library.
 
*/

#include "pathPlanning.h"

float angleInputServo1_0 = 2;        // This value changes with the movements of the 1st joint
float angleKnownServo1_f = 11;        // This value static and known and are preset in the library 

float angleInputServo2_0 = 2;         // This value changes with the movements of the 2nd joint 
float angleKnownServo2_f = 47;        // This value static and known and are preset in the library

float angleInputServo3_0 = 21;        // This value changes with the movements of the 3rd joint
float angleKnownServo3_f = 0;        // This value static and known and are preset in the library


void setup() {
Serial.begin(9600);
pathPlanning pathPlan;
delay(500);

Serial.println("Ready");
delay(500);

Serial.print("Dominant delta theta = ");
float deltaTheta = pathPlan.dominantServoDeltaTheta(angleInputServo1_0, angleInputServo2_0, angleInputServo3_0, angleKnownServo1_f, angleKnownServo2_f, angleKnownServo3_f);
Serial.println(deltaTheta);

Serial.print("totaltime = ");
float totalTime = pathPlan.timeTotal(deltaTheta);
Serial.println(totalTime);

Serial.print("dominant timeConstantVelocity = ");
float timeConstantVel = pathPlan.dominantTimeConstantVelocity(totalTime);
Serial.println(timeConstantVel);

Serial.print("dominant AccelerationCorrection = ");
float accelerationCor = pathPlan.dominantAccelerationCorrection(deltaTheta, totalTime);
Serial.println(accelerationCor);
delay(500);


Serial.println("");
Serial.print("Servo_1 timeConstantVelocity = ");
float servo1_delta = fabs(angleKnownServo1_f - angleInputServo1_0);
float servo1_timeConstantVelocity = pathPlan.individualTimeConstantVelocity(deltaTheta, servo1_delta, totalTime);
Serial.println(servo1_timeConstantVelocity);
Serial.print("Servo_1 acceleration amount  = ");
float servo1_acceleration = pathPlan.individualAcceleration(servo1_delta);
Serial.println(servo1_acceleration);

Serial.println("");
Serial.print("Servo_2 timeConstantVelocity = ");
float servo2_delta = fabs(angleKnownServo2_f - angleInputServo2_0);
float servo2_timeConstantVelocity = pathPlan.individualTimeConstantVelocity(deltaTheta, servo2_delta, totalTime);
Serial.println(servo2_timeConstantVelocity);
Serial.print("Servo_2 acceleration amount  = ");
float servo2_acceleration = pathPlan.individualAcceleration(servo2_delta);
Serial.println(servo2_acceleration);

Serial.println("");
Serial.print("Servo_3 timeConstantVelocity = ");
float servo3_delta = fabs(angleKnownServo3_f - angleInputServo3_0);
float servo3_timeConstantVelocity = pathPlan.individualTimeConstantVelocity(deltaTheta, servo3_delta, totalTime);
Serial.println(servo3_timeConstantVelocity);
Serial.print("Servo_3 acceleration amount  = ");
float servo3_acceleration = pathPlan.individualAcceleration(servo3_delta);
Serial.println(servo3_acceleration);

}

void loop() {

}


