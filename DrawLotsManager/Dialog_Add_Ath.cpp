// Dialog_Add_Ath.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "Dialog_Add_Ath.h"
#include "afxdialogex.h"
#include "CGridRowTraitXP.h"
#include "CGridColumnTraitCombo.h"
#include "CGridColumnTraitEdit.h"
#include "CGridColumnTraitDateTime.h"
#include "AthleteManagerView.h"


// CDialog_Add_Ath 对话框

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


// CDialog_Add_Ath 消息处理程序


BOOL CDialog_Add_Ath::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	//list_Ath.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	list_Ath.SetCellMargin(1.2);
	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	list_Ath.SetDefaultRowTrait(pRowTrait);

	// Create Columns
	list_Ath.InsertHiddenLabelColumn();	// Requires one never uses column 0
	list_Ath.InsertColumnTrait(1, _T("姓名"), LVCFMT_CENTER, 100, -1, new CGridColumnTraitEdit);
	CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
	pComboTrait->AddItem((DWORD_PTR)0, _T("男"));
	pComboTrait->AddItem((DWORD_PTR)0, _T("女"));
	list_Ath.InsertColumnTrait(2, _T("性别"), LVCFMT_CENTER, 100, -1, pComboTrait);
	CGridColumnTraitDateTime* pDateTimeTrait = new CGridColumnTraitDateTime;
	pDateTimeTrait->SetToggleSelection(true);
	list_Ath.InsertColumnTrait(3, _T("出生日期"), LVCFMT_CENTER, 100, -1, pDateTimeTrait);
	pComboTrait = new CGridColumnTraitCombo;
	AthleteManagerView* parent = (AthleteManagerView*)this->m_pParentWnd;
	vector<Organization>::iterator i_d;
	int index = 0;
	for(i_d = parent->allOrg.begin(); i_d != parent->allOrg.end(); ++i_d, ++index){
		pComboTrait->AddItem(i_d->ID, i_d->Name);
	}
	list_Ath.InsertColumnTrait(4, _T("单位"), LVCFMT_CENTER, 100, -1, pComboTrait);
	list_Ath.InsertColumnTrait(5, _T("备注"), LVCFMT_CENTER, 100, -1, new CGridColumnTraitEdit);	

	// Insert data into list-control by copying from datamodel
	list_Ath.InsertItem(0, _T(""));
	list_Ath.SetItemText(0, 1, _T("<新记录>"));
	list_Ath.SetItemText(0, 2, _T("男"));
	list_Ath.SetItemText(0, 3, _T("1979/06/04"));
	list_Ath.SetItemText(0, 4, _T(""));
	list_Ath.SetItemText(0, 5, _T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
