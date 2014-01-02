// Dialog_Add_Ath.cpp : ʵ���ļ�
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
	ON_BN_CLICKED(IDOK, &CDialog_Add_Ath::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialog_Add_Ath ��Ϣ�������


BOOL CDialog_Add_Ath::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��	
	//list_Ath.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	list_Ath.SetCellMargin(1.2);
	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	list_Ath.SetDefaultRowTrait(pRowTrait);

	// Create Columns
	list_Ath.InsertHiddenLabelColumn();	// Requires one never uses column 0
	list_Ath.InsertColumnTrait(1, _T("����"), LVCFMT_CENTER, 100, -1, new CGridColumnTraitEdit);
	CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
	pComboTrait->AddItem((DWORD_PTR)0, _T("��"));
	pComboTrait->AddItem((DWORD_PTR)0, _T("Ů"));
	list_Ath.InsertColumnTrait(2, _T("�Ա�"), LVCFMT_CENTER, 100, -1, pComboTrait);
	CGridColumnTraitDateTime* pDateTimeTrait = new CGridColumnTraitDateTime;
	pDateTimeTrait->SetToggleSelection(true);
	list_Ath.InsertColumnTrait(3, _T("��������"), LVCFMT_CENTER, 100, -1, pDateTimeTrait);
	pComboTrait = new CGridColumnTraitCombo;
	AthleteManagerView* parent = (AthleteManagerView*)this->m_pParentWnd;
	vector<Organization>::iterator i_d;
	int index = 0;
	for(i_d = parent->allOrg.begin(); i_d != parent->allOrg.end(); ++i_d, ++index){
		pComboTrait->AddItem(i_d->ID, i_d->Name);
	}
	list_Ath.InsertColumnTrait(4, _T("��λ"), LVCFMT_CENTER, 100, -1, pComboTrait);
	list_Ath.InsertColumnTrait(5, _T("��ע"), LVCFMT_CENTER, 100, -1, new CGridColumnTraitEdit);	

	// Insert data into list-control by copying from datamodel
	list_Ath.InsertItem(0, _T(""));
	list_Ath.SetItemText(0, 1, NEWCOLTEXT);
	list_Ath.SetItemText(0, 2, _T("��"));
	list_Ath.SetItemText(0, 3, _T("1979/06/04"));
	list_Ath.SetItemText(0, 4, _T(""));
	list_Ath.SetItemText(0, 5, _T(""));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDialog_Add_Ath::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int row = list_Ath.GetItemCount() - 1;
	while(row >= 0) {
		if(list_Ath.GetItemText(row, 1).Compare(NEWCOLTEXT) == 0){
			--row;
			continue;
		}
		Athlete ath;
		ath.Name = list_Ath.GetItemText(row, 1);
		ath.Sex = list_Ath.GetItemText(row, 2);
		ath.Birth = list_Ath.GetItemText(row, 3);
		ath.Org.Name = list_Ath.GetItemText(row, 4);
		CGridColumnTraitCombo* ccb = (CGridColumnTraitCombo*)list_Ath.GetCellColumnTrait(row, 4);
		ath.Org.ID = ccb->GetSelKey(ath.Org.Name);
		ath.Description = list_Ath.GetItemText(row, 5);

		if(ath.AddNew() == TRUE)
			list_Ath.DeleteItem(row);
		--row;
	}

	if(ath.AddNew() == NOTONLYONE){
		CString msg;
		msg.Format(_T("���ݿ����Ѿ�����ͬ����ͬ�ӵ��˶�Ա���Ƿ���Ȼ��ӣ�"
		if(MessageBox(_T("���ݿ����Ѿ�����ͬ����ͬ�ӵ��˶�Ա��\n�Ƿ���Ȼ��ӣ�"),
			_T("�Ƿ����"), MB_YESNO|MB_ICONQUESTION) == IDNO)
			return;
		ath.AddNew(FALSE);
	}


	CDialogEx::OnOK();
}
