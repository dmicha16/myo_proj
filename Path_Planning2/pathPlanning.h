#ifndef pathPlanning_h
#define pathPlanning_h

#include "Arduino.h"

class pathPlanning
{
  public:
	float dominantTimeConstantVelocity(float totaltime);
	float individualTimeConstantVelocity(float biggest_deltaTheta, float individual_deltaTheta, float totalTime);
	float dominantAccelerationCorrection(float biggest_deltaTheta, float totalTime);
	float individualAcceleration(float individual_deltaTheta);
	float dominantServoDeltaTheta(float inputServo1_0, float inputServo2_0, float inputServo3_0, float knownServo1_f, float knownServo2_f, float knownServo3_f);
	float directionOfAcceleration(float theta_0, float theta_f, float acceleration);
	float directionOfDeceleration(float theta_0, float theta_f, float deceleration);
	float timeTotal(float delta_theta);
    float unitToDegree(int unit);
    int degreeToUnit(float degree);
	
    
  private: 
    float timeAcceleration = 0.25;		// This is the preset acceleration duration time.
    float theta_2_dot = 180;			// This is the preset max acceleration
};

#endif

