
// DrawLotsManager.h : DrawLotsManager 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CDrawLotsManagerApp:
// 有关此类的实现，请参阅 DrawLotsManager.cpp
//

class CDrawLotsManagerApp : public CWinAppEx
{
public:
	CDrawLotsManagerApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	BOOL  m_bHiColorIcons;
	CMultiDocTemplate* m_pTemplateAthlete;
	CMultiDocTemplate* m_pTemplateMeeting;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawLotsManagerApp theApp;
