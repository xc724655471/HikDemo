#include "stdafx.h"
#include "HIK.h"


HIK::HIK()
{


	//NET_DVR_SetSDKInitCfg(1,);
	//isLogin = false;



	// 初始化
	NET_DVR_Init();
}


HIK::~HIK()
{

	////注销用户
	//if(lUserID>0)
	//	NET_DVR_Logout(lUserID);
	//释放SDK资源
	NET_DVR_Cleanup();
}

void HIK::Init(char * ip,int port,char * username,char * password)
{

	//NET_DVR_SetConnectTime(2000, 1);
	//NET_DVR_SetReconnect(10000, true);

	//---------------------------------------
	//设置异常消息回调函数
	//NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);

	//登录参数，包括设备地址、登录用户、密码等
//	NET_DVR_USER_LOGIN_INFO struLoginInfo = { 0 };
	//struLoginInfo.bUseAsynLogin = 0; //同步登录方式
	//strcpy_s(struLoginInfo.sDeviceAddress, ip); //设备IP地址
	//struLoginInfo.wPort = port; //设备服务端口
	//strcpy_s(struLoginInfo.sUserName, username); //设备登录用户名
	//strcpy_s(struLoginInfo.sPassword, password); //设备登录密码

												 //设备信息, 输出参数
	//NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = { 0 };

	//lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	//if (lUserID < 0)
	//{
	//	printf("Login failed, error code: %d\n", NET_DVR_GetLastError());
	//	isLogin = false;
	//	//NET_DVR_Cleanup();
	//	//return;
	//}
	//else
	//{
	//	isLogin = true;
	//}
	//return lUserID;





}

bool HIK::Logout(LONG ID)
{
	bool i=NET_DVR_Logout(ID);
	if (i)
		return true;
	return false;
}


/*************************************************
Function:Login
Description:设备注册
Input:  char * ip           设备IP
		int port            设备端口
		char * username     用户名
		char * password     密码
Output:
Return:注册设备iD号
Others:
*************************************************/
LONG HIK::Login(char * ip, int port, char * username, char * password, NET_DVR_DEVICEINFO_V40 &struDeviceInfoV40)
{

	NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
	strcpy_s(struLoginInfo.sDeviceAddress, ip); //设备IP地址
	struLoginInfo.wPort = port; //设备服务端口
	strcpy_s(struLoginInfo.sUserName, username); //设备登录用户名
	strcpy_s(struLoginInfo.sPassword, password); //设备登录密码

												 //设备信息, 输出参数
	//NET_DVR_DEVICEINFO_V40 struDeviceInfoV400 = { 0 };

	LONG lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
	if (lUserID < 0)
	{
		printf("Login failed, error code: %d\n", NET_DVR_GetLastError());
		//isLogin = false;
		return -1;
		//NET_DVR_Cleanup();
		//return;
	}
	else
	{
		//isLogin = true;
	}
	//return lUserID;
	return lUserID;
}

//bool HIK::GetCompressionParameters()
//{
//
//
//
//	return true;
//}

bool HIK::GetBasicParameters()
{


	return false;
}

bool HIK::EndPreview()
{
	////关闭预览
	//NET_DVR_StopRealPlay(lRealPlayHandle);

	return false;
}


/*************************************************
Function:    GetDVRConfig
Description: 获取设备的配置信息
Input:       LONG lUserID,              注册ID
			 DWORD dwCommand,			设备配置命令
			 LONG lChannel,				通道号
			 LPVOID lpOutBuffer,		接收数据缓冲指针
			 DWORD dwOutBufferSize		接收数据缓冲长度（以字节为单位），不能为0
Output:
Return:		 true 获取成功
			 false 获取失败
Others:
*************************************************/
bool HIK::GetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize)
{
	int iRet;
	DWORD dwReturnLen;
	iRet = NET_DVR_GetDVRConfig(lUserID, dwCommand, lChannel, lpOutBuffer, dwOutBufferSize, &dwReturnLen);
	if (iRet)
		return true;
	return false;
}

