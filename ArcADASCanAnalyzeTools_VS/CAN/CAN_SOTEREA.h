#pragma once
#include "canparser.h"

namespace SOTEREA_CAN_Parser_ns
{
	class CAN_SOTEREA : public CanParser
	{
	public:
		CAN_SOTEREA(QObject *parent = nullptr);
		~CAN_SOTEREA();

		bool openCan(int canDeviceType, int canDeviceIndex, int canChannel, int canBitRate, QString& msg);
		bool closeCan();
		bool isCanOpened();
		bool analyzeFrameTxt(const QString& filePath);

		bool initCANWriter(const QString localPath);
		void saveCANEnable(bool isEnable);

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