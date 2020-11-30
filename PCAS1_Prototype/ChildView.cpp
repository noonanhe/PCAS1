/**
* \file ChildView.cpp
* 
* This file is responsible for handling Window messages, which basically means it contains all the functions
* that control the functionality of the GUI
*/

#include "pch.h"
#include "framework.h"
#include "PCAS1_Prototype.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include <string>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;

// CChildView

/**
* Constructor
*/
CChildView::CChildView()
{
	
}

/**
* Destructor
*/
CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_RUN_SCENARIO1, &CChildView::OnRunScenario1)
	ON_WM_TIMER()
	ON_COMMAND(ID_RUN_STATICSCENARIO2, &CChildView::OnRunStaticscenario2)
	ON_COMMAND(ID_RUN_STATICSCENARIO3, &CChildView::OnRunStaticscenario3)
	ON_COMMAND(ID_RUN_STOPSTARTSCENARIO1, &CChildView::OnRunStopStartscenario1)
	ON_COMMAND(ID_RUN_STOPSTARTSCENARIO2, &CChildView::OnRunStopStartscenario2)
	ON_COMMAND(ID_RUN_STOPSTARTSCENARIO3, &CChildView::OnRunStopStartscenario3)
	ON_COMMAND(ID_RUN_STARTSTOPSCENARIO1, &CChildView::OnRunStartStopscenario1)
	ON_COMMAND(ID_RUN_STARTSTOPSCENARIO2, &CChildView::OnRunStartStopscenario2)
	ON_COMMAND(ID_RUN_STARTSTOPSCENARIO3, &CChildView::OnRunStartStopscenario3)
	ON_COMMAND(ID_RUN_STARTSTOPSCENARIO4, &CChildView::OnRunStartStopscenario4)
END_MESSAGE_MAP()



// CChildView message handlers
/**
 * This function is called before the window is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
 * This function is called to draw in the window.
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 */
void CChildView::OnPaint() 
{

	//40px / m

	CPaintDC paintDC(this); // device context for painting
	CDoubleBufferDC dc(&paintDC); //device context for painting

	Graphics graphics(dc.m_hDC); //Create GDI+ graphics context

	//lets draw the x & y axis
	Pen pen(Color(0, 0, 0), 3); //<black pen
	graphics.DrawLine(&pen, 0, 499, 2000, 499); //<x-axis
	graphics.DrawLine(&pen, 159, 10, 159, 990); //<y-axis

	//draw the vehicle and pedestrian
	mVehicle.OnDraw(&graphics);
	mPedestrian.OnDraw(&graphics);

	//draw rectangle for stats
	SolidBrush rect(Color(255, 255, 153));
	graphics.DrawRectangle(&pen, 1400, 18, 400, 150);
	graphics.FillRectangle(&rect, 1400, 18, 400, 150);

	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 10);
	Gdiplus::Font statsTitle(&fontFamily, 12);
	SolidBrush green(Color(0, 64, 0));

	graphics.DrawString(L"Stats:", -1, &statsTitle, PointF(1400, 20), &green);

	// Obtain the values for speeds, delay, and acceleration
	wstring pedestrianSpeed = to_wstring(round(((mPedestrian.getVelocity()*18)/5)));
	wstring vehicleSpeed = to_wstring(round(((mVehicle.getVelocity()*18)/5)));
	wstring vehicleAcceleration = to_wstring(mVehicle.getAcceleration());
	wstring delay = to_wstring(mPedestrian.getDelay());

	// Calculating lost time
	double currentTime = mVehicle.getTime();
	double vehicleX = mVehicle.getXCoordinate();
	double vehicleSteady = mVehicle.getSpeed();

	double expectedTime = vehicleX / vehicleSteady;
	double lostTime = currentTime - expectedTime;
	wstring lostTimeString = to_wstring(lostTime);

	Gdiplus::Font fontBrake(&fontFamily, 20);
	SolidBrush red(Color(64, 0, 0));

	// Display "Braking" text to show that the vehicle is braking
	if (mVehicle.getAcceleration() < 0) {
		graphics.DrawString(L"Braking", -1, &fontBrake, PointF(1400, 175), &red);
	}
	if (mVehicle.getAcceleration() > 0) {
		graphics.DrawString(L"Accelerating", -1, &fontBrake, PointF(1400, 175), &green);
	}

	// Display the stats values and titles
	graphics.DrawString(L"Vehicle Acceleration (m/s^2) :", -1, &font, PointF(1400, 45), &green);
	graphics.DrawString(L"Vehicle Speed (km/h) :", -1, &font, PointF(1400, 70), &green);
	graphics.DrawString(L"Pedestrian Speed (km/h) :", -1, &font, PointF(1400, 95), &green);
	graphics.DrawString(L"Pedestrian Delay (s) :", -1, &font, PointF(1400, 120), &green);
	graphics.DrawString(L"Lost Time (s) :", -1, &font, PointF(1400, 145), &green);
	if (mVehicle.getAcceleration() < 0)
	{
		graphics.DrawString(vehicleAcceleration.c_str(), -1, &font, PointF(1700, 45), &red);
		graphics.DrawString(vehicleSpeed.c_str(), -1, &font, PointF(1700, 70), &red);
	}
	else {
		graphics.DrawString(vehicleAcceleration.c_str(), -1, &font, PointF(1700, 45), &green);
		graphics.DrawString(vehicleSpeed.c_str(), -1, &font, PointF(1700, 70), &green);
	}
	graphics.DrawString(pedestrianSpeed.c_str(), -1, &font, PointF(1700, 95), &green);
	graphics.DrawString(delay.c_str(), -1, &font, PointF(1700, 120), &green);
	graphics.DrawString(lostTimeString.c_str(), -1, &font, PointF(1700, 145), &green);

	//if we have just successfully avoided a collision from a scenario
	if (avoided)
	{
		// Draw the test "Collision Avoided!"
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 24);
		SolidBrush green(Color(0, 64, 0));
		graphics.DrawString(L"Collision Avoided!", -1, &font, PointF(600, 50), &green);
		avoided = false;
	}
}

