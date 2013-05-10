// ElevatorView.h : CElevatorView 类的接口
//
#include "CElevator.h"
#pragma once

#define THREAD_NUM 5
UINT RunElevator(LPVOID pParam);

class CElevatorView : public CView
{
protected: // 仅从序列化创建
	CElevatorView();
	DECLARE_DYNCREATE(CElevatorView)

// 属性
public:
	CElevatorDoc* GetDocument() const;

// 操作
public:

// 重写
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

// 实现
public:
	virtual ~CElevatorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // ElevatorView.cpp 中的调试版本
inline CElevatorDoc* CElevatorView::GetDocument() const
   { return reinterpret_cast<CElevatorDoc*>(m_pDocument); }
#endif

