/**
* \file PedestrianSensor.h
* 
* Defines the Pedestrian Sensor class
*/
#include <memory>
#include <vector>
#include "Pedestrian.h"

#pragma once
/** Class that models the pedestrian detection sensor of the
* vehicle
*/
class PedestrianSensor
{
private:
	double locationAccuracy = .5; //<delivers position accuracy with +/- .5m
	double speedAccuracy = .2; //delivers speed with accuracy +/- .2m/s
	double directionAccuracy = 5; //delivers direction with +/- 5 deg accuracy

	std::shared_ptr<Pedestrian> detected_pedestrian;
public:
	PedestrianSensor() { detected_pedestrian = std::make_shared<Pedestrian>(0, 0, 0); } //<constructor
	std::vector<double> SendData();
	void Detect(std::shared_ptr<Pedestrian> ped);
};

