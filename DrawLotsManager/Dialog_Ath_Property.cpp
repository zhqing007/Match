// Dialog_Ath_Property.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "Dialog_Ath_Property.h"
#include "afxdialogex.h"
#include "AthleteManagerView.h"


// CDialog_Ath_Property 对话框

IMPLEMENT_DYNAMIC(CDialog_Ath_Property, CDialogEx)

CDialog_Ath_Property::CDialog_Ath_Property(Athlete* ath_, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Ath_Property::IDD, pParent)
	, ath(ath_)
{

}

CDialog_Ath_Property::~CDialog_Ath_Property()
{
}

void CDialog_Ath_Property::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, ath->Name);
	DDX_CBString(pDX, IDC_COMBO_SEX, ath->Sex);
	DDX_DateTimeCtrl(pDX, IDC_DATE_BIRTH, ath->Birth);
	DDX_Text(pDX, IDC_EDIT_DES, ath->Description);
	DDX_Control(pDX, IDC_COMBO_ORG, cb_org);
}


BEGIN_MESSAGE_MAP(CDialog_Ath_Property, CDialogEx)
END_MESSAGE_MAP()


// CDialog_Ath_Property 消息处理程序


BOOL CDialog_Ath_Property::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	AthleteManagerView* parent = (AthleteManagerView*)this->m_pParentWnd;
	vector<Organization>::iterator i_d;
	int index = 0;
	for(i_d = parent->allOrg.begin(); i_d != parent->allOrg.end(); ++i_d, ++index){
		cb_org.InsertString(index, i_d->Name);
		cb_org.SetItemData(index, i_d->ID);
		if(i_d->Name == ath->Org.Name) cb_org.SetCurSel(index);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
