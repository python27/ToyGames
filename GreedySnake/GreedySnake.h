// GreedySnake.h : main header file for the GREEDYSNAKE application
//

#if !defined(AFX_GREEDYSNAKE_H__D81DD212_BC7A_41C6_983D_C659D74A3FCF__INCLUDED_)
#define AFX_GREEDYSNAKE_H__D81DD212_BC7A_41C6_983D_C659D74A3FCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGreedySnakeApp:
// See GreedySnake.cpp for the implementation of this class
//

class CGreedySnakeApp : public CWinApp
{
public:
	CGreedySnakeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGreedySnakeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGreedySnakeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GREEDYSNAKE_H__D81DD212_BC7A_41C6_983D_C659D74A3FCF__INCLUDED_)
