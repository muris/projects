// ElevatorDoc.cpp : CElevatorDoc 类的实现
//

#include "stdafx.h"
#include "Elevator.h"

#include "ElevatorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CElevatorDoc

IMPLEMENT_DYNCREATE(CElevatorDoc, CDocument)

BEGIN_MESSAGE_MAP(CElevatorDoc, CDocument)
END_MESSAGE_MAP()


// CElevatorDoc 构造/析构

CElevatorDoc::CElevatorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CElevatorDoc::~CElevatorDoc()
{
}

BOOL CElevatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CElevatorDoc 序列化

void CElevatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CElevatorDoc 诊断

#ifdef _DEBUG
void CElevatorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CElevatorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CElevatorDoc 命令

void CElevatorDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetTitle(_T("Elevator Schedule Application"));
}
