
// ̰����1.0View.h : C̰����10View ��Ľӿ�
//

#pragma once

#include "Afxtempl.h"  //�����ռ���ģ��


class C̰����10View : public CView
{
protected: // �������л�����
	C̰����10View();
	DECLARE_DYNCREATE(C̰����10View)

// ����
public:
	C̰����10Doc* GetDocument() const;

// ����
public:

private:                     /*******************************   �������   *********************************/
	void ReDisplay(CPoint pPoint);
	void IniAim();
	void IniGame();
	int m_nLeft, m_nTop, m_nWidth, m_nHight, m_nSize;  //��ʼ���꣬��/�ߣ���������ÿ���С
	int m_nDirect;  //��ǰ����1-�ϣ�2-�£�3-��4-�ң�
	CPoint m_pAim;  //��ǰĿ������
	CArray <CPoint, CPoint> m_aBody; //����
	int m_nGameStatus;  //��Ϸ״̬��0-δ��ʼ��1-��ʼ��
	int m_nCount;  //�Ե�Ŀ����
	int m_nTime, m_nTime1;  //��ʱ��

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~C̰����10View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSnakeStart();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // ̰����1.0View.cpp �еĵ��԰汾
inline C̰����10Doc* C̰����10View::GetDocument() const
   { return reinterpret_cast<C̰����10Doc*>(m_pDocument); }
#endif

