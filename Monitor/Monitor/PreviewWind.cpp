// PreviewWind.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "PreviewWind.h"
#include "afxdialogex.h"


// PreviewWind dialog

IMPLEMENT_DYNAMIC(PreviewWind, CDialogEx)

PreviewWind::PreviewWind(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIDEOSHOW, pParent)
{

}

PreviewWind::~PreviewWind()
{
}

void PreviewWind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHOW1, m_show1);
	DDX_Control(pDX, IDC_STATIC_SHOW2, m_show2);
}


BEGIN_MESSAGE_MAP(PreviewWind, CDialogEx)
END_MESSAGE_MAP()


// PreviewWind message handlers


void PreviewWind::CreateShowWind(CRect rect)
{
	int allwidth = rect.Width();
	int allheight = rect.Height()-20;
	int width = allwidth / 3;
	int height = allheight / 3;
	for (int i = 0; i < 9; i++)
	{
		int x = i % 3;
		int y = i / 3;
		RECT rc;
		rc.left = x * width;
		rc.right = x * width + width;
		rc.top = y * height;
		rc.bottom = y * height + height;
		CString text;
		text.Format(_T("%d"), i);
		m_wndShow[i].Create(text, WS_VISIBLE | WS_CHILD, rc, this, IDD_DIALOG_VIDEOSHOW + i);
	}

}
