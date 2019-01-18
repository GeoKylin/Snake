
// ̰����1.0View.cpp : C̰����10View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "̰����1.0.h"
#endif

#include "̰����1.0Doc.h"
#include "̰����1.0View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C̰����10View

IMPLEMENT_DYNCREATE(C̰����10View, CView)

BEGIN_MESSAGE_MAP(C̰����10View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SNAKE_START, &C̰����10View::OnSnakeStart)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// C̰����10View ����/����

C̰����10View::C̰����10View()
{
	// TODO:  �ڴ˴���ӹ������

	IniGame();                      //��Ϸ��ʼ��

}

C̰����10View::~C̰����10View()
{
}

BOOL C̰����10View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// C̰����10View ����

void C̰����10View::OnDraw(CDC* pDC)
{
	C̰����10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

	//����Ϸ����
	pDC->SelectStockObject(WHITE_BRUSH);      //���ն�����ѡ���豸����
	pDC->Rectangle(CRect(m_nLeft - 1, m_nTop - 1, m_nLeft + m_nWidth*m_nSize + 1, m_nTop + m_nHight*m_nSize + 1));

	//��ʾ��ǰ��ʱ
	CString uStr;
	uStr.Format(_T("��ǰ��ʱ:%d s"), m_nTime);     //ʹ�������͵�����ת����һ���ַ���
	pDC->TextOutW(m_nLeft + m_nWidth*m_nSize + 30, 40, uStr);

	//��ʾ��ǰ�÷�
	uStr.Format(_T("��ǰ�÷�:%d"),m_nCount);
	pDC->TextOutW(m_nLeft + m_nWidth*m_nSize + 30, 140, uStr);

	//��ʾĿ��
	pDC->SelectStockObject(LTGRAY_BRUSH);
	pDC->Rectangle(CRect(m_nLeft + m_pAim.y*m_nSize, m_nTop + m_pAim.x*m_nSize, m_nLeft + (m_pAim.y + 1)*m_nSize, m_nTop + (m_pAim.x + 1)*m_nSize));

	//����
	for (int i = 0; i <= m_aBody.GetUpperBound(); i++)
	{
		CPoint uPoint = m_aBody.GetAt(i);
		pDC->Rectangle(CRect(m_nLeft + uPoint.y*m_nSize, m_nTop + uPoint.x*m_nSize, m_nLeft + (uPoint.y + 1)*m_nSize, m_nTop + (uPoint.x + 1)*m_nSize));
	}
}


// C̰����10View ��ӡ

BOOL C̰����10View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C̰����10View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C̰����10View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// C̰����10View ���

#ifdef _DEBUG
void C̰����10View::AssertValid() const
{
	CView::AssertValid();
}

void C̰����10View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C̰����10Doc* C̰����10View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C̰����10Doc)));
	return (C̰����10Doc*)m_pDocument;
}
#endif //_DEBUG


// C̰����10View ��Ϣ�������


void C̰����10View::OnSnakeStart()
{
	// TODO:  �ڴ���������������
	//������Ϸ��������ʱ��
	IniGame();
	m_nGameStatus = 1;
	SetTimer(1, 100, NULL);   //����ʱ�����ƣ�ʱ����/ms,ʹ��OnTime������
	Invalidate();     //�������ڿͻ�����Ч
}


