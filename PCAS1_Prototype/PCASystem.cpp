#include "pch.h"
#include "PCASystem.h"


void PCASystem::CheckCollision()
{
	// get info from sensor
	int x = 1;

	if (x == 1) //pedestrian detected
	{
		ApplyBrakes();
	}
	else if (x == 0) // pedestrian not detected
	{
		// no collision imminent
	}
}

void PCASystem::ApplyBrakes()
{
	// sends a request to the Brake-by-Wire Actuator to apply a given deceleration value
}