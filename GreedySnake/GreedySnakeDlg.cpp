// GreedySnakeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GreedySnake.h"
#include "GreedySnakeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGreedySnakeDlg dialog

CGreedySnakeDlg::CGreedySnakeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGreedySnakeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGreedySnakeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_snake.push_back(std::make_pair(10, 10));
    m_snake.push_back(std::make_pair(10, 11));
    m_snake.push_back(std::make_pair(10, 12));
}

void CGreedySnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGreedySnakeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGreedySnakeDlg, CDialog)
	//{{AFX_MSG_MAP(CGreedySnakeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, OnButtonQuit)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGreedySnakeDlg message handlers

BOOL CGreedySnakeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    this->MoveWindow(100,100,500, 450);

    CWnd* pPic = GetDlgItem(IDC_STATIC_PIC);
    pPic->MoveWindow(10, 10, 300, 400);

    CWnd* pGroupBox = GetDlgItem(IDC_STATIC_GROUPBOX);
    pGroupBox->MoveWindow(330, 10, 150, 200);
    

    CWnd* pScore = GetDlgItem(IDC_STATIC_SCORE);
    pScore->MoveWindow(345, 30, 120, 40);
    CWnd* pScoreNum = GetDlgItem(IDC_STATIC_SCORE_NUM);
    pScoreNum->MoveWindow(345, 75, 120, 40);


    CWnd* pGroupBoxButton = GetDlgItem(IDC_STATIC_GROUPBOX_BUTTON);
    pGroupBoxButton->MoveWindow(330, 260, 150, 150);

    CWnd* pStartBtn = GetDlgItem(IDC_BUTTON_START);
    pStartBtn->MoveWindow(350, 285, 110, 40);

    CWnd* pQuitBtn = GetDlgItem(IDC_BUTTON_QUIT);
    pQuitBtn->MoveWindow(350, 350, 110, 40);
	
    this->SetTimer(1, 200, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGreedySnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGreedySnakeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
        int i, j;
        CWnd* pPic = GetDlgItem(IDC_STATIC_PIC);
        CPaintDC dc(pPic);
        CPen pen(PS_COSMETIC, 1, RGB(220, 220, 220));
        CPen* pOldPen = dc.SelectObject(&pen);
        for (i = 0; i < 400 / 10; ++i)
        {
            for (j = 0; j < 300 / 10; ++j)
            {
                dc.Rectangle(j * 10, i * 10, (j+1) * 10, (i+1)*10);
            }
        }

        CBrush brush(RGB(0, 0, 0));
        CBrush* pOldBrush = dc.SelectObject(&brush);

        CFont font;
        font.CreateFont(32,20,0,0,100,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Arial");

        CWnd* pScore = GetDlgItem(IDC_STATIC_SCORE);
        pScore->SetFont(&font);
        pScore->SetWindowText("Score");

        CWnd* pScoreNum = GetDlgItem(IDC_STATIC_SCORE_NUM);
        pScoreNum->SetFont(&font);
        
        int r = rand() % 10;
        char buf[32] = {'\0'};
        sprintf(buf, "%d", r);
        pScoreNum->SetWindowText(CString(buf));


        CBrush brush2(RGB(255, 0, 0));
        pOldBrush = dc.SelectObject(&brush2);

        for (size_t k = 0; k < m_snake.size(); ++k)
        {
            int r = m_snake[k].first;
            int c = m_snake[k].second;
            dc.Rectangle(c * 10, r * 10, (c+1)*10, (r+1)*10);
        }

        

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGreedySnakeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGreedySnakeDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	
}

void CGreedySnakeDlg::OnButtonQuit() 
{
	// TODO: Add your control notification handler code here
	this->KillTimer(1);
}

void CGreedySnakeDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    if (nIDEvent == 1)
    {
        
        for (size_t k = 0; k < m_snake.size(); ++k)
        {
            m_snake[k].second = (m_snake[k].second + 1) % 30;
        }

        this->Invalidate(FALSE);
        this->UpdateWindow();

    }


	CDialog::OnTimer(nIDEvent);

}
