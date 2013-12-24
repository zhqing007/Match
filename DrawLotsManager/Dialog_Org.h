#pragma once
#include "afxcmn.h"
#include "DBObject.h"

// CDialog_Org �Ի���

class CDialog_Org : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Org)

public:
	CDialog_Org(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog_Org();

// �Ի�������
	enum { IDD = IDD_ORG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddOrg();
	CListCtrl list_org;
	virtual BOOL OnInitDialog();
	afx_msg void OnHdnItemdblclickListOrg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListOrg(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAddnew();

private:
	void AddOrtToList(Organization* org);
public:
	afx_msg void OnBnClickedButtonDelete();
};


// CDialog_Org_Property �Ի���

class CDialog_Org_Property : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_Org_Property)

public:
	//CDialog_Org_Property(CWnd* pParent = NULL);   // ��׼���캯��
	CDialog_Org_Property(Organization*, int, CWnd* pParent = NULL);
	virtual ~CDialog_Org_Property();

// �Ի�������
	enum { IDD = IDD_ORG_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	Organization* p_org;
	int type;//0 ��ӣ� 1 �޸�
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
