
// MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMonitorDlg dialog



CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MONITOR_DIALOG, pParent)
	, m_DevPort(8000)
	, m_UserName(_T("admin"))
	, m_PassWord(_T("admin172"))
	//, m_lPlayHandle(0)
	//, m_bIsPlaying(false)
	, m_iCurChanIndex(0)
	, DeviceNum(0)
	, CurrentDeviceNum(0)
	, CurrentChannelNum(0)
	, m_PlayingWindNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_DevPort = 0;
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_DevPort);
	DDX_Text(pDX, IDC_EDIT_USER, m_UserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_PassWord);
	DDX_Control(pDX, IDC_IPADDRESS_DEV, m_DevIP);
	DDX_Control(pDX, IDC_TREE_DEV, m_ctrlTreeDev);
	//  DDX_Control(pDX, IDC_STATIC_PLAYWINDOW1, m_PlayWind1);
	//  DDX_Control(pDX, IDC_STATIC_PLAYWINDOW2, m_PlayWind2);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMonitorDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMonitorDlg::OnBnClickedButtonPlay)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEV, &CMonitorDlg::OnNMDblclkTreeDev)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CMonitorDlg::OnBnClickedButtonLogout)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, &CMonitorDlg::OnTcnSelchangeTabControl)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CMonitorDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CMonitorDlg::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMonitorDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CLOUDS_UP, &CMonitorDlg::OnBnClickedButtonCloudsUp)
END_MESSAGE_MAP()


// CMonitorDlg message handlers

BOOL CMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_DevIP.SetAddress(192,168,0,254);
	//m_PlayWnd[0] = GetDlgItem(IDC_STATIC_PLAYWINDOW1)->m_hWnd;
	//m_PlayWnd[1] = GetDlgItem(IDC_STATIC_PLAYWINDOW2)->m_hWnd;
	//m_tab.InsertItem(0,_T("视频预览"));
	//m_tab.InsertItem(1, _T("参数配置"));
	TabConfig();//
	m_ConfigWind.Init();
	//m_PreviewWind.
	//GetDlgItem(IDC_STATIC_SHOW1)->m_hWnd;
	//m_PlayWnd[0] = GetDlgItem(IDC_STATIC_SHOW1)->m_hWnd;
	//m_PlayWnd[1] = GetDlgItem(IDC_STATIC_SHOW2)->m_hWnd;
	//m_PlayWnd[0]=m_tab.GetWindow(IDD_DIALOG_VIDEOSHOW)->GetDlgItem(IDC_STATIC_SHOW1)->m_hWnd;
	//m_tab.GetWindow(IDD_DIALOG_VIDEOSHOW)->GetDlgItem(IDC_STATIC_SHOW1)->m_hWnd;
	//m_tab.get_accChild(IDD_DIALOG_VIDEOSHOW);
	for(int i=0;i<9;i++)
		m_PlayWnd[i] = m_PreviewWind.m_wndShow[i].m_hWnd;
	//m_PlayWnd[1] = m_PreviewWind.m_wndShow[1].m_hWnd;

	//CRect rect;
	
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMonitorDlg::OnBnClickedButtonLogin()
{
	// TODO: Add your control notification handler code here
	//if (!m_IsLogin)
	//{
		if (Login())
		{
			GetCompressioncfg();
			DoGetDeviceResoureCfg();  //获取设备资源信息	
			CreateDeviceTree(m_struDeviceInfo[DeviceNum].lLoginID);        //创建通道树
			CurrentDeviceNum = DeviceNum;
			DeviceNum++;
			//GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText(_T("Logout"));
			//m_IsLogin = true;

		}
		
	//}
	//else
	//{
		//hik.Logout(hik.lUserID);
		//GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText(_T("Login"));

	//}
}

