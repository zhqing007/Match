// MeetingManagerView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "MeetingManagerView.h"
#include "DrawLotsManagerDoc.h"

// MatchView

IMPLEMENT_DYNCREATE(MatchView, CFormView)

MatchView::MatchView()
	: CFormView(MatchView::IDD)
{

}

MatchView::~MatchView()
{
}

void MatchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list_match);
}

BEGIN_MESSAGE_MAP(MatchView, CFormView)
	ON_BN_CLICKED(IDC_BU_M_ADD, &MatchView::OnBnClickedBuMAdd)
	ON_BN_CLICKED(IDC_BU_M_DEL, &MatchView::OnBnClickedBuMDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &MatchView::OnNMDblclkList1)
END_MESSAGE_MAP()


// MatchView ���

#ifdef _DEBUG
void MatchView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MatchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MatchView ��Ϣ�������
// D:\Match\DrawLotsManager\MeetingManagerView.cpp : ʵ���ļ�
// MatchOrgAthView

IMPLEMENT_DYNCREATE(MatchOrgAthView, CFormView)

MatchOrgAthView::MatchOrgAthView()
	: CFormView(MatchOrgAthView::IDD)
{

}

MatchOrgAthView::~MatchOrgAthView()
{
}

void MatchOrgAthView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(MatchOrgAthView, CFormView)
END_MESSAGE_MAP()


// MatchOrgAthView ���

#ifdef _DEBUG
void MatchOrgAthView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MatchOrgAthView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MatchOrgAthView ��Ϣ�������

// MeetingManagerView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawLotsManager.h"
#include "MeetingManagerView.h"


// MeetingManagerView

IMPLEMENT_DYNCREATE(MeetingManagerView, CView)

MeetingManagerView::MeetingManagerView()
{

}

MeetingManagerView::~MeetingManagerView()
{
}

BEGIN_MESSAGE_MAP(MeetingManagerView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// MeetingManagerView ��ͼ

void MeetingManagerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// MeetingManagerView ���

#ifdef _DEBUG
void MeetingManagerView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void MeetingManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// MeetingManagerView ��Ϣ�������

int MeetingManagerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CDrawLotsManagerDoc* drawDoc = (CDrawLotsManagerDoc*)this->GetDocument();
	meetingID = drawDoc->l_Meeting_ID;
	meetingName = drawDoc->str_Meeting_Name;
	GetParentFrame()->SetWindowText(meetingName);

	CRect rc;  
    GetWindowRect(&rc);  

	VERIFY(m_wndSplitter.CreateStatic(this, 1, 2, WS_CHILD | WS_VISIBLE)); 	
	CCreateContext *pContext = (CCreateContext*) lpCreateStruct->lpCreateParams;
	
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(MatchView), CSize(300, rc.Height()), pContext);	
	m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(MatchOrgAthView), CSize(0, rc.Height()), pContext);
	MatchView* pViewRes = (MatchView*)m_wndSplitter.GetPane(0,0);
	pViewRes->meetingID = drawDoc->l_Meeting_ID;
	pViewRes->rightView = (MatchOrgAthView*)m_wndSplitter.GetPane(0,1);
	m_wndSplitter.MoveWindow(0, 0, rc.Width(), rc.Height());
	
	return 0;
}


void MeetingManagerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	m_wndSplitter.MoveWindow(0, 0, cx, cy);
}


void MatchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	list_match.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	list_match.InsertColumn(0, _T("��������"), LVCFMT_CENTER);
	list_match.InsertColumn(1, _T("�ٰ�ʱ��"), LVCFMT_CENTER);

	CHeaderCtrl* pHeader = list_match.GetHeaderCtrl();
	int nCurrWidth, nColHdrWidth;
	ASSERT(pHeader);
	list_match.SetRedraw(FALSE);
	for(int iCurrCol = 0; iCurrCol < pHeader->GetItemCount(); ++iCurrCol){
		list_match.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE);
		nCurrWidth = list_match.GetColumnWidth(iCurrCol);
		list_match.SetColumnWidth(iCurrCol, LVSCW_AUTOSIZE_USEHEADER);
		nColHdrWidth = list_match.GetColumnWidth(iCurrCol);
		list_match.SetColumnWidth(iCurrCol, max(nCurrWidth, nColHdrWidth));
	}
	list_match.SetRedraw(TRUE);
	list_match.Invalidate();

	Match mat;
	mat._meeting.ID = this->meetingID;
	vector<Match> v_match = mat.Query();
	vector<Match>::iterator i_d;
	for(i_d = v_match.begin(); i_d != v_match.end(); ++i_d){
		AddMatToList(&(*i_d));
	}
}

