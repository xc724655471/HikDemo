#pragma once
#include"head.h"
#include"GeneralDef.h"
//#include"hik\HCNetSDK.h"
#include"time.h"
using namespace std;


//typedef HWND(WINAPI *PROCGETCONSOLEWINDOW)();
//PROCGETCONSOLEWINDOW GetConsoleWindowAPI;

//HCNetSDK.lib
//PlayCtrl.lib


#pragma  comment(lib, "HCNetSDK.lib")
#pragma  comment(lib, "PlayCtrl.lib")

//void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
//{
//	char tempbuf[256] = { 0 };
//	switch (dwType)
//	{
//	case EXCEPTION_RECONNECT:    //预览时重连
//		printf("----------reconnect--------%d\n", time(NULL));
//		break;
//	default:
//		break;
//	}
//}


class HIK
{
public:
	HIK();
	~HIK();
	void Init(char * ip, int port, char * username, char * password);
	bool Logout(LONG ID);
	LONG Login(char * ip, int port, char * username, char * password, NET_DVR_DEVICEINFO_V40 &struDeviceInfoV40);
	//bool GetCompressionParameters();
	bool GetBasicParameters();
	bool StartPreview();
	bool EndPreview();
	/*参数配置*/
	bool GetDVRConfig(LONG lUserID,DWORD dwCommand,LONG lChannel,LPVOID lpOutBuffer,DWORD dwOutBufferSize);
	bool SetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize);
	bool GetDeviceConfig(LONG lUserID, DWORD dwCommand,DWORD dwCount,LPVOID lpInBuffer,DWORD dwInBufferSize,LPVOID lpStatusList,LPVOID lpOutBuffer, DWORD dwOutBufferSize);
	bool SetDeviceConfig(LONG lUserID, DWORD dwCommand, DWORD dwCount, LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpStatusList, LPVOID lpOutBuffer);
	bool GetSTDConfig(LONG lUserID, DWORD dwCommand,LPNET_DVR_STD_CONFIG lpConfigParam);
	bool SetSTDConfig(LONG lUserID, DWORD dwCommand, LPNET_DVR_STD_CONFIG lpConfigParam);
	bool STDXMLConfig(LONG lUserID, NET_DVR_XML_CONFIG_INPUT     *lpInputParam,NET_DVR_XML_CONFIG_OUTPUT    *lpOutputParam);
	bool RemoteControl(LONG lUserID, DWORD dwCommand,LPVOID    lpInBuffer,DWORD     dwInBufferSize);
	/*GetDVRConfig*/
	bool GetDeviceParameters(LONG lUserID, LONG lChannel, NET_DVR_DEVICECFG_V40&struParams);//设备参数(扩展)
	bool GetImageParameters(LONG lUserID, LONG lChannel, NET_DVR_PICCFG_V40 &struParams);//图像参数
	bool GetCompressionParameters(LONG lUserID, LONG lChannel, NET_DVR_COMPRESSIONCFG_V30 &struParams);//压缩参数
	bool SetCompressionParameters(LONG lUserID, LONG lChannel,  NET_DVR_COMPRESSIONCFG_V30 &struParams);//设置压缩参数
	bool GetRecordingPlanParameters(LONG lUserID, LONG lChannel);//录像计划参数
	//bool GetVideoInputImageParameters(LONG lChannel); //通道视频输入图像参数(设备不支持)
	bool GetNetworkParameters(LONG lUserID);//设备网络参数(设备不支持)
	bool GetHTTPSInformation(LONG lUserID);//HTTP信息
	bool GetIPAccessConfigurationParameters(LONG lUserID);//接入IP配置参数(设备不支持)
	bool TestFunctiong(LONG lUserID,DWORD dwCommand);//测试用
	/*GetDeviceConfig*/


	/*云台控制*/
	bool PTZControl(LONG     lRealHandle,DWORD    dwPTZCommand,DWORD    dwStop);
	bool TiltUp(LONG     lRealHandle, DWORD    dwStop);//上
	bool TiltDown(LONG     lRealHandle, DWORD    dwStop);//下
	bool PanLeft(LONG     lRealHandle, DWORD    dwStop);//左
	bool PanRight(LONG     lRealHandle, DWORD    dwStop);//右

public:
	//LONG lUserID;
	//bool isLogin;
	
	
	//NET_DVR_USER_LOGIN_INFO struLoginInfo;
	
	
	//NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;
	//vector<NET_DVR_COMPRESSIONCFG_V30> strCompressioncfg_V30//;
	//NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;//网络参数配置结构体
	//NET_DVR_DEVICECFG m_struDeviceCfg;//设备参数配置结构体
	//NET_DVR_GET_TIMECFG test;
	//NET_DVR_GET_DEVICECFG_V40 t;
	//LONG lRealPlayHandle;


	//LOCAL_DEVICE_INFO struDeviceInfo;
};

