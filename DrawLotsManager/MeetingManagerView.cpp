// MeetingManagerView.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "MeetingManagerView.h"
#include "DrawLotsManagerDoc.h"
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

// MeetingManagerView.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "MeetingManagerView.h"


// MeetingManagerView

IMPLEMENT_DYNCREATE(MeetingManagerView, CView)

MeetingManagerView::MeetingManagerView()
{

}

MeetingManagerView::~MeetingManagerView()
{
}

BEGIN_MESSAGE_MAP(MeetingManagerView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// MeetingManagerView 绘图

void MeetingManagerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


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

int MeetingManagerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CDrawLotsManagerDoc* drawDoc = (CDrawLotsManagerDoc*)this->GetDocument();
	meetingID = drawDoc->l_Meeting_ID;
	meetingName = drawDoc->str_Meeting_Name;
	GetParentFrame()->SetWindowText(meetingName);

	CRect rc;  
    GetWindowRect(&rc);  

	VERIFY(m_wndSplitter.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE));  
	
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;
	
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(MatchView), CSize(300, rc.Height()), pContext);
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(MatchOrgAthView), CSize(0, rc.Height()), pContext);

	m_wndSplitter.MoveWindow(0, 0, rc.Width(), rc.Height());  
	
	return 0;
}


void MeetingManagerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	m_wndSplitter.MoveWindow(0, 0, cx, cy);
}
