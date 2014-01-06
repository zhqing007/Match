// MeetingManagerView.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "MeetingManagerView.h"
#include "DrawLotsManagerDoc.h"


// MeetingManagerView
IMPLEMENT_DYNCREATE(MeetingManagerView, CView)

MeetingManagerView::MeetingManagerView()
{

}

MeetingManagerView::~MeetingManagerView()
{
}

void MeetingManagerView::DoDataExchange(CDataExchange* pDX)
{
	CView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MeetingManagerView, CView)
END_MESSAGE_MAP()


// MeetingManagerView 诊断

#ifdef _DEBUG
void MeetingManagerView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MeetingManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MeetingManagerView 消息处理程序

void MeetingManagerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CDrawLotsManagerDoc* drawDoc = (CDrawLotsManagerDoc*)this->GetDocument();
	meetingID = drawDoc->l_Meeting_ID;
	meetingName = drawDoc->str_Meeting_Name;
	GetParentFrame()->SetWindowText(meetingName);
}


BOOL MeetingManagerView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_wndSplitter.CreateStatic(this, 2, 1);
    m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(MatchView), CSize(0,0), pContext);  
    m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(MatchOrgAthView), CSize(0,0), pContext);  

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


// D:\Match\DrawLotsManager\MeetingManagerView.cpp : 实现文件
// MatchView

IMPLEMENT_DYNCREATE(MatchView, CFormView)

MatchView::MatchView()
	: CFormView(MatchView::IDD)
{

}

MatchView::~MatchView()
{
}

void MatchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MatchView, CFormView)
END_MESSAGE_MAP()


// MatchView 诊断

#ifdef _DEBUG
void MatchView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MatchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MatchView 消息处理程序
// D:\Match\DrawLotsManager\MeetingManagerView.cpp : 实现文件
// MatchOrgAthView

IMPLEMENT_DYNCREATE(MatchOrgAthView, CFormView)

MatchOrgAthView::MatchOrgAthView()
	: CFormView(MatchOrgAthView::IDD)
{

}

MatchOrgAthView::~MatchOrgAthView()
{
}

void MatchOrgAthView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MatchOrgAthView, CFormView)
END_MESSAGE_MAP()


// MatchOrgAthView 诊断

#ifdef _DEBUG
void MatchOrgAthView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MatchOrgAthView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MatchOrgAthView 消息处理程序

