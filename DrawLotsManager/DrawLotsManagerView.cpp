
// DrawLotsManagerView.cpp : CDrawLotsManagerView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "DrawLotsManager.h"
#endif

#include "DrawLotsManagerDoc.h"
#include "DrawLotsManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawLotsManagerView

IMPLEMENT_DYNCREATE(CDrawLotsManagerView, CView)

BEGIN_MESSAGE_MAP(CDrawLotsManagerView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawLotsManagerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDrawLotsManagerView ����/����

CDrawLotsManagerView::CDrawLotsManagerView()
{
	// TODO: �ڴ˴���ӹ������

}

CDrawLotsManagerView::~CDrawLotsManagerView()
{
}

BOOL CDrawLotsManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDrawLotsManagerView ����

void CDrawLotsManagerView::OnDraw(CDC* /*pDC*/)
{
	CDrawLotsManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDrawLotsManagerView ��ӡ


void CDrawLotsManagerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawLotsManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDrawLotsManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDrawLotsManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CDrawLotsManagerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDrawLotsManagerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDrawLotsManagerView ���

#ifdef _DEBUG
void CDrawLotsManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawLotsManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawLotsManagerDoc* CDrawLotsManagerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawLotsManagerDoc)));
	return (CDrawLotsManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawLotsManagerView ��Ϣ�������
