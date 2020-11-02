/**
* \file Vehicle.cpp
* 
* implementation of the Vehicle class
*/

#include "pch.h"
#include "Vehicle.h"

using namespace std;
using namespace Gdiplus;

/**Constructor
* param x: The starting x coordinate of vehicle
* param y: the starting y coordinate of vehicle
* param acceleration: The starting acceleration of the the vehicle
*/
Vehicle::Vehicle(double x, double y, double acceleration)
{
    this->x = x;
    this->y = y;
    this->acceleration = acceleration;

    //loading image 
    mImage = Bitmap::FromFile(L"images/vehicle.png");
    if (mImage->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/vehicle.png");
    }
}

/** 
* Draws the vehicle
* param: graphics The GDI+ graphics context to draw on
*/
void Vehicle::OnDraw(Gdiplus::Graphics* graphics)
{
	FontFamily fontFamily(L"Arial");

    //change x,y to proper coordinates cause origin is at 160, 500
    float graph_x = 160 + (x*40) - mImage->GetWidth();
    float graph_y = 500 - (y*40) - (mImage->GetHeight()/2);
    
    graphics->DrawImage(mImage, graph_x, graph_y, mImage->GetWidth(), mImage->GetHeight());
}

/**
* Updates vehicle position
* param time: The elapsed time
*/
void Vehicle::Move(double time)
{

}