/*************************************************
Function:Login
Description:设备注册
Input:
Output:         
Return:         
Others:        

*************************************************/
bool CMonitorDlg::Login()
{
	UpdateData(TRUE);


	CString DeviceIp;
	//char * ip;
	//char * user;
	//char * password;
	m_DevIP.GetWindowTextW(DeviceIp);


	for (auto i = ipstring.cbegin(); i != ipstring.cend(); i++)
	{
		int j=DeviceIp.Compare(*i);
		if (0 == j)
		{
			MessageBox(_T("设备已注册"));
			return false;
		}
			
	}
	///DeviceIp.Compare(ipstring._Get_data);

	int n, len;

	//字符串处理 CString转为char*       //ip
	 n = DeviceIp.GetLength(); //获取str的字符数    
	 len = WideCharToMultiByte(CP_ACP, 0, DeviceIp, n, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的    
	char *ip = new char[len + 1]; //以字节为单位    
	WideCharToMultiByte(CP_ACP, 0, DeviceIp, n, ip, len, NULL, NULL); //宽字节编码转换成多字节编码    
	ip[len] = '\0'; //多字节字符以'\0'结束 原文代码有错误哦  

	//字符串处理 CString转为char*     //username
	 n = m_UserName.GetLength(); //获取str的字符数    
	 len = WideCharToMultiByte(CP_ACP, 0, m_UserName, n, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的    
	char *user = new char[len + 1]; //以字节为单位    
	WideCharToMultiByte(CP_ACP, 0, m_UserName, n, user, len, NULL, NULL); //宽字节编码转换成多字节编码    
	user[len] = '\0'; //多字节字符以'\0'结束 原文代码有错误哦  

	//字符串处理 CString转为char*     //password
	n = m_PassWord.GetLength(); //获取str的字符数    
	len = WideCharToMultiByte(CP_ACP, 0, m_PassWord, n, NULL, 0, NULL, NULL); //获取宽字节字符的大小，大小是按字节计算的    
	char *password = new char[len + 1]; //以字节为单位    
	WideCharToMultiByte(CP_ACP, 0, m_PassWord, n, password, len, NULL, NULL); //宽字节编码转换成多字节编码    
	password[len] = '\0'; //多字节字符以'\0'结束 原文代码有错误哦  



	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40={ 0 };
	LONG LoginID=hik.Login(ip,m_DevPort,user, password, struDeviceInfoV40);


	if (-1==LoginID)
	{
		MessageBox(_T("Login to Device failed!"));
		CString str;
		str.Format(_T("%d", NET_DVR_GetLastError));
		MessageBox(str);
		return FALSE;
	}
	MessageBox(_T("success"));

	ipstring.push_back(DeviceIp);//

	m_struDeviceInfo[DeviceNum].lLoginID = LoginID;// lLoginID;
	m_struDeviceInfo[DeviceNum].iDeviceChanNum = struDeviceInfoV40.struDeviceV30.byChanNum;//DeviceInfoTmp.byChanNum;
	m_struDeviceInfo[DeviceNum].iIPChanNum = struDeviceInfoV40.struDeviceV30.byIPChanNum;
	m_struDeviceInfo[DeviceNum].iStartChan = struDeviceInfoV40.struDeviceV30.byStartChan;
	m_struDeviceInfo[DeviceNum].iIPStartChan = struDeviceInfoV40.struDeviceV30.byStartDChan;

	return TRUE;
}
void CMonitorDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < 9; i++)
	{
		if (CurrentDeviceNum == IDChMatchWind[i].lLoginID
			&&m_iCurChanIndex == IDChMatchWind[i].iDeviceChan)
		{
			//if (IDChMatchWind[m_PlayingWindNum].bIsPlaying)
			//{
				StopPlay(IDChMatchWind[i]);
			//}

		}
	}
	//StopPlay(CurrentDeviceNum, m_iCurChanIndex);
}

