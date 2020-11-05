#include "pch.h"
#include "PedestrianSensor.h"

using namespace std;

/** sends info about the detected pedestrian
* return: vector consisting of pedestrian info
*		0 = ped's x coordinate
*		1 = ped's y coordinate
*/
vector<double> PedestrianSensor::SendData()
{
	//construct a vector
	vector<double> info;
	info.push_back(detected_pedestrian->getXCoordinate());
	info.push_back(detected_pedestrian->getYCoordiante());
	info.push_back(detected_pedestrian->getVelocity());
	return info;
}

/** Setter for detected_pedestrian
* param: ped The Pedestrian to detect
*/
void PedestrianSensor::Detect(Pedestrian* ped)
{
	detected_pedestrian = ped;
}