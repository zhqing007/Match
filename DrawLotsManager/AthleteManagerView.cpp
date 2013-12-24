// AthleteManagerView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "AthleteManagerView.h"
#include <vector>
#include "DBObject.h"

using namespace std;


// AthleteManagerView

IMPLEMENT_DYNCREATE(AthleteManagerView, CFormView)

AthleteManagerView::AthleteManagerView()
	: CFormView(AthleteManagerView::IDD)
	, str_Name(_T(""))
	, str_Sex(_T(""))
	, i_Age(0)
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
	DDX_Text(pDX, IDC_EDIT_AGE, i_Age);
	DDX_Control(pDX, IDC_COMBO_ORG, cb_Org);
	DDX_Control(pDX, IDC_LIST_ATH, list_Ath);
}

BEGIN_MESSAGE_MAP(AthleteManagerView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &AthleteManagerView::OnBnClickedButtonQuery)
END_MESSAGE_MAP()


// AthleteManagerView ���

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


// AthleteManagerView ��Ϣ�������

void AthleteManagerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	list_Ath.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	list_Ath.InsertColumn(0, _T("����"), LVCFMT_CENTER);
	list_Ath.InsertColumn(1, _T("�Ա�"), LVCFMT_CENTER);
	list_Ath.InsertColumn(2, _T("����"), LVCFMT_CENTER);
	list_Ath.InsertColumn(3, _T("��λ"), LVCFMT_CENTER);
	list_Ath.InsertColumn(4, _T("��ע"), LVCFMT_CENTER);

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

	vector<Organization> allOrg = Organization::GetAll();
	vector<Organization>::iterator i_d;
	int index = 0;
	for(i_d = allOrg.begin(); i_d != allOrg.end(); ++i_d, ++index){
		cb_Org.InsertString(index, i_d->Name);
		cb_Org.SetItemData(index, i_d->ID);
	}
	// TODO: �ڴ����ר�ô����/����û���
}


void AthleteManagerView::OnBnClickedButtonQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int curSel = cb_Org.GetCurSel();
	CString text;
	cb_Org.GetWindowText(text);
	text.Format(_T("%s %d %d"), text, curSel, cb_Org.GetItemData(curSel));
	MessageBox(text);
}
