// MeetingManagerView.cpp : ʵ���ļ�
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


// MeetingManagerView ���

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


// MeetingManagerView ��Ϣ�������


void MeetingManagerView::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString tt;
	tt.Format(_T("%d, %s"), meetingID, meetingName);
	MessageBox(tt);
}


void MeetingManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	//CString tt;
	//tt.Format(_T("%d, %s"), meetingID, meetingName);
	//MessageBox(tt);
}
