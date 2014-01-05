// MeetingManagerView.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "MeetingManagerView.h"


// MeetingManagerView

IMPLEMENT_DYNCREATE(MeetingManagerView, CFormView)

MeetingManagerView::MeetingManagerView()
	: CFormView(MeetingManagerView::IDD)
{

}

MeetingManagerView::~MeetingManagerView()
{
}

void MeetingManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MeetingManagerView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &MeetingManagerView::OnBnClickedButton1)
END_MESSAGE_MAP()


// MeetingManagerView 诊断

#ifdef _DEBUG
void MeetingManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MeetingManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MeetingManagerView 消息处理程序


void MeetingManagerView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tt;
	tt.Format(_T("%d, %s"), meetingID, meetingName);
	MessageBox(tt);
}


void MeetingManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//CString tt;
	//tt.Format(_T("%d, %s"), meetingID, meetingName);
	//MessageBox(tt);
}