/**
* This function is responsible for running Static Scenario 1
* Pedestrian remains static at position (35, 0)
*/
void CChildView::OnRunScenario1()
{

	mPedestrian.setYCoordinate(0); //set the pedestrian's Y position to 0
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	//Set a timer to run every 100 ms, this function basically calls OnTimer() every 100 ms
	SetTimer(1, 100,0);
}


/**
* This function is responsible for running Static Scenario 2
* Pedestrian remains static at position (35, -2)
*/
void CChildView::OnRunStaticscenario2()
{
	mPedestrian.setYCoordinate(-2); //set the pedestrian's Y position to -2
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(1, 100, 0); //run the scenario
}

/**
* This funciton is responsible for running Static Scenario 3
* Pedestrian remains static at position (35, -4)
*/
void CChildView::OnRunStaticscenario3()
{
	// TODO: Add your command handler code here
	mPedestrian.setYCoordinate(-4); //set ped's Y position to -4
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(1, 100, 0); //run the scenario
}

/**
* First scenario of initial movement then stopping
* Pedestrian moves from (35, -7) to (35, 0)
*/
void CChildView::OnRunStartStopscenario1()
{
	// TODO: Add your command handler code here
	mPedestrian.setYCoordinate(-7); //set ped's Y position to -7
	mPedestrian.setLimit(0); // Set pedestrian's final position to be at 0
	mPedestrian.setVelocity(2.78); // set pedestrian's velocity to be 2.78
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(2, 100, 0); //run the scenario
}

/**
* Second scenario of initial movement then stopping
* Pedestrian moves from (35, -7) to (35, -2)
*/
void CChildView::OnRunStartStopscenario2()
{
	mPedestrian.setYCoordinate(-7); //set ped's Y position to -7
	mPedestrian.setLimit(-2); // Set pedestrian's final position to be at -2
	mPedestrian.setVelocity(2.78); // set pedestrian's velocity to be 2.78
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(2, 100, 0); //run the scenario
}

/**
* Third scenario of initial movement then stopping
* Pedestrian moves from (35, -7) to (35, -3)
*/
void CChildView::OnRunStartStopscenario3()
{
	mPedestrian.setYCoordinate(-7); //set ped's Y position to -7
	mPedestrian.setLimit(-3); // Set pedestrian's final position to be at -3
	mPedestrian.setVelocity(2.78); // set pedestrian's velocity to be 2.78
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(2, 100, 0); //run the scenario
}

/**
* Fourth scenario of initial movement then stopping
* Pedestrian moves from (35, -7) to (35, -5)
*/
void CChildView::OnRunStartStopscenario4()
{
	mPedestrian.setYCoordinate(-7); //set ped's Y position to -7
	mPedestrian.setLimit(-5); // Set pedestrian's final position to be at -5
	mPedestrian.setVelocity(2.78); // set pedestrian's velocity to be 2.78
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(2, 100, 0); //run the scenario
}

