#pragma once



// MeetingManagerView ������ͼ

class MeetingManagerView : public CFormView
{
	DECLARE_DYNCREATE(MeetingManagerView)

protected:
	MeetingManagerView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual void OnInitialUpdate();
};


