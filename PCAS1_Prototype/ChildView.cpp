/**
* \file ChildView.cpp
*/

#include "pch.h"
#include "framework.h"
#include "PCAS1_Prototype.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"

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

	mVehicle.OnDraw(&graphics);
	mPedestrian.OnDraw(&graphics);

	if (avoided)
	{
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 16);
		SolidBrush green(Color(0, 64, 0));
		graphics.DrawString(L"Collision Avoided!", -1, &font, PointF(600, 50), &green);
		avoided = false;
	}
}

/**
* This function is responsible for running Static Scenario 1
*/
void CChildView::OnRunScenario1()
{
	mPedestrian.setYCoordinate(0); //<move pedestrian to correct position
	mVehicle.SensePedestrian(std::make_shared<Pedestrian>(mPedestrian)); //sense pedestrian
	//Set a timer to run every 100 ms, this function basically calls OnTimer() every 100 ms
	SetTimer(1, 100,0);

	//KillTimer(1);
}

/** Event handler for a timer
* param nIDEvent: id of a timer
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	CWnd::OnTimer(nIDEvent);
	//if the vehicle has traveled < 35 m
	if (mVehicle.getXCoordinate() < 35 && mVehicle.getVelocity() > 0)
	{
		mVehicle.ProcessData();
		mVehicle.Move(.1); //update vehicles position based on 100 ms passing
		Invalidate(); //have to force screen redraw
	}
	else
	{
		avoided = true;
		Invalidate();
		KillTimer(1);
	}
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}