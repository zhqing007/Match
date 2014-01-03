// AthleteManagerView.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "AthleteManagerView.h"
#include "Dialog_Ath_Property.h"
#include "Dialog_Add_Ath.h"

using namespace std;


// AthleteManagerView

IMPLEMENT_DYNCREATE(AthleteManagerView, CFormView)

AthleteManagerView::AthleteManagerView()
	: CFormView(AthleteManagerView::IDD)
	, str_Name(_T(""))
	, str_Sex(_T(""))
	, str_Age(_T(""))
{

}

AthleteManagerView::~AthleteManagerView()
{
}

void AthleteManagerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, str_Name);
	DDX_CBString(pDX, IDC_COMBO_SEX, str_Sex);
	DDX_CBString(pDX, IDC_EDIT_AGE, str_Age);
	DDX_Control(pDX, IDC_COMBO_ORG, cb_Org);
	DDX_Control(pDX, IDC_LIST_ATH, list_Ath);
}

BEGIN_MESSAGE_MAP(AthleteManagerView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &AthleteManagerView::OnBnClickedButtonQuery)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ATH, &AthleteManagerView::OnNMDblclkListAth)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &AthleteManagerView::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &AthleteManagerView::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// AthleteManagerView 诊断

#ifdef _DEBUG
void AthleteManagerView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void AthleteManagerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// AthleteManagerView 消息处理程序

void AthleteManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	list_Ath.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	list_Ath.InsertColumn(0, _T("姓名"), LVCFMT_CENTER);
	list_Ath.InsertColumn(1, _T("性别"), LVCFMT_CENTER);
	list_Ath.InsertColumn(2, _T("出生日期"), LVCFMT_CENTER);
	list_Ath.InsertColumn(3, _T("单位"), LVCFMT_CENTER);
	list_Ath.InsertColumn(4, _T("备注"), LVCFMT_CENTER);

	CHeaderCtrl* pHeader = list_Ath.GetHeaderCtrl();
	int nCurrWidth, nColHdrWidth;
	ASSERT(pHeader);
	list_Ath.SetRedraw(FALSE);
	for(int iCurrCol = 0; iCurrCol < pHeader->GetItemCount(); ++iCurrCol){
		list_Ath.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE);
		nCurrWidth = list_Ath.GetColumnWidth(iCurrCol);
		list_Ath.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
		nColHdrWidth = list_Ath.GetColumnWidth(iCurrCol);
		list_Ath.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
	}
	list_Ath.SetRedraw(TRUE);
	list_Ath.Invalidate();

	allOrg = Organization::GetAll();
	vector<Organization>::iterator i_d;
	int index = 0;
	for(i_d = allOrg.begin(); i_d != allOrg.end(); ++i_d, ++index){
		cb_Org.InsertString(index, i_d->Name);
		cb_Org.SetItemData(index, i_d->ID);
	}

	str_Age = _T("");
	// TODO: 在此添加专用代码和/或调用基类
}


void AthleteManagerView::OnBnClickedButtonQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	//int curSel = cb_Org.GetCurSel();
	//CString text;
	//cb_Org.GetWindowText(text);
	//text.Format(_T("%s %d %d"), text, curSel, cb_Org.GetItemData(curSel));
	//MessageBox(text);
	UpdateData(TRUE);
	Athlete ath;
	ath.Name = str_Name;
	ath.Sex = str_Sex;
	int orgSel =  cb_Org.GetCurSel();
	if(orgSel >= 0)
		ath.Org.ID = cb_Org.GetItemData(orgSel);

	str_Age = str_Age.Trim();
	if(str_Age.GetLength() != 0){
		CTime t_age = GetCurrentTime();
		int i_age = _ttoi(str_Age);
		if(i_age <= 0){
			MessageBox(_T("年龄不得为0!"), _T("提示"), MB_ICONINFORMATION | MB_OK);
			return;
		}
		ath.Age = i_age;
	}

	list_Ath.DeleteAllItems();
	vector<Athlete> v_athList = ath.Query();
	vector<Athlete>::iterator i_d;
	int index = 0;
	for(i_d = v_athList.begin(); i_d != v_athList.end(); ++i_d, ++index){
		AddAthToList(&(*i_d));
	}
}

void AthleteManagerView::AddAthToList(Athlete* ath)
{
	LVITEMW vitem;
	vitem.pszText = (LPWSTR)(LPCWSTR)ath->Name;
	vitem.iItem = list_Ath.GetItemCount();
	vitem.iSubItem = 0;
	vitem.mask = LVIF_TEXT | LVIF_PARAM;
	vitem.lParam = (LPARAM)ath->ID;
	list_Ath.InsertItem(&vitem);
	list_Ath.SetItemText(vitem.iItem, 1, ath->Sex);
	list_Ath.SetItemText(vitem.iItem, 2, ath->Birth);
	list_Ath.SetItemText(vitem.iItem, 3, ath->Org.Name);
	list_Ath.SetItemText(vitem.iItem, 4, ath->Description);
}

void AthleteManagerView::OnNMDblclkListAth(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	Athlete ath;

	ath.ID = list_Ath.GetItemData(pNMItemActivate->iItem);
	ath.Name = list_Ath.GetItemText(pNMItemActivate->iItem, 0);
	ath.Sex = list_Ath.GetItemText(pNMItemActivate->iItem, 1);
	ath.Birth = list_Ath.GetItemText(pNMItemActivate->iItem, 2);
	ath.Org.Name = list_Ath.GetItemText(pNMItemActivate->iItem, 3);
	ath.Description = list_Ath.GetItemText(pNMItemActivate->iItem, 4);

	CDialog_Ath_Property org_pro(&ath, this);
	int n_Modal = org_pro.DoModal();
	if(n_Modal == IDOK){
		list_Ath.SetItemText(pNMItemActivate->iItem, 0, ath.Name);
		list_Ath.SetItemText(pNMItemActivate->iItem, 1, ath.Sex);
		list_Ath.SetItemText(pNMItemActivate->iItem, 2, ath.Birth);
		list_Ath.SetItemText(pNMItemActivate->iItem, 3, ath.Org.Name);
		list_Ath.SetItemText(pNMItemActivate->iItem, 4, ath.Description);
	}



	*pResult = 0;
}

void AthleteManagerView::OnBnClickedButtonDel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox(_T("确定删除所选人员吗？"), _T("确认"), MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;
	int n_se = list_Ath.GetSelectionMark();
	Athlete ath;
	ath.ID = list_Ath.GetItemData(n_se);
	ath.Delete();
	list_Ath.DeleteItem(n_se);
}

void AthleteManagerView::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_Add_Ath addAth(this);
	addAth.DoModal();
}
