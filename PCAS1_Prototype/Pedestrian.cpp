/**
* \file Pedestrian.cpp
* 
* implementation of Pedestrian class
*/

#include "pch.h"
#include "Pedestrian.h"

using namespace std;
using namespace Gdiplus;

/**Constructor
* param: speed The starting speed of pedestrian
* param x: The starting x coordinate of the pedestrina
* param y: the starting y coordinate of the pedestrian
**/
Pedestrian::Pedestrian( double x, double y,double speed )
{
	this->velocity = speed;
	this->x = x;
	this->y = y;

    //loading image 
    mImage = Bitmap::FromFile(L"images/pedestrian.png");
    if (mImage->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/pedestrian.png");
    }
}

/**
* Draws the vehicle
* param: graphics The GDI+ graphics context to draw on
*/
void Pedestrian::OnDraw(Gdiplus::Graphics* graphics)
{
    FontFamily fontFamily(L"Arial");

    //change x,y to proper coordinates cause origin is at 160, 500
    float graph_x = 160 + (x * 40) - mImage->GetWidth();
    float graph_y = 500 - (y * 40) - (mImage->GetHeight() / 2);

    graphics->DrawImage(mImage, graph_x, graph_y, mImage->GetWidth(), mImage->GetHeight());
}

/**
* Updates the pedestrian's position
* param: time The elapsed time
*/
void Move(double time)
{

}