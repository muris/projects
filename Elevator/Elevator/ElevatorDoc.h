// ElevatorDoc.h : CElevatorDoc ��Ľӿ�
//


#pragma once

class CElevatorDoc : public CDocument
{
protected: // �������л�����
	CElevatorDoc();
	DECLARE_DYNCREATE(CElevatorDoc)

// ����
public:


// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CElevatorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
};


