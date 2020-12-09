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
* param ped_info: vector with x & y position of pedestrian and pedestrian velocity
* param vehicle_info: vector with x & y position of vehicle and vehicle velocity
* return: the deceleration requested 0 means no collision imminent so no deceleration needed
*/
double PCASystem::CheckCollision(vector<double> ped_info, vector<double> vehicle_info, double stop_time)
{
	/** this is temporary check collision implementation for static scenarios **/
	//* the max decel value must be applied within 14 m
	/**
	double time;
	//if vehicle acceleration is non zero we have to use quad formula
	if (vehicle_info[3] != 0)
	{
		//when will vehicle reach pedestrian's position? need to solve for time in x = x +vt + 1/2at^2 using quad formula
		double a = (.5) * (vehicle_info[3]); //1/2*a
		double b = vehicle_info[2]; //v
		double c = ped_info[0] - vehicle_info[0] - 2; //final - initial position

		time = abs((-b + sqrt(pow(b, 2) - (4 * a * c)) / (2 * a))); //getting time from quad formula
	}
	else
	{
		time = (ped_info[0] - vehicle_info[0] - 2) / vehicle_info[2];
	}

	//where will pedestrian be at that time?
	double ped_future = (ped_info[1]) + ped_info[2] * time; //pedestrian's future y position based on their position and velocity
	*/

	//if the pedestrian is moving we're going to assume they are going to move in front of us until they are actually past us

	//will the pedestrian be in our collision zone?
	if (abs(ped_info[1] - vehicle_info[1]) < 2 || (ped_info[2] > 0 && ped_info[1] <= vehicle_info[1]))
	{
		//if so return decel value needed to stop within .5 of pedestrian
		// accel = v_final - v_initial / 2 * x
		double future_ped = ped_info[0] + ped_info[1] * stop_time;
		double future_vehicle = vehicle_info[0] + vehicle_info[1] * stop_time +(.5 * vehicle_info[3] * pow(stop_time, 2));
		double decel = 0;
		
		if (stop_time == .9)
		{
			decel = (0 - pow(vehicle_info[2], 2)) / (2 * (ped_info[0] - vehicle_info[0] - 2))*2;
		}
		else
		{
			decel = (0 - pow(vehicle_info[2], 2)) / (2 * (ped_info[0] - vehicle_info[0] - 2));
		}
		
		//decel = (0 - pow(vehicle_info[2], 2)) / (2 * (future_ped- future_vehicle - (2*stop_time)));
		return decel;
	}
	else
	{
		//is vehicle at steady state velocity, if not return?
		if (vehicle_info[2] <= 13.9)
		{
			return 3; // moderate acceleration value; temporary
		}
		else
		{
			return 0; //no need to accelerate or decelerate
		}
	}

	/**
	//if pedestrian is within 35 meters in the x direction and is in the vehicle's collision zone
	if (abs(ped_info[0] - vehicle_info[0]) <= 35 && abs(ped_info[1] - vehicle_info[1]) < 2)
	{
		//return -3; //return a deceleration of -3 m/s^2 (this is temporary)
	}
	else // no collision imminent
	{
		return 0; //no deceleration needed
	}
	*/
}
