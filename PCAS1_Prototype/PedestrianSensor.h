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

	Pedestrian* detected_pedestrian;
public:
	PedestrianSensor() { } //<constructor
	std::vector<double> SendData(); //<sends pedestrian data
	void Detect(Pedestrian* ped); //setter for detected_pedestrian variable
};

