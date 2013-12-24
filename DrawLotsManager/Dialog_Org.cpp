// Dialog_Org.cpp : 实现文件
//
#include "stdafx.h"
#include "DrawLotsManager.h"
#include "Dialog_Org.h"
#include "afxdialogex.h"
#include "DBManager.h"


// CDialog_Org 对话框

IMPLEMENT_DYNAMIC(CDialog_Org, CDialogEx)

CDialog_Org::CDialog_Org(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Org::IDD, pParent)
{
}

CDialog_Org::~CDialog_Org()
{
}

void CDialog_Org::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ORG, list_org);
}


BEGIN_MESSAGE_MAP(CDialog_Org, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ORG, &CDialog_Org::OnNMDblclkListOrg)
	ON_BN_CLICKED(IDC_BUTTON_ADDNEW, &CDialog_Org::OnBnClickedButtonAddnew)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDialog_Org::OnBnClickedButtonDelete)
END_MESSAGE_MAP()


// CDialog_Org 消息处理程序


BOOL CDialog_Org::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	list_org.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	list_org.InsertColumn(0, _T("中文队名"), LVCFMT_CENTER);
	list_org.InsertColumn(1, _T("英文队名"), LVCFMT_CENTER);
	list_org.InsertColumn(2, _T("备注"), LVCFMT_CENTER);

	CHeaderCtrl* pHeader = list_org.GetHeaderCtrl();
	int nCurrWidth, nColHdrWidth;
	ASSERT(pHeader);
	list_org.SetRedraw(FALSE);
	for(int iCurrCol = 0; iCurrCol < pHeader->GetItemCount(); ++iCurrCol){
		list_org.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE);
		nCurrWidth = list_org.GetColumnWidth(iCurrCol);
		list_org.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
		nColHdrWidth = list_org.GetColumnWidth(iCurrCol);
		list_org.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
	}
	list_org.SetRedraw(TRUE);
	list_org.Invalidate();

	vector<Organization> allOrg = Organization::GetAll();
	vector<Organization>::iterator i_d;
	for(i_d = allOrg.begin(); i_d != allOrg.end(); ++i_d){
		AddOrtToList(&(*i_d));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


// CDialog_Org_Property 对话框

IMPLEMENT_DYNAMIC(CDialog_Org_Property, CDialogEx)

CDialog_Org_Property::CDialog_Org_Property(Organization* p_o, int n_type, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Org_Property::IDD, pParent)
	, p_org(p_o)
	, type(n_type)
{

}

CDialog_Org_Property::~CDialog_Org_Property()
{
}

void CDialog_Org_Property::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, p_org->Name);
	DDX_Text(pDX, IDC_EDIT_NA_EN, p_org->Name_en);
	DDX_Text(pDX, IDC_EDIT_DES, p_org->Description);
}


BEGIN_MESSAGE_MAP(CDialog_Org_Property, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_Org_Property::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialog_Org_Property 消息处理程序


void CDialog_Org::OnNMDblclkListOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	Organization org;
	//LVITEMW vitem;
	//vitem.iItem = pNMItemActivate->iItem;
	//vitem.mask = LVIF_TEXT | LVIF_PARAM;
	//vitem.iSubItem = 0;
	//vitem.pszText = new WCHAR[100];
	//vitem.cchTextMax = 99;
	//list_org.GetItem(&vitem);
	//org.ID = vitem.lParam;
	//org.Name = vitem.pszText;	

	org.ID = list_org.GetItemData(pNMItemActivate->iItem);
	org.Name = list_org.GetItemText(pNMItemActivate->iItem, 0);
	org.Name_en = list_org.GetItemText(pNMItemActivate->iItem, 1);
	org.Description = list_org.GetItemText(pNMItemActivate->iItem, 2);

	CDialog_Org_Property org_pro(&org, 1);
	int n_Modal = org_pro.DoModal();
	if(n_Modal == IDOK){
		list_org.SetItemText(pNMItemActivate->iItem, 0, org.Name);
		list_org.SetItemText(pNMItemActivate->iItem, 1, org.Name_en);
		list_org.SetItemText(pNMItemActivate->iItem, 2, org.Description);
	}

	*pResult = 0;
}


BOOL CDialog_Org_Property::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	switch(type){
	case 0: this->SetWindowText(_T("新增运动队"));break;
	case 1: this->SetWindowText(_T("修改运动队"));break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDialog_Org::OnBnClickedButtonAddnew()
{
	// TODO: 在此添加控件通知处理程序代码
	Organization org;
	CDialog_Org_Property org_pro(&org, 0);
	int n_Modal = org_pro.DoModal();
	if(n_Modal == IDOK)
		AddOrtToList(&org);
}

void CDialog_Org::AddOrtToList(Organization* org)
{
	LVITEMW vitem;
	vitem.pszText = (LPWSTR)(LPCWSTR)org->Name;
	vitem.iItem = list_org.GetItemCount();
	vitem.iSubItem = 0;
	vitem.mask = LVIF_TEXT | LVIF_PARAM;
	vitem.lParam = (LPARAM)org->ID;
	list_org.InsertItem(&vitem);
	list_org.SetItemText(vitem.iItem, 1, org->Name_en);
	list_org.SetItemText(vitem.iItem, 2, org->Description);
}


void CDialog_Org_Property::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(p_org->Name.GetLength() == 0){
		MessageBox(_T("队名不得为空。"), _T("添加错误"), MB_OK);
		return;
	}
	switch(type){
	case 0: //添加
		if(p_org->AddNew() == NOTONLYONE){
			MessageBox(_T("数据库中已经存在相同名称的运动队。"), _T("添加错误"), MB_OK);
			return;
		}
		break;
	case 1: //修改 
		if(p_org->Update() == NOTONLYONE){
			MessageBox(_T("数据库中已经存在相同名称的运动队。"), _T("修改错误"), MB_OK);
			return;
		}
		break;
	}
	
	CDialogEx::OnOK();
}



void CDialog_Org::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox(_T("确定删除所选队吗？"), _T("确认"), MB_YESNO) == IDNO)
		return;
	int n_se = list_org.GetSelectionMark();
	Organization org;
	org.ID = list_org.GetItemData(n_se);
	org.Delete();
	list_org.DeleteItem(n_se);
}
