
// DrawLotsManager.h : DrawLotsManager Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CDrawLotsManagerApp:
// �йش����ʵ�֣������ DrawLotsManager.cpp
//

class CDrawLotsManagerApp : public CWinAppEx
{
public:
	CDrawLotsManagerApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;
	CMultiDocTemplate* m_pTemplateAthlete;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDrawLotsManagerApp theApp;
