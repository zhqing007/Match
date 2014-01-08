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

Dialog_Match_Prop::Dialog_Match_Prop(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog_Match_Prop::IDD, pParent)
{

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
	CDialogEx::OnOK();
}
