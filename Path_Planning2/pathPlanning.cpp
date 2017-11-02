/*
	This libraries functionality is to take in servos' current and goal positions and based on those and the acceleration constrients (placed inside the library) 
	compute the amount of time(sec) to apply acceleration(deg/s^2), constant velocity(deg/s) and the amount of acceleration to be applied during 
	the acceleration time periode.
*/

#include "Arduino.h"
#include "pathPlanning.h"

// this function finds and returns the biggest duration of the Constant Velocity  
float pathPlanning::dominantTimeConstantVelocity(float totalTime){

	float timeConstantVelocity;

	  if(totalTime >= 2 * timeAcceleration){
		  timeConstantVelocity = (totalTime - (2 * timeAcceleration)); 
		  return(timeConstantVelocity);   
	   }else{
		  timeConstantVelocity = 0; 
		  return(timeConstantVelocity);
	   }
}

// This function finds and return the Constant Velocity duration a chosen servo needs to have in order to fulfill the overall timeTotal and
// acceleration constrients.
// It takes arguments from the biggestServoDeltaTheta() and timeTotal() functions aswell as the specific servos delta theta.
float pathPlanning::individualTimeConstantVelocity(float dominant_deltaTheta, float individual_deltaTheta, float totalTime) {

	float timeConstantVelocity;
	float individualTimeTotal = timeTotal(individual_deltaTheta);

		if(dominant_deltaTheta > individual_deltaTheta && individualTimeTotal > 2 * timeAcceleration){
			timeConstantVelocity = (individualTimeTotal - (2 * timeAcceleration));
			return(timeConstantVelocity);
		}
		if(dominant_deltaTheta == individual_deltaTheta){
			timeConstantVelocity = dominantTimeConstantVelocity(totalTime);
			return(timeConstantVelocity);
		}
		else {
			return(0);
		}
}

// This function finds and returns the biggest amount of acceleration that the servo which has to travle the furtheste achrives.
// It takes arguments from the biggestServoDeltaTheta() and timeTotal().
float pathPlanning::dominantAccelerationCorrection(float dominant_deltaTheta, float totalTime){

	float acceleration;
	  if(totalTime < 2 * timeAcceleration){
		  acceleration = (dominant_deltaTheta / (timeAcceleration * timeAcceleration));
		  return(acceleration);
	   }else{
		  acceleration = 180;
		  return(acceleration);
	   }
}

// This function finds and returns the acceleration needed for a specific servo, for it to reach its position simultaneously with the other
// servos
// It takes an argument from the specific servo, its delta theta. 
float pathPlanning::individualAcceleration(float individual_deltaTheta) {

	float acceleration;
	float individualTimeTotal = timeTotal(individual_deltaTheta);

	if(individualTimeTotal < 2 * timeAcceleration){
		acceleration = (individual_deltaTheta / (timeAcceleration * timeAcceleration));
		return(acceleration);
	}else {
		acceleration = 180;
		return(acceleration);
	}

}

// This function finds and returns the biggest delta theta value of three servos.
// It takes three arguments from the servos' (their current position) and three arguments which are the servos' desired position.
float pathPlanning::dominantServoDeltaTheta(float inputServo1_0, float inputServo2_0, float inputServo3_0, float knownServo1_f, float knownServo2_f, float knownServo3_f){
	
		float servo1_deltaTheta = fabs(knownServo1_f - inputServo1_0);
		float servo2_deltaTheta = fabs(knownServo2_f - inputServo2_0);
		float servo3_deltaTheta = fabs(knownServo3_f - inputServo3_0);
      
	  if(servo1_deltaTheta > servo2_deltaTheta && servo1_deltaTheta > servo3_deltaTheta){
		  return(servo1_deltaTheta);
	   }
        
	  if(servo2_deltaTheta > servo1_deltaTheta && servo2_deltaTheta > servo3_deltaTheta){
		  return(servo2_deltaTheta);
	   }
          
	  if(servo3_deltaTheta > servo2_deltaTheta && servo3_deltaTheta > servo1_deltaTheta){
		  return(servo3_deltaTheta);
	   }  
}

// This function determines and returns the direction(+/-) that the acceleration needs to have.
// It takes the arguments theta_0 and theta_f from the servo and the acceleration necessary from the individualAcceleration() function. 
float pathPlanning::directionOfAcceleration(float theta_0, float theta_f, float acceleration){

	if (theta_0 > theta_f) {
		return(acceleration);
	}
	else {
		return(-acceleration);
	}
}

// This function determines and returns the direction(+/-) that the deceleration needs to have.
// It takes the arguments theta_0 and theta_f from the servo and the deceleration necessary from the individualAcceleration() function. 
float pathPlanning::directionOfDeceleration(float theta_0, float theta_f, float deceleration){

	if (theta_0 > theta_f) {
		return(-deceleration);
	}
	else {
		return(deceleration);
	}
}

// This function finds and returns the duration for the movement based on the acceleration constrients.
// It takes an argument in the form of delta theta of a servo.
float pathPlanning::timeTotal(float delta_theta){
	float timeTotal = (delta_theta / (theta_2_dot * timeAcceleration) + timeAcceleration);
	return(timeTotal);
}

// This function convertes the units from the servos into degrees.
// It takes a unit input.
float pathPlanning::unitToDegree(int unit){
	  float degree = (unit * 0.088);     
	  return(degree); 
}

// This function convertes degrees into units to be sent to the servos.
// It takes a degree input.
int pathPlanning::degreeToUnit(float degree){
	  float unit = (degree / 0.088);
	  return(unit); 
}







  
