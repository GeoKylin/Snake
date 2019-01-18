
// 贪吃蛇1.0View.h : C贪吃蛇10View 类的接口
//

#pragma once

#include "Afxtempl.h"  //数据收集类模板


class C贪吃蛇10View : public CView
{
protected: // 仅从序列化创建
	C贪吃蛇10View();
	DECLARE_DYNCREATE(C贪吃蛇10View)

// 特性
public:
	C贪吃蛇10Doc* GetDocument() const;

// 操作
public:

private:                     /*******************************   定义变量   *********************************/
	void ReDisplay(CPoint pPoint);
	void IniAim();
	void IniGame();
	int m_nLeft, m_nTop, m_nWidth, m_nHight, m_nSize;  //起始坐标，宽/高（格数），每格大小
	int m_nDirect;  //当前方向（1-上，2-下，3-左，4-右）
	CPoint m_pAim;  //当前目标坐标
	CArray <CPoint, CPoint> m_aBody; //蛇身
	int m_nGameStatus;  //游戏状态（0-未开始，1-开始）
	int m_nCount;  //吃掉目标数
	int m_nTime, m_nTime1;  //用时间

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~C贪吃蛇10View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSnakeStart();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // 贪吃蛇1.0View.cpp 中的调试版本
inline C贪吃蛇10Doc* C贪吃蛇10View::GetDocument() const
   { return reinterpret_cast<C贪吃蛇10Doc*>(m_pDocument); }
#endif

