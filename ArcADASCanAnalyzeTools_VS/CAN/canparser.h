#ifndef CANPARSER_H
#define CANPARSER_H

#include "global_header.h"
#include "threadsafe_queue.inl"
#include "Widget/MyLabel.h"
#include "Network.h"
#include "Tool.h"

#include <QObject>
#include <QThread>
#include <fstream>
#include <QDebug>
#include <QString>

enum CAN_Type
{
	Soterea,
	Mobileye
};

class CanParser : public QObject
{
    Q_OBJECT
public:
    explicit CanParser(QObject *parent = nullptr);
	~CanParser();

	virtual bool openCan(int canDeviceType, int canDeviceIndex, int canChannel, int canBitRate, QString& msg) = 0;
	virtual bool closeCan() = 0;
	virtual bool isCanOpened() = 0;
	virtual bool analyzeFrameTxt(const QString& filePath) = 0;
	virtual bool initCANWriter(const QString localPath) = 0;
	virtual void saveCANEnable(bool isEnable) = 0;

signals:
	void signalDisplayObjData(const ME_DeviceData& drawObjData);
	void signalClearAllObj();

	void signalUpdateDisplayMessage(const QList<DisplayAndWarningMsg>& displayMsgs);
	void signalFrameTxtAnalyzeFinished();

	void sigUpdateDeviceData(const ME_DeviceData& data);

private:
	virtual void startReceiveData() = 0;
    virtual void startAnalyzeData() = 0;

    void showCanFrameInfo(VCI_CAN_OBJ *obj);

private:
    QThread runningThread;
    
};
#endif // CANPARSER_H
