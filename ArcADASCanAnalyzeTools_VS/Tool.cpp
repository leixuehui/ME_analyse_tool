#include "Tool.h"
#include "Json/json.h"

#include <strmif.h>
#include <initguid.h>
#include <fstream>
#include <QDateTime>

#pragma comment(lib, "setupapi.lib")

#define VI_MAX_CAMERAS 20
DEFINE_GUID(CLSID_SystemDeviceEnum, 0x62be5d10, 0x60eb, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(CLSID_VideoInputDeviceCategory, 0x860bb310, 0x5d01, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(IID_ICreateDevEnum, 0x29840822, 0x5b84, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);

std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)(str.length()), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}

std::string GBKToUTF8(const std::string& strGBK)
{
	std::string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	
	delete[]str1;
	str1 = NULL;
	
	delete[]str2;
	str2 = NULL;
	
	return strOutUTF8;
}

//列出摄像头
int listDevices(std::vector<std::string>& list)
{
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	int deviceCounter = 0;
	CoInitialize(NULL);

	HRESULT hr = CoCreateInstance(
		CLSID_SystemDeviceEnum,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum,
		reinterpret_cast<void**>(&pDevEnum)
	);

	if (SUCCEEDED(hr))
	{
		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
		if (hr == S_OK) {

			IMoniker *pMoniker = NULL;
			while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
			{
				IPropertyBag *pPropBag;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
					(void**)(&pPropBag));

				if (FAILED(hr)) {
					pMoniker->Release();
					continue; // Skip this one, maybe the next one will work.
				}

				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"Description", &varName, 0);
				if (FAILED(hr))
				{
					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				}

				if (SUCCEEDED(hr))
				{
					hr = pPropBag->Read(L"FriendlyName", &varName, 0);
					int count = 0;
					char tmp[255] = { 0 };
					while (varName.bstrVal[count] != 0x00 && count < 255)
					{
						tmp[count] = (char)varName.bstrVal[count];
						count++;
					}
					list.push_back(tmp);
				}

				pPropBag->Release();
				pPropBag = NULL;
				pMoniker->Release();
				pMoniker = NULL;

				deviceCounter++;
			}

			pDevEnum->Release();
			pDevEnum = NULL;
			pEnum->Release();
			pEnum = NULL;
		}
	}
	return deviceCounter;
}

