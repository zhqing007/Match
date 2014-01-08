#pragma once
#include "afxcmn.h"
#include "DBObject.h"
#include "atltime.h"


// Dialog_Meeting 对话框

class CDialog_Meeting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Meeting)

public:
	CDialog_Meeting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Meeting();

// 对话框数据
	enum { IDD = IDD_MEETING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl list_meeting;
	LONG meetingID;
	CString meetingName;

private:
	void AddMeetingToList(Meeting*);
public:
	afx_msg void OnBnClickedBuMAdd();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBuMMod();
};
#pragma once


// CDialog_Add_Meeting 对话框

class CDialog_Add_Meeting : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Add_Meeting)

public:
	CDialog_Add_Meeting(BOOL isModify = FALSE, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Add_Meeting();

// 对话框数据
	enum { IDD = IDD_ADD_MEETING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Meeting currMeeting;
	//CTime t_MeetingStart;
	BOOL isModify;
	afx_msg void OnBnClickedOk();
	//CString str_StartDate;
};
