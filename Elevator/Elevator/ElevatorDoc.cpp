// ElevatorDoc.cpp : CElevatorDoc ���ʵ��
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


// CElevatorDoc ����/����

CElevatorDoc::CElevatorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CElevatorDoc::~CElevatorDoc()
{
}

BOOL CElevatorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CElevatorDoc ���л�

void CElevatorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CElevatorDoc ���

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


// CElevatorDoc ����

void CElevatorDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetTitle(_T("Elevator Schedule Application"));
}
