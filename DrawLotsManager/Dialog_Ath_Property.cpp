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
	ON_BN_CLICKED(IDOK, &CDialog_Ath_Property::OnBnClickedOk)
	ON_CBN_CLOSEUP(IDC_COMBO_ORG, &CDialog_Ath_Property::OnCbnCloseupComboOrg)
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

void CDialog_Ath_Property::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	cb_org.GetWindowText(ath->Org.Name);
	ath->Org.ID = cb_org.GetItemData(cb_org.GetCurSel());
	if(ath->Name.GetLength() == 0){
		MessageBox(_T("姓名不得为空。"), _T("修改错误"), MB_OK|MB_ICONWARNING);
		return;
	}
	if(ath->Update() == NOTONLYONE){
		if(MessageBox(_T("数据库中已经存在同名且同队的运动员，\n是否仍然添加？"),
			_T("是否继续"), MB_YESNO|MB_ICONQUESTION) == IDNO)
			return;
		ath->Update(FALSE);
	}
	CDialogEx::OnOK();
}


void CDialog_Ath_Property::OnCbnCloseupComboOrg()
{
	// TODO: 在此添加控件通知处理程序代码
	//cb_org.GetWindowText(ath->Org.Name);
	//ath->Org.ID = cb_org.GetItemData(cb_org.GetCurSel());	
}
