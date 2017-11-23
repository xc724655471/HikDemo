#pragma once
#include "afxwin.h"

#include"GeneralDef.h"


// ConfigWind dialog

class ConfigWind : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigWind)

public:
	ConfigWind(CWnd* pParent = NULL);   // standard constructor
	virtual ~ConfigWind();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CONFIGURATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CListBox BirateType;
//	CListBox PicQuality;
//	CListBox StreamType;
//	CListBox VideoFrameRate;
//	CListBox Resolution;
	void Init();
	CComboBox StreamType;
	CComboBox BitrateType;
	CComboBox PicQuality;
	CComboBox Resolution;
	CComboBox VideoFrameRate;
	//void UpdateData(BYTE byResolution);
	void UpdateConfieData(BYTE byResolution);
	void UpdateConfieData(NET_DVR_COMPRESSION_INFO_V30 struNormHighRecordPara);


};
