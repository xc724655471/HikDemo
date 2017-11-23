// ConfigWind.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "ConfigWind.h"
#include "afxdialogex.h"


// ConfigWind dialog

IMPLEMENT_DYNAMIC(ConfigWind, CDialogEx)

ConfigWind::ConfigWind(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CONFIGURATION, pParent)
{
	//Init();
}

ConfigWind::~ConfigWind()
{
}

void ConfigWind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST_BIRATETYPE, BirateType);
	//  DDX_Control(pDX, IDC_LIST_PICQUALITY, PicQuality);
	//  DDX_Control(pDX, IDC_LIST_STREAMTYPE, StreamType);
	//  DDX_Control(pDX, IDC_LIST_VIDEOFRAMERATE, VideoFrameRate);
	//  DDX_Control(pDX, IDC_LIST2_RESOULTION, Resolution);
	DDX_Control(pDX, IDC_COMBO_STREAMTYPE, StreamType);
	DDX_Control(pDX, IDC_COMBO_BIRATETYPE, BitrateType);
	DDX_Control(pDX, IDC_COMBO_PICQUALITY, PicQuality);
	DDX_Control(pDX, IDC_COMBO_RESOULTION, Resolution);
	DDX_Control(pDX, IDC_COMBO_VIDEOFRAMERATE, VideoFrameRate);
}


BEGIN_MESSAGE_MAP(ConfigWind, CDialogEx)
END_MESSAGE_MAP()


// ConfigWind message handlers


void ConfigWind::Init()
{
	BitrateType.InsertString(0,_T("变码率"));//0
	BitrateType.InsertString(1, _T("定码率"));//1
	BitrateType.SetCurSel(-1);

	PicQuality.InsertString(0, _T("最好"));//0
	PicQuality.InsertString(1, _T("次好"));//1
	PicQuality.InsertString(2, _T("较好"));//2
	PicQuality.InsertString(3, _T("一般"));//3
	PicQuality.InsertString(4, _T("较差"));//4
	PicQuality.InsertString(5, _T("差"));//5
	PicQuality.SetCurSel(-1);

	StreamType.InsertString(0, _T("视频流"));//0
	StreamType.InsertString(1, _T("混合流"));//1
	StreamType.SetCurSel(-1);


	VideoFrameRate.InsertString(0, _T("全部"));//0  0
	VideoFrameRate.InsertString(1, _T("1/16"));//1  1
	VideoFrameRate.InsertString(2, _T("1/8"));//2  2
	VideoFrameRate.InsertString(3, _T("1/4"));//3  3
	VideoFrameRate.InsertString(4, _T("1/2"));//4  4
	VideoFrameRate.InsertString(5, _T("1"));//5  5
	VideoFrameRate.InsertString(6, _T("2"));//6  6
	VideoFrameRate.InsertString(7, _T("4"));//7 7
	VideoFrameRate.InsertString(8, _T("6"));//8  8
	VideoFrameRate.InsertString(9, _T("8"));//9  9
	VideoFrameRate.InsertString(10, _T("10"));//10  10 
	VideoFrameRate.InsertString(11, _T("12"));//11  11
	VideoFrameRate.InsertString(12, _T("16"));//12  12 
	VideoFrameRate.InsertString(13, _T("20"));//13  13
	VideoFrameRate.InsertString(14, _T("15"));//13  13
	VideoFrameRate.InsertString(15, _T("18"));//13  13
	VideoFrameRate.InsertString(16, _T("22"));//16  14
	//VideoFrameRate.InsertString(17);//13  13
	//VideoFrameRate.str
	VideoFrameRate.SetCurSel(-1);

	
	//Resolution.InsertString(0, _T("DCIF(528*384"));//3   1

	Resolution.InsertString(-1, _T("VGA(640*480)"));//16   0
	Resolution.InsertString(-1, _T("4CIF(704*576)"));//3   1
	Resolution.InsertString(-1, _T("HD720P(1280*720)"));//19   2
	Resolution.InsertString(-1, _T("XVGA(1280*960)"));//20   3
	Resolution.SetCurSel(-1);
	//Resolution





}


//void ConfigWind::UpdateData(BYTE byResolution)
//{
//	//switch (byResolution)
//	//{
//	//case '19':Resolution.SetCurSel(2); break;
//	//default:
//	//	break;
//	//}
//	////UpdateData(false);
//	//UpdateWindow();
//
//}


void ConfigWind::UpdateConfieData(NET_DVR_COMPRESSION_INFO_V30 struNormHighRecordPara)
{
	//NET_DVR_COMPRESSION_INFO_V30 struNormHighRecordPara;    //录像 对应8000的普通
	//码率设置

	//char ch1 = struNormHighRecordPara.byBitrateType;
	//int ch = ch1;
	//switch (struNormHighRecordPara.byBitrateType)

	//码流类型设置
	switch (int(struNormHighRecordPara.byStreamType))
	{
	case 0:StreamType.SetCurSel(0); break;
	case 1:StreamType.SetCurSel(1); break;
	default:
		break;
	}

	//分辨率设置
	switch (int(struNormHighRecordPara.byResolution))
	{
	case 16:Resolution.SetCurSel(0); break;
	case 3:Resolution.SetCurSel(1); break;
	case 19:Resolution.SetCurSel(2); break;
	case 20:Resolution.SetCurSel(3); break;
	default:
		break;
	}
		//码率类型设置
	switch (int(struNormHighRecordPara.byBitrateType))
	{
	case 0:BitrateType.SetCurSel(0); break;
	case 1:BitrateType.SetCurSel(1); break;
	default:
		break;
	}

	//图像质量设置
	switch (int(struNormHighRecordPara.byPicQuality))
	{
	case 0:PicQuality.SetCurSel(0); break;
	case 1:PicQuality.SetCurSel(1); break;
	case 2:PicQuality.SetCurSel(2); break;
	case 3:PicQuality.SetCurSel(3); break;
	case 4:PicQuality.SetCurSel(4); break;
	case 5:PicQuality.SetCurSel(5); break;
	default:
		break;
	}





	//视频帧率设置
	switch (struNormHighRecordPara.dwVideoFrameRate)
	{
	case 0:VideoFrameRate.SetCurSel(0); break;
	case 1:VideoFrameRate.SetCurSel(1); break;
	case 2:VideoFrameRate.SetCurSel(2); break;
	case 3:VideoFrameRate.SetCurSel(3); break;
	case 4:VideoFrameRate.SetCurSel(4); break;
	case 5:VideoFrameRate.SetCurSel(5); break;
	case 6:VideoFrameRate.SetCurSel(6); break;
	case 7:VideoFrameRate.SetCurSel(7); break;
	case 8:VideoFrameRate.SetCurSel(8); break; 
	case 9:VideoFrameRate.SetCurSel(9); break;
	case 10:VideoFrameRate.SetCurSel(10); break;
	case 11:VideoFrameRate.SetCurSel(11); break;
	case 12:VideoFrameRate.SetCurSel(12); break;
	case 13:VideoFrameRate.SetCurSel(13); break;
	//case 6:VideoFrameRate.SetCurSel(13); break;
	case 16:VideoFrameRate.SetCurSel(16); break;
	default:
		break;
	}
	UpdateData(false);
	//UpdateWindow();
}
