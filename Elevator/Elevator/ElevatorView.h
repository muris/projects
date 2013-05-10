// ElevatorView.h : CElevatorView ��Ľӿ�
//
#include "CElevator.h"
#pragma once

#define THREAD_NUM 5
UINT RunElevator(LPVOID pParam);

class CElevatorView : public CView
{
protected: // �������л�����
	CElevatorView();
	DECLARE_DYNCREATE(CElevatorView)

// ����
public:
	CElevatorDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // Override
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	virtual void OnInitialUpdate();
public:
	CStatic m_wndFlourTitle;
	CStatic m_wndUpTitle;
	CStatic m_wndDownTitle;
	CStatic m_wndFlourName1;
	CStatic m_wndFlourName2;
	CStatic m_wndFlourName3;
	CStatic m_wndFlourName4;
	CStatic m_wndFlourName5;

	CWinThread *m_pThread[THREAD_NUM];
	CElevatorSingle m_pParam[THREAD_NUM];

// ʵ��
public:
	virtual ~CElevatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnStart();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // ElevatorView.cpp �еĵ��԰汾
inline CElevatorDoc* CElevatorView::GetDocument() const
   { return reinterpret_cast<CElevatorDoc*>(m_pDocument); }
#endif

