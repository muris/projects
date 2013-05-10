// ElevatorView.cpp : CElevatorView 类的实现
//

#include "stdafx.h"
#include "Elevator.h"

#include "ElevatorDoc.h"
#include "ElevatorView.h"
#include <vector>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int m_cxTitle = 155;
int m_cyTitle = 20;

vector<int> up;
vector<int> down;
vector<int> uptemp;
vector<int> downtemp;
// CElevatorView

IMPLEMENT_DYNCREATE(CElevatorView, CView)

BEGIN_MESSAGE_MAP(CElevatorView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
//	ON_WM_CREATE()
ON_COMMAND(ID_START, &CElevatorView::OnStart)
ON_WM_TIMER()
END_MESSAGE_MAP()

// CElevatorView 构造/析构

CElevatorView::CElevatorView()
{
	// TODO: 在此处添加构造代码
	for (int i = 0; i < THREAD_NUM; i++)
		m_pParam[i].m_id = i+1;
}

CElevatorView::~CElevatorView()
{
}

BOOL CElevatorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CElevatorView 绘制

void CElevatorView::OnDraw(CDC* pDC)
{
	CElevatorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect(0, 0, 155, 425);
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CPen *oldpen = pDC->SelectObject(&pen);
	for (int i = 1; i < 7; i++)
	{
		pDC->Rectangle(rect);
		rect.SetRect(i*m_cxTitle, 0, (i+1)*m_cxTitle, 425);
	}
	pDC->SelectObject(oldpen);

	CString temp;
	for (int i = 1; i < 21; i++)
	{
		rect.SetRect(1, i*m_cyTitle, m_cxTitle/3, (i+1)*m_cyTitle);
		temp.Format(_T("%d"), 21 - i);
		pDC->DrawText(temp, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
	for (int i = 0; i < THREAD_NUM; i++)
	{
		int nowflour = m_pParam[i].GetNowFlour();
		temp.Format(_T("%d"), nowflour);
		rect.SetRect((2*m_pParam[i].m_id + 1)*m_cxTitle/2, m_cyTitle, (m_pParam[i].m_id +1)*m_cxTitle, 2*m_cyTitle);
		pDC->DrawText(temp, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		rect.SetRect(m_pParam[i].m_id*m_cxTitle+m_cxTitle/3+2, (21 - nowflour)*m_cyTitle,  m_pParam[i].m_id*m_cxTitle+2*m_cxTitle/3, (22 - nowflour)*m_cyTitle);
		pDC->Rectangle(rect);
	}

	CBrush brush(RGB(0,192,0));
	pDC->SelectObject(&brush);
	int i;
	for (int j = 1; j < 6; j++)
	{
		for (i = 1; i < 21; i++)
		{
			rect.SetRect(j*m_cxTitle+2, i*m_cyTitle, j*m_cxTitle+m_cxTitle/3, (i+1)*m_cyTitle);
			pDC->Rectangle(rect);
		}
		i = 1;
	}
	
	for (i = 2; i < 21; i++)
	{
		rect.SetRect(m_cxTitle/3, i*m_cyTitle, 2*m_cxTitle/3, (i+1)*m_cyTitle);
		pDC->Rectangle(rect);
	}
	CBrush brushdown(RGB(192, 0, 0));
	pDC->SelectObject(&brushdown);
	for (i = 1; i < 20; i++)
	{
		rect.SetRect(2*m_cxTitle/3, i*m_cyTitle, 154, (i+1)*m_cyTitle);
		pDC->Rectangle(rect);
	}
}


// CElevatorView 打印

BOOL CElevatorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CElevatorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CElevatorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}


// CElevatorView 诊断

#ifdef _DEBUG
void CElevatorView::AssertValid() const
{
	CView::AssertValid();
}

void CElevatorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CElevatorDoc* CElevatorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CElevatorDoc)));
	return (CElevatorDoc*)m_pDocument;
}
#endif //_DEBUG

void CElevatorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CElevatorDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPaintDC dc(this);
	CRect rect;
	rect.SetRect(1, 1, m_cxTitle/3, m_cyTitle);
	m_wndFlourTitle.Create(_T("Flour"), WS_CHILD | WS_VISIBLE|SS_CENTER, rect, this);
	rect.SetRect(m_cxTitle/3, 1, 2*m_cxTitle/3, m_cyTitle);
	m_wndUpTitle.Create(_T("↑"), WS_CHILD | WS_VISIBLE | SS_CENTER , rect, this);
	rect.SetRect(2*m_cxTitle/3, 1, 154, m_cyTitle);
	m_wndDownTitle.Create(_T("↓"), WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this);

	rect.SetRect(m_cxTitle+2, 1, 2*m_cxTitle-2, m_cyTitle);
	m_wndFlourName1.Create(_T("The 1st Elevator"), WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this);
	rect.SetRect(2*m_cxTitle+2, 1, 3*(m_cxTitle-1), m_cyTitle);
	m_wndFlourName2.Create(_T("The 2nd Elevator"), WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this);
	rect.SetRect(3*m_cxTitle+2, 1, 4*(m_cxTitle-1), m_cyTitle);
	m_wndFlourName3.Create(_T("The 3rd Elevator"), WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this);
	rect.SetRect(4*m_cxTitle+2, 1, 5*(m_cxTitle-1), m_cyTitle);
	m_wndFlourName4.Create(_T("The 4th Elevator"), WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this);
	rect.SetRect(5*m_cxTitle+2, 1, 6*(m_cxTitle-1), m_cyTitle);
	m_wndFlourName5.Create(_T("The 5th Elevator"), WS_CHILD | WS_VISIBLE | SS_CENTER, rect, this);

}
// CElevatorView 消息处理程序

void CElevatorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
	int id = point.x / m_cxTitle;
	if (id < 0 || id > 5)
		return;
	CRect rect;
	if (id > 0)
	{
		rect.SetRect(id*m_cxTitle, m_cyTitle, id*m_cxTitle+m_cxTitle/3, 21*m_cyTitle);
		if (!rect.PtInRect(point))
			return;
		CElevatorDoc *pDoc = GetDocument();
		int n = 21 - point.y / m_cyTitle;
		if (n < 1 || n > 20)
			return;
		switch (id)//When the button is pressed in the elevator, make sure which flour and elevator
		{
		case 1:
			{
				if (m_pParam[0].GetDirection() == UP)
				{
					if (n <= m_pParam[0].GetNowFlour())
						return;
				}
				else if (m_pParam[0].GetDirection() == DOWN)
				{
					if (n >= m_pParam[0].GetNowFlour())
						return;
				}
				m_pParam[0].WantedFlour(n);
			}
			break;
		case 2:
			{
				if (m_pParam[1].GetDirection() == UP)
				{
					if (n <= m_pParam[1].GetNowFlour())
						return;
				}
				else if (m_pParam[1].GetDirection() == DOWN)
				{
					if (n >= m_pParam[1].GetNowFlour())
						return;
				}
				m_pParam[1].WantedFlour(n);
			}
			break;
		case 3:
			{
				if (m_pParam[2].GetDirection() == UP)
				{
					if (n <= m_pParam[2].GetNowFlour())
						return;
				}
				else if (m_pParam[2].GetDirection() == DOWN)
				{
					if (n >= m_pParam[2].GetNowFlour())
						return;
				}
				m_pParam[2].WantedFlour(n);
			}
			break;
		case 4:
			{
				if (m_pParam[3].GetDirection() == UP)
				{
					if (n <= m_pParam[3].GetNowFlour())
						return;
				}
				else if (m_pParam[3].GetDirection() == DOWN)
				{
					if (n >= m_pParam[3].GetNowFlour())
						return;
				}

				m_pParam[3].WantedFlour(n);
			}
			break;
		case 5:
			{
				if (m_pParam[4].GetDirection() == UP)
				{
					if (n <= m_pParam[4].GetNowFlour())
						return;
				}
				else if (m_pParam[4].GetDirection() == DOWN)
				{
					if (n >= m_pParam[4].GetNowFlour())
						return;
				}

				m_pParam[4].WantedFlour(n);
			}
			break;
		}
		rect.SetRect(id*m_cxTitle+2,  (21 - n)*m_cyTitle, id*m_cxTitle+m_cxTitle/3, (22-n)*m_cyTitle);
	}
	else//put the flour number in the vector based on the directions
	{
		rect.SetRect(0, 0, m_cxTitle/3, 154);
		if (rect.PtInRect(point))
			return;
		rect.SetRect(m_cxTitle/3, 2*m_cyTitle, 2*m_cxTitle/3, 21*m_cyTitle);//up
		CRect rect1(2*m_cxTitle/3, m_cyTitle, 154, 20*m_cyTitle);//down
		if (rect.PtInRect(point))//Up button, insert by the increasing order
		{
			int n = 21 - point.y / m_cyTitle;
			if (n < 1 || n > 19)
				return;
			vector<int>::iterator it;
			for (it = up.begin(); it != up.end(); it++)
			{
				if (n > (*it))
					continue;
				else
					break;
			}
			if (it != up.end())
			{
				up.insert(it, n);
			}
			else
			{
				up.push_back(n);
			}
			rect.SetRect(m_cxTitle/3, (21 - n)*m_cyTitle, 2*m_cxTitle/3, (22 - n)*m_cyTitle); 
		}
		else if (rect1.PtInRect(point))//Down button, insert by the decreasing order
		{
			int n = 21 - point.y / m_cyTitle;
			if (n < 2 || n > 20)
				return;
			vector<int>::iterator it;
			for (it = down.begin(); it != down.end(); it++)
			{
				if (n < (*it))
					continue;
				else
					break;
			}
			if (it != down.end())
			{
				down.insert(it, n);
			}
			else
			{
				down.push_back(n);
			}
			rect.SetRect(2*m_cxTitle/3, (21 - n)*m_cyTitle, 154, (22 - n)*m_cyTitle); 
		}
		else
			return;
	}
	CClientDC dc(this);
	CBrush brush(RGB(0,129,129));
	dc.SelectObject(&brush);
	dc.Rectangle(rect);
}

