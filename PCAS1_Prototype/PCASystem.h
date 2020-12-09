/**
* \file PCASystem.h
* 
* This class hold the actual functionality of the avoidance algorithm
*/
#include <vector>
#include <memory>
#include "PedestrianSensor.h"
#pragma once
/** Class that represents the PCA algorithm*/
class PCASystem
{
private:
	const double minDistance = .5; //<minimum distance vehicle and pedestrian are allowed to come within
	const double maxDecel = 6.867; //max deceleration allowed m/s^2

	std::shared_ptr<PedestrianSensor> sensor;
public:
	PCASystem() {};
	double CheckCollision(std::vector<double> ped_info, std::vector<double> vehicle_info, double stop_time = .1);
	//IsCorrupt()??
};

