/**
* file: PCASystem.cpp
* 
* This file contains the implementation for the PCASystem functionality
*/
#include "pch.h"
#include "PCASystem.h"

using namespace std;

/** this function is responsible for determining if the vehicle has entered
* within the minimum distance of a pedestrian
* param ped_info: vector with x & y position of pedestrian
* param vehicle_info: vector with x & y position of vehicle
* return: the deceleration requested 0 means no collision imminent so no deceleration needed
*/
double PCASystem::CheckCollision(vector<double> ped_info, vector<double> vehicle_info)
{
	/** this is temporary check collision implementation for static scenarios **/

	//if pedestrian is within 35 meters in the x direction and is in the vehicle's collision zone
	if (abs(ped_info[0] - vehicle_info[0]) <= 35 && abs(ped_info[1] - vehicle_info[1]) < 2)
	{
		return -3; //return a deceleration of -3 m/s^2 (this is temporary)
	}
	else // no collision imminent
	{
		return 0; //no deceleration needed
	}
}
