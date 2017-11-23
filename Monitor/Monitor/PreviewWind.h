#pragma once
#include "afxwin.h"


// PreviewWind dialog

class PreviewWind : public CDialogEx
{
	DECLARE_DYNAMIC(PreviewWind)

public:
	PreviewWind(CWnd* pParent = NULL);   // standard constructor
	virtual ~PreviewWind();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIDEOSHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_show1;
	CStatic m_show2;
	void CreateShowWind(CRect rect);
	CStatic m_wndShow[9];
};
