
// paintView.cpp : implementation of the CpaintView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "paint.h"
#endif

#include "paintDoc.h"
#include "paintView.h"
#include <memory>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CpaintView

IMPLEMENT_DYNCREATE(CpaintView, CView)

BEGIN_MESSAGE_MAP(CpaintView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
//	ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_SETCOLOR_RED, &CpaintView::OnSetcolorRed)
ON_COMMAND(ID_SETCOLOR_GREEN, &CpaintView::OnSetcolorGreen)
ON_COMMAND(ID_SETCOLOR_BLUE, &CpaintView::OnSetcolorBlue)
ON_COMMAND(ID_SETCOLOR_BLACK, &CpaintView::OnSetcolorBlack)
ON_COMMAND(ID_SETWIDTH_1, &CpaintView::OnSetwidth1)
ON_COMMAND(ID_SETWIDTH_3, &CpaintView::OnSetwidth3)
ON_COMMAND(ID_SETWIDTH_5, &CpaintView::OnSetwidth5)
ON_COMMAND(ID_SETTYPE_POINT, &CpaintView::OnSettypePoint)
ON_COMMAND(ID_SETTYPE_LINE, &CpaintView::OnSettypeLine)
ON_COMMAND(ID_SETTYPE_RECTANGLE, &CpaintView::OnSettypeRectangle)
ON_COMMAND(ID_SETTYPE_ELLIPSE, &CpaintView::OnSettypeEllipse)
ON_COMMAND(ID_SETTYPE_ERASER, &CpaintView::OnSettypeEraser)
END_MESSAGE_MAP()

// CpaintView construction/destruction

CpaintView::CpaintView() noexcept
{
	// TODO: add construction code here
	baseFigure = new PPoint(penColor, penWidth);
}

CpaintView::~CpaintView()
{
	delete baseFigure;
}

BOOL CpaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	

	return CView::PreCreateWindow(cs);
}

// CpaintView drawing

BasicPaintType* CpaintView::getFigurePtr(const figure &f)
{
	if (f.figureName == L"PPoint") 
		return new PPoint(penColor, penWidth);
	
	if (f.figureName == L"PLine")
		return new PLine(penColor, penWidth);
	
	if (f.figureName == L"PEllipse") 
		return new PEllipse(penColor, penWidth);
	
	if (f.figureName == L"PRectangle")
		return new PRectangle(penColor, penWidth);

	if (f.figureName == L"PEraser")
		return new PRectangle(penColor, penWidth);
	
	return nullptr;
}

void CpaintView::OnDraw(CDC* pDC)
{
	CpaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	BasicPaintType* tmpFigure;

	std::vector<figure> figureVector = pDoc->getVector();

	if (figureVector.size() > 0)
	{
		for(auto i = 0; i < figureVector.size(); i++)
		{
			tmpFigure = getFigurePtr(figureVector[i]);
			CPen myPen(PS_SOLID, figureVector[i].width, figureVector[i].color);
			pDC->SelectObject(&myPen);
			tmpFigure->Draw(pDC, figureVector[i]);
			delete tmpFigure;
			
		}
	}
	// TODO: add draw code for native data here

	//pDC->Rectangle(100, 100, 400, 400);
	//pDC->Ellipse(200, 200, 500, 500);	
}


// CpaintView printing

BOOL CpaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CpaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CpaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CpaintView diagnostics

#ifdef _DEBUG
void CpaintView::AssertValid() const
{
	CView::AssertValid();
}

void CpaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CpaintDoc* CpaintView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CpaintDoc)));
	return (CpaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CpaintView message handlers


void CpaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//this->downPressX = point.x;
	//this->downPressY = point.y;

	drawingInProgress = true;

	CpaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//baseFigure = new PPoint(penColor,penWidth);
	baseFigure->mouseDown(point, pDoc,penColor,penWidth);
	/*pDoc->addPoint(point);*/

	Invalidate();
	UpdateWindow();
	CView::OnLButtonDown(nFlags, point);
}


void CpaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CpaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	drawingInProgress = false;
	//baseFigure = new PPoint(penColor, penWidth);
	baseFigure->mouseUp(point, pDoc, penColor, penWidth);

	Invalidate();
	UpdateWindow();

	CView::OnLButtonUp(nFlags, point);
}


void CpaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CpaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (drawingInProgress)
	{
		//baseFigure = new PPoint(penColor, penWidth);
		baseFigure->mouseMove(point, pDoc, penColor, penWidth);

	/*	pDoc->addPoint(point);*/
		Invalidate();
		UpdateWindow();
	}

	CView::OnMouseMove(nFlags, point);
}


void CpaintView::OnSetcolorRed()
{
	penColor = RGB(255,0,0);
	// TODO: Add your command handler code here
}


void CpaintView::OnSetcolorGreen()
{
	// TODO: Add your command handler code here
	penColor = RGB(0, 255, 0);
}


void CpaintView::OnSetcolorBlue()
{
	// TODO: Add your command handler code here
	penColor = RGB(0, 0, 255);

}


void CpaintView::OnSetcolorBlack()
{
	// TODO: Add your command handler code here
	penColor = RGB(0, 0, 0);
}


void CpaintView::OnSetwidth1()
{
	// TODO: Add your command handler code here
	penWidth = 1;
}

void CpaintView::OnSetwidth3()
{
	// TODO: Add your command handler code here
	penWidth = 3;
}

void CpaintView::OnSetwidth5()
{
	penWidth = 5;
}


void CpaintView::OnSettypePoint()
{
	delete baseFigure;
	baseFigure = new PPoint(penColor, penWidth);
	// TODO: Add your command handler code here
}


void CpaintView::OnSettypeLine()
{
	delete baseFigure;
	baseFigure = new PLine(penColor, penWidth);
	// TODO: Add your command handler code here
}


void CpaintView::OnSettypeRectangle()
{
	delete baseFigure;
	baseFigure = new PRectangle(penColor, penWidth);
	// TODO: Add your command handler code here
}


void CpaintView::OnSettypeEllipse()
{
	delete baseFigure;
	baseFigure = new PEllipse(penColor, penWidth);
	// TODO: Add your command handler code here
}


void CpaintView::OnSettypeEraser()
{
	delete baseFigure;
	baseFigure = new PEraser(penColor, penWidth);
	// TODO: Add your command handler code here
}
