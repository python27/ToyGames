// GreedySnakeDlg.h : header file
//

#if !defined(AFX_GREEDYSNAKEDLG_H__A33B7CA6_817D_49D4_815E_DDF5BD66FC8D__INCLUDED_)
#define AFX_GREEDYSNAKEDLG_H__A33B7CA6_817D_49D4_815E_DDF5BD66FC8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <utility>
/////////////////////////////////////////////////////////////////////////////
// CGreedySnakeDlg dialog

class CGreedySnakeDlg : public CDialog
{
// Construction
public:
	CGreedySnakeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGreedySnakeDlg)
	enum { IDD = IDD_GREEDYSNAKE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGreedySnakeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGreedySnakeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonQuit();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    std::vector<std::pair<int, int> > m_snake;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GREEDYSNAKEDLG_H__A33B7CA6_817D_49D4_815E_DDF5BD66FC8D__INCLUDED_)
