#pragma once
#include "afxcmn.h"
#include "CGridListCtrlEx.h"


// CDialog_Add_Ath �Ի���

class CDialog_Add_Ath : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Add_Ath)

public:
	CDialog_Add_Ath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Add_Ath();

// �Ի�������
	enum { IDD = IDD_ADD_ATHLETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CGridListCtrlEx list_Ath;
};
