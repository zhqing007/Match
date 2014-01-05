#pragma once



// MeetingManagerView 窗体视图

class MeetingManagerView : public CFormView
{
	DECLARE_DYNCREATE(MeetingManagerView)

protected:
	MeetingManagerView();           // 动态创建所使用的受保护的构造函数
	virtual ~MeetingManagerView();

public:
	enum { IDD = IDD_MEETINGMANAGERVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	LONG meetingID;
	CString meetingName;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual void OnInitialUpdate();
};


