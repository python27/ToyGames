
// 2048Game.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy2048GameApp: 
// �йش����ʵ�֣������ 2048Game.cpp
//

class CMy2048GameApp : public CWinApp
{
public:
	CMy2048GameApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy2048GameApp theApp;