/**
* \file ChildView.h
* 
* Class that implements the child window the program draws in.
* 
* The window is a child of the main frame, which holds this window, the menu
* bar, and the status bar.
*/
#include "Vehicle.h"
#include "Pedestrian.h"

#pragma once

/**
 * The child window the program draws in.
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	// x = 0, y = 0, acceleration =0
	Vehicle mVehicle = Vehicle(0, 0, 0);
	//x = 35, y = -7 m, velocity =0
	std::shared_ptr<Pedestrian> mPedestrian = std::make_shared<Pedestrian>(35, -7, 0);
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRunScenario1();
};

