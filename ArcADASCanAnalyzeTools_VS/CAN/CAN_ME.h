#pragma once
#include "canparser.h"
#include <QTimer>
#include <QMutex>

#pragma comment (lib, "libdbcppp.lib")

namespace ME_CAN_Parser_ns
{
	class CAN_ME : public CanParser
	{
	public:
		CAN_ME(QObject *parent = nullptr);
		~CAN_ME();

		bool openCan(int canDeviceType, int canDeviceIndex, int canChannel, int canBitRate, QString& msg);
		bool closeCan();
		bool isCanOpened();
		bool analyzeFrameTxt(const QString& filePath);

		bool initCANWriter(const QString localPath);
		void saveCANEnable(bool isEnable);

	private:
		void startReceiveData();
		void startAnalyzeData();

	protected:
		void getFrameCan();

	private:
		QTimer *m_CANFrameTimer;
		DWORD m_CanDevType;
		DWORD m_CanDevIndex;
		DWORD m_CanChn;
		DWORD m_CanBitRate;
		VCI_BOARD_INFO m_vbi;

		std::atomic<bool> m_CanOpened;
		std::atomic<bool> m_isSaveCANData;
		QString m_CANLocalSavePath;

		threadsafe_queue<CanObjData>    m_dataQueue;
		threadsafe_queue<ME_DeviceData> m_frameData;

		int m_frameTimer;
	};
}


