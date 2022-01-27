#include "CAN_SOTEREA.h"
#include <QFile>
#include <algorithm>
#include <QTextCodec>

namespace SOTEREA_CAN_Parser_ns
{
	CAN_SOTEREA::CAN_SOTEREA(QObject * parent)
	{

	}

	CAN_SOTEREA::~CAN_SOTEREA()
	{

	}

	bool CAN_SOTEREA::openCan(int canDeviceType, int canDeviceIndex, int canChannel, int canBitRate, QString & msg)
	{
		DWORD dwRel = VCI_OpenDevice(canDeviceType, canDeviceIndex, canChannel);
		if (dwRel != STATUS_OK) {
			qDebug() << "VCI_OpenDevice failed " << dwRel;
			//msg = "VCI_OpenDevice failed, 设备不存在或USB掉线";
			//        QMessageBox::warning(this, "错误", "VCI_OpenDevice failed, 设备不存在或USB掉线");
			return false;
		}

		qDebug() << "VCI_OpenDevice success";

		dwRel = VCI_ClearBuffer(canDeviceType, canDeviceIndex, canChannel);
		if (dwRel != STATUS_OK) {
			qDebug() << "VCI_ClearBuffer " << canChannel << " failed";
			//            QMessageBox::warning(this, "错误", "VCI_ClearBuffer failed");
			//msg = "VCI_ClearBuffer failed";
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
		if (dwRel != STATUS_OK) {
			qDebug() << "VCI_InitCAN failed";
			//msg = "VCI_InitCAN failed, 设备不存在或USB掉线";
			//            QMessageBox::warning(this, "错误", "VCI_InitCAN failed, 设备不存在或USB掉线");
			closeCan();
			return false;
		}

		qDebug() << "VCI_InitCAN success";

		dwRel = VCI_StartCAN(m_CanDevType, m_CanDevIndex, m_CanChn);
		if (dwRel != STATUS_OK) 
		{
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

	bool CAN_SOTEREA::closeCan()
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

	bool CAN_SOTEREA::isCanOpened()
	{
		return m_CanOpened;
	}

	bool CAN_SOTEREA::analyzeFrameTxt(const QString & filePath)
	{
		std::thread([=]()
		{
			QFile file(filePath);

			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				qDebug() << "open CanTestFrame.txt failed, " << file.errorString().toLatin1().data();
				return false;
			}

			while (!file.atEnd())
			{
				QByteArray lineBA = file.readLine(4096);
				QString text = QTextCodec::codecForName("GBK")->toUnicode(lineBA);
				QStringList list = text.split(QRegExp("[ \t\n]"));
				if (list.at(1).compare(QString("接收")) == 0)
				{
					VCI_CAN_OBJ vco;
					memset(&vco, 0, sizeof(vco));
					vco.ID = list.at(3).toInt(nullptr, 16);
					vco.DataLen = list.at(7).toInt(nullptr, 10);
					int startOffset = 8;
					for (quint8 i = 0; i < vco.DataLen; i++) {
						vco.Data[i] = list.at(startOffset).toInt(nullptr, 16);
						startOffset++;
					}

					CanObjData objData;
					objData.objList.append(vco);
					dataQueue.push(objData);
				}

				QThread::msleep(10);
			}

			file.close();
			emit signalFrameTxtAnalyzeFinished();

		}).detach();

		startAnalyzeData();

		return true;
	}

	bool CAN_SOTEREA::initCANWriter(const QString localPath)
	{
		return false;
	}

	void CAN_SOTEREA::saveCANEnable(bool isEnable)
	{
	}

	void CAN_SOTEREA::startReceiveData()
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

	void CAN_SOTEREA::startAnalyzeData()
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

			std::unordered_map<uint64_t, const dbcppp::IMessage*> messages;
			for (const dbcppp::IMessage& msg : net->Messages())
			{
				//            QString hex = QString("0x%1").arg(msg.Id(), 4, 16, QLatin1Char('0'));
				//            qDebug()<<"msg.Id()"<<hex;
				messages.insert(std::make_pair(msg.Id(), &msg));
			}

			DrawObjData drawObjData;

			while (true)
			{
				CanObjData canObjData;
				while (dataQueue.wait_and_pop(canObjData))
				{
					//analyze can data
					for (int i = 0; i < canObjData.objList.size(); ++i)
					{
						VCI_CAN_OBJ canObj = canObjData.objList[i];
						//showCanFrameInfo(&canObj);

						/*
						 * 此处仅存储需要的消息
						 * 0x780: 显示与预警
						 * 0x790: 障碍物状态
						 * 0x7B0~0x7BF: 障碍物基本信息
						 * 0x7C0~0x7CF: 障碍物额外信息
						 * 0x791: 左车道线信息 A
						 * 0x792: 左车道线信息 B
						 * 0x793: 右车道线信息 A
						 * 0x794: 右车道线信息 B
						 * 0x7A0: 限速牌
						 * 0x7A1: 设备信息
						 */
						 //障碍物信息组合完整

						 // qDebug()<<"canObj.ID"<<QString("0x%1").arg(canObj.ID, 4, 16, QLatin1Char('0'));
						auto iter = messages.find(canObj.ID);
						if (iter != messages.end())
						{
							const dbcppp::IMessage* msg = iter->second;
							//qDebug() << "Received Message: " << msg->Name().c_str() << "\n";

							if (canObj.ID == 0x780)
							{
								QList<DisplayAndWarningMsg> displayAndWarningMsgs;
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										DisplayAndWarningMsg tempMsg;
										tempMsg.signalName = sig.Name().c_str();
										tempMsg.value = QString::number(sig.RawToPhys(sig.Decode(canObj.Data)));
										tempMsg.unit = QString::fromStdString(GBKToUTF8(sig.Unit().c_str()));
										displayAndWarningMsgs.append(tempMsg);
									}
								}

								emit signalUpdateDisplayMessage(displayAndWarningMsgs);
							}
							else if (canObj.ID == 0x790)
							{
								//发送上一次接收到的所有障碍物信息，进行绘制
								if (!drawObjData.objs.empty())
								{
								//	emit signalDisplayObjData(drawObjData);
								}
								
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "obj_nums")
										{
											drawObjData.leftLaneAInfo.valid = false;
											drawObjData.leftLaneBInfo.valid = false;
											drawObjData.rightLaneAInfo.valid = false;
											drawObjData.rightLaneBInfo.valid = false;
											drawObjData.speedlimitSign = -1;
											drawObjData.deviceInfoObj.valid = false;
											drawObjData.frameObjCount = sig.RawToPhys(sig.Decode(canObj.Data));
											drawObjData.objs.clear();

											qDebug() << "obj_nums" << sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "rightlane_status")
										{
											drawObjData.statuInfo.rightLaneStatus = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "leftlane_status")
										{
											drawObjData.statuInfo.leftLaneStatus = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "sv_leftlane")
										{
											drawObjData.statuInfo.leftLaneLength = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "sv_rightlane")
										{
											drawObjData.statuInfo.rightLaneLength = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "drive_status")
										{
											drawObjData.statuInfo.driverStatus = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "device_status")
										{
											drawObjData.statuInfo.deviceStatus = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "meas_counter")
										{
											drawObjData.statuInfo.measCounter = sig.RawToPhys(sig.Decode(canObj.Data));
										}

									}
								}


								if (drawObjData.frameObjCount == 0)
								{
								//	emit signalDisplayObjData(drawObjData);
								}

							}
							else if (canObj.ID == 0x791)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										//qDebug()<<sigName;
										if (sigName == "Lane_type")
										{
											drawObjData.leftLaneAInfo.laneType = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Width_marking")
										{
											drawObjData.leftLaneAInfo.widthMarking = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Quality")
										{
											drawObjData.leftLaneAInfo.quality = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "C0")
										{
											drawObjData.leftLaneAInfo.c0 = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "C1")
										{
											drawObjData.leftLaneAInfo.c1 = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}

								drawObjData.leftLaneAInfo.valid = true;
							}
							else if (canObj.ID == 0x792)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "View_range_valid")
										{
											drawObjData.leftLaneBInfo.viewRangeValid = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "View_Range")
										{
											drawObjData.leftLaneBInfo.viewRange = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "C2")
										{
											drawObjData.leftLaneBInfo.c2 = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}

								drawObjData.leftLaneBInfo.valid = true;
							}
							else if (canObj.ID == 0x793)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "Lane_type")
										{
											drawObjData.rightLaneAInfo.laneType = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Width_marking")
										{
											drawObjData.rightLaneAInfo.widthMarking = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "Quality")
										{
											drawObjData.rightLaneAInfo.quality = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "C0")
										{
											drawObjData.rightLaneAInfo.c0 = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "C1")
										{
											drawObjData.rightLaneAInfo.c1 = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}

								drawObjData.rightLaneAInfo.valid = true;
							}
							else if (canObj.ID == 0x794)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "View_range_valid")
										{
											drawObjData.rightLaneBInfo.viewRangeValid = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "View_Range")
										{
											drawObjData.rightLaneBInfo.viewRange = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "C2")
										{
											drawObjData.rightLaneBInfo.c2 = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}

								drawObjData.rightLaneBInfo.valid = true;
							}
							else if (canObj.ID == 0x7A0)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "speed_limit_sign_mark")
										{
											drawObjData.speedlimitSign = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "speed_limit_value")
										{
											drawObjData.speed = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}
							}
							else if (canObj.ID == 0x7A1)
							{
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "time_interval")
										{
											drawObjData.deviceInfoObj.timeInterval = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "calib_percentage")
										{
											drawObjData.deviceInfoObj.calibPercentage = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "calib_status")
										{
											drawObjData.deviceInfoObj.calibStatus = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "sightline_shelter")
										{
											drawObjData.deviceInfoObj.sightlineShelter = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "version_main")
										{
											drawObjData.deviceInfoObj.versionMain = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "version_minor")
										{
											drawObjData.deviceInfoObj.versionMinor = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "version_patch")
										{
											drawObjData.deviceInfoObj.versionPatch = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}

								drawObjData.deviceInfoObj.valid = true;
							}
							else if (canObj.ID >= 0x7B0 && canObj.ID <= 0x7BF)
							{
								ObjInfo objInfo = { 0,0,0,0,0,0,0 };

								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										//                                    qDebug()<<sigName;
										if (sigName == "obj_class")
										{
											objInfo.type = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "obj_x")
										{
											objInfo.PosX = sig.RawToPhys(sig.Decode(canObj.Data));
											objInfo.PosX = (objInfo.PosX > 0 ? objInfo.PosX : 0);
										}
										else if (sigName == "obj_y")
										{
											objInfo.PosY = sig.RawToPhys(sig.Decode(canObj.Data));
										}
										else if (sigName == "obj_id")
										{
											objInfo.ID = sig.RawToPhys(sig.Decode(canObj.Data));
										}
									}
								}

								drawObjData.objs.append(objInfo);
							}
							else if (canObj.ID >= 0x7C0 && canObj.ID <= 0x7CF)
							{
								//更新障碍物额外信息到 ObjInfo
								ObjInfo* objInfoPtr = nullptr;
								for (const dbcppp::ISignal& sig : msg->Signals())
								{
									const dbcppp::ISignal* mux_sig = msg->MuxSignal();
									if (sig.MultiplexerIndicator() != dbcppp::ISignal::EMultiplexer::MuxValue ||
										(mux_sig && mux_sig->Decode(canObj.Data) == sig.MultiplexerSwitchValue()))
									{
										QString sigName(sig.Name().c_str());
										if (sigName == "obj_id")
										{
											quint8 objId = sig.RawToPhys(sig.Decode(canObj.Data));
											for (int i = 0; i < drawObjData.objs.size(); ++i)
											{
												if (drawObjData.objs.at(i).ID == objId)
												{
													objInfoPtr = &drawObjData.objs[i];
													break;
												}
											}
										}
										else if (sigName == "obj_width")
										{
											if (objInfoPtr != nullptr)
											{
												objInfoPtr->Width = sig.RawToPhys(sig.Decode(canObj.Data));
											}
										}
										else if (sigName == "obj_y_arel")
										{
											if (objInfoPtr != nullptr)
											{
												objInfoPtr->RelValY = sig.RawToPhys(sig.Decode(canObj.Data));
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}).detach();
	}
}
