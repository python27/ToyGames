
// 2048GameDlg.h : 头文件
//

#pragma once
#include "GameLogic.h"
#define N  4

// CMy2048GameDlg 对话框
class CMy2048GameDlg : public CDialogEx
{
// 构造
public:
	CMy2048GameDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY2048GAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	GameLogic myGame;
	int m_Score;
	COLORREF m_colors[12];
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonRestart();
	afx_msg void OnBnClickedButtonQuit();
};