QImage cvMatToQImage(const cv::Mat & mat)
{
	if (mat.type() == CV_8UC1) 
	{
		// 8-bits unsigned, NO. OF CHANNELS = 1  
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)  
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
			image.setColor(i, qRgb(i, i, i));

		// Copy input Mat  
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++) 
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}

		return image;
	}
	else if (mat.type() == CV_8UC3) 
	{
		// 8-bits unsigned, NO. OF CHANNELS = 3  
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		//qDebug() << "CV_8UC4";
		// Copy input Mat  
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat  
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		
		return image.copy();
	}
	else 
	{
		//qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

bool writeToLocal(const QString & filePath, const ME_DeviceData & data)
{
	Json::Value root;
	Json::Value root_frame;

	Json::Value generalInfo;
	std::string str_time_indicator = "";
	std::string str_obstacle_Type = "";

	
	switch (data.generalInfo.time_indicator)
	{
	case 0:
		str_time_indicator = "Day";
		break;
	case 1:
		str_time_indicator = "Dusk";
		break;
	case 2:
		str_time_indicator = "Night";
		break;
	default:
		break;
	}
	generalInfo["time_indicator"] = Json::Value(str_time_indicator);
	generalInfo["headway_valid"] = Json::Value(data.generalInfo.headway_valid);
	generalInfo["headway_mesurement"] = Json::Value(data.generalInfo.headway_mesurement);
	generalInfo["FCW_on"] = Json::Value(data.generalInfo.FCW_on);
	generalInfo["FailSafe"] = Json::Value(data.generalInfo.failSafe);
	generalInfo["Tamper_Alert"] = Json::Value(data.generalInfo.Tamper_Alert);
	std::string str_PCW_PedDZ = "";
	switch (data.generalInfo.PCW_PedDZ)
	{
	case 2:
		str_PCW_PedDZ = "人在危险区域";
		break;
	case 3:
		str_PCW_PedDZ = "碰撞预警";
		break;
	default:
		break;
	}
	generalInfo["PCW_PedDZ"] = Json::Value(str_PCW_PedDZ);

	std::string str_TSR_warning_level = "";
	switch (data.generalInfo.TSR_warning_level)
	{
	case 0:
		str_TSR_warning_level = "speed vehicle <= road speed + 10";
		break;
	case 1:
		str_TSR_warning_level = "speed vehicle > road at speed";
		break;
	case 2:
		str_TSR_warning_level = "speed vehicle > road speed + 5";
		break;
	case 3:
		str_TSR_warning_level = "speed vehicle > road speed + 10";
		break;
	case 4:
		str_TSR_warning_level = "speed vehicle > road speed + 15";
		break;
	case 5:
		str_TSR_warning_level = "speed vehicle > road speed + 20";
		break;
	case 6:
		str_TSR_warning_level = "speed vehicle > road speed + 25";
		break;
	case 7:
		str_TSR_warning_level = "speed vehicle > road speed + 30";
		break;
	default:
		break;
	}
	generalInfo["TSR_warning_level"] = Json::Value(str_TSR_warning_level);

	std::string str_HW_warning_level = "";
	switch (data.generalInfo.TSR_warning_level)
	{
	case 0:
		str_HW_warning_level = "No CIPV in Frame";
		break;
	case 1:
		str_HW_warning_level = "CIPV > HW configuration";
		break;
	case 2:
		str_HW_warning_level = "CIPV <= HW configuration";
		break;
	default:
		break;
	}
	generalInfo["HW_warning_level"] = Json::Value(str_HW_warning_level);

	generalInfo["numberOfObstacles"] = Json::Value(data.obstacleStatus.numberOfObstacles);
	generalInfo["LeftCloseRangCutIn"] = Json::Value(data.obstacleStatus.LeftCloseRangCutIn);
	generalInfo["RightCloseRangCutIn"] = Json::Value(data.obstacleStatus.RightCloseRangCutIn);
	generalInfo["closeCar"] = Json::Value(data.obstacleStatus.closeCar);
	
	std::string str_Fail_safe = "";
	switch (data.obstacleStatus.failSafe)
	{
	case 0:
		str_Fail_safe = "No Failsafe";
		break;
	case 1:
		str_Fail_safe = "Low Sun";
		break;
	case 2:
		str_Fail_safe = "Blur Image";
		break;
	default:
		break;
	}
	generalInfo["Fail_safe"] = Json::Value(str_Fail_safe);
	generalInfo["selfSpeed"] = Json::Value(data.selfSpeed);


	root["info"] = generalInfo;

	for (int i = 0; i < 4; i++)
	{
		Json::Value obj;
		auto iter_A = data.mapObstacleDataA.find(i);
		if (iter_A != data.mapObstacleDataA.end())
		{
			obj["obstacleID"] = Json::Value(iter_A.value().obstacleID);
			obj["obstaclePosition"].append(Json::Value(iter_A.value().obstaclePosition.position_x));
			obj["obstaclePosition"].append(Json::Value(iter_A.value().obstaclePosition.position_y));
			obj["blinkerInfo"] = Json::Value(iter_A.value().blinkerInfo);

			std::string str_cutInAndOut;
			switch (iter_A.value().cutInAndOut)
			{
			case 1:
				str_cutInAndOut = "in_host_lane";
				break;
			case 2:
				str_cutInAndOut = "out_host_lane";
				break;
			case 3:
				str_cutInAndOut = "cut_in";
				break;
			case 4:
				str_cutInAndOut = "cut_out";
				break;
			default:
				break;
			}
			obj["cutInAndOut"] = Json::Value(str_cutInAndOut);
			switch (iter_A.value().obstacle_Type)
			{
			case 0:
				str_obstacle_Type = "Vehicle";
				break;
			case 1:
				str_obstacle_Type = "Truck";
				break;
			case 2:
				str_obstacle_Type = "Bike";
				break;
			case 3:
				str_obstacle_Type = "Ped";
				break;
			case 4:
				str_obstacle_Type = "Bicycle";
				break;
			case 5:
				str_obstacle_Type = "Unused";
				break;
			default:
				break;
			}
			obj["obstacle_Type"] = Json::Value(str_obstacle_Type);
			obj["obstacleRelvel_X"] = Json::Value(iter_A.value().obstacleRelvel_X);
			std::string str_obstacleStatus;
			switch (iter_A.value().obstacleStatus)
			{
			case 1:
				str_obstacleStatus = "Standing";
				break;
			case 2:
				str_obstacleStatus = "Stopped";
				break;
			case 3:
				str_obstacleStatus = "Moving";
				break;
			case 4:
				str_obstacleStatus = "Oncoming";
				break;
			case 5:
				str_obstacleStatus = "Parked";
				break;
			default:
				break;
			}
			obj["obstacleStatus"] = Json::Value(str_obstacleStatus);
			obj["obstacleBrakeLights"] = Json::Value(iter_A.value().obstacleBrakeLights);
		}



		auto iter_B = data.mapObstacleDataB.find(i);
		if (iter_B != data.mapObstacleDataB.end())
		{
			obj["obstacleLength"] = Json::Value(iter_B.value().obstacleLength);
			obj["obstacleWidth"] = Json::Value(iter_B.value().obstacleWidth);
			std::string str_obstacleLane = "";
			switch (iter_B.value().obstacleLane)
			{
			case 1:
				str_obstacleLane = "Ego Lane";
				break;
			case 2:
				str_obstacleLane = "Next Lane";
				break;
			case 3:
				str_obstacleLane = "Invalid Signal";
				break;
			default:
				break;
			}
			obj["obstacleLane"] = Json::Value(str_obstacleLane);
			obj["CIPVFlags"] = Json::Value(iter_B.value().CIPVFlags);
		}

		auto iter_C = data.mapObstacleDataC.find(i);
		if (iter_C != data.mapObstacleDataC.end())
		{
			obj["obstacleAngleRate"] = Json::Value(iter_C.value().obstacleAngleRate);
			obj["obstacleScaleChange"] = Json::Value(iter_C.value().obstacleScaleChange);
			obj["objectAccel_X"] = Json::Value(iter_C.value().objectAccel_X);
			obj["obstacleAngle"] = Json::Value(iter_C.value().obstacleAngle);
		}

		std::string objName = "obj_" + std::to_string(i);
		root[objName] = obj;
	}

	Json::StyledWriter SW;
	std::ofstream os;
	

	os.open(UTF8_To_string(filePath.toStdString()), std::ios_base::out | std::ios_base::app);//续写
	if (os.is_open())
	{

		//os.seekp(1L, std::ios::end);
		os << SW.write(root);
		os << ',';
		os.close();
	}

	return false;
}
