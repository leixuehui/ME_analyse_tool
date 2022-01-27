#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QPen>
#include <QTableWidgetItem>
#include <QAtomicInteger>
#include <QFuture>
#include <QMessageBox>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QButtonGroup>
#include <QDesktopWidget>
#include <vector>

#include "CAN/canparser.h"
#include "Video/videoUtils.h"
#include "global_header.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

struct FaultCodeObj
{
    QString typeName;
    QString showText;
    QLabel* valueLabel;
};

struct CarStatusObj
{
    QString typeName;
    QString showText;
    QTableWidgetItem* valueItem;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
	void initWidget(); 
	void initCamera();
	void initCAN();
	void connectSlot();
	void loadStyle(const QString &qssFile);

	CanParser* createCANParserObj(CAN_Type canType);
	void openCamera();
	void closeCamera();

	//线程函数
	void cameraView();
	void videoView(int frameTotal);
	void dataView(int frameTotal);
	//实时播放相关图标使能开关
	void setRealtimePlayIconEnable(bool isEnable);
	//视频播放相关图标使能开关
	void setVideoPlayIconEnable(bool isEnable);

	void recoveryStatus();
	void setFrameUI(int nIndex);
	bool gotoFrame(int nIndex);
	bool gotoFrameCan(int nIndex);
	
protected:
	void paintEvent(QPaintEvent *event);
	void timerEvent(QTimerEvent *event);

signals:
    void signalCoordinateChanged(int xIndex,int yIndex);
	void signalVideoPlayFinished();

private slots:
    void slotUpdateDisplayMessage(const QList<DisplayAndWarningMsg>& displayMsgs);
	void slotUpdateCANData(const ME_DeviceData& canData);

	void operationCamera();
	void openrationCAN();
	void operationRecord();
	void operationPlayVideo();

	void openFrameFile();
	void openVideoFile();
	void openCANFile();
	

	void onButtonClicked(QAbstractButton* btn);

private:
    Ui::Widget *ui;
	QButtonGroup* m_pButtonGroup;

    QList<FaultCodeObj> faultCodeObjs;
    QList<CarStatusObj> carStatusObjs;

	CanParser* m_CANParser;

	std::atomic<int>  m_frameIndex;

	bool m_realTimeFlag; // 是否是实时播放

	std::atomic<bool> m_isOpenCamera;
	std::atomic<bool> m_isVideoPlay;
	std::atomic<bool> m_isCANRecord;

	std::vector<std::string> m_cameraNameList;
	int m_rgbCameraId;
	
	VideoUtils* m_camera;
	VideoUtils* m_video;
	
	QPixmap m_pixRgbImage;       //视频模式下预览数据
	QPixmap m_pixStaticRgbImage; //静态图预览数据

	QTimer *m_saveTimer;
	QTime m_saveTime;
	int m_frameTimer;

	std::string m_strJson;
	std::vector<bool> FCW_on;
	std::vector<bool> FailSafe;
	std::vector<std::string> Fail_safe;
	std::vector<bool> Tamper_Alert;
	std::vector<std::string> HW_waring_level;
	std::vector<bool> LeftCloseRangCutIn;
	std::vector<std::string>	PCW_PedDZ;
	std::vector<bool> RightCloseRangCutIn;
	std::vector<std::string> TSR_warning_level;
	std::vector<bool> closeCar;
	std::vector<double>	headway_mesurement;
	std::vector<bool> headway_valid;
	std::vector<int> numberOfObstacles;
	std::vector<int> selfSpeed;
	std::vector<std::string>	time_indicator;
		

	QVector<QVector<int>> obstacleID;
	QVector<QVector<std::string>> obstacleLane;
	QVector<QVector<bool>> CIPVFlags;
	QVector<QVector<std::string>> cutInAndOut;
	QVector<QVector<double>> obstacleLength;
	QVector<QVector<double>>	obstacleWidth;
	QVector<QVector<std::string>> obstacle_Type;
	QVector<QVector<std::string>> obstacleStatus;
	QVector<QVector<double>> obstaclePositionX;
	QVector<QVector<double>> obstaclePositionY;
	QVector<QVector<double>>	obstacleRelvel_X;
	QVector<QVector<double>> objectAccel_X;
	QVector<QVector<double>> obstacleScaleChange;
	QVector<QVector<double>> obstacleAngleRate;
	QVector<QVector<double>>	obstacleAngle;
	QVector<QVector<bool>>	obstacleBrakeLights;
	QVector<QVector<int>>	blinkerInfo;
};
#endif // WIDGET_H
