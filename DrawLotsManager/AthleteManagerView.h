#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "DBObject.h"


// AthleteManagerView 窗体视图

class AthleteManagerView : public CFormView
{
	DECLARE_DYNCREATE(AthleteManagerView)

protected:
	AthleteManagerView();           // 动态创建所使用的受保护的构造函数
	virtual ~AthleteManagerView();

public:
	enum { IDD = IDD_ATHLETEMANAGERVIEW };
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
	CString str_Name;
	CString str_Sex;
	CString str_Age;
	CComboBox cb_Org;
	CListCtrl list_Ath;
	vector<Organization> allOrg;

	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonQuery();

private:
	void AddAthToList(Athlete*);
public:
	afx_msg void OnNMDblclkListAth(NMHDR *pNMHDR, LRESULT *pResult);
};


