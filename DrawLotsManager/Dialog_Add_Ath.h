#pragma once
#include "afxcmn.h"
#include "CGridListCtrlEx.h"


// CDialog_Add_Ath 对话框

class CDialog_Add_Ath : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Add_Ath)

public:
	CDialog_Add_Ath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog_Add_Ath();

// 对话框数据
	enum { IDD = IDD_ADD_ATHLETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CGridListCtrlEx list_Ath;
};
