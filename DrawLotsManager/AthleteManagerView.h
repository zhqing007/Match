#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// AthleteManagerView ������ͼ

class AthleteManagerView : public CFormView
{
	DECLARE_DYNCREATE(AthleteManagerView)

protected:
	AthleteManagerView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString str_Name;
	CString str_Sex;
	int i_Age;
	CComboBox cb_Org;
	CListCtrl list_Ath;
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonQuery();
};

