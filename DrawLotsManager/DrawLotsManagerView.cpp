
// DrawLotsManagerView.cpp : CDrawLotsManagerView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDrawLotsManagerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDrawLotsManagerView 构造/析构

CDrawLotsManagerView::CDrawLotsManagerView()
{
	// TODO: 在此处添加构造代码

}

CDrawLotsManagerView::~CDrawLotsManagerView()
{
}

BOOL CDrawLotsManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawLotsManagerView 绘制

void CDrawLotsManagerView::OnDraw(CDC* /*pDC*/)
{
	CDrawLotsManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDrawLotsManagerView 打印


void CDrawLotsManagerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDrawLotsManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawLotsManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawLotsManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CDrawLotsManagerView 诊断

#ifdef _DEBUG
void CDrawLotsManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawLotsManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawLotsManagerDoc* CDrawLotsManagerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawLotsManagerDoc)));
	return (CDrawLotsManagerDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawLotsManagerView 消息处理程序
