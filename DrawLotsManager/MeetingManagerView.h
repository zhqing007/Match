#pragma once



// MeetingManagerView 窗体视图

class MeetingManagerView : public CView
{
public:
	DECLARE_DYNCREATE(MeetingManagerView)
	MeetingManagerView();           // 动态创建所使用的受保护的构造函数
	virtual ~MeetingManagerView();

//public:
//	enum { IDD = IDD_MEETINGMANAGERVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CSplitterWnd m_wndSplitter;
	LONG meetingID;
	CString meetingName;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
};


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
};


#pragma once



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
