
// 2048GameDlg.h : ͷ�ļ�
//

#pragma once
#include "GameLogic.h"
#define N  4

// CMy2048GameDlg �Ի���
class CMy2048GameDlg : public CDialogEx
{
// ����
public:
	CMy2048GameDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY2048GAME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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


