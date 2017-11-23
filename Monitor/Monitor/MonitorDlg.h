
// MonitorDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "HIK.h"
#include"PreviewWind.h"
#include"ConfigWind.h"
#include "afxwin.h"



// CMonitorDlg dialog
class CMonitorDlg : public CDialogEx
{
// Construction
public:
	CMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	unsigned int m_DevPort;
	UINT m_DevPort;
	CString m_UserName;
	CString m_PassWord;
	CIPAddressCtrl m_DevIP;
	afx_msg void OnBnClickedButtonLogin();
public:
	HIK hik;
	bool m_IsLogin;//是否登录标记
	bool Login();//注册函数
	afx_msg void OnBnClickedButtonPlay();
	bool StartPlay(int loginID,int ch);
	long m_lPlayHandle[9];
	bool m_bIsPlaying[9];
	bool StopPlay(int handID);
	bool StopPlay(ID_CH_HAND_MATCH &hd);
	CTreeCtrl m_ctrlTreeDev;
	void DoGetDeviceResoureCfg();
	LOCAL_DEVICE_INFO m_struDeviceInfo[10];//设备信息结构体
	//int DeviceNum;
	HTREEITEM m_hDevItem;
	void CreateDeviceTree(LONG longinID);
	afx_msg void OnNMDblclkTreeDev(NMHDR *pNMHDR, LRESULT *pResult);
	int m_iCurChanIndex;
	void DbPlayChannel(int,int index);
	int DeviceNum;//注册的所有设备
	afx_msg void OnBnClickedButtonLogout();
	HWND m_PlayWnd[9];
//	CStatic m_PlayWind1;
//	CStatic m_PlayWind2;
	void CodeMatching(NET_DVR_COMPRESSION_INFO_V30 info);
	CTabCtrl m_tab;//对话框控件
	PreviewWind m_PreviewWind;
	ConfigWind m_ConfigWind;
	void TabCpnfig();
	void TabConfig();
	afx_msg void OnTcnSelchangeTabControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonConfig();
	int CurrentDeviceNum;//当前选中设备
	int ResolutionCodeMatch(int code);
	void GetCompressioncfg();
	int CurrentChannelNum;
	afx_msg void OnBnClickedButtonStop();
	int m_PlayingWindNum;//当前正在播放的窗口号
	vector<CString> ipstring;
	ID_CH_HAND_MATCH IDChMatchWind[9];
	afx_msg void OnBnClickedButtonCloudsUp();
};