/**
* First scenario of delayed start then movement
* Pedestrian stays at (35, 0) for 1.5 seconds before moving
*/
void CChildView::OnRunStopStartscenario1()
{
	mPedestrian.setYCoordinate(0); //set ped's Y position to 0
	mPedestrian.setLimit(1000); // No limit on pedestrian position
	mPedestrian.setDelay(1.5); // Delay time set to 1.5 seconds - might need to be corrected
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(3, 100, 0); //run the scenario
}

/**
* Second scenario of delayed start then movement
* Pedestrian stays at (35, -2) for 1.8 seconds before moving
*/
void CChildView::OnRunStopStartscenario2()
{
	mPedestrian.setYCoordinate(-2); //set ped's Y position to -2
	mPedestrian.setLimit(1000);  // No limit on pedestrian position
	mPedestrian.setDelay(1.8); // Delay time set to 1.8 seconds - might need to be corrected
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(3, 100, 0); //run the scenario
}

/**
* Third scenario of delayed start then movement
* Pedestrian stays at (35, -4) for 1.1 seconds before moving
*/
void CChildView::OnRunStopStartscenario3()
{
	mPedestrian.setYCoordinate(-2); //set ped's Y position to -4
	mPedestrian.setLimit(1000); // No limit on pedestrian position
	mPedestrian.setDelay(1.1); // Delay time set to 1.1 seconds - might need to be corrected
	mVehicle.SensePedestrian(&mPedestrian); //sense pedestrian
	SetTimer(2, 100, 0); //run the scenario
}


/** Event handler for a timer
* param nIDEvent: id of a timer
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	CWnd::OnTimer(nIDEvent);

	//switch statement based on timer id, each run scenario function creates a timer with a unique ID, so each 
	// case statement refers to a different scenario type
	switch (nIDEvent)
	{
		//case statement for Static Scenarios
	case 1:
		//if vehicle hasn't passed pedestrian and isn't stopped
		if (mVehicle.getXCoordinate() < 40 && mVehicle.getVelocity() > 0)
		{
			mVehicle.ProcessData(); //check for collisions, update decel as necessary
			mVehicle.Move(.1); //update vehicles position based on 100 ms passing
			Invalidate(); //have to force screen redraw
		}
		else
		{
			avoided = true; //this is needed for "Collision Avoided" text to appear
			KillTimer(1); //kill the timer cause the scenario is done
			Invalidate(); //force screen to redraw so we can see the text
			Sleep(1000); //pause
			mVehicle.Reset(); //reset vehicle so another scenario can be run
			mPedestrian.Reset(); //reset pedestrian so another scenario can be run
			Invalidate(); //force screen to redraw
		}
		break;

	// for start stop scenarios where pedestrian starts out moving then stops
	case 2:
		if (mVehicle.getXCoordinate() < 40 && mVehicle.getVelocity() > 0)
		{
			mVehicle.ProcessData(); //check for collisions, update decel as necessary
			mPedestrian.Move(.1); //update pedestrian's position based on 100 ms passing
			mVehicle.Move(.1); //update vehicles position based on 100 ms passing
			Invalidate(); //have to force screen redraw
		}
		else
		{
			avoided = true; //this is needed for "Collision Avoided" text to appear
			KillTimer(2); //kill the timer cause the scenario is done
			Invalidate(); //force screen to redraw so we can see the text
			Sleep(1000); //pause
			mVehicle.Reset(); //reset vehicle so another scenario can be run
			mPedestrian.Reset(); //reset pedestrian so another scenario can be run
			Invalidate(); //force screen to redraw
		}
		break;
		//for stop start scenarios where pedestrian has delayed start time
	case 3:
		if (mVehicle.getXCoordinate() < 40)
		{
			mVehicle.ProcessData(); //check for collisions, update decel as necessary
			mPedestrian.Move(.1); //update pedestrian's position based on 100 ms passing
			mVehicle.Move(.1); //update vehicles position based on 100 ms passing
			Invalidate(); //have to force screen redraw
		}
		else
		{
			avoided = true; //this is needed for "Collision Avoided" text to appear
			KillTimer(3); //kill the timer cause the scenario is done
			Invalidate(); //force screen to redraw so we can see the text
			Sleep(1000); //pause
			mVehicle.Reset(); //reset vehicle so another scenario can be run
			mPedestrian.Reset(); //reset pedestrian so another scenario can be run
			Invalidate(); //force screen to redraw
		}
		break;
	}


}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}





