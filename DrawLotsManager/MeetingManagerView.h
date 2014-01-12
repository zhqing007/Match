#pragma once
#include "afxcmn.h"
#include "DBObject.h"
#include "afxwin.h"

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
	afx_msg void OnBnClickedBuMAdd();
	afx_msg void OnBnClickedBuMDel();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
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
public:
	CStatic cs_MatchName;

	afx_msg void OnBnClickedBuSubTr();
	afx_msg void OnBnClickedSplitAddtr();
	virtual void OnInitialUpdate();
	void SetMatchID(long matchID, CString matchName);
private:
	LONG matchID;
	CListBox lbox_troop;
	CSplitButton splBu_AddTr;

	void AddTroToList(Troop* tro);
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
	Dialog_Match_Prop(BOOL _isModify = FALSE, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog_Match_Prop();

// 对话框数据
	enum { IDD = IDD_MATCH_PROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Match _match;
	BOOL isModify;
	afx_msg void OnBnClickedOk();
};
