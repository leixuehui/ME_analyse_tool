#include "CAN_Radar.h"
#include <QString>

namespace Radar_CAN_Parser_ns
{
	CAN_Radar::CAN_Radar(QObject * parent)
	{
	}

	CAN_Radar::~CAN_Radar()
	{
	}

	bool CAN_Radar::openCan(int canDeviceType, int canDeviceIndex, int canChannel, int canBitRate, QString & msg)
	{
		DWORD dwRel = VCI_OpenDevice(canDeviceType, canDeviceIndex, canChannel);
		if (dwRel != STATUS_OK) 
		{
			msg = "VCI_OpenDevice failed, 设备不存在或USB掉线";
			return false;
		}

		qDebug() << "VCI_OpenDevice success";

		dwRel = VCI_ClearBuffer(canDeviceType, canDeviceIndex, canChannel);
		if (dwRel != STATUS_OK)
		{
			msg = "VCI_ClearBuffer failed, canChannel: " + canChannel;
			closeCan();
			return false;
		}

		m_CanDevType = canDeviceType;
		m_CanDevIndex = canDeviceIndex;
		m_CanChn = canChannel;
		m_CanBitRate = canBitRate;

		qDebug() << "VCI_ClearBuffer success";

		VCI_INIT_CONFIG vic;
		memset(&vic, 0, sizeof(VCI_INIT_CONFIG));
		vic.AccCode = 0x00000000;
		vic.AccMask = 0xFFFFFFFF;
		vic.Filter = 1;
		vic.Mode = 0;

		switch (canBitRate) {
		case 10:
			vic.Timing0 = 0x31;
			vic.Timing1 = 0x1c;
			break;
		case 20:
			vic.Timing0 = 0x18;
			vic.Timing1 = 0x1c;
			break;
		case 40:
			vic.Timing0 = 0x87;
			vic.Timing1 = 0xff;
			break;
		case 50:
			vic.Timing0 = 0x09;
			vic.Timing1 = 0x1c;
			break;
		case 80:
			vic.Timing0 = 0x83;
			vic.Timing1 = 0xff;
			break;
		case 100:
			vic.Timing0 = 0x04;
			vic.Timing1 = 0x1c;
			break;
		case 125:
			vic.Timing0 = 0x03;
			vic.Timing1 = 0x1c;
			break;
		case 200:
			vic.Timing0 = 0x81;
			vic.Timing1 = 0xfa;
			break;
		case 250:
			vic.Timing0 = 0x01;
			vic.Timing1 = 0x1c;
			break;
		case 400:
			vic.Timing0 = 0x80;
			vic.Timing1 = 0xfa;
			break;
		case 500:
			vic.Timing0 = 0x00;
			vic.Timing1 = 0x1c;
			break;
		case 666:
			vic.Timing0 = 0x80;
			vic.Timing1 = 0xb6;
			break;
		case 800:
			vic.Timing0 = 0x00;
			vic.Timing1 = 0x16;
			break;
		case 1000:
			vic.Timing0 = 0x00;
			vic.Timing1 = 0x14;
			break;
		case 33:
			vic.Timing0 = 0x09;
			vic.Timing1 = 0x6f;
			break;
		case 66:
			vic.Timing0 = 0x04;
			vic.Timing1 = 0x6f;
			break;
		case 83:
			vic.Timing0 = 0x03;
			vic.Timing1 = 0x6f;
			break;
		default:
			break;
		}

		dwRel = VCI_InitCAN(m_CanDevType, m_CanDevIndex, m_CanChn, &vic);
		if (dwRel != STATUS_OK) 
		{
			msg = "VCI_InitCAN failed, 设备不存在或USB掉线";
			closeCan();
			return false;
		}

		qDebug() << "VCI_InitCAN success";

		dwRel = VCI_StartCAN(m_CanDevType, m_CanDevIndex, m_CanChn);
		if (dwRel != STATUS_OK) {
			qDebug() << "VCI_StartCAN failed";
			//msg = "VCI_StartCAN failed, 设备不存在或USB掉线";

			closeCan();
			return false;
		}

		qDebug() << "VCI_StartCAN success";

		dwRel = VCI_ReadBoardInfo(m_CanDevType, m_CanDevIndex, &m_vbi);
		if (dwRel != STATUS_OK)
		{
			//msg = "VCI_ReadBoardInfo failed";
			qDebug() << "VCI_ReadBoardInfo failed";
			return false;
		}
		else
		{
			qDebug() << "CAN通道数：" << (unsigned int)m_vbi.can_Num;
			qDebug() << "硬件版本号：" << m_vbi.hw_Version;
			qDebug() << "接口库版本号：" << m_vbi.in_Version;
			qDebug() << "中断号：" << m_vbi.irq_Num;

			QTextStream stream(&msg);
			stream << " [" << (canDeviceType == 0 ? "USBCAN-2A " : "USBCAN-2C ");
			stream << "SN:" << m_vbi.str_Serial_Num;
			stream << "]";
		}

		startReceiveData();
		startAnalyzeData();

		m_CanOpened = true;

		return true;
	}

	bool CAN_Radar::closeCan()
	{
		if (m_CanOpened)
		{
			DWORD dwRel = VCI_CloseDevice(m_CanDevType, m_CanDevIndex);
			if (dwRel != STATUS_OK)
			{
				qDebug() << "VCI close failed";
				return false;
			}
			m_CanOpened = false;
		}

		return true;
	}

	bool CAN_Radar::isCanOpened()
	{
		return m_CanOpened;
	}

	void CAN_Radar::startReceiveData()
	{
		std::thread([=]()
		{
			while (true)
			{
				VCI_CAN_OBJ vco[2500];
				memset(vco, 0, sizeof(vco));
				ULONG ret = VCI_Receive(m_CanDevType, m_CanDevIndex, m_CanChn, vco, 2500, 0);
				if (ret > 0)
				{
					CanObjData objData;
					for (ULONG i = 0; i < ret; i++)
					{
						objData.objList.append(vco[i]);
					}

					dataQueue.push(objData);
				}
				else if (ret == (ULONG)(-1))
				{
					closeCan();
					//qDebug() << "VCI_Receive failed! USBCAN不存在或USB掉线";
				}

				QThread::msleep(1);
			}
		}).detach();
	}

	void CAN_Radar::startAnalyzeData()
	{
		std::thread([=]()
		{
			std::unique_ptr<dbcppp::INetwork> net;
			{
				std::ifstream idbc(R"(CAN-ADAS.dbc)");
				net = dbcppp::INetwork::LoadDBCFromIs(idbc);
			}

			if (!net)
			{
				return;
			}

			/*std::unordered_map<uint64_t, const dbcppp::IMessage*> messages;
			for (const dbcppp::IMessage& msg : net->Messages())
			{
				messages.insert(std::make_pair(msg.Id(), &msg));
			}*/

			DrawObjData drawObjData;

			while (true)
			{
				CanObjData canObjData;
				while (dataQueue.wait_and_pop(canObjData))
				{
					//analyze can data
					for (int i = 0; i < canObjData.objList.size(); ++i)
					{
						/*
						 * 此处仅存储需要的消息
						 * 0x700:
						 * 0x738:
						 * 0x760:
						 * 0x739 0x73C 0x73F 0x742:
						 * 0x73A 0x73D 0x740 0x743:
						 * 0X73B 0x73E 0x741 0x744:
						*/

						VCI_CAN_OBJ canObj = canObjData.objList[i];
					}
				}
			}
		}).detach();
	}
};