void CElevatorView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
}

UINT RunElevator(LPVOID pParam)
{
	CElevatorSingle *m_pParam = (CElevatorSingle*)pParam;
	CWnd m_Wnd;

	int tempflour;
	int nextflour;
	int nowflour;
	CString now;
	m_Wnd.Attach(m_pParam->m_hWnd);
	CClientDC dc(&m_Wnd);
	CRect rect;
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen *oldpen;
	vector<int>::iterator it = m_pParam->m_FlourNum.begin();
	while (true)
	{
		nowflour = m_pParam->GetNowFlour();
		while (!m_pParam->m_FlourNum.empty())
		{
			m_pParam->SetState(WORK);
			nextflour = m_pParam->m_FlourNum[0];
			if (m_pParam->GetDirection() == UP)
			{
				while (nowflour != nextflour)
				{
					if (!m_pParam->m_FlourNum.empty())
					{
						tempflour = m_pParam->m_FlourNum[0];
						if (tempflour < nextflour)
							nextflour = tempflour;
					}
					nowflour++;
					now.Format(_T("%d"), nowflour);
					rect.SetRect((2*m_pParam->m_id + 1)*m_cxTitle/2, m_cyTitle, (m_pParam->m_id +1)*m_cxTitle, 2*m_cyTitle);
					dc.DrawText(now, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					rect.SetRect(m_pParam->m_id*m_cxTitle+m_cxTitle/3+2, (21 - nowflour)*m_cyTitle,  m_pParam->m_id*m_cxTitle+2*m_cxTitle/3, (22 - nowflour)*m_cyTitle);
					dc.Rectangle(rect);
					oldpen = dc.SelectObject(&pen);
					rect.SetRect(m_pParam->m_id*m_cxTitle+m_cxTitle/3+2, (22 - nowflour)*m_cyTitle,  m_pParam->m_id*m_cxTitle+2*m_cxTitle/3, (23 - nowflour)*m_cyTitle);
					dc.Rectangle(rect);
					dc.SelectObject(oldpen);
					m_pParam->SetNowFlour(nowflour);
					Sleep(1000);
				}
				rect.SetRect(m_pParam->m_id*m_cxTitle+2,  (21 - nowflour)*m_cyTitle, m_pParam->m_id*m_cxTitle+m_cxTitle/3, (22-nowflour)*m_cyTitle);
				CBrush brush(RGB(0,192,0));
				CBrush *oldbrush;
				oldbrush = dc.SelectObject(&brush);
				dc.Rectangle(rect);
				if (!uptemp.empty())
				{
					if (nowflour == uptemp[0])
					{
						rect.SetRect(m_cxTitle/3, (21 - nowflour)*m_cyTitle, 2*m_cxTitle/3, (22 - nowflour)*m_cyTitle);
						dc.Rectangle(rect);
						CBrush brushtemp(RGB(192, 0, 0));
						rect.SetRect(2*m_cxTitle/3, (21 - nowflour)*m_cyTitle, 154, (22 - nowflour)*m_cyTitle);
						dc.SelectObject(&brushtemp);
						dc.Rectangle(rect);
						uptemp.erase(uptemp.begin());
					}
				}
				dc.SelectObject(oldbrush);
				rect.SetRect(m_pParam->m_id*m_cxTitle+m_cxTitle/3+2, (21 - nowflour)*m_cyTitle,  m_pParam->m_id*m_cxTitle+2*m_cxTitle/3, (22 - nowflour)*m_cyTitle);
				dc.DrawText(_T("Open Door"), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				Sleep(2000);
			}
			else if (m_pParam->GetDirection() == DOWN)
			{
				while (nowflour != nextflour)
				{
					if (!m_pParam->m_FlourNum.empty())
					{
						tempflour = m_pParam->m_FlourNum[0];
						if (tempflour > nextflour)
							nextflour = tempflour;
					}
					nowflour--;
					now.Format(_T("%d"), nowflour);
					rect.SetRect((2*m_pParam->m_id + 1)*m_cxTitle/2, m_cyTitle, (m_pParam->m_id +1)*m_cxTitle, 2*m_cyTitle);
					dc.DrawText(now, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
					rect.SetRect(m_pParam->m_id*m_cxTitle+m_cxTitle/3+2, (21 - nowflour)*m_cyTitle,  m_pParam->m_id*m_cxTitle+2*m_cxTitle/3, (22 - nowflour)*m_cyTitle);
					dc.Rectangle(rect);
					oldpen = dc.SelectObject(&pen);
					rect.SetRect(m_pParam->m_id*m_cxTitle+m_cxTitle/3+2, (20 - nowflour)*m_cyTitle,  m_pParam->m_id*m_cxTitle+2*m_cxTitle/3, (21 - nowflour)*m_cyTitle);
					dc.Rectangle(rect);
					dc.SelectObject(oldpen);
					m_pParam->SetNowFlour(nowflour);
					Sleep(1000);
				}
				rect.SetRect(m_pParam->m_id*m_cxTitle+2,  (21 - nowflour)*m_cyTitle, m_pParam->m_id*m_cxTitle+m_cxTitle/3, (22-nowflour)*m_cyTitle);
				CBrush brush(RGB(0,192,0));
				CBrush *oldbrush;
				oldbrush = dc.SelectObject(&brush);
				dc.Rectangle(rect);
				if (!downtemp.empty())
				{
					if (nowflour == downtemp[0])
					{
						rect.SetRect(m_cxTitle/3, (21 - nowflour)*m_cyTitle, 2*m_cxTitle/3, (22 - nowflour)*m_cyTitle);
						dc.Rectangle(rect);
						rect.SetRect(2*m_cxTitle/3, (21 - nowflour)*m_cyTitle, 154, (22 - nowflour)*m_cyTitle);
						CBrush brushtemp(RGB(192, 0, 0));
						dc.SelectObject(&brushtemp);
						dc.Rectangle(rect);
						downtemp.erase(downtemp.begin());
					}
				}
				dc.SelectObject(oldbrush);
				rect.SetRect(m_pParam->m_id*m_cxTitle+m_cxTitle/3+2, (21 - nowflour)*m_cyTitle,  m_pParam->m_id*m_cxTitle+2*m_cxTitle/3, (22 - nowflour)*m_cyTitle);
				dc.DrawText(_T("Open Door"), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				Sleep(2500);
			}
			it = m_pParam->m_FlourNum.begin();
			if (it != m_pParam->m_FlourNum.end())
			{
				it = m_pParam->m_FlourNum.erase(it);
			}
		}
		m_pParam->SetDirection(STOP);
		m_pParam->SetState(FREE);
		Sleep(2500);
	}
	m_Wnd.Detach();
	return 0;
}

void CElevatorView::OnStart()
{
	// TODO: Add your command handler code here
	for (int i = 0; i < THREAD_NUM; i++)
	{
		m_pThread[i] = NULL;
		m_pParam[i].m_hWnd = GetSafeHwnd();
		m_pThread[i] = AfxBeginThread(RunElevator, (LPVOID)(&m_pParam[i]));
	}
	SetTimer(0, 1000, NULL);
}

void CElevatorView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	vector<int>::iterator iter_up = up.begin();
	vector<int>::iterator iter_down = down.begin();
	int id = 0;
	if (!up.empty())
	{
		int d = 20;
		while (iter_up != up.end())
		{
			for (int i = 0; i < THREAD_NUM; i++)
			{
				if ((((m_pParam[i].GetDirection() == UP) && ((*iter_up) - m_pParam[i].GetNowFlour()) < d && ((*iter_up) - m_pParam[i].GetNowFlour()) > 0)) || (m_pParam[i].GetState() == FREE && abs(m_pParam[i].GetNowFlour() - (*iter_up)) < d))
				{
					d = abs((*iter_up) - m_pParam[i].GetNowFlour());
					id = m_pParam[i].m_id;
				}
			}
			if (id != 0)
			{
				m_pParam[id-1].WantedFlour((*iter_up));
				if (m_pParam[id-1].GetNowFlour() < (*iter_up))
				{
					uptemp.push_back((*iter_up));
				}
				else
				{
					vector<int>::iterator itt = downtemp.begin();
					for (; itt != downtemp.end(); itt++)
					{
						if ((*iter_up) < (*itt))
							continue;
						else
							break;
					}
					if (itt != downtemp.end())
						downtemp.insert(itt, *iter_up);
					else
						downtemp.push_back(*iter_up);
				}
				iter_up = up.erase(iter_up);
			}
		}
	}
	if (!down.empty())
	{
		int d = 20;
		while (iter_down != down.end())
		{
			for (int i = 0; i < THREAD_NUM; i++)
			{
				if ((((m_pParam[i].GetDirection() == DOWN) && (m_pParam[i].GetNowFlour() - (*iter_down)) < d && (m_pParam[i].GetNowFlour() - (*iter_down)) > 0)) ||(m_pParam[i].GetState() == FREE && abs(m_pParam[i].GetNowFlour() - (*iter_down)) < d))
				{
					d = abs(m_pParam[i].GetNowFlour() - (*iter_down));
					id = m_pParam[i].m_id;
				}
			}
			if (id != 0)
			{
				m_pParam[id-1].WantedFlour((*iter_down));
				if (m_pParam[id-1].GetNowFlour() > (*iter_down))
				{
					downtemp.push_back((*iter_down));
				}
				else
				{
					vector<int>::iterator itt = uptemp.begin();
					for (; itt != uptemp.end(); itt++)
					{
						if ((*iter_down) > (*itt))
							continue;
						else
							break;
					}
					if (itt != uptemp.end())
						uptemp.insert(itt, *iter_down);
					else
						uptemp.push_back(*iter_down);
				}
				iter_down = down.erase(iter_down);
			}
		}
	}
	CView::OnTimer(nIDEvent);
}
