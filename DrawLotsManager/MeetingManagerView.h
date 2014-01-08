#pragma once
#include "afxcmn.h"
#include "DBObject.h"

class MatchOrgAthView;
// MatchView ������ͼ
class MatchView : public CFormView
{
	DECLARE_DYNCREATE(MatchView)

protected:
	MatchView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MatchView();

public:
	enum { IDD = IDD_MATCHVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	LONG meetingID;
	MatchOrgAthView* rightView;
	CListCtrl list_match;

	virtual void OnInitialUpdate();
	void AddMatToList(Match*);
};


// MatchOrgAthView ������ͼ

class MatchOrgAthView : public CFormView
{
	DECLARE_DYNCREATE(MatchOrgAthView)

protected:
	MatchOrgAthView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MatchOrgAthView();

public:
	enum { IDD = IDD_MATCHORGATHVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};

// MeetingManagerView ��ͼ

class MeetingManagerView : public CView
{
	DECLARE_DYNCREATE(MeetingManagerView)

protected:
	MeetingManagerView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~MeetingManagerView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	CSplitterWnd m_wndSplitter;
	LONG meetingID;
	CString meetingName;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};



// Dialog_Match_Prop �Ի���

class Dialog_Match_Prop : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Match_Prop)

public:
	Dialog_Match_Prop(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog_Match_Prop();

// �Ի�������
	enum { IDD = IDD_MEETING_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Match _match;
	afx_msg void OnBnClickedOk();
};
