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
	// get info from sensor
	int x = 1;

	if (x == 1) //pedestrian detected
	{
		return 1; //return some deceleration value to apply
	}
	else if (x == 0) // pedestrian not detected
	{
		// no collision imminent
		return 0; //no deceleration needed
	}
}
