/**
* 
* \file Vehicle.h
* 
* Contains the vehicle class that models a vehicle
*/
#include "PedestrianSensor.h"
#include "PCASystem.h"
#include "BrakeActuator.h"
#include <memory>
#include <ctime>

#pragma once
/** Class that models a vehicle */
class Vehicle
{
public:
	//Constructor
	Vehicle(double x, double y, double acceleration);

	/************* Getters ******************/
	double getSpeed() {
		return steady_state_speed;
	}

	double getwidth() {
		return width;
	}

	double getXCoordinate() {
		return x;
	}

	double getYCoordinate() {
		return y;
	}

	double getAcceleration() {
		return acceleration;
	}

	double getVelocity()
	{
		return velocity;
	}

	double getTime()
	{
		return time;
	}

	/************* Setters ****************/
	double setAcceleration(double acceleration) {
		this->acceleration = acceleration;
	}

	double setXCoordinate(double x) {
		this->x = x;
	}

	double setYCoordiante(double y) {
		this->y = y;
	}

	void setTime(double t) {
		this->time= t;
	}

	void OnDraw(Gdiplus::Graphics* graphics); //<draws vehicle image
	void Move(double time); //<updates position of vehicle
	void SensePedestrian(Pedestrian* ped);
	void ProcessData(double stop_time = .2);
	void Reset();

private:
	const double steady_state_speed = 13.9; //in meters/second
	const int width = 2; //in meters
	double x; //vehicle's x position
	double y; //vehicle's y position
	double acceleration; //vehicle's acceleration
	double velocity; //represents vehicles current speed
	bool failSafe; //indicates whether vehicle is in fail safe mode
	double time = 0; //start time in simulation

	Gdiplus::Bitmap* mImage; //image to use for vehicle

	std::shared_ptr<PedestrianSensor> sensor;
	std::shared_ptr<PCASystem> pca_system;
	std::shared_ptr<BrakeActuator> brakes;
};

