#include "CAN_ME.h"
#include <QFile>
#include <algorithm>
#include <QTextCodec>
#include <io.h>


namespace ME_CAN_Parser_ns
{
	CAN_ME::CAN_ME(QObject * parent) : 
		m_CanOpened(false),
		m_isSaveCANData(true),
		m_CANLocalSavePath(""),
		m_CANFrameTimer(nullptr)
	{
		
	}

	CAN_ME::~CAN_ME()
	{
	}

	bool CAN_ME::openCan(int canDeviceType, int canDeviceIndex, int canChannel, int canBitRate, QString & msg)
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
			msg = "VCI_ClearBuffer(" + QString::number(canChannel) + ") failed";
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
		if (dwRel != STATUS_OK) 
		{
			msg = "VCI_StartCAN failed, 设备不存在或USB掉线";
			closeCan();
			return false;
		}

		qDebug() << "VCI_StartCAN success";

		dwRel = VCI_ReadBoardInfo(m_CanDevType, m_CanDevIndex, &m_vbi);
		if (dwRel != STATUS_OK)
		{
			msg = "VCI_ReadBoardInfo failed";
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

		m_CanOpened = true;
		if (m_frameTimer != 0)
		{
			killTimer(m_frameTimer);
		}

		m_frameTimer = startTimer(40);

		startReceiveData();
		startAnalyzeData();

		return true;
	}

