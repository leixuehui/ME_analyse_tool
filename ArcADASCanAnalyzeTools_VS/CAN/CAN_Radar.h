#pragma once
#include "canparser.h"

namespace Radar_CAN_Parser_ns
{
	class CAN_Radar : public CanParser
	{
	public:
		CAN_Radar(QObject *parent = nullptr);
		~CAN_Radar();

		bool openCan(int canDeviceType, int canDeviceIndex, int canChannel, int canBitRate, QString& msg);
		bool closeCan();
		bool isCanOpened();

	private:
		void startReceiveData();
		void startAnalyzeData();

	private:
		DWORD m_CanDevType;
		DWORD m_CanDevIndex;
		DWORD m_CanChn;
		DWORD m_CanBitRate;
		VCI_BOARD_INFO m_vbi;
		bool m_CanOpened;

		threadsafe_queue<CanObjData> dataQueue;
	};
}