void MatchView::AddMatToList(Match* mat)
{
	LVITEMW vitem;
	vitem.pszText = (LPWSTR)(LPCWSTR)mat->Name;
	vitem.iItem = list_match.GetItemCount();
	vitem.iSubItem = 0;
	vitem.mask = LVIF_TEXT | LVIF_PARAM;
	vitem.lParam = (LPARAM)mat->ID;
	list_match.InsertItem(&vitem);
	list_match.SetItemText(vitem.iItem, 1, mat->StartDate);
}

// Dialog_Match_Prop �Ի���

IMPLEMENT_DYNAMIC(Dialog_Match_Prop, CDialogEx)

Dialog_Match_Prop::Dialog_Match_Prop(BOOL _isModify, CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog_Match_Prop::IDD, pParent)
	,isModify(_isModify)
{
	if(!isModify){
		_match.StartDate = CTime::GetCurrentTime().Format("%Y/%m/%d");
		_match.Minage = 0;
		_match.Maxage = 0;
		_match.Sex = "����";
	}
}

Dialog_Match_Prop::~Dialog_Match_Prop()
{
}

void Dialog_Match_Prop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MATCH_NAME, _match.Name);
	DDX_Text(pDX, IDC_MATCH_ADD, _match.Address);
	DDX_DateTimeCtrl(pDX, IDC_MATCH_DATE, _match.StartDate);
	DDX_CBString(pDX, IDC_MATCH_SEX, _match.Sex);
	DDX_Text(pDX, IDC_M_MINAGE, _match.Minage);
	DDX_Text(pDX, IDC_M_MAXAGE, _match.Maxage);
}


BEGIN_MESSAGE_MAP(Dialog_Match_Prop, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_Match_Prop::OnBnClickedOk)
END_MESSAGE_MAP()


// Dialog_Match_Prop ��Ϣ�������


void Dialog_Match_Prop::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(_match.Name.Trim().GetLength() == 0){
		MessageBox(_T("�������Ʋ���Ϊ�գ�"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		return;
	}
	if(this->isModify){
		if(_match.Update() == NOTONLYONE){
			MessageBox(_T("�Ѿ�����ͬ���ı������ƣ����޸ģ�"),
				_T("��ʾ"), MB_OK | MB_ICONWARNING);
			return;
		}
	}
	else
		if(_match.AddNew() == NOTONLYONE){
			MessageBox(_T("�Ѿ�����ͬ���ı������ƣ����޸ģ�"),
				_T("��ʾ"), MB_OK | MB_ICONWARNING);
			return;
		}

	CDialogEx::OnOK();
}

void MatchView::OnBnClickedBuMAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Dialog_Match_Prop d_Ma_Prop;
	d_Ma_Prop._match._meeting.ID = this->meetingID;
	d_Ma_Prop._match._matchType.ID = 0;
	if(d_Ma_Prop.DoModal() == IDOK)
		AddMatToList(&(d_Ma_Prop._match));
}


void MatchView::OnBnClickedBuMDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBox(_T("ȷ��ɾ����ѡ������"), _T("ȷ��"), MB_YESNO | MB_ICONQUESTION) == IDNO)
		return;
	int n_se = list_match.GetSelectionMark();
	Match mat;
	mat.ID = list_match.GetItemData(n_se);
	mat.Delete();
	list_match.DeleteItem(n_se);
}


void MatchView::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(pNMItemActivate->iItem < 0) return;
	Match mat;
	mat.ID = list_match.GetItemData(pNMItemActivate->iItem);
	vector<Match> v_m = mat.Query();
	Dialog_Match_Prop d_Ma_Prop(TRUE);
	d_Ma_Prop._match = v_m[0];
	if(d_Ma_Prop.DoModal() == IDOK){
		list_match.SetItemText(pNMItemActivate->iItem, 0, d_Ma_Prop._match.Name);
		list_match.SetItemText(pNMItemActivate->iItem, 1, d_Ma_Prop._match.StartDate);
	}

	*pResult = 0;
}