	bool CAN_ME::closeCan()
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
			m_dataQueue.clear();
		}

		return true;
	}

	bool CAN_ME::isCanOpened()
	{
		return m_CanOpened;
	}

	bool CAN_ME::analyzeFrameTxt(const QString & filePath)
	{
		std::thread([=]()
		{
			QFile file(filePath);

			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qDebug() << "open CanTestFrame.txt failed, " << file.errorString().toLatin1().data();
				return false;
			}

			CanObjData objData;
			while (!file.atEnd())
			{
				QByteArray lineBA = file.readLine(4096);
				QString text = QTextCodec::codecForName("GBK")->toUnicode(lineBA);
				QStringList list = text.split(QRegExp("[ \t\n]"));
				if (list.at(1).compare(QString("接收")) == 0)
				{
					VCI_CAN_OBJ vco;
					memset(&vco, 0, sizeof(vco));
					vco.ID = list.at(4).toInt(nullptr, 16);
					vco.DataLen = list.at(7).toInt(nullptr, 10);
					int startOffset = 8;
					for (quint8 i = 0; i < vco.DataLen; i++) {
						vco.Data[i] = list.at(startOffset).toInt(nullptr, 16);
						startOffset++;
					}

					objData.objList.append(vco);
					if (objData.objList.size() >= 30)
					{
						m_dataQueue.push(objData);
						objData.objList.clear();
					}
				}

				QThread::msleep(1);
			}

			file.close();
			emit signalFrameTxtAnalyzeFinished();

		}).detach();

		startAnalyzeData();

		return true;
	}

	bool CAN_ME::initCANWriter(const QString localPath)
	{
		QByteArray temp = localPath.toLocal8Bit();
		char* m_CANLocalSavePath_temp = temp.data();
		//判断路径是否可写
		if (_access(m_CANLocalSavePath_temp, 2) != -1)
		{
			return false;
		}
		m_CANLocalSavePath=localPath;
		return true;
	}

	void CAN_ME::saveCANEnable(bool isEnable)
	{
		m_isSaveCANData = isEnable;

		if (!m_isSaveCANData)
		{
			m_CANLocalSavePath.clear();
		}
	}

	void CAN_ME::startReceiveData()
	{
		std::thread([=]()
		{
			while (m_CanOpened)
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

					m_dataQueue.push(objData);
				}
				else if (ret == (ULONG)(-1))
				{
					closeCan();
					qDebug() << "VCI_Receive failed! USBCAN不存在或USB掉线";
					return;
				}

				QThread::msleep(1);
			}
		}).detach();
	}

	void CAN_ME::startAnalyzeData()
	{
		std::thread([=]()
		{
			std::unique_ptr<dbcppp::INetwork> net;
			{
				std::ifstream idbc(R"(ME.dbc)");
				net = dbcppp::INetwork::LoadDBCFromIs(idbc);
			}

			if (!net)
			{
				return;
			}

			std::unordered_map<uint64_t, const dbcppp::IMessage*> messages;
			for (const dbcppp::IMessage& msg : net->Messages())
			{
				messages.insert(std::make_pair(msg.Id(), &msg));
			}

			while (true)
			{
				CanObjData canObjData;
				while (m_dataQueue.wait_and_pop(canObjData))
				{
					ME_DeviceData objData;
					//analyze can data
					for (int i = 0; i < canObjData.objList.size(); ++i)
					{
						/*
						 * 此处仅存储需要的消息
						 * 一般信息：0x700 0x738 0x760
						 * 目标信息：0x739 0x73C 0x73F 0x742
						 *			 0x73A 0x73D 0x740 0x743
						 *		     0X73B 0x73E 0x741 0x744:
						 * line signal : 0x737 0x669 0x766 0x768
						 *				0x767 0x769 
						*/
						VCI_CAN_OBJ canObj = canObjData.objList[i];
						auto iter = messages.find(canObj.ID);
						if (iter != messages.end())
						{
							const dbcppp::IMessage* msg = iter->second;
							if (canObj.ID == 0x700)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "time_indicator")
										{
											objData.generalInfo.time_indicator = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Headway_valid")
										{
											objData.generalInfo.headway_valid = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Headway_measurement")
										{
											objData.generalInfo.headway_mesurement = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "FCW_on")
										{
											objData.generalInfo.FCW_on = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Fail_safe")
										{
											objData.generalInfo.failSafe = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "PCW_PedDZ")
										{
											objData.generalInfo.PCW_PedDZ = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "TSR_warning_level")
										{
											objData.generalInfo.TSR_warning_level = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "HW_Warning_level")
										{
											objData.generalInfo.HW_warning_level = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Tamper_Alert")
										{
											objData.generalInfo.Tamper_Alert = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "LDW_off")
										{
											objData.generalInfo.LDW_off = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "LLDW_on")
										{
											objData.generalInfo.Left_LDW_Availability = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "RLDW_on")
										{
											objData.generalInfo.Right_LDW_Availability = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if(canObj.ID == 0x738)
							{
								
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Num_Obstacles")
										{
											objData.obstacleStatus.numberOfObstacles = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Left_close_rang_cut_in")
										{
											objData.obstacleStatus.LeftCloseRangCutIn = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Right_close_rang_cut_in")
										{
											objData.obstacleStatus.RightCloseRangCutIn = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Close_car")
										{
											objData.obstacleStatus.closeCar = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Failsafe")
										{
											objData.obstacleStatus.failSafe = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if (canObj.ID == 0x760)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "speed")
										{
											objData.selfSpeed = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if (canObj.ID == 0x739 || canObj.ID == 0x73c || canObj.ID == 0x73F || canObj.ID == 0x742)
							{
								ObstacleData_A obj_A;
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Obstacle_ID")
										{
											obj_A.obstacleID = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Pos_X")
										{
											obj_A.obstaclePosition.position_x = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Pos_Y")
										{
											obj_A.obstaclePosition.position_y = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Blinker_Info")
										{
											obj_A.blinkerInfo = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Cut_in_and_out")
										{
											obj_A.cutInAndOut = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Rel_Vel_X")
										{
											obj_A.obstacleRelvel_X = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Status")
										{
											obj_A.obstacleStatus = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Brake_Lights")
										{
											obj_A.obstacleBrakeLights = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Type")
										{
											obj_A.obstacle_Type = sig.RawToPhys(sig.Decode(canObj.Data));
										}	
									}
								}
								objData.objs.append(obj_A.obstaclePosition);
								objData.mapObstacleDataA.insert((canObj.ID - 0x739) / 3, obj_A);
							}
							else if (canObj.ID == 0x73A || canObj.ID == 0x73D || canObj.ID == 0x740 || canObj.ID == 0x743)
							{
								ObstacleData_B obj_B;
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Obstacle_Length")
										{
											obj_B.obstacleLength = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Width")
										{
											obj_B.obstacleWidth = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Lane")
										{
											obj_B.obstacleLane = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "CIPV_Flag")
										{
											obj_B.CIPVFlags = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}

								objData.mapObstacleDataB.insert((canObj.ID - 0x73A) / 3, obj_B);
							}
							else if (canObj.ID == 0x73B || canObj.ID == 0x73E || canObj.ID == 0x741 || canObj.ID == 0x744)
							{
								ObstacleData_C obj_C;
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Obstacle_Angle_Rate")
										{
											obj_C.obstacleAngleRate = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Scale_Change")
										{
											obj_C.obstacleScaleChange = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Object_Accel_X")
										{
											obj_C.objectAccel_X = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Obstacle_Angle")
										{
											obj_C.obstacleAngle = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
								int i = (canObj.ID - 0x73B) / 3;
								objData.mapObstacleDataC.insert((canObj.ID - 0x73B) / 3, obj_C);
							}
							else if (canObj.ID == 0x737)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
									{
										const dbcppp::ISignal* mux_sig = msg->MuxSignal();
										if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
											(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
										{
											QString sigName(sig.Name().c_str());
											if (sigName == "Lane_Curvature")
											{
												objData.generalInfo.Lane_Curvature = sig.RawToPhys(sig.Decode(canObj.Data));
											}
											if (sigName == "Pitch_Angle")
											{
												objData.generalInfo.Pitch_Angle = sig.RawToPhys(sig.Decode(canObj.Data));
											}if (sigName == "Yaw_Angle")
											{
												objData.generalInfo.Yaw_Angle = sig.RawToPhys(sig.Decode(canObj.Data));
											}if (sigName == "Right_LDW_Availability")
											{
												objData.generalInfo.Right_LDW_Availability = sig.RawToPhys(sig.Decode(canObj.Data));
											}if (sigName == "Left_LDW_Availability")
											{
												objData.generalInfo.Left_LDW_Availability = sig.RawToPhys(sig.Decode(canObj.Data));
											}
										}
									}
							}
							else if (canObj.ID == 0x669)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "LDW_availability_right")
										{
											objData.lane_Status.LDW_availability_right = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "LDW_availability_left")
										{
											objData.lane_Status.LDW_availability_left = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Lane_type_left")
										{
											objData.lane_Status.Lane_type_left = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "Lane_type_left")
										{
											objData.lane_Status.Lane_type_left = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Lane_type_right")
										{
											objData.lane_Status.Lane_type_right = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "distance_to_alne_L")
										{
											objData.lane_Status.distance_to_alne_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "distance_to_alne_R")
										{
											objData.lane_Status.distance_to_alne_R = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "Lane_conf_right")
										{
											objData.lane_Status.Lane_conf_right = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "Lane_conf_left")
										{
											objData.lane_Status.Lane_conf_left = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if (canObj.ID == 0x766 )//left
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Lane_Type")
										{
											objData.left_Status.Lane_Type_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "Quality")
										{
											objData.left_Status.Quality_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Curvature")
										{
											objData.left_Status.Curvature_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Position")
										{
											objData.left_Status.Position_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Width_left_marking")
										{
											objData.left_Status.Width_left_marking = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if (canObj.ID == 0x768)//right
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Lane_Type")
										{
											objData.right_Status.Lane_Type_R= sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "Quality")
										{
											objData.right_Status.Quality_R = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Curvature")
										{
											objData.right_Status.Curvature_R = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Position")
										{
											objData.right_Status.Position_R = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "Width_right_marking")
										{
											objData.right_Status.Width_right_marking = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if (canObj.ID == 0x767)  //left
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Heading_Angle")
										{
											objData.left_Status.Heading_Angle_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "View_Range")
										{
											objData.left_Status.View_Range_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "View_Rang_Availability")
										{
											objData.left_Status.View_Rang_Availability_L = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if (canObj.ID == 0x769)  //right
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Heading_Angle")
										{
											objData.right_Status.Heading_Angle_R = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										if (sigName == "View_Range")
										{
											objData.right_Status.View_Range_R = sig.RawToPhys(sig.Decode(canObj.Data));
										}if (sigName == "View_Rang_Availability")
										{
											objData.right_Status.View_Rang_Availability_R = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
						}
					}

					m_frameData.push(objData);
					
					if (objData.obstacleStatus.numberOfObstacles != 0)
					{
						emit signalDisplayObjData(objData);
					}
				}
			}
		}).detach();
	}


	void CAN_ME::getFrameCan()
	{	
			ME_DeviceData objData;
			
			if (m_frameData.empty())
			{
				return;
			}

			threadsafe_queue<ME_DeviceData> temp_frameData = m_frameData;
			int frameSize = temp_frameData.size();
			if (frameSize >= 1)
			{
				QList<ME_DeviceData> tempList;
				ME_DeviceData tempData;
				while (temp_frameData.try_pop(tempData))
				{
					tempList.append(tempData);
					m_frameData.try_pop();
				}

				objData = tempList.at(m_frameData.size() / 2);
			}

			if (m_isSaveCANData)
			{
				writeToLocal(m_CANLocalSavePath, objData);
			}
	}
};