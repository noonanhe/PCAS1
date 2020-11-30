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
    this->velocity = steady_state_speed; //default velocity is the steady state speed
    this->failSafe = false;

    //loading image 
    mImage = Bitmap::FromFile(L"images/vehicle.png");
    if (mImage->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/vehicle.png");
    }

    sensor = make_shared<PedestrianSensor>();
    brakes = make_shared<BrakeActuator>();
    pca_system = make_shared<PCASystem>();
}

/** 
* Draws the vehicle
* param: graphics The GDI+ graphics context to draw on
*/
void Vehicle::OnDraw(Gdiplus::Graphics* graphics)
{
    //change x,y to proper coordinates cause origin is at 160, 500
    float graph_x = 160 + (x*40) - mImage->GetWidth();
    float graph_y = 500 - (y*40) - (mImage->GetHeight()/2);
    
    graphics->DrawImage(mImage, graph_x, graph_y, mImage->GetWidth(), mImage->GetHeight());
}

/**
* Updates vehicle position
* param time: The elapsed time in seconds
*/
void Vehicle::Move(double time)
{
    //i think this if statement is going to have to change, right now it only moves the vehicle until it
    //comes to a complete stop
    if (velocity > 0)
    {
        
        //displacemt = velocity*time + 1/2(accel)time^2
        x = x + (velocity * time) + (.5 * acceleration * pow(time, 2));
        //velocity = init_velocity + accel*time
        velocity = velocity + (acceleration * time);
    }
}

/** Passes on pedestrian information to the sensor
* param ped: the pedestrian to detect
*/
void Vehicle::SensePedestrian(Pedestrian* ped)
{
    sensor->Detect(ped);
}

/** 
* This function is resoponsible for calling the PCASystem's Check Collision function
* and handling the deceleration value returned from that function call
*/
void Vehicle::ProcessData()
{
    //put vehicle info in vector form
    vector<double> vehicle_info;
    vehicle_info.push_back(x);
    vehicle_info.push_back(y);
    vehicle_info.push_back(velocity);
    vehicle_info.push_back(acceleration);
    //check for a collision
    double decel = pca_system->CheckCollision(sensor->SendData(), vehicle_info);

    //if no collision imminent
    if (decel == 0)
    {
        //release brakes if they've been applied
        acceleration = 0;
    }
    else //there's a collision possibility
    {
        //decelerate
       //decel = brakes->SlowDown(decel);
       acceleration = decel;
    }
}

/**
* This function is responsible for setting the vehicle's position, acceleration, and velocity
* back to the default after a scenario is run
*/
void Vehicle::Reset()
{
    x = 0; //vehicle's x position
    y = 0; //vehicle's y position
    acceleration = 0; //vehicle's acceleration
    velocity = steady_state_speed; //represents vehicles current speed
    failSafe = false; //indicates whether vehicle is in fail safe mode
}