/**
* file: BrakeActuator.h
* 
* defines Brake actuator class
*/
#include <memory>
#include "PCASystem.h"
#pragma once
/** models a vehicle's brake actuator*/
class BrakeActuator
{
private:
	const double decelAccuracy = .02; //can apply a sepcifed deceleration value +/- 2%
	const double decelTime = 200; //it takes 200ms to reach specifed decel value
	const double releaseTime = 100; //it takes 100ms to enact acceleration to get back to steady state

	std::shared_ptr<PCASystem> pca_system; 
public:
	BrakeActuator() {};
	double SlowDown(double decel) {
		return decel;
	} // eventually decel*decelAccuracy
	void ReturnToSteady();
};