void CMonitorDlg::OnBnClickedButtonPlay()
{
	bool tempflag = true;
	for (int i = 0; i < 9; i++)
	{
		//if (!IDChMatchWind[i].iPlayWindID)
		//{

			if (CurrentDeviceNum == IDChMatchWind[i].lLoginID
				&&m_iCurChanIndex == IDChMatchWind[i].iDeviceChan
				)
			{
				tempflag = false;
				if (!IDChMatchWind[i].bIsPlaying)
					tempflag = true;
				break;
			}

				//StartPlay(CurrentDeviceNum, m_iCurChanIndex);

		//}
	}
	//for (int i = 0; i < 9; i++)
	//{
	if (tempflag)
	{
		//if (!IDChMatchWind[m_PlayingWindNum].bIsPlaying)
		//{

		//	if (CurrentDeviceNum != IDChMatchWind[m_PlayingWindNum].lLoginID
		//		&&m_iCurChanIndex != IDChMatchWind[m_PlayingWindNum].iDeviceChan
		//		)

				StartPlay(CurrentDeviceNum, m_iCurChanIndex);
		//}

	}

	//}





	//CurrentDeviceNum].lLoginID==

	//if(!m_bIsPlaying[CurrentDeviceNum])
	//	StartPlay(m_struDeviceInfo[CurrentDeviceNum].lLoginID, m_iCurChanIndex);

	//for (int i = 0; i < DeviceNum; i++)
	//{

	//	if (!m_bIsPlaying[i])  //Play
	//	{
	//		StartPlay(m_struDeviceInfo[i].lLoginID, m_struDeviceInfo[i].iIPChanNum);
	//		//StartPlay(m_struDeviceInfo[DeviceNum - 1].lLoginID, m_struDeviceInfo[DeviceNum - 1].iIPChanNum);

	//	
	//		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("停止播放"));
	//	}	
	//	else                //Stop,play
	//	{
	//		StopPlay(i); 
	//		//StartPlay();
	//		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("播放"));
	//	}
	//}

}


bool CMonitorDlg::StartPlay(int loginID,int ch)
{


	IDChMatchWind[m_PlayingWindNum].lLoginID = loginID;
	IDChMatchWind[m_PlayingWindNum].iDeviceChan = ch;
	IDChMatchWind[m_PlayingWindNum].iPlayWindID = m_PlayingWindNum;

	//NET_DVR_PREVIEWINFO ClientInfo;
	//ClientInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PLAYWINDOW1)->m_hWnd;
	///*ClientInfo.lChannel = m_iCurChanIndex + 1;*/
	//ClientInfo.lChannel = 1;
	//ClientInfo.dwLinkMode = 0;
	////ClientInfo.sMultiCastIP = NULL;

	NET_DVR_CLIENTINFO ClientInfo;
	/*ClientInfo.hPlayWnd = GetDlgItem(IDC_STATIC_PLAYWINDOW1)->m_hWnd;*/
	ClientInfo.hPlayWnd = m_PlayWnd[m_PlayingWindNum];
	ClientInfo.lChannel = ch +1;
	//ClientInfo.lChannel = index + 1;
	ClientInfo.lLinkMode = 0;
	ClientInfo.sMultiCastIP = NULL;

	TRACE("Channel number:%d\n", ClientInfo.lChannel);


	//m_lPlayHandle[CurrentDeviceNum] = NET_DVR_RealPlay_V30(loginID, &ClientInfo, NULL, NULL, TRUE);
	IDChMatchWind[m_PlayingWindNum].LPlayHandID = NET_DVR_RealPlay_V30(loginID, &ClientInfo, NULL, NULL, TRUE);


	//if (-1 == m_lPlayHandle[CurrentDeviceNum])
	if (-1 == IDChMatchWind[m_PlayingWindNum].LPlayHandID)
	{
		DWORD err = NET_DVR_GetLastError();
		CString m_csErr;
		m_csErr.Format(_T("播放出错，错误代码%d"), err);
		MessageBox(m_csErr);
		return false;
	}

	//m_bIsPlaying[CurrentDeviceNum] = TRUE;
	IDChMatchWind[m_PlayingWindNum].bIsPlaying = true;

	m_PlayingWindNum++;

	return true;
}


bool CMonitorDlg::StopPlay(int hangID)
{

	if (hangID != -1)
	{
		//if (m_bIsRecording)  //正在录像，先停止
		//{
		//	StopRecord();
		//}
		NET_DVR_StopRealPlay(hangID);
		m_lPlayHandle[CurrentDeviceNum] = -1;
		m_bIsPlaying[CurrentDeviceNum] = FALSE;
		//m_PlayWnd[index]
		
//		switch (m_PlayingWindNum)
//		{
////			case 0:GetDlgItem(IDC_STATIC_PLAYWINDOW1)->Invalidate(); break;
//			case 1:m_PreviewWind.m_wndShow->Invalidate(); break;
//			default:break;
//		}
		m_PreviewWind.m_wndShow[CurrentDeviceNum].Invalidate();
		m_PlayingWindNum--;
		//GetDlgItem(IDC_STATIC_PLAYWINDOW1)->Invalidate();
	}
	return false;
}

bool CMonitorDlg::StopPlay(ID_CH_HAND_MATCH &hd)
{

	if (hd.LPlayHandID != -1)
	{
		//if (m_bIsRecording)  //正在录像，先停止
		//{
		//	StopRecord();
		//}
		NET_DVR_StopRealPlay(hd.LPlayHandID);
		//m_lPlayHandle[CurrentDeviceNum] = -1;
		hd.LPlayHandID = -1;
		//m_bIsPlaying[CurrentDeviceNum] = FALSE;
		hd.bIsPlaying = false;


		//m_PlayWnd[index]

		//		switch (m_PlayingWindNum)
		//		{
		////			case 0:GetDlgItem(IDC_STATIC_PLAYWINDOW1)->Invalidate(); break;
		//			case 1:m_PreviewWind.m_wndShow->Invalidate(); break;
		//			default:break;
		//		}
		m_PreviewWind.m_wndShow[hd.iPlayWindID].Invalidate();
		m_PlayingWindNum--;
		//GetDlgItem(IDC_STATIC_PLAYWINDOW1)->Invalidate();
		return true;
	}
	return false;
}


void CMonitorDlg::DoGetDeviceResoureCfg()
{


	NET_DVR_IPPARACFG_V40 IpAccessCfg;
	memset(&IpAccessCfg, 0, sizeof(IpAccessCfg));
	DWORD  dwReturned;

	//m_struDeviceInfo.bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo.lLoginID, NET_DVR_GET_IPPARACFG_V40, 0, &IpAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);
	m_struDeviceInfo[DeviceNum].bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo[DeviceNum].lLoginID, NET_DVR_GET_IPPARACFG_V40, 0, &IpAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);

	int i;
	if (!m_struDeviceInfo[DeviceNum].bIPRet)   //不支持ip接入,9000以下设备不支持禁用模拟通道
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)
		{
			if (i < m_struDeviceInfo[DeviceNum].iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo[DeviceNum].iStartChan);
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = i + m_struDeviceInfo[DeviceNum].iStartChan;  //通道号
				m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = TRUE;

			}
			else
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "");
			}
		}
	}
	else        //支持IP接入，9000设备
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)  //模拟通道
		{
			if (i < m_struDeviceInfo[DeviceNum].iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo[DeviceNum].iStartChan);
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = i + m_struDeviceInfo[DeviceNum].iStartChan;
				if (IpAccessCfg.byAnalogChanEnable[i])
				{
					m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = TRUE;
				}
				else
				{
					m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = FALSE;
				}

			}
			else//clear the state of other channel
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "");
			}
		}

		//数字通道
		for (i = 0; i<MAX_IP_CHANNEL; i++)
		{
			if (IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ip通道在线
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = TRUE;
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = i + IpAccessCfg.dwStartDChan;
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName, "IP Camera %d", i + 1);

			}
			else
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = FALSE;
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}


	}
}

///
void CMonitorDlg::CreateDeviceTree(LONG loginID)
{
	CString str = _T("Dev");
	CString strnum;
	LONG a = loginID;
	strnum.Format(_T("%d"), a);
	str += strnum;
	//m_hDevItem = m_ctrlTreeDev.InsertItem(_T("Dev"));
	m_hDevItem = m_ctrlTreeDev.InsertItem(str);
	//m_ctrlTreeDev.InsertItem();
	m_ctrlTreeDev.SetItemData(m_hDevItem, DEVICETYPE * 1000);
	for (int i = 0; i<MAX_CHANNUM_V30; i++)
	{

		if (m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable)  //通道有效，插入通道树
		{

			if (i<MAX_ANALOG_CHANNUM)
			{
				CString str(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName);
				HTREEITEM ChanItem = m_ctrlTreeDev.InsertItem(str, m_hDevItem);
				m_iCurChanIndex = i;
				m_ctrlTreeDev.SetItemData(ChanItem, CHANNELTYPE * 1000 + 100 * loginID + i);   //Data对应通道在数组中的索引
			}
			else
			{
				CString str(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName);
				HTREEITEM ChanItem = m_ctrlTreeDev.InsertItem(str, m_hDevItem);
				m_iCurChanIndex = i- MAX_ANALOG_CHANNUM;
				m_ctrlTreeDev.SetItemData(ChanItem, CHANNELTYPE * 1000 + 100 * loginID + i);   //Data对应通道在数组中的索引
			}
			////LPCTSTR buffer;
			////lstrcpy(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, buffer);

			////wcstombs();
			//CString str(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName);
			//HTREEITEM ChanItem = m_ctrlTreeDev.InsertItem(str, m_hDevItem);
			//m_iCurChanIndex = i;
			//m_ctrlTreeDev.SetItemData(ChanItem, CHANNELTYPE * 1000 + 100*loginID +i);   //Data对应通道在数组中的索引
		}
	}
	m_ctrlTreeDev.Expand(m_hDevItem, TVE_EXPAND);
}


void CMonitorDlg::OnNMDblclkTreeDev(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM hSelected = m_ctrlTreeDev.GetSelectedItem();
	//未选中
	if (NULL == hSelected)
		return;
	DWORD itemData = m_ctrlTreeDev.GetItemData(hSelected);
	HTREEITEM hParent = NULL;
	int itype = itemData / 1000;    //
	
	/*int iIndex = itemData % 1000;*/
	int id = itemData / 100 % 10;

	int shiwei = itemData / 10 % 10;
	int gewei= itemData % 10;
	int iIndex = shiwei * 10 + gewei;


	if (iIndex >= MAX_ANALOG_CHANNUM)
		iIndex = iIndex - MAX_ANALOG_CHANNUM;



	switch (itype)
	{
	case DEVICETYPE:
		m_iCurChanIndex = -1;
		break;
	case CHANNELTYPE:
		m_iCurChanIndex = iIndex;
		TRACE("select chan: %d\n", iIndex);
		CurrentDeviceNum = id;
		//DbPlayChannel(m_struDeviceInfo[id].lLoginID,iIndex);
		//OnSelchangeComboPreset();
		break;
	default:
		break;

	}
	*pResult = 0;
}


void CMonitorDlg::DbPlayChannel(int LongID,int index)
{
	if (!m_bIsPlaying[LongID])  //Play
	{
		StartPlay(LongID,index);
	}
	else                //Stop,play
	{
		StopPlay(LongID);
		//StartPlay(LongID,index);

	}
}


void CMonitorDlg::OnBnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < DeviceNum; i++)
	{
		hik.Logout(m_struDeviceInfo[i].lLoginID);
		//GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText(_T("Login"));
	}
}


void CMonitorDlg::CodeMatching(NET_DVR_COMPRESSION_INFO_V30 info)
{
	BYTE     byStreamType= info.byStreamType;//码流类型  0-视频流，1-复合流
	BYTE     byResolution= info.byResolution;//分辨率  16-VGA(640*480)，3-4CIF(704*576/704*480) 19-HD720P(1280*720)，20-XVGA(1280*960)，
	BYTE     byBitrateType= info.byBitrateType;//码率类型  0-变码率，1-定码率 

	BYTE     byPicQuality= info.byPicQuality;//图像质量  0-最好，1-次好，2-较好，3-一般，4-较差，5-差
	//DWORD    dwVideoBitrate;//视频码率  0-保留，1-16K(保留)，2-32K，3-48k，4-64K，5-80K，6-96K，7-128K，8-160k，9-192K，10-224K，11-256K，12-320K，13-384K，14-448K，15-512K，16-640K，17-768K，18-896K，19-1024K，20-1280K，21-1536K，22-1792K，23-2048K，24-3072K，25-4096K，26-8192K，27-16384K，
	DWORD    dwVideoFrameRate= info.dwVideoFrameRate;//视频帧率 0-全部，1-1/16，2-1/8，3-1/4，4-1/2，5-1，6-2，7-4，8-6，9-8，10-10，11-12，12-16，13-20，14-15，15-18，16－22，17-25，18-30，19-35，20-40，21-45，22-50，23-55，24-60，25-3，26-5，27-7，28-9，29-100，30-120，31-24，32-48，
	BYTE     byFormatType= info.byFormatType;//视频编码类型 0-私有264，1-标准h264，2-标准mpeg4，7-M-JPEG，8-MPEG2，9-SVAC，10-标准h265，0xfe- 自动（和源一致），0xff-无效 
	//码流
	switch (byStreamType)
	{
	case '0':; break;
	case '1':; break;
	default:
		break;
	}

	//分辨率
	switch (byResolution)
	{
	case '3':; break;
	case '16':; break;
	case '19':; break;
	case '20':; break;
	default:
		break;
	}


	//码率类型
	switch (byBitrateType)
	{
	case '0':; break;
	case '1':; break;
	default:
		break;
	}

	//图像质量
	switch (byPicQuality)
	{
	case '0':; break;
	case '1':; break;
	case '2':; break;
	case '3':; break;
	case '4':; break;
	case '5':; break;
	default:
		break;
	}

	////视频码率
	//switch (dwVideoBitrate)
	//{
	//case '0':; break;
	//case '1':; break;
	//default:
	//	break;
	//}

	//视频帧率
	switch (dwVideoFrameRate)
	{
	case 0:; break;
	case 1:; break;
	case 2:; break;
	case 3:; break;
	case 4:; break;
	case 5:; break;
	case 6:; break;
	case 7:; break;
	case 8:; break;
	case 9:; break;
	case 10:; break;
	case 11:; break;
	case 12:; break;
	case 13:; break;
	case 14:; break;
	case 15:; break;
	case 16:; break;
	case 17:; break;
	default:
		break;
	}

	//视频编码类型
	switch (byFormatType)
	{
	case '0':; break;
	case '1':; break;
	case '2':; break;
	case '6':; break;
	case '7':; break;
	case '8':; break;
	case '9':; break;
	case '10':; break;
	default:
		break;
	}







}


void CMonitorDlg::TabCpnfig()
{
}

/*************************************************
Function:TabConfig
Description:TabControl控件初始配置
Input:
Output:
Return:
Others:
*************************************************/
void CMonitorDlg::TabConfig()
{

	m_tab.InsertItem(0, _T("视频预览"));
	m_tab.InsertItem(1, _T("参数配置"));
	m_PreviewWind.Create(IDD_DIALOG_VIDEOSHOW, GetDlgItem(IDC_TAB_CONTROL));
	m_ConfigWind.Create(IDD_DIALOG_CONFIGURATION, GetDlgItem(IDC_TAB_CONTROL));



	CRect rs;
	m_tab.GetClientRect(&rs);

	//m_PreviewWind.CreateShowWind(rs);
	//rs.Height;
	//rs.Width;
	CString str;
	rs.Height();
	str.Format(_T("%d,%d"), rs.Height(), rs.Width());
	//AfxMessageBox(str);
	
	
	rs.top += 20;
	//rs.bottom -= 10;
	//rs.left += 1;
	//rs.right -= 2;
	
		
	m_PreviewWind.MoveWindow(&rs);
	m_ConfigWind.MoveWindow(&rs);
	//m_result.MoveWindow(&rs);

	m_PreviewWind.ShowWindow(true);
	m_ConfigWind.ShowWindow(false);


	m_PreviewWind.CreateShowWind(rs);


	m_tab.SetCurSel(0);
}

/*************************************************
Function:OnTcnSelchangeTabControl
Description:TabControl控件标签页切换响应函数
Input:
Output:
Return:
Others:
*************************************************/
void CMonitorDlg::OnTcnSelchangeTabControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int CurSel = m_tab.GetCurSel();
	switch (CurSel)
	{
	case 0:m_PreviewWind.ShowWindow(true);
		m_ConfigWind.ShowWindow(false);
		break;
	case 1: m_PreviewWind.ShowWindow(false);
		m_ConfigWind.ShowWindow(true);
		break;
	default:
		break;
	}
	*pResult = 0;
}


void CMonitorDlg::OnBnClickedButtonGet()
{
	// TODO: Add your control notification handler code here
	GetCompressioncfg();


	//hik.struDeviceInfoV40.struDeviceV30.
}

/*************************************************
Function:OnTcnSelchangeTabControl
Description:TabControl控件标签页切换响应函数
Input:
Output:
Return:
Others:
*************************************************/
void CMonitorDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
	m_ConfigWind.UpdateData();


	//CString s;
	//m_ConfigWind.VideoFrameRate.GetWindowTextW(s);

	//m_ConfigWind.VideoFrameRate.GetCurSel();

	NET_DVR_COMPRESSIONCFG_V30 struParams;
	if (hik.GetCompressionParameters(m_struDeviceInfo[CurrentDeviceNum].lLoginID, 1, struParams))
	{
		
		struParams.struNormHighRecordPara.dwVideoFrameRate = m_ConfigWind.VideoFrameRate.GetCurSel();//视频帧率
		struParams.struNormHighRecordPara.byPicQuality = m_ConfigWind.PicQuality.GetCurSel();//图像质量
		struParams.struNormHighRecordPara.byStreamType = m_ConfigWind.StreamType.GetCurSel();//码流类型
		struParams.struNormHighRecordPara.dwVideoBitrate = m_ConfigWind.BitrateType.GetCurSel();//码率类型

		struParams.struNormHighRecordPara.byResolution = ResolutionCodeMatch(m_ConfigWind.Resolution.GetCurSel());//码率类型
	}
		
	if (hik.SetCompressionParameters(m_struDeviceInfo[CurrentDeviceNum].lLoginID, 1, struParams))
	{

		m_ConfigWind.UpdateConfieData(struParams.struNormHighRecordPara);
	//m_ConfigWind.UpdateData(false);
		AfxMessageBox(_T("OK"));
	}

	
}


/*************************************************
Function:ResolutionCodeMatch
Description:视频分辨率参数代码匹配
Input:int code	下拉列表对应顺序
Output:
Return:temp		视频分辨率对应代码
Others:
*************************************************/
int CMonitorDlg::ResolutionCodeMatch(int code)
{
	int temp = -1;
	switch (code)
	{
	case 0:temp = 16; break;
	case 1:temp = 3; break;
	case 2:temp = 19; break;
	case 3:temp = 20; break;
	default:
		break;
	}
	return temp;
}


void CMonitorDlg::GetCompressioncfg()
{

	//m_PreviewWind.updatec();
	NET_DVR_COMPRESSIONCFG_V30 struParams;
	//hik.GetCompressionParameters(m_struDeviceInfo[DeviceNum].lLoginID, m_struDeviceInfo[DeviceNum].struChanInfo, struParams);
	if (hik.GetCompressionParameters(m_struDeviceInfo[CurrentDeviceNum].lLoginID, 1, struParams))


		//m_ConfigWind.UpdateConfieData(struParams.struEventRecordPara.byResolution);
		m_ConfigWind.UpdateConfieData(struParams.struNormHighRecordPara);
}





void CMonitorDlg::OnBnClickedButtonCloudsUp()
{
	// TODO: Add your control notification handler code here
}
