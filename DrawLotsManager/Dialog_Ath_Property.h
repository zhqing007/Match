#pragma once
#include "atltime.h"
#include "DBObject.h"
#include "afxwin.h"


// CDialog_Ath_Property �Ի���

class CDialog_Ath_Property : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Ath_Property)

public:
	CDialog_Ath_Property(Athlete*, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Ath_Property();

// �Ի�������
	enum { IDD = IDD_ATH_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//CString name;
	//CString sex;
	//CTime birth;
	//CString org;
	//CString des;

private:
	Athlete* ath;
public:
	virtual BOOL OnInitDialog();
	CComboBox cb_org;
};
