// Dialog_Meeting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "Dialog_Meeting.h"
#include "afxdialogex.h"


// Dialog_Meeting �Ի���

IMPLEMENT_DYNAMIC(CDialog_Meeting, CDialogEx)

CDialog_Meeting::CDialog_Meeting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Meeting::IDD, pParent)
{

}

CDialog_Meeting::~CDialog_Meeting()
{
}

void CDialog_Meeting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_meeting);
}


BEGIN_MESSAGE_MAP(CDialog_Meeting, CDialogEx)
	ON_BN_CLICKED(IDC_BU_M_ADD, &CDialog_Meeting::OnBnClickedBuMAdd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDialog_Meeting::OnNMDblclkList1)
	//ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDialog_Meeting::OnNMClickList1)
	ON_BN_CLICKED(IDOK, &CDialog_Meeting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BU_M_MOD, &CDialog_Meeting::OnBnClickedBuMMod)
END_MESSAGE_MAP()


// Dialog_Meeting ��Ϣ�������


BOOL CDialog_Meeting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	list_meeting.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	list_meeting.InsertColumn(0, _T("�˶�����"), LVCFMT_CENTER);
	list_meeting.InsertColumn(1, _T("�ٰ�ʱ��"), LVCFMT_CENTER);
	list_meeting.InsertColumn(2, _T("�ٰ�ص�"), LVCFMT_CENTER);

	CHeaderCtrl* pHeader = list_meeting.GetHeaderCtrl();
	int nCurrWidth, nColHdrWidth;
	ASSERT(pHeader);
	list_meeting.SetRedraw(FALSE);
	for(int iCurrCol = 0; iCurrCol < pHeader->GetItemCount(); ++iCurrCol){
		list_meeting.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE);
		nCurrWidth = list_meeting.GetColumnWidth(iCurrCol);
		list_meeting.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
		nColHdrWidth = list_meeting.GetColumnWidth(iCurrCol);
		list_meeting.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
	}
	list_meeting.SetRedraw(TRUE);
	list_meeting.Invalidate();

	vector<Meeting> allMeeting = Meeting::GetAll();
	vector<Meeting>::iterator i_d;
	for(i_d = allMeeting.begin(); i_d != allMeeting.end(); ++i_d){
		AddMeetingToList(&(*i_d));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDialog_Meeting::AddMeetingToList(Meeting* met)
{
	LVITEMW vitem;
	vitem.pszText = (LPWSTR)(LPCWSTR)met->Name;
	vitem.iItem = list_meeting.GetItemCount();
	vitem.iSubItem = 0;
	vitem.mask = LVIF_TEXT | LVIF_PARAM;
	vitem.lParam = (LPARAM)met->ID;
	list_meeting.InsertItem(&vitem);
	list_meeting.SetItemText(vitem.iItem, 1, met->StartDate);
	list_meeting.SetItemText(vitem.iItem, 2, met->Address);
}

void CDialog_Meeting::OnBnClickedBuMAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog_Add_Meeting dia_Add;
	if(dia_Add.DoModal() != IDOK) return;
	AddMeetingToList(&(dia_Add.currMeeting));
}

void CDialog_Meeting::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	OnBnClickedOk();
}

void CDialog_Meeting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int s = list_meeting.GetSelectionMark();
	if(s == -1){
		MessageBox(_T("��ѡ��һ���˶��ᣡ"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		return;
	}
	meetingID = list_meeting.GetItemData(s);
	meetingName = list_meeting.GetItemText(s, 0);
	CDialogEx::OnOK();
}


// D:\Match\DrawLotsManager\Dialog_Meeting.cpp : ʵ���ļ�
//
// CDialog_Add_Meeting �Ի���

IMPLEMENT_DYNAMIC(CDialog_Add_Meeting, CDialogEx)

CDialog_Add_Meeting::CDialog_Add_Meeting(BOOL _isModify, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Add_Meeting::IDD, pParent)
	//, t_MeetingStart(CTime::GetCurrentTime())
	, isModify(_isModify)
{
	if(!isModify)
		currMeeting.StartDate = CTime::GetCurrentTime().Format("%Y/%m/%d");
}

CDialog_Add_Meeting::~CDialog_Add_Meeting()
{
}

void CDialog_Add_Meeting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, currMeeting.Name);
	//DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, t_MeetingStart);
	DDX_Text(pDX, IDC_EDIT3, currMeeting.Address);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, currMeeting.StartDate);
}


BEGIN_MESSAGE_MAP(CDialog_Add_Meeting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_Add_Meeting::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialog_Add_Meeting ��Ϣ�������

void CDialog_Add_Meeting::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(currMeeting.Name.Trim().GetLength() == 0){
		MessageBox(_T("�˶������Ʋ���Ϊ�գ�"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		return;
	}
	//currMeeting.StartDate = t_MeetingStart.Format("%Y/%m/%d");
	if(this->isModify){
		if(currMeeting.Update() == NOTONLYONE){
			MessageBox(_T("�Ѿ�����ͬ�����˶������ƣ����޸ģ�"),
				_T("��ʾ"), MB_OK | MB_ICONWARNING);
			return;
		}
	}
	else
		if(currMeeting.AddNew() == NOTONLYONE){
			MessageBox(_T("�Ѿ�����ͬ�����˶������ƣ����޸ģ�"),
				_T("��ʾ"), MB_OK | MB_ICONWARNING);
			return;
		}
	CDialogEx::OnOK();
}

void CDialog_Meeting::OnBnClickedBuMMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int s = list_meeting.GetSelectionMark();
	if(s == -1){
		MessageBox(_T("��ѡ��һ���˶��ᣡ"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		return;
	}

	CDialog_Add_Meeting dia_Modify(TRUE);
	dia_Modify.currMeeting.ID = list_meeting.GetItemData(s);
	dia_Modify.currMeeting.Name = list_meeting.GetItemText(s, 0);
	dia_Modify.currMeeting.StartDate = list_meeting.GetItemText(s, 1);
	dia_Modify.currMeeting.Address = list_meeting.GetItemText(s, 2);	
	if(dia_Modify.DoModal() == IDOK){
		list_meeting.SetItemText(s, 0, dia_Modify.currMeeting.Name);
		list_meeting.SetItemText(s, 1, dia_Modify.currMeeting.StartDate);
		list_meeting.SetItemText(s, 2, dia_Modify.currMeeting.Address);
	}
}
