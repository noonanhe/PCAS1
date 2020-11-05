/** 
* \file Pedestrian.h
* 
* Defines the Pedestrian class 
*/

#pragma once

/** Class that models a pedestrian */
class Pedestrian
{
public:
	//Constructor
	Pedestrian(double x, double y, double velcoity);

	/************* Getters **************/
	double getVelocity() {
		return velocity;
	}

	double getDiameter() {
		return diameter;
	}

	double getXCoordinate() {
		return x;
	}

	double getYCoordiante() {
		return y;
	}

	/************** Setters **************/
	void setVelocity(double velocity) {
		this->velocity = velocity;
	}

	void setDiameter(double area) {
		this->diameter = area;
	}

	void setXCoordinate(double x) {
		this->x = x;
	}

	void setYCoordinate(double y) {
		this->y = y;
	}

	// Set the end location of the pedestrian
	void setLimit(double limit) {
		this->limit = limit;
	}

	// Set the delay time for pedestrian movement
	void setDelay(double delay) {
		this->delay = delay;
	}

	void OnDraw(Gdiplus::Graphics* graphics); //<draws vehicle image
	void Move(double time); //<updates pedestrians position
	void Reset(); //<resets to defaults

private:
	double velocity; //<speed of the pedestiran
	double diameter = .5; //<diameter of pedestrian in m
	double x; //x coordinate
	double y; //y coordinate
	double limit = 0; // Location where the pedestrian stops
	double delay = 0; // delay before movement
	double elapsed_time = 0; //time since scenario started

	Gdiplus::Bitmap* mImage;
};