void C̰����10View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nChar)
	{
	case 38:m_nDirect = 4;   //������
		break;
	case 40:m_nDirect = 3;
		break;
	case 37:m_nDirect = 2;
		break;
	case 39:m_nDirect = 1;
		break;
	//default:
	//	break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void C̰����10View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_nTime1++;    //��ʱ
	if (m_nTime1==10)     //�ﵽ1��
	{
		m_nTime++;
		m_nTime1 = 0;
		Invalidate();
	}
	CPoint uPoint = m_aBody.GetAt(0);  //��ͷ��λ��
	int uTag = 0;                     //�Ƿ�ʧ��
	switch (m_nDirect)     //�ж���һ�����Ƿ����
	{
	case 1:
		uPoint.y++;
		if (uPoint.y >= m_nWidth)  uTag = 1;
		break;
	case 2:
		uPoint.y--;
		if (uPoint.y <0)  uTag = 1;
		break;
	case 3:
		uPoint.x++;
		if (uPoint.x >= m_nHight)  uTag = 1;
		break;
	case 4:
		uPoint.x--;
		if (uPoint.x <0)  uTag = 1;
		break;
	}
	if (uTag==0)           //�ж����Ƿ�����������
	{
		for (int i = 0; i <= m_aBody.GetUpperBound(); i++)
		{
			CPoint uPoint1 = m_aBody.GetAt(i);
			if (uPoint1.x==uPoint.x&&uPoint1.y==uPoint.y)
			{
				uTag = 1;
				break;
			}
		}
	}
	if (uTag==0)
	{
		m_aBody.InsertAt(0, uPoint);   //����ͷ��λ��
		ReDisplay(uPoint);
		if (uPoint.x==m_pAim.x&&uPoint.y==m_pAim.y)   //����Ŀ��
		{
			m_nCount++;
			IniAim();
			Invalidate();
		}
		else
		{
			CPoint uPoint1 = m_aBody.GetAt(m_aBody.GetUpperBound());
			m_aBody.RemoveAt(m_aBody.GetUpperBound());   //�Ƴ����һ��Ԫ��         �����ʣ�������
			ReDisplay(uPoint1);
		}
	}
	else   //��Ϸ����
	{
		KillTimer(1);
		AfxMessageBox(_T("��սʧ��!"));
	}

	CView::OnTimer(nIDEvent);
}

/********************************    ��Ϸ����    *********************************/

void C̰����10View::IniAim()  //�ú����������һ�����߳Ե�Ŀ�꣬�����Ŀ��ǡ���������غϣ������²���һ��
{
	int uX, uY;    //Ŀ��λ��
	while (1)
	{
		uX = rand() % m_nHight;     //����������ĺ���
		uY = rand() % m_nWidth;
		int uTag = 0;               //0-���������غϣ�1-�غ�
		for (int i = 0; i <=m_aBody.GetUpperBound(); i++)     //��ȡ���������±�
		{
			CPoint uPoint = m_aBody.GetAt(i);    //����ָ�������ŵ�����Ԫ��
			if (uPoint.x==uX||uPoint.y==uY)     //Ŀ���������غ�
			{
				uTag = 1;
				break;
			}
		}
		if (uTag == 0) break;
	}
	m_pAim = CPoint(uX, uY);    //������Ŀ�����ڳ�Ա������
}

void C̰����10View::IniGame()   //�ú�������Ϸ��ʼ����������Ϸ�ĳ�ʼ״̬
{
	//��Ϸ����
	m_nLeft = 20;
	m_nTop = 20;
	m_nWidth = 40;
	m_nHight = 30;
	m_nSize = 10;

	//��Ϸ��ʼ״̬
	m_nGameStatus = 0;  //δ��ʼ
	m_nDirect = 1;  //����
	m_nCount = 0;   //δ��

	//��ʼ������
	m_aBody.RemoveAll();   //��Dictionary������ɾ�����йؼ��ֺ���Ŀ��
	m_aBody.Add(CPoint(2, 7));
	m_aBody.Add(CPoint(2, 6));
	m_aBody.Add(CPoint(2, 5));
	m_aBody.Add(CPoint(2, 4));

	//��ʱ������
	m_nTime = 0;
	m_nTime1 = 0;

	//��ʼ�������������
	srand((unsigned)time(NULL));

	//����һ��Ŀ��
	IniAim();
}

void C̰����10View::ReDisplay(CPoint pPoint)   //ˢ����Ϸ������pPoint����һ��С����
{
	InvalidateRect(CRect(m_nLeft + pPoint.y*m_nSize, m_nTop + pPoint.x*m_nSize, m_nLeft + (pPoint.y + 1)*m_nSize, m_nTop + (pPoint.x + 1)*m_nSize));
	//��������������һ������
}