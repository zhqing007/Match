// Dialog_Add_Ath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "Dialog_Add_Ath.h"
#include "afxdialogex.h"


// CDialog_Add_Ath �Ի���

IMPLEMENT_DYNAMIC(CDialog_Add_Ath, CDialogEx)

CDialog_Add_Ath::CDialog_Add_Ath(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Add_Ath::IDD, pParent)
{

}

CDialog_Add_Ath::~CDialog_Add_Ath()
{
}

void CDialog_Add_Ath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_Ath);
}


BEGIN_MESSAGE_MAP(CDialog_Add_Ath, CDialogEx)
END_MESSAGE_MAP()


// CDialog_Add_Ath ��Ϣ�������


BOOL CDialog_Add_Ath::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��	
	list_Ath.SetExtendedStyle(LVS_EX_GRIDLINES);
	list_Ath.InsertColumn(0, _T("���Ķ���"), LVCFMT_CENTER);
	LVITEMW vitem;
	vitem.pszText = _T("XXX");;
	vitem.iItem = 0;
	vitem.iSubItem = 0;
	vitem.mask = LVIF_TEXT;
	list_Ath.InsertItem(&vitem);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
