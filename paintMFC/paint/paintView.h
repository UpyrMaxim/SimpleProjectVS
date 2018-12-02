
// paintView.h : interface of the CpaintView class
//

#pragma once


class CpaintView : public CView
{
protected: // create from serialization only
	CpaintView() noexcept;
	DECLARE_DYNCREATE(CpaintView)

// Attributes
public:
	CpaintDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CpaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// myVArs
private:
	int downPressX;
	int downPressY;
	bool drawingInProgress{ false };
	unsigned long penColor = RGB(0, 0, 0);
	int penWidth =1;
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetcolorRed();
	afx_msg void OnSetcolorGreen();
	afx_msg void OnSetcolorBlue();
	afx_msg void OnSetcolorBlack();
	afx_msg void OnSetwidth1();
	afx_msg void OnSetwidth3();
	afx_msg void OnSetwidth5();
};

#ifndef _DEBUG  // debug version in paintView.cpp
inline CpaintDoc* CpaintView::GetDocument() const
   { return reinterpret_cast<CpaintDoc*>(m_pDocument); }
#endif

