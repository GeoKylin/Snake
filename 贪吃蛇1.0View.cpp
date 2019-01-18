
// 贪吃蛇1.0View.cpp : C贪吃蛇10View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "贪吃蛇1.0.h"
#endif

#include "贪吃蛇1.0Doc.h"
#include "贪吃蛇1.0View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C贪吃蛇10View

IMPLEMENT_DYNCREATE(C贪吃蛇10View, CView)

BEGIN_MESSAGE_MAP(C贪吃蛇10View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SNAKE_START, &C贪吃蛇10View::OnSnakeStart)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// C贪吃蛇10View 构造/析构

C贪吃蛇10View::C贪吃蛇10View()
{
	// TODO:  在此处添加构造代码

	IniGame();                      //游戏初始化

}

C贪吃蛇10View::~C贪吃蛇10View()
{
}

BOOL C贪吃蛇10View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// C贪吃蛇10View 绘制

void C贪吃蛇10View::OnDraw(CDC* pDC)
{
	C贪吃蛇10Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码

	//画游戏区域
	pDC->SelectStockObject(WHITE_BRUSH);      //把终端字体选入设备环境
	pDC->Rectangle(CRect(m_nLeft - 1, m_nTop - 1, m_nLeft + m_nWidth*m_nSize + 1, m_nTop + m_nHight*m_nSize + 1));

	//显示当前用时
	CString uStr;
	uStr.Format(_T("当前用时:%d s"), m_nTime);     //使任意类型的数据转换成一个字符串
	pDC->TextOutW(m_nLeft + m_nWidth*m_nSize + 30, 40, uStr);

	//显示当前得分
	uStr.Format(_T("当前得分:%d"),m_nCount);
	pDC->TextOutW(m_nLeft + m_nWidth*m_nSize + 30, 140, uStr);

	//显示目标
	pDC->SelectStockObject(LTGRAY_BRUSH);
	pDC->Rectangle(CRect(m_nLeft + m_pAim.y*m_nSize, m_nTop + m_pAim.x*m_nSize, m_nLeft + (m_pAim.y + 1)*m_nSize, m_nTop + (m_pAim.x + 1)*m_nSize));

	//画蛇
	for (int i = 0; i <= m_aBody.GetUpperBound(); i++)
	{
		CPoint uPoint = m_aBody.GetAt(i);
		pDC->Rectangle(CRect(m_nLeft + uPoint.y*m_nSize, m_nTop + uPoint.x*m_nSize, m_nLeft + (uPoint.y + 1)*m_nSize, m_nTop + (uPoint.x + 1)*m_nSize));
	}
}


// C贪吃蛇10View 打印

BOOL C贪吃蛇10View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C贪吃蛇10View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void C贪吃蛇10View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// C贪吃蛇10View 诊断

#ifdef _DEBUG
void C贪吃蛇10View::AssertValid() const
{
	CView::AssertValid();
}

void C贪吃蛇10View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C贪吃蛇10Doc* C贪吃蛇10View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C贪吃蛇10Doc)));
	return (C贪吃蛇10Doc*)m_pDocument;
}
#endif //_DEBUG


// C贪吃蛇10View 消息处理程序


void C贪吃蛇10View::OnSnakeStart()
{
	// TODO:  在此添加命令处理程序代码
	//启动游戏，启动定时器
	IniGame();
	m_nGameStatus = 1;
	SetTimer(1, 100, NULL);   //（计时器名称，时间间隔/ms,使用OnTime函数）
	Invalidate();     //整个窗口客户区无效
}


void C贪吃蛇10View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case 38:m_nDirect = 4;   //键盘码
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


void C贪吃蛇10View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_nTime1++;    //计时
	if (m_nTime1==10)     //达到1秒
	{
		m_nTime++;
		m_nTime1 = 0;
		Invalidate();
	}
	CPoint uPoint = m_aBody.GetAt(0);  //蛇头的位置
	int uTag = 0;                     //是否失败
	switch (m_nDirect)     //判断下一步蛇是否出界
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
	if (uTag==0)           //判断蛇是否碰到了自身
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
		m_aBody.InsertAt(0, uPoint);   //新蛇头的位置
		ReDisplay(uPoint);
		if (uPoint.x==m_pAim.x&&uPoint.y==m_pAim.y)   //碰上目标
		{
			m_nCount++;
			IniAim();
			Invalidate();
		}
		else
		{
			CPoint uPoint1 = m_aBody.GetAt(m_aBody.GetUpperBound());
			m_aBody.RemoveAt(m_aBody.GetUpperBound());   //移除最后一个元素         有疑问？？？？
			ReDisplay(uPoint1);
		}
	}
	else   //游戏结束
	{
		KillTimer(1);
		AfxMessageBox(_T("挑战失败!"));
	}

	CView::OnTimer(nIDEvent);
}

/********************************    游戏函数    *********************************/

void C贪吃蛇10View::IniAim()  //该函数随机产生一个供蛇吃的目标，如果该目标恰好与蛇身重合，则重新产生一个
{
	int uX, uY;    //目标位置
	while (1)
	{
		uX = rand() % m_nHight;     //产生随机数的函数
		uY = rand() % m_nWidth;
		int uTag = 0;               //0-不与蛇身重合，1-重合
		for (int i = 0; i <=m_aBody.GetUpperBound(); i++)     //获取数组的最高下标
		{
			CPoint uPoint = m_aBody.GetAt(i);    //返回指定索引号的数组元素
			if (uPoint.x==uX||uPoint.y==uY)     //目标与蛇身重合
			{
				uTag = 1;
				break;
			}
		}
		if (uTag == 0) break;
	}
	m_pAim = CPoint(uX, uY);    //产生的目标存放在成员变量中
}

void C贪吃蛇10View::IniGame()   //该函数对游戏初始化，定义游戏的初始状态
{
	//游戏区域
	m_nLeft = 20;
	m_nTop = 20;
	m_nWidth = 40;
	m_nHight = 30;
	m_nSize = 10;

	//游戏初始状态
	m_nGameStatus = 0;  //未开始
	m_nDirect = 1;  //向右
	m_nCount = 0;   //未吃

	//初始化蛇身
	m_aBody.RemoveAll();   //从Dictionary对象中删除所有关键字和条目对
	m_aBody.Add(CPoint(2, 7));
	m_aBody.Add(CPoint(2, 6));
	m_aBody.Add(CPoint(2, 5));
	m_aBody.Add(CPoint(2, 4));

	//计时器清零
	m_nTime = 0;
	m_nTime1 = 0;

	//初始化随机数发生器
	srand((unsigned)time(NULL));

	//产生一个目标
	IniAim();
}

void C贪吃蛇10View::ReDisplay(CPoint pPoint)   //刷新游戏区域中pPoint处的一个小方格
{
	InvalidateRect(CRect(m_nLeft + pPoint.y*m_nSize, m_nTop + pPoint.x*m_nSize, m_nLeft + (pPoint.y + 1)*m_nSize, m_nTop + (pPoint.x + 1)*m_nSize));
	//窗体更新区域添加一个矩形
}