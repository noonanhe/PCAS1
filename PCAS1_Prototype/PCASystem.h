/**
* \file PCASystem.h
* 
* This class hold the actual functionality of the avoidance algorithm
*/

#pragma once
/** Class that represents the PCA algorithm*/
class PCASystem
{
private:
	const double minDistance = .5; //<minimum distance vehicle and pedestrian are allowed to come within
	const double maxDecel = .7; //mas deceleration allowed

public:
	PCASystem() {};
	double CheckCollision();
	//IsCorrupt()??
	//ApplyBrakes()
	//ReleaseBrakes()
};

