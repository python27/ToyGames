
// 2048GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "2048Game.h"
#include "2048GameDlg.h"
#include "afxdialogex.h"
#include "GameLogic.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy2048GameDlg 对话框



CMy2048GameDlg::CMy2048GameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy2048GameDlg::IDD, pParent)
	, m_Score(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2048GameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_Score);
}

BEGIN_MESSAGE_MAP(CMy2048GameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_RESTART, &CMy2048GameDlg::OnBnClickedButtonRestart)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CMy2048GameDlg::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// CMy2048GameDlg 消息处理程序

BOOL CMy2048GameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);


	srand((unsigned int)time(NULL));
	myGame.Init();
	
	// 窗口居中
	
	CWnd* w = GetDlgItem(IDC_STATIC_PIC);
	w->MoveWindow(20, 20, 480, 480);

	CWnd* pStaticScore = GetDlgItem(IDC_STATIC_SCORE);
	pStaticScore->MoveWindow(550, 20, 120, 100);
	CWnd* pEditScore = GetDlgItem(IDC_EDIT_SCORE);
	pEditScore->MoveWindow(540, 100, 140, 70);

	CWnd* pStart = GetDlgItem(IDC_BUTTON_RESTART);
	pStart->MoveWindow(540, 340, 150, 60);
	CWnd* pQuit = GetDlgItem(IDC_BUTTON_QUIT);
	pQuit->MoveWindow(540, 430, 150, 60);
	CWnd* pGroupBox = GetDlgItem(IDC_STATIC);
	pGroupBox->MoveWindow(530, 320, 170, 180);


	CRect rect;
	this->MoveWindow(100, 100, 800, 800);

	m_colors[0] = RGB(220, 220, 220);
	m_colors[1] = RGB(250, 235, 215);
	m_colors[2] = RGB(252, 230,	201);
	m_colors[3] = RGB(244, 164,	96);
	m_colors[4] = RGB(255, 125,	64);
	m_colors[5] = RGB(255, 128,	0);
	m_colors[6] = RGB(255, 97,	0);
	m_colors[7] = RGB(218, 112,	214);
	m_colors[8] = RGB(255, 99,	71);
	m_colors[9] = RGB(255, 69,	0);
	m_colors[10] = RGB(176,	48,	96);
	m_colors[11] = RGB(178,	34,	34);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy2048GameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2048GameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CWnd* w = GetDlgItem(IDC_STATIC_PIC);
		CClientDC cdc(w);
		vector<vector<int> > curGrid = myGame.GetCurGrid();

		CFont font;
		font.CreateFontW(60,
			20,
			0,
			0,
			600,
			FALSE,
			FALSE,
			0,
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			_T("MyFont"));

		CRect rect;
		w->GetClientRect(&rect);
		int height = rect.Height();
		int width = rect.Width();
		int gridHeight = height / 4;
		int gridWidth = width / 4;
		int gridUpPadding = 35;
		int gridLeftPadding = 10;
		TRACE("h=%d\n", height);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				int n = curGrid[i][j];
				int idx = 0;
				if (n != 0)
				{
					idx = (int)log2(double(n));
					
				}

				CBrush brush(m_colors[idx]);
				cdc.SelectObject(&brush);

				cdc.Rectangle(j * gridWidth, i * gridHeight,
					(j + 1) * gridWidth,
					(i + 1) * gridHeight);

				CFont* pOldFont = cdc.SelectObject(&font);
				
				if (n != 0)
				{				
					char buf[32] = { '\0' };
					sprintf_s(buf, "%d", n);
					CString s(buf);
					cdc.SetTextColor(RGB(255, 0, 0));
					cdc.SetBkColor(m_colors[idx]);
					cdc.TextOutW(gridLeftPadding + j * gridWidth, gridUpPadding + i * gridHeight, s);
				}
				
			}


		}

		CWnd* pStart = GetDlgItem(IDC_BUTTON_RESTART);
		pStart->SetFont(&font);
		CWnd* pQuit = GetDlgItem(IDC_BUTTON_QUIT);
		pQuit->SetFont(&font);

		CWnd* pStaticScore = GetDlgItem(IDC_STATIC_SCORE);
		pStaticScore->SetFont(&font);
		CWnd* pEditScore = GetDlgItem(IDC_EDIT_SCORE);
		pEditScore->SetFont(&font);
		char buffer[32] = {'\0'};
		int step = myGame.GetSteps();
		sprintf_s(buffer, "%d", step);
		pEditScore->SetWindowTextW(CString(buffer));

		font.DeleteObject();

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy2048GameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CMy2048GameDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	bool is_win = myGame.IsWin();
	bool is_lost = myGame.IsLose();
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
			case VK_UP:
				myGame.MoveUp();
				Invalidate(0);
				UpdateWindow();
				if (is_win)
				{
					MessageBox(CString("Congratulations ! You Win the Game !"), CString("Congratulation"), MB_OK);
				}
				if (is_lost)
				{
					if (IDRETRY == MessageBox(CString("Game over !"), CString("Game over"), MB_RETRYCANCEL))
					{
						myGame.Init();
						Invalidate(0);
						UpdateWindow();
					}
					else
					{

					}
				}
				break;
			case VK_DOWN:
				myGame.MoveDown();
				Invalidate(0);
				UpdateWindow();
				if (is_win)
				{
					MessageBox(CString("Congratulations ! You Win the Game !"), CString("Congratulation"), MB_OK);
				}
				if (is_lost)
				{
					if (IDRETRY == MessageBox(CString("Game over !"), CString("Game over"), MB_RETRYCANCEL))
					{
						myGame.Init();
						Invalidate(0);
						UpdateWindow();
					}
					else
					{

					}
				}
				break;
			case VK_LEFT:
				myGame.MoveLeft();
				Invalidate(0);
				UpdateWindow();
				if (is_win)
				{
					MessageBox(CString("Congratulations ! You Win the Game !"), CString("Congratulation"), MB_OK);
				}
				if (is_lost)
				{
					if (IDRETRY == MessageBox(CString("Game over !"), CString("Game over"), MB_RETRYCANCEL))
					{
						myGame.Init();
						Invalidate(0);
						UpdateWindow();
					}
					else
					{

					}
				}
				break;
			case VK_RIGHT:
				myGame.MoveRight();
				Invalidate(0);
				UpdateWindow();
				if (is_win)
				{
					MessageBox(CString("Congratulations ! You Win the Game !"), CString("Congratulation"), MB_OK);
				}
				if (is_lost)
				{
					if (IDRETRY == MessageBox(CString("Game over !"), CString("Game over"), MB_RETRYCANCEL))
					{
						myGame.Init();
						Invalidate(0);
						UpdateWindow();
					}
					else
					{

					}
				}
				break;
			default:
				break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CMy2048GameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_SCORE)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMy2048GameDlg::OnBnClickedButtonRestart()
{
	// TODO:  在此添加控件通知处理程序代码
	myGame.Init();
	Invalidate(0);
	UpdateWindow();
}


void CMy2048GameDlg::OnBnClickedButtonQuit()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnOK();
}
