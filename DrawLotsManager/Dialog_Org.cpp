// Dialog_Org.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "DrawLotsManager.h"
#include "Dialog_Org.h"
#include "afxdialogex.h"
#include "DBManager.h"


// CDialog_Org �Ի���

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


// CDialog_Org ��Ϣ�������


BOOL CDialog_Org::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	list_org.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	list_org.InsertColumn(0, _T("���Ķ���"), LVCFMT_CENTER);
	list_org.InsertColumn(1, _T("Ӣ�Ķ���"), LVCFMT_CENTER);
	list_org.InsertColumn(2, _T("��ע"), LVCFMT_CENTER);

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
	// �쳣: OCX ����ҳӦ���� FALSE
}


// CDialog_Org_Property �Ի���

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


// CDialog_Org_Property ��Ϣ�������


void CDialog_Org::OnNMDblclkListOrg(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	switch(type){
	case 0: this->SetWindowText(_T("�����˶���"));break;
	case 1: this->SetWindowText(_T("�޸��˶���"));break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDialog_Org::OnBnClickedButtonAddnew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(p_org->Name.GetLength() == 0){
		MessageBox(_T("��������Ϊ�ա�"), _T("��Ӵ���"), MB_OK);
		return;
	}
	switch(type){
	case 0: //���
		if(p_org->AddNew() == NOTONLYONE){
			MessageBox(_T("���ݿ����Ѿ�������ͬ���Ƶ��˶��ӡ�"), _T("��Ӵ���"), MB_OK);
			return;
		}
		break;
	case 1: //�޸� 
		if(p_org->Update() == NOTONLYONE){
			MessageBox(_T("���ݿ����Ѿ�������ͬ���Ƶ��˶��ӡ�"), _T("�޸Ĵ���"), MB_OK);
			return;
		}
		break;
	}
	
	CDialogEx::OnOK();
}



void CDialog_Org::OnBnClickedButtonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox(_T("ȷ��ɾ����ѡ����"), _T("ȷ��"), MB_YESNO) == IDNO)
		return;
	int n_se = list_org.GetSelectionMark();
	Organization org;
	org.ID = list_org.GetItemData(n_se);
	org.Delete();
	list_org.DeleteItem(n_se);
}
