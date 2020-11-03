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
	mPedestrian->OnDraw(&graphics);



	//mVehicle.SensePedestrian(mPedestrian);
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}


void CChildView::OnRunScenario1()
{
	// TODO: Add your command handler code here
	mVehicle.Move(0);
	Invalidate();

	mVehicle.Move(0);
	Invalidate();
}
