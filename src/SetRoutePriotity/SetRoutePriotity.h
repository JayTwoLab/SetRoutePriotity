// SetRoutePriotity.h : main header file for the PROJECT_NAME application
//

#ifndef _SET_ROUTE_PRI_H
#define _SET_ROUTE_PRI_H

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSetRoutePriotityApp:
// See SetRoutePriotity.cpp for the implementation of this class
//

class CSetRoutePriotityApp : public CWinApp
{
public:
	CSetRoutePriotityApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CSetRoutePriotityApp theApp;

#endif