/*************************************************
Function:    SetDVRConfig
Description: 设置设备的配置信息
Input:       LONG lUserID,              注册ID
			 DWORD dwCommand,			设备配置命令
			 LONG lChannel,				通道号
			 LPVOID lpInBuffer,			输入数据缓冲指针
			 DWORD dwInBufferSize		输入数据缓冲长度（以字节为单位）
Output:
Return:		 true 设置成功
			 false 设置失败
Others:
*************************************************/
bool HIK::SetDVRConfig(LONG lUserID,DWORD dwCommand, LONG lChannel, LPVOID lpInBuffer, DWORD dwInBufferSize)
{
	int iRet;
	//DWORD dwReturnLen;
	iRet = NET_DVR_SetDVRConfig(lUserID, dwCommand, lChannel, lpInBuffer, dwInBufferSize);
	int error = NET_DVR_GetLastError();
	if (iRet)
		return true;
	return false;
}

bool HIK::GetDeviceConfig(LONG lUserID, DWORD dwCommand, DWORD dwCount, LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpStatusList, LPVOID lpOutBuffer, DWORD dwOutBufferSize)
{
	int iRet;
	//DWORD dwReturnLen=0;
	iRet = NET_DVR_GetDeviceConfig(lUserID, dwCommand, dwCount, lpInBuffer, dwInBufferSize, lpStatusList, lpOutBuffer, dwOutBufferSize);
	if (iRet)
		return true;
	return false;
	return false;
}

bool HIK::SetDeviceConfig(LONG lUserID, DWORD dwCommand, DWORD dwCount, LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpStatusList, LPVOID lpOutBuffer)
{
	return false;
}

bool HIK::GetSTDConfig(LONG lUserID, DWORD dwCommand, LPNET_DVR_STD_CONFIG lpConfigParam)
{
	return false;
}

bool HIK::SetSTDConfig(LONG lUserID, DWORD dwCommand, LPNET_DVR_STD_CONFIG lpConfigParam)
{
	return false;
}

bool HIK::STDXMLConfig(LONG lUserID, NET_DVR_XML_CONFIG_INPUT * lpInputParam, NET_DVR_XML_CONFIG_OUTPUT * lpOutputParam)
{
	return false;
}

bool HIK::RemoteControl(LONG lUserID, DWORD dwCommand, LPVOID lpInBuffer, DWORD dwInBufferSize)
{
	return false;
}


/*************************************************
Function:    GetDeviceParameters
Description: 获取设备参数(扩展)
Input:       LONG lUserID,              注册ID
			 LONG lChannel,				通道号
Output:
Return:		 true 获取成功
			 false 获取失败
Others:
*************************************************/
bool HIK::GetDeviceParameters(LONG lUserID,LONG lChannel,NET_DVR_DEVICECFG_V40 &struParams)
{
	if (lUserID < 0)
	{
		return false;
	}
	bool iRet = false;
	////获取设备参数(扩展)
	//NET_DVR_DEVICECFG_V40 struParams = { 0 };
	iRet = GetDVRConfig(lUserID,NET_DVR_GET_DEVICECFG_V40, lChannel,&struParams, sizeof(NET_DVR_DEVICECFG_V40));
	if (iRet)
	{
		//cout << struParams.byChanNum << endl;
		return true;
	}
	cout<<"NET_DVR_GetDVRConfig NET_DVR_DEVICECFG_V40 error"<<endl;
	return false;
}

bool HIK::GetImageParameters(LONG lUserID,LONG lChannel, NET_DVR_PICCFG_V40 &struParams)
{
	if (lUserID < 0)
	{
		return false;
	}
	bool iRet=false;
	////获取图像参数
	//NET_DVR_PICCFG_V40 struParams = { 0 };
	iRet = GetDVRConfig(lUserID,NET_DVR_GET_PICCFG_V40, lChannel, &struParams, sizeof(NET_DVR_PICCFG_V40));
	if (iRet)
	{
		//cout << struParams.byChanNum << endl;
		cout << "success" << endl;
		return true;
	}
	cout << "NET_DVR_GetDVRConfig NET_DVR_PICCFG_V40 error" << endl;
	return false;
}

bool HIK::GetCompressionParameters(LONG lUserID,LONG lChannel, NET_DVR_COMPRESSIONCFG_V30 &struParams)
{
	if (lUserID < 0)
	{
		return false;
	}
	bool iRet = false;
	//获取压缩参数
	//NET_DVR_COMPRESSIONCFG_V30 struParams = { 0 };
	iRet = GetDVRConfig(lUserID,NET_DVR_GET_COMPRESSCFG_V30, lChannel, &struParams, sizeof(NET_DVR_COMPRESSIONCFG_V30));
	if (iRet)
	{
		//cout << struParams.byChanNum << endl;
		cout << "success" << endl;
		return true;
	}
	cout << "NET_DVR_GetDVRConfig NET_DVR_GET_COMPRESSCFG_V30 error" << endl;
	return false;
}


/*************************************************
Function:   SetCompressionParameters
Description:通道参数配置-获取压缩参数
Input:      LONG lUserID,									注册ID
			LONG lChannel,									通道号
			NET_DVR_COMPRESSIONCFG_V30 & struParams			通道压缩参数结构体
Output:
Return:		true 设置成功
			false 设置失败
Others:
*************************************************/
bool HIK::SetCompressionParameters(LONG lUserID, LONG lChannel,  NET_DVR_COMPRESSIONCFG_V30 & struParams)
{

	if (lUserID<0)//判断ID号是否有效
	{
		return false;
	}
	bool iRet = false;
	iRet = SetDVRConfig(lUserID, NET_DVR_SET_COMPRESSCFG_V30, lChannel, &struParams, sizeof(NET_DVR_COMPRESSIONCFG_V30));
	if (iRet)
	{
		//cout << struParams.byChanNum << endl;
		//cout << "success" << endl;
		return true;
	}
	cout << "NET_DVR_GetDVRConfig NET_DVR_SET_COMPRESSCFG_V30 error" << endl;
	return false;
}
///
bool HIK::GetRecordingPlanParameters(LONG lUserID,LONG lChannel)
{
	if (lUserID<0)
	{
		return false;
	}
	bool iRet = false;
	//获取录像计划参数
	NET_DVR_RECORD_V40 struParams = { 0 };
	iRet = GetDVRConfig(lUserID,NET_DVR_GET_RECORDCFG_V40, lChannel, &struParams, sizeof(NET_DVR_RECORD_V40));
	if (iRet)
	{
		//cout << struParams.byChanNum << endl;
		cout << "success" << endl;
		return true;
	}
	cout << "NET_DVR_GetDVRConfig NET_DVR_GET_RECORDCFG_V40 error" << endl;
	return false;
}

bool HIK::GetNetworkParameters(LONG lUserID)//ceshi
{
	//if (!isLogin)
	//{
	//	return false;
	//}
	//bool iRet = false;
	////获取网络参数
	//NET_DVR_IPPARACFG_V40 struParams = { 0 };
	//iRet = GetDVRConfig(NET_DVR_GET_IPPARACFG_V40, 0, &struParams, sizeof(NET_DVR_IPPARACFG_V40));
	//if (iRet)
	//{
	//	//cout << struParams.byChanNum << endl;
	//	cout << "success" << endl;
	//	return true;
	//}
	//cout << "NET_DVR_GetDVRConfig NET_DVR_GET_IPPARACFG_V40 error" << NET_DVR_GetLastError() << endl;
	//return false;
	return false;
}

bool HIK::GetHTTPSInformation(LONG lUserID)
{
	if (lUserID<0)
	{
		return false;
	}
	bool iRet = false;
	//获取HTTP信息
	NET_DVR_HTTPS_CFG struParams = { 0 };
	iRet = GetDVRConfig(lUserID,NET_DVR_GET_HTTPS_CFG, 0, &struParams, sizeof(NET_DVR_HTTPS_CFG));
	if (iRet)
	{
		//cout << struParams.byChanNum << endl;
		cout << "success" << endl;
		return true;
	}
	cout << "NET_DVR_GetDVRConfig NET_DVR_GET_HTTPS_CFG error" << endl;
	return false;
	return false;
	return false;
}

bool HIK::GetIPAccessConfigurationParameters(LONG lUserID)
{
	return false;
}

bool HIK::TestFunctiong(LONG lUserID,DWORD dwCommand)
{
		if (lUserID<0)
		{
			return false;
		}
		bool iRet = false;

		//NET_DVR_VIDEO_INPUT_EFFECT struParams = { 0 };

		//NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND * lpInBuffer = new NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND[dwCommand];
		//UINT32 * lpStatusList=new UINT32[dwCommand];
		//NET_DVR_MULTI_STREAM_COMPRESSIONCFG *lpOutBuffer = new NET_DVR_MULTI_STREAM_COMPRESSIONCFG[dwCommand];


		NET_DVR_STREAM_INFO  lpInBuffer;
		UINT32  lpStatusList; 
		NET_DVR_RECORD_PASSBACK_SCH_CFG lpOutBuffer;

		iRet = GetDeviceConfig(lUserID,NET_DVR_GET_RECORD_PASSBACK_PLAN_CFG, dwCommand, &lpInBuffer, sizeof(NET_DVR_STREAM_INFO), &lpStatusList,&lpOutBuffer, sizeof(NET_DVR_RECORD_PASSBACK_SCH_CFG));
		if (iRet)
		{
			//cout << struParams.byChanNum << endl;
			cout << "success" << endl;
			//delete [] lpInBuffer;
			//delete [] lpStatusList;
			//delete [] lpOutBuffer;
			return true;
		}
		cout << "NET_DVR_GetDVRConfig NET_DVR_GET_VIDEO_INPUT_EFFECT error:" << NET_DVR_GetLastError ()<< endl;
		//delete [] lpInBuffer;
		//delete [] lpStatusList;
		//delete [] lpOutBuffer;
		return false;
}

bool HIK::PTZControl(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop)
{


	bool i = NET_DVR_PTZControl(lRealHandle, dwPTZCommand, dwStop);
	if (i)
		return true;

	return false;
}

bool HIK::TiltUp(LONG lRealHandle, DWORD dwStop)
{
	if (lRealHandle < 0)
		return false;
	bool iRet = false;
	iRet = PTZControl(lRealHandle, TILT_UP, dwStop);
	if (iRet)
		return true;
	return false;
}

bool HIK::TiltDown(LONG lRealHandle, DWORD dwStop)
{
	if (lRealHandle < 0)
		return false;
	bool iRet = false;
	iRet = PTZControl(lRealHandle, TILT_DOWN, dwStop);
	if (iRet)
		return true;
	return false;
}

bool HIK::PanLeft(LONG lRealHandle, DWORD dwStop)
{
	if (lRealHandle < 0)
		return false;
	bool iRet = false;
	iRet = PTZControl(lRealHandle, PAN_LEFT, dwStop);
	if (iRet)
		return true;
	return false;
}

bool HIK::PanRight(LONG lRealHandle, DWORD dwStop)
{
	if (lRealHandle < 0)
		return false;
	bool iRet = false;
	iRet = PTZControl(lRealHandle, PAN_RIGHT, dwStop);
	if (iRet)
		return true;
	return false;
}

//bool HIK::GetVideoInputImageParameters(LONG lChannel)
//{
//	if (!isLogin)
//	{
//		return false;
//	}
//	bool iRet = false;
//	//获取通道视频输入图像参数
//	NET_DVR_VIDEO_INPUT_EFFECT struParams = { 0 };
//	iRet = GetDVRConfig(NET_DVR_GET_VIDEO_INPUT_EFFECT, lChannel, &struParams, sizeof(NET_DVR_VIDEO_INPUT_EFFECT));
//	if (iRet)
//	{
//		//cout << struParams.byChanNum << endl;
//		cout << "success" << endl;
//		return true;
//	}
//	cout << "NET_DVR_GetDVRConfig NET_DVR_GET_VIDEO_INPUT_EFFECT error:" << NET_DVR_GetLastError ()<< endl;
//	return false;
//}

bool HIK::StartPreview()
{
	////启动预览并设置回调数据流
	////LONG lRealPlayHandle;
	////HWND hWnd = GetConsoleWindowAPI();     //获取窗口句柄
	//NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
	////struPlayInfo.hPlayWnd = hWnd;         //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
	//struPlayInfo.lChannel = 1;       //预览通道号
	//struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
	//struPlayInfo.dwLinkMode = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
	//struPlayInfo.bBlocked = 1;       //0- 非阻塞取流，1- 阻塞取流

	//lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, NULL, NULL);
	//if (lRealPlayHandle < 0)
	//{
	//	printf("NET_DVR_RealPlay_V40 error\n");
	//	NET_DVR_Logout(lUserID);
	//	NET_DVR_Cleanup();
	//	return false;
	//}

	//Sleep(10000);
	return false;
}
