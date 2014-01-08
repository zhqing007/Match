#pragma once
#include "afxcmn.h"
#include "DBObject.h"

class MatchOrgAthView;
// MatchView 窗体视图
class MatchView : public CFormView
{
	DECLARE_DYNCREATE(MatchView)

protected:
	MatchView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	LONG meetingID;
	MatchOrgAthView* rightView;
	CListCtrl list_match;

	virtual void OnInitialUpdate();
	void AddMatToList(Match*);
};


// MatchOrgAthView 窗体视图

class MatchOrgAthView : public CFormView
{
	DECLARE_DYNCREATE(MatchOrgAthView)

protected:
	MatchOrgAthView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

// MeetingManagerView 视图

class MeetingManagerView : public CView
{
	DECLARE_DYNCREATE(MeetingManagerView)

protected:
	MeetingManagerView();           // 动态创建所使用的受保护的构造函数
	virtual ~MeetingManagerView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
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



// Dialog_Match_Prop 对话框

class Dialog_Match_Prop : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Match_Prop)

public:
	Dialog_Match_Prop(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog_Match_Prop();

// 对话框数据
	enum { IDD = IDD_MEETING_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Match _match;
	afx_msg void OnBnClickedOk();
};
