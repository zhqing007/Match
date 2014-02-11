// MeetingManagerView.cpp : 实现文件
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
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &MatchView::OnNMClickList1)
END_MESSAGE_MAP()


// MatchView 诊断

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


// MatchView 消息处理程序
// D:\Match\DrawLotsManager\MeetingManagerView.cpp : 实现文件
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
	DDX_Control(pDX, IDC_TROOP_LIST, lbox_troop);
	DDX_Control(pDX, IDC_SPLIT_ADDTR, splBu_AddTr);
	DDX_Control(pDX, IDC_S_MATCHNAME, cs_MatchName);
}

BEGIN_MESSAGE_MAP(MatchOrgAthView, CFormView)
	ON_BN_CLICKED(IDC_BU_SUB_TR, &MatchOrgAthView::OnBnClickedBuSubTr)
	ON_BN_CLICKED(IDC_SPLIT_ADDTR, &MatchOrgAthView::OnBnClickedSplitAddtr)
	ON_LBN_DBLCLK(IDC_TROOP_LIST, &MatchOrgAthView::OnLbnDblclkTroopList)
END_MESSAGE_MAP()


// MatchOrgAthView 诊断

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


// MatchOrgAthView 消息处理程序

// MeetingManagerView.cpp : 实现文件
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


// MeetingManagerView 绘图

void MeetingManagerView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// MeetingManagerView 诊断

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


// MeetingManagerView 消息处理程序

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

	// TODO: 在此处添加消息处理程序代码
	m_wndSplitter.MoveWindow(0, 0, cx, cy);
}


void MatchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	list_match.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	list_match.InsertColumn(0, _T("比赛名称"), LVCFMT_CENTER);
	list_match.InsertColumn(1, _T("举办时间"), LVCFMT_CENTER);

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

// Dialog_Match_Prop 对话框

IMPLEMENT_DYNAMIC(Dialog_Match_Prop, CDialogEx)

Dialog_Match_Prop::Dialog_Match_Prop(BOOL _isModify, CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog_Match_Prop::IDD, pParent)
	,isModify(_isModify)
{
	if(!isModify){
		_match.StartDate = CTime::GetCurrentTime().Format("%Y/%m/%d");
		_match.Minage = 0;
		_match.Maxage = 0;
		_match.Sex = "不限";
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


// Dialog_Match_Prop 消息处理程序


void Dialog_Match_Prop::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(_match.Name.Trim().GetLength() == 0){
		MessageBox(_T("比赛名称不能为空！"), _T("提示"), MB_OK | MB_ICONWARNING);
		return;
	}
	if(this->isModify){
		if(_match.Update() == NOTONLYONE){
			MessageBox(_T("已经存在同名的比赛名称，请修改！"),
				_T("提示"), MB_OK | MB_ICONWARNING);
			return;
		}
	}
	else
		if(_match.AddNew() == NOTONLYONE){
			MessageBox(_T("已经存在同名的比赛名称，请修改！"),
				_T("提示"), MB_OK | MB_ICONWARNING);
			return;
		}

	CDialogEx::OnOK();
}

void MatchView::OnBnClickedBuMAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	Dialog_Match_Prop d_Ma_Prop;
	d_Ma_Prop._match._meeting.ID = this->meetingID;
	d_Ma_Prop._match._matchType.ID = 0;
	if(d_Ma_Prop.DoModal() == IDOK)
		AddMatToList(&(d_Ma_Prop._match));
}


void MatchView::OnBnClickedBuMDel()
{
	// TODO: 在此添加控件通知处理程序代码
	if(MessageBox(_T("确定删除所选比赛吗？"), _T("确认"), MB_YESNO | MB_ICONQUESTION) == IDNO)
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
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
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
}


void MatchOrgAthView::SetMatchID(long matchID, CString matchName)
{
	lbox_troop.ResetContent();
	Troop tro;
	tro._match.ID = this->matchID = matchID;
	cs_MatchName.SetWindowText(matchName);
	vector<Troop> v_mat = tro.Query();
	vector<Troop>::iterator i_d;
	for(i_d = v_mat.begin(); i_d != v_mat.end(); ++i_d)
		AddTroToList(&(*i_d));
}


void MatchView::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	if(pNMItemActivate->iItem < 0) return;
	this->rightView->SetMatchID(list_match.GetItemData(pNMItemActivate->iItem),
		list_match.GetItemText(pNMItemActivate->iItem, 0));
}

void MatchOrgAthView::OnBnClickedBuSubTr()
{
	// TODO: 在此添加控件通知处理程序代码
}

void MatchOrgAthView::AddTroToList(Troop* tro)
{
	int c = lbox_troop.GetCount();
	lbox_troop.InsertString(c, tro->Name);
	lbox_troop.SetItemData(c, tro->ID);
}


void MatchOrgAthView::OnBnClickedSplitAddtr()
{
	// TODO: 在此添加控件通知处理程序代码
	Troop tro;
	tro._match.ID = matchID;
	Dialog_TrName trn(&tro);
	if(trn.DoModal() == IDOK)
		AddTroToList(&tro);
}


void MatchOrgAthView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	splBu_AddTr.SetDropDownMenu(IDR_ADDTR_SPLITBU, 0);
}


void MatchOrgAthView::OnLbnDblclkTroopList()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = lbox_troop.GetCurSel();
	if(sel < 0) return;
	Troop tro;
	tro._match.ID = matchID;
	tro.ID = lbox_troop.GetItemData(sel);
	lbox_troop.GetText(sel, tro.Name);
	Dialog_TrName trn(&tro, TRUE);
	if(trn.DoModal() == IDOK){
		lbox_troop.DeleteString(sel);
		lbox_troop.InsertString(sel, tro.Name);
		lbox_troop.SetItemData(sel, tro.ID);
	}
}



// D:\MYCPP\Match\DrawLotsManager\MeetingManagerView.cpp : 实现文件
//

// Dialog_TrName 对话框

IMPLEMENT_DYNAMIC(Dialog_TrName, CDialogEx)

Dialog_TrName::Dialog_TrName(Troop* _tr, BOOL _isModify, CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog_TrName::IDD, pParent)
	, tr(_tr)
	, isModify(_isModify)
{

}

Dialog_TrName::~Dialog_TrName()
{
}

void Dialog_TrName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TRNAME, tr->Name);
}


BEGIN_MESSAGE_MAP(Dialog_TrName, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_TrName::OnBnClickedOk)
END_MESSAGE_MAP()


// Dialog_TrName 消息处理程序


void Dialog_TrName::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int re;
	if(isModify)
		re = tr->Update(FALSE);
	else
		re = tr->AddNew(FALSE);
	if(re == NOTONLYONE){
		MessageBox(_T("已经存在相同的队名，请修改！"), _T("提示"), MB_OK | MB_ICONWARNING);
		return;
	}
	CDialogEx::OnOK();
}

