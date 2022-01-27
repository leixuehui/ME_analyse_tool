#include "Widget.h"
#include "ui_Widget.h"
#include "MyLabel.h"
#include "Tool.h"
#include "CAN/CAN_ME.h"
#include "CAN/CAN_SOTEREA.h"
#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"
#include <fstream>
#include <iostream>

#include <algorithm>
#include <QTextCursor>
#include <QApplication>
#include <QFileDialog>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),
	m_rgbCameraId(0),
	m_frameIndex(0),
	m_realTimeFlag(true),
	m_isOpenCamera(false), 
	m_isVideoPlay(false),
	m_saveTime(QTime::fromString("00:00:00"))
{
    initWidget();
	initCamera();
	initCAN();
	connectSlot();   
	m_frameTimer = startTimer(40);
}



Widget::~Widget()
{
    delete ui;
}

void Widget::initWidget()
{
    ui->setupUi(this);

	QDesktopWidget *desktop = QApplication::desktop();
	move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2);


	//camere Channel
	ui->comboBox->setInsertPolicy(QComboBox::InsertAfterCurrent);
	ui->comboBox->setCurrentIndex(1);


	ui->tableWidget->setItem(0, 0, new QTableWidgetItem("time_indicator"));
	ui->tableWidget->setItem(1, 0, new QTableWidgetItem("failSafe"));
	ui->tableWidget->setItem(2, 0, new QTableWidgetItem("fail_safe"));
	ui->tableWidget->setItem(3, 0, new QTableWidgetItem("Tamper Alert"));
	ui->tableWidget->setItem(4, 0, new QTableWidgetItem("headway_valid"));
	ui->tableWidget->setItem(5, 0, new QTableWidgetItem("HW_warning_level"));
	ui->tableWidget->setItem(6, 0, new QTableWidgetItem("headway_mesurement"));
	ui->tableWidget->setItem(7, 0, new QTableWidgetItem("TSR_warning_level"));
	ui->tableWidget->setItem(8, 0, new QTableWidgetItem("selfSpeed"));
	ui->tableWidget->setItem(9, 0, new QTableWidgetItem("FCW_on"));
	ui->tableWidget->setItem(10, 0, new QTableWidgetItem("PCW_PedDZ"));
	ui->tableWidget->setItem(11, 0, new QTableWidgetItem("numberOfObstacles"));
	ui->tableWidget->setItem(12, 0, new QTableWidgetItem("LeftCloseRangCutIn"));
	ui->tableWidget->setItem(13, 0, new QTableWidgetItem("RightCloseRangCutIn"));
	ui->tableWidget->setItem(14, 0, new QTableWidgetItem("closeCar"));


   /* carStatusObjs.append({"LDW","LDW 开关",nullptr});
    carStatusObjs.append({"Left_LDW_On","左车道偏离预警",nullptr});
    carStatusObjs.append({"Right_LDW_On","右车道偏离预警",nullptr});
    carStatusObjs.append({"","Lane Curvature",nullptr});
    carStatusObjs.append({"","Pitch Angle",nullptr});
    carStatusObjs.append({"","Yaw Angle",nullptr});
    carStatusObjs.append({"","Right LDW Availability",nullptr});
    carStatusObjs.append({"","Left LDW Availability",nullptr});
    carStatusObjs.append({"","distance to left lane",nullptr});
	carStatusObjs.append({ "","distance to right lane",nullptr });
	carStatusObjs.append({ "","lane confidence left",nullptr });
	carStatusObjs.append({ "","lane confidence right",nullptr });
	carStatusObjs.append({ "","LDW Availability left",nullptr });
	carStatusObjs.append({ "","LDW Availability right",nullptr });
	carStatusObjs.append({ "","Lane Type",nullptr });

    for(int i =0;i< carStatusObjs.size();++i)
    {
        carStatusObjs[i].valueItem =  new QTableWidgetItem();

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(carStatusObjs[i].showText));
        ui->tableWidget->setItem(i, 1, carStatusObjs[i].valueItem);
    }*/


	ui->tableWidget->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget->horizontalHeader()->setVisible(true);
	ui->tableWidget->verticalHeader()->setVisible(false);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui->tableWidget_ME_1->setItem(0, 0, new QTableWidgetItem("obstacleID"));
	ui->tableWidget_ME_1->setItem(1, 0, new QTableWidgetItem("obstacleLane"));
	ui->tableWidget_ME_1->setItem(2, 0, new QTableWidgetItem("CIPVFlags"));
	ui->tableWidget_ME_1->setItem(3, 0, new QTableWidgetItem("cutInAndOut"));
	ui->tableWidget_ME_1->setItem(4, 0, new QTableWidgetItem("obstacleLength"));
	ui->tableWidget_ME_1->setItem(5, 0, new QTableWidgetItem("obstacleWidth"));
	ui->tableWidget_ME_1->setItem(6, 0, new QTableWidgetItem("Obstacle Type"));
	ui->tableWidget_ME_1->setItem(7, 0, new QTableWidgetItem("obstacleStatus"));
	ui->tableWidget_ME_1->setItem(8, 0, new QTableWidgetItem("obstaclePositionX"));
	ui->tableWidget_ME_1->setItem(9, 0, new QTableWidgetItem("obstaclePositionY"));
	ui->tableWidget_ME_1->setItem(10, 0, new QTableWidgetItem("obstacleRelvel_X"));
	ui->tableWidget_ME_1->setItem(11, 0, new QTableWidgetItem("objectAccel_X"));
	ui->tableWidget_ME_1->setItem(12, 0, new QTableWidgetItem("obstacleScaleChange"));
	ui->tableWidget_ME_1->setItem(13, 0, new QTableWidgetItem("obstacleAngleRate"));
	ui->tableWidget_ME_1->setItem(14, 0, new QTableWidgetItem("obstacleAngle"));
	ui->tableWidget_ME_1->setItem(15, 0, new QTableWidgetItem("obstacleBrakeLights"));
	ui->tableWidget_ME_1->setItem(16, 0, new QTableWidgetItem("blinkerInfo"));
	
	ui->tableWidget_ME_2->setItem(0, 0, new QTableWidgetItem("obstacleID"));
	ui->tableWidget_ME_2->setItem(1, 0, new QTableWidgetItem("obstacleLane"));
	ui->tableWidget_ME_2->setItem(2, 0, new QTableWidgetItem("CIPVFlags"));
	ui->tableWidget_ME_2->setItem(3, 0, new QTableWidgetItem("cutInAndOut"));
	ui->tableWidget_ME_2->setItem(4, 0, new QTableWidgetItem("obstacleLength"));
	ui->tableWidget_ME_2->setItem(5, 0, new QTableWidgetItem("obstacleWidth"));
	ui->tableWidget_ME_2->setItem(6, 0, new QTableWidgetItem("Obstacle Type"));
	ui->tableWidget_ME_2->setItem(7, 0, new QTableWidgetItem("obstacleStatus"));
	ui->tableWidget_ME_2->setItem(8, 0, new QTableWidgetItem("obstaclePositionX"));
	ui->tableWidget_ME_2->setItem(9, 0, new QTableWidgetItem("obstaclePositionY"));
	ui->tableWidget_ME_2->setItem(10, 0, new QTableWidgetItem("obstacleRelvel_X"));
	ui->tableWidget_ME_2->setItem(11, 0, new QTableWidgetItem("objectAccel_X"));
	ui->tableWidget_ME_2->setItem(12, 0, new QTableWidgetItem("obstacleScaleChange"));
	ui->tableWidget_ME_2->setItem(13, 0, new QTableWidgetItem("obstacleAngleRate"));
	ui->tableWidget_ME_2->setItem(14, 0, new QTableWidgetItem("obstacleAngle"));
	ui->tableWidget_ME_2->setItem(15, 0, new QTableWidgetItem("obstacleBrakeLights"));
	ui->tableWidget_ME_2->setItem(16, 0, new QTableWidgetItem("blinkerInfo"));
									  
	ui->tableWidget_ME_3->setItem(0, 0, new QTableWidgetItem("obstacleID"));
	ui->tableWidget_ME_3->setItem(1, 0, new QTableWidgetItem("obstacleLane"));
	ui->tableWidget_ME_3->setItem(2, 0, new QTableWidgetItem("CIPVFlags"));
	ui->tableWidget_ME_3->setItem(3, 0, new QTableWidgetItem("cutInAndOut"));
	ui->tableWidget_ME_3->setItem(4, 0, new QTableWidgetItem("obstacleLength"));
	ui->tableWidget_ME_3->setItem(5, 0, new QTableWidgetItem("obstacleWidth"));
	ui->tableWidget_ME_3->setItem(6, 0, new QTableWidgetItem("Obstacle Type"));
	ui->tableWidget_ME_3->setItem(7, 0, new QTableWidgetItem("obstacleStatus"));
	ui->tableWidget_ME_3->setItem(8, 0, new QTableWidgetItem("obstaclePositionX"));
	ui->tableWidget_ME_3->setItem(9, 0, new QTableWidgetItem("obstaclePositionY"));
	ui->tableWidget_ME_3->setItem(10, 0, new QTableWidgetItem("obstacleRelvel_X"));
	ui->tableWidget_ME_3->setItem(11, 0, new QTableWidgetItem("objectAccel_X"));
	ui->tableWidget_ME_3->setItem(12, 0, new QTableWidgetItem("obstacleScaleChange"));
	ui->tableWidget_ME_3->setItem(13, 0, new QTableWidgetItem("obstacleAngleRate"));
	ui->tableWidget_ME_3->setItem(14, 0, new QTableWidgetItem("obstacleAngle"));
	ui->tableWidget_ME_3->setItem(15, 0, new QTableWidgetItem("obstacleBrakeLights"));
	ui->tableWidget_ME_3->setItem(16, 0, new QTableWidgetItem("blinkerInfo"));

	ui->tableWidget_ME_4->setItem(0, 0, new QTableWidgetItem("obstacleID"));
	ui->tableWidget_ME_4->setItem(1, 0, new QTableWidgetItem("obstacleLane"));
	ui->tableWidget_ME_4->setItem(2, 0, new QTableWidgetItem("CIPVFlags"));
	ui->tableWidget_ME_4->setItem(3, 0, new QTableWidgetItem("cutInAndOut"));
	ui->tableWidget_ME_4->setItem(4, 0, new QTableWidgetItem("obstacleLength"));
	ui->tableWidget_ME_4->setItem(5, 0, new QTableWidgetItem("obstacleWidth"));
	ui->tableWidget_ME_4->setItem(6, 0, new QTableWidgetItem("Obstacle Type"));
	ui->tableWidget_ME_4->setItem(7, 0, new QTableWidgetItem("obstacleStatus"));
	ui->tableWidget_ME_4->setItem(8, 0, new QTableWidgetItem("obstaclePositionX"));
	ui->tableWidget_ME_4->setItem(9, 0, new QTableWidgetItem("obstaclePositionY"));
	ui->tableWidget_ME_4->setItem(10, 0, new QTableWidgetItem("obstacleRelvel_X"));
	ui->tableWidget_ME_4->setItem(11, 0, new QTableWidgetItem("objectAccel_X"));
	ui->tableWidget_ME_4->setItem(12, 0, new QTableWidgetItem("obstacleScaleChange"));
	ui->tableWidget_ME_4->setItem(13, 0, new QTableWidgetItem("obstacleAngleRate"));
	ui->tableWidget_ME_4->setItem(14, 0, new QTableWidgetItem("obstacleAngle"));
	ui->tableWidget_ME_4->setItem(15, 0, new QTableWidgetItem("obstacleBrakeLights"));
	ui->tableWidget_ME_4->setItem(16, 0, new QTableWidgetItem("blinkerInfo"));

	//line
	/*ui->tableWidget_ME_1->setItem(34, 0, new QTableWidgetItem("Lane Type"));
	ui->tableWidget_ME_1->setItem(35, 0, new QTableWidgetItem("Lane quality"));
	ui->tableWidget_ME_1->setItem(36, 0, new QTableWidgetItem("Width_left_marking"));
	ui->tableWidget_ME_1->setItem(37, 0, new QTableWidgetItem("position"));
	ui->tableWidget_ME_1->setItem(38, 0, new QTableWidgetItem("Curvature"));
	ui->tableWidget_ME_1->setItem(39, 0, new QTableWidgetItem("Lane Heading_Angle"));
	ui->tableWidget_ME_1->setItem(40, 0, new QTableWidgetItem("Lane View_Range"));
	ui->tableWidget_ME_1->setItem(41, 0, new QTableWidgetItem("Lane View_Range_Availability"));

	ui->tableWidget_ME_1->setItem(42, 0, new QTableWidgetItem("Lane Type"));
	ui->tableWidget_ME_1->setItem(43, 0, new QTableWidgetItem("Lane quality"));
	ui->tableWidget_ME_1->setItem(44, 0, new QTableWidgetItem("Width_left_marking"));
	ui->tableWidget_ME_1->setItem(45, 0, new QTableWidgetItem("position"));
	ui->tableWidget_ME_1->setItem(46, 0, new QTableWidgetItem("Curvature"));
	ui->tableWidget_ME_1->setItem(47, 0, new QTableWidgetItem("Lane Heading_Angle"));
	ui->tableWidget_ME_1->setItem(48, 0, new QTableWidgetItem("Lane View_Range"));
	ui->tableWidget_ME_1->setItem(49, 0, new QTableWidgetItem("Lane View_Range_Availability"));
*/


	ui->tableWidget_ME_1->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget_ME_1->horizontalHeader()->setVisible(true);
	ui->tableWidget_ME_1->verticalHeader()->setVisible(false);
	ui->tableWidget_ME_1->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui->tableWidget_ME_2->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget_ME_2->horizontalHeader()->setVisible(true);
	ui->tableWidget_ME_2->verticalHeader()->setVisible(false);
	ui->tableWidget_ME_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui->tableWidget_ME_3->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget_ME_3->horizontalHeader()->setVisible(true);
	ui->tableWidget_ME_3->verticalHeader()->setVisible(false);
	ui->tableWidget_ME_3->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui->tableWidget_ME_4->horizontalHeader()->sectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget_ME_4->horizontalHeader()->setVisible(true);
	ui->tableWidget_ME_4->verticalHeader()->setVisible(false);
	ui->tableWidget_ME_4->setEditTriggers(QAbstractItemView::NoEditTriggers);



    QStringList xRangeStringList;
    xRangeStringList  << "10m"<< "20m"<< "30m"<< "50m"<< "100m";
    ui->cB_X_Range->addItems(xRangeStringList);
    ui->cB_X_Range->setCurrentIndex(3);

    QStringList yRangeStringList;
    yRangeStringList<< "10m"<< "20m"<< "30m"<< "50m"<< "100m"<< "150m"<< "200m"<< "250m"<< "300m";
    ui->cB_Y_Range->addItems(yRangeStringList);
    ui->cB_Y_Range->setCurrentIndex(6);

	m_pButtonGroup = new QButtonGroup(this);
	m_pButtonGroup->setExclusive(true);
	m_pButtonGroup->addButton(ui->radio_camera);
	m_pButtonGroup->addButton(ui->radio_video);
	ui->radio_camera->setChecked(true);
	setVideoPlayIconEnable(false);

}

void Widget::initCamera()
{
	m_cameraNameList.clear();

	m_camera = new VideoUtils;
	m_video  = new VideoUtils;
}

void Widget::initCAN()
{
	m_CANParser = createCANParserObj(Mobileye);
	//m_CANParser = createCANParserObj(Soterea);
}

void Widget::connectSlot()
{
	qRegisterMetaType<DrawObjData>("const DrawObjData&");
	connect(m_CANParser, &CanParser::signalDisplayObjData, ui->label_ObjectDisplay, &MyLabel::slotDisplayObj);

	qRegisterMetaType<QList<DisplayAndWarningMsg>>("const QList<DisplayAndWarningMsg>&");
	connect(m_CANParser, &CanParser::signalUpdateDisplayMessage, this, &Widget::slotUpdateDisplayMessage);

	qRegisterMetaType<ME_DeviceData>("const ME_DeviceData&");
	bool bret = connect(m_CANParser, &CanParser::sigUpdateDeviceData, this, &Widget::slotUpdateCANData);

	connect(ui->label_ObjectDisplay, &MyLabel::signalObstacleInfoChanged, [=](const QString& info, const QString& otherInfo)
	{
		//ui->textBrowser_ObstacleInfo->setText(info);
		//ui->textBrowser_OtherInfo->setText(otherInfo);
	});

	connect(ui->cB_X_Range, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index)
	{
		emit signalCoordinateChanged(index, ui->cB_Y_Range->currentIndex());
	});

	connect(ui->cB_Y_Range, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index)
	{
		emit signalCoordinateChanged(ui->cB_X_Range->currentIndex(), index);
	});

	connect(this, &Widget::signalCoordinateChanged, ui->label_ObjectDisplay, &MyLabel::slotCoordinateChanged);

	connect(ui->btn_StartCAN, &QPushButton::clicked, this, &Widget::openrationCAN);

	connect(m_CANParser, &CanParser::signalFrameTxtAnalyzeFinished, [=]()
	{
		ui->btn_analyzeFrameText->setEnabled(true);
		ui->btn_StartCAN->setEnabled(true);
	});

	connect(ui->btn_openCamera, &QPushButton::clicked, this, &Widget::operationCamera);
	connect(ui->btn_startRecord, &QPushButton::clicked, this, &Widget::operationRecord);
	connect(ui->btn_play, &QPushButton::clicked, this, &Widget::operationPlayVideo);

	connect(ui->btn_videoSavePath, &QPushButton::clicked, this, [=]()
	{
		QString dirName = QFileDialog::getExistingDirectory(this, tr("选择路径"), ".");
		ui->lE_videoSavePath->setText(dirName);
	});

	connect(ui->btn_CANSavePath, &QPushButton::clicked, this, [=]()
	{
		QString dirName = QFileDialog::getExistingDirectory(this, tr("选择路径"), ".");
		ui->lE_CANSavePath->setText(dirName);
	});

	connect(ui->btn_analyzeFrameText, &QPushButton::clicked, this, &Widget::openFrameFile);
	connect(ui->btn_openVideoFile, &QPushButton::clicked, this, &Widget::openVideoFile);
	connect(ui->btn_openCANFile, &QPushButton::clicked, this, &Widget::openCANFile);
	
	m_saveTimer = new QTimer;
	m_saveTimer->setInterval(1000);
	connect(m_saveTimer, &QTimer::timeout, this, [=]()
	{
		m_saveTime = m_saveTime.addSecs(1);
		QString currentTime = m_saveTime.toString("hh:mm:ss");
		ui->label_recordTime->setText(currentTime);
	});

	connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

	connect(ui->videoSlider, &QSlider::sliderReleased, [=]()
	{
		int frameIndex = ui->videoSlider->value();
		gotoFrame(frameIndex);
		gotoFrameCan(frameIndex);
	});

	connect(ui->btn_goto, &QPushButton::clicked, [=]()
	{
		int frameIndex = ui->lE_gotoFrame->text().toInt();
		gotoFrame(frameIndex);
	});

	connect(this, &Widget::signalVideoPlayFinished, [=]()
	{
		ui->btn_play->setText("开始播放");
	});
	
	emit signalCoordinateChanged(ui->cB_X_Range->currentIndex(), ui->cB_Y_Range->currentIndex());
}

void Widget::loadStyle(const QString & qssFile)
{
	//加载样式表
	QString qss;
	QFile file(qssFile);
	if (file.open(QFile::ReadOnly)) 
	{
		//用QTextStream读取样式文件不用区分文件编码 带bom也行
		QStringList list;
		QTextStream in(&file);
		//in.setCodec("utf-8");
		while (!in.atEnd())
		{
			QString line;
			in >> line;
			list << line;
		}

		file.close();
		qss = list.join("\n");
		QString paletteColor = qss.mid(20, 7);
		qApp->setPalette(QPalette(paletteColor));
		qApp->setStyleSheet(qss);
	}
}

CanParser * Widget::createCANParserObj(CAN_Type canType)
{
	switch (canType)
	{
	case Soterea:
	{
		m_CANParser = new SOTEREA_CAN_Parser_ns::CAN_SOTEREA();
		break; 
	}
	case Mobileye:
	{
		m_CANParser = new ME_CAN_Parser_ns::CAN_ME();
		break;
	}
	default:
	{
		m_CANParser = new ME_CAN_Parser_ns::CAN_ME();
		break;
	}
	}

	return m_CANParser;
}

void Widget::openCamera()
{
	m_cameraNameList.clear();
	listDevices(m_cameraNameList);


	if (2 == m_cameraNameList.size())
	{
		m_rgbCameraId= ui->comboBox->currentIndex();

		std::string errMsg;
		if (!m_camera->openCamera(m_rgbCameraId, VIDEO_FRAME_DEFAULT_WIDTH, VIDEO_FRAME_DEFAULT_HEIGHT, errMsg))
		{
			QMessageBox::about(NULL, "提示", QString::fromStdString(errMsg));
		}
		else
		{
			m_isOpenCamera = true;
		}
	}
	else
	{
		QMessageBox::about(NULL, "提示", "摄像头数量不支持！");
	}
}

void Widget::closeCamera()
{
	m_isOpenCamera = false;
	Sleep(200);
}

void Widget::cameraView()
{
	QString currentTime = QDateTime::currentDateTime().toString("MMddHHmmsszzz");

	while (m_isOpenCamera)
	{
		Sleep(3);

		m_pixRgbImage = m_camera->getFrame();
		cv::imwrite(str + currentTime, m_pixRgbImage);
	}

	ui->CameraView->clear();
	m_camera->closeVideo();
}

void Widget::videoView(int frameTotal)
{


	while (m_isVideoPlay)
	{
		m_pixStaticRgbImage = m_video->getFrame();
		
		m_frameIndex++;
		gotoFrameCan(m_frameIndex);

		if (m_frameIndex == frameTotal - 1)
		{
			Sleep(25);
			m_isVideoPlay = false;
			emit signalVideoPlayFinished();
			break;
		}

		Sleep(5);
	}
	
	m_video->closeVideo();
}
//
//void Widget::dataView(int frameTotal)
//{
//		m_frameIndex++;
//		gotoFrameCan(m_frameIndex);
//		
//		Sleep(25);
//	
//		
//}

void Widget::setRealtimePlayIconEnable(bool isEnable)
{
	//实时播放相关按钮
	ui->btn_openCamera->setEnabled(isEnable);

	ui->lE_videoSavePath->setEnabled(isEnable);
	ui->btn_videoSavePath->setEnabled(isEnable);

	ui->lE_CANSavePath->setEnabled(isEnable);
	ui->btn_CANSavePath->setEnabled(isEnable);

	ui->btn_startRecord->setEnabled(isEnable);
}

void Widget::setVideoPlayIconEnable(bool isEnable)
{
	//视频回放相关按钮
	ui->lE_videoFilePath->setEnabled(isEnable);
	ui->btn_openVideoFile->setEnabled(isEnable);

	ui->lE_CANFilePath->setEnabled(isEnable);
	ui->btn_openCANFile->setEnabled(isEnable);

	ui->btn_play->setEnabled(isEnable);
	ui->videoSlider->setEnabled(isEnable);
	ui->lE_gotoFrame->setEnabled(isEnable);
	ui->btn_goto->setEnabled(isEnable);
}

void Widget::recoveryStatus()
{
	m_isVideoPlay = false;
	m_frameIndex = 0;
	setFrameUI(0);
	ui->lE_videoFilePath->clear();
}

void Widget::setFrameUI(int nIndex)
{
	ui->videoSlider->setValue(nIndex);
	ui->lE_gotoFrame->setText(QString::number(nIndex));


}

bool Widget::gotoFrame(int nIndex)
{

	m_frameIndex = nIndex;
	setFrameUI(nIndex);

	std::string filePath = ui->lE_videoFilePath->text().toStdString();
	m_video->closeVideo();
	if (!m_video->openVideo(filePath))
	{
		return false;
	}

	m_video->setSpecifyFrame(nIndex);
	m_pixStaticRgbImage = m_video->getFrame();

	

	return true;
}




bool Widget::gotoFrameCan(int nIndex)
{
	QString boolText;

		ui->tableWidget->setItem(0, 1, new QTableWidgetItem(QString::fromStdString(time_indicator[nIndex])));
		ui->tableWidget->setItem(1, 1, new QTableWidgetItem(QString::number(FailSafe[nIndex])));
		ui->tableWidget->setItem(2, 1, new QTableWidgetItem(QString::fromStdString(Fail_safe[nIndex])));
		boolText = Tamper_Alert[nIndex] ? "true" : "false";
		ui->tableWidget->setItem(3, 1, new QTableWidgetItem(boolText));
		boolText = headway_valid[nIndex] ? "true" : "false";
		ui->tableWidget->setItem(4, 1, new QTableWidgetItem(boolText));
		ui->tableWidget->setItem(5, 1, new QTableWidgetItem(QString::fromStdString(HW_waring_level[nIndex])));
		ui->tableWidget->setItem(6, 1, new QTableWidgetItem(QString::number(headway_mesurement[nIndex],10,1)));
		ui->tableWidget->setItem(7, 1, new QTableWidgetItem(QString::fromStdString(TSR_warning_level[nIndex])));
		ui->tableWidget->setItem(8, 1, new QTableWidgetItem(QString::number(selfSpeed[nIndex])));
		boolText = headway_valid[nIndex] ? "true" : "false";
		ui->tableWidget->setItem(9, 1, new QTableWidgetItem(boolText));
		ui->tableWidget->setItem(10, 1, new QTableWidgetItem(QString::fromStdString(PCW_PedDZ[nIndex])));
		ui->tableWidget->setItem(11, 1, new QTableWidgetItem(QString::number(numberOfObstacles[nIndex])));
		boolText = LeftCloseRangCutIn[nIndex] ? "true" : "false";
		ui->tableWidget->setItem(12, 1, new QTableWidgetItem(boolText));
		boolText = RightCloseRangCutIn[nIndex] ? "true" : "false";
		ui->tableWidget->setItem(13, 1, new QTableWidgetItem(boolText));
		boolText = closeCar[nIndex] ? "true" : "false";
		ui->tableWidget->setItem(14, 1, new QTableWidgetItem(boolText));
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			ui->tableWidget_ME_1->setItem(0, 1, new QTableWidgetItem(QString::number(obstacleID[nIndex][0])));
			ui->tableWidget_ME_1->setItem(1, 1, new QTableWidgetItem(QString::fromStdString(obstacleLane[nIndex][0])));
			boolText = CIPVFlags[nIndex][0] ? "true" : "false";
			ui->tableWidget_ME_1->setItem(2, 1, new QTableWidgetItem(boolText));
			ui->tableWidget_ME_1->setItem(3, 1, new QTableWidgetItem(QString::fromStdString(cutInAndOut[nIndex][0])));
			ui->tableWidget_ME_1->setItem(4, 1, new QTableWidgetItem(QString::number(obstacleLength[nIndex][0], 10, 1)));
			ui->tableWidget_ME_1->setItem(5, 1, new QTableWidgetItem(QString::number(obstacleWidth[nIndex][0], 10, 1)));
			ui->tableWidget_ME_1->setItem(6, 1, new QTableWidgetItem(QString::fromStdString(obstacle_Type[nIndex][0])));
			ui->tableWidget_ME_1->setItem(7, 1, new QTableWidgetItem(QString::fromStdString(obstacleStatus[nIndex][0])));
			ui->tableWidget_ME_1->setItem(8, 1, new QTableWidgetItem(QString::number(obstaclePositionX[nIndex][0],10,5)));
			ui->tableWidget_ME_1->setItem(9, 1, new QTableWidgetItem(QString::number(obstaclePositionY[nIndex][0], 10, 1)));
			ui->tableWidget_ME_1->setItem(10, 1, new QTableWidgetItem(QString::number(obstacleRelvel_X[nIndex][0], 10, 1)));
			ui->tableWidget_ME_1->setItem(11, 1, new QTableWidgetItem(QString::number(objectAccel_X[nIndex][0], 10, 1)));
			ui->tableWidget_ME_1->setItem(12, 1, new QTableWidgetItem(QString::number(obstacleScaleChange[nIndex][0], 10, 1)));
			ui->tableWidget_ME_1->setItem(13, 1, new QTableWidgetItem(QString::number(obstacleAngleRate[nIndex][0], 10, 1)));
			ui->tableWidget_ME_1->setItem(14, 1, new QTableWidgetItem(QString::number(obstacleAngle[nIndex][0], 10, 1)));
			boolText = obstacleBrakeLights[nIndex][0] ? "true" : "false";
			ui->tableWidget_ME_1->setItem(15, 1, new QTableWidgetItem(boolText));
			ui->tableWidget_ME_1->setItem(16, 1, new QTableWidgetItem(QString::number(blinkerInfo[nIndex][0])));
		

			 ui->tableWidget_ME_2->setItem(0, 1, new QTableWidgetItem(QString::number(obstacleID[nIndex][1])));
			 ui->tableWidget_ME_2->setItem(1, 1, new QTableWidgetItem(QString::fromStdString(obstacleLane[nIndex][1])));
			 boolText = CIPVFlags[nIndex][1] ? "true" : "false";
			 ui->tableWidget_ME_2->setItem(2, 1, new QTableWidgetItem(boolText));
			 ui->tableWidget_ME_2->setItem(3, 1, new QTableWidgetItem(QString::fromStdString(cutInAndOut[nIndex][1])));
			 ui->tableWidget_ME_2->setItem(4, 1, new QTableWidgetItem(QString::number(obstacleLength[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(5, 1, new QTableWidgetItem(QString::number(obstacleWidth[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(6, 1, new QTableWidgetItem(QString::fromStdString(obstacle_Type[nIndex][1])));
			 ui->tableWidget_ME_2->setItem(7, 1, new QTableWidgetItem(QString::fromStdString(obstacleStatus[nIndex][1])));
			 ui->tableWidget_ME_2->setItem(8, 1, new QTableWidgetItem(QString::number(obstaclePositionX[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(9, 1, new QTableWidgetItem(QString::number(obstaclePositionY[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(10, 1, new QTableWidgetItem(QString::number(obstacleRelvel_X[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(11, 1, new QTableWidgetItem(QString::number(objectAccel_X[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(12, 1, new QTableWidgetItem(QString::number(obstacleScaleChange[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(13, 1, new QTableWidgetItem(QString::number(obstacleAngleRate[nIndex][1], 10, 1)));
			 ui->tableWidget_ME_2->setItem(14, 1, new QTableWidgetItem(QString::number(obstacleAngle[nIndex][1], 10, 1)));
			 boolText = obstacleBrakeLights[nIndex][1] ? "true" : "false";
			 ui->tableWidget_ME_2->setItem(15, 1, new QTableWidgetItem(boolText));
			 ui->tableWidget_ME_2->setItem(16, 1, new QTableWidgetItem(QString::number(blinkerInfo[nIndex][1])));

			 ui->tableWidget_ME_3->setItem(0, 1, new QTableWidgetItem(QString::number(obstacleID[nIndex][2])));
			 ui->tableWidget_ME_3->setItem(1, 1, new QTableWidgetItem(QString::fromStdString(obstacleLane[nIndex][2])));
			 boolText = CIPVFlags[nIndex][2] ? "true" : "false";
			 ui->tableWidget_ME_3->setItem(2, 1, new QTableWidgetItem(boolText));
			 ui->tableWidget_ME_3->setItem(3, 1, new QTableWidgetItem(QString::fromStdString(cutInAndOut[nIndex][2])));
			 ui->tableWidget_ME_3->setItem(4, 1, new QTableWidgetItem(QString::number(obstacleLength[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(5, 1, new QTableWidgetItem(QString::number(obstacleWidth[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(6, 1, new QTableWidgetItem(QString::fromStdString(obstacle_Type[nIndex][2])));
			 ui->tableWidget_ME_3->setItem(7, 1, new QTableWidgetItem(QString::fromStdString(obstacleStatus[nIndex][2])));
			 ui->tableWidget_ME_3->setItem(8, 1, new QTableWidgetItem(QString::number(obstaclePositionX[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(9, 1, new QTableWidgetItem(QString::number(obstaclePositionY[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(10, 1, new QTableWidgetItem(QString::number(obstacleRelvel_X[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(11, 1, new QTableWidgetItem(QString::number(objectAccel_X[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(12, 1, new QTableWidgetItem(QString::number(obstacleScaleChange[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(13, 1, new QTableWidgetItem(QString::number(obstacleAngleRate[nIndex][2], 10, 1)));
			 ui->tableWidget_ME_3->setItem(14, 1, new QTableWidgetItem(QString::number(obstacleAngle[nIndex][2], 10, 1)));
			 boolText = obstacleBrakeLights[nIndex][2] ? "true" : "false";
			 ui->tableWidget_ME_3->setItem(15, 1, new QTableWidgetItem(boolText));
			 ui->tableWidget_ME_3->setItem(16, 1, new QTableWidgetItem(QString::number(blinkerInfo[nIndex][2])));


			 ui->tableWidget_ME_4->setItem(0, 1, new QTableWidgetItem(QString::number(obstacleID[nIndex][3])));
			 ui->tableWidget_ME_4->setItem(1, 1, new QTableWidgetItem(QString::fromStdString(obstacleLane[nIndex][3])));
			 boolText = CIPVFlags[nIndex][3] ? "true" : "false";
			 ui->tableWidget_ME_4->setItem(2, 1, new QTableWidgetItem(boolText));
			 ui->tableWidget_ME_4->setItem(3, 1, new QTableWidgetItem(QString::fromStdString(cutInAndOut[nIndex][3])));
			 ui->tableWidget_ME_4->setItem(4, 1, new QTableWidgetItem(QString::number(obstacleLength[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(5, 1, new QTableWidgetItem(QString::number(obstacleWidth[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(6, 1, new QTableWidgetItem(QString::fromStdString(obstacle_Type[nIndex][3])));
			 ui->tableWidget_ME_4->setItem(7, 1, new QTableWidgetItem(QString::fromStdString(obstacleStatus[nIndex][3])));
			 ui->tableWidget_ME_4->setItem(8, 1, new QTableWidgetItem(QString::number(obstaclePositionX[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(9, 1, new QTableWidgetItem(QString::number(obstaclePositionY[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(10, 1, new QTableWidgetItem(QString::number(obstacleRelvel_X[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(11, 1, new QTableWidgetItem(QString::number(objectAccel_X[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(12, 1, new QTableWidgetItem(QString::number(obstacleScaleChange[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(13, 1, new QTableWidgetItem(QString::number(obstacleAngleRate[nIndex][3], 10, 1)));
			 ui->tableWidget_ME_4->setItem(14, 1, new QTableWidgetItem(QString::number(obstacleAngle[nIndex][3], 10, 1)));
			 boolText = obstacleBrakeLights[nIndex][3] ? "true" : "false";
			 ui->tableWidget_ME_4->setItem(15, 1, new QTableWidgetItem(boolText));
			 ui->tableWidget_ME_4->setItem(16, 1, new QTableWidgetItem(QString::number(blinkerInfo[nIndex][3])));
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			 if (obstacleID[nIndex][0] == 0 && obstacle_Type[nIndex][0] == "")
			 {
				 for (int i = 0; i < 20; i++)
					 ui->tableWidget_ME_1->setItem(i, 1, new QTableWidgetItem(""));
			 }
			 if (obstacleID[nIndex][1] == 0 && obstacle_Type[nIndex][1] == "")
			 {
				 for (int i = 0; i < 20; i++)
					 ui->tableWidget_ME_2->setItem(i, 1, new QTableWidgetItem(""));
			 }
			 if (obstacleID[nIndex][2] == 0 && obstacle_Type[nIndex][2] == "")
			 {
				 for (int i = 0; i < 20; i++)
					 ui->tableWidget_ME_3->setItem(i, 1, new QTableWidgetItem(""));

			 }
			 if (obstacleID[nIndex][3] == 0 && obstacle_Type[nIndex][3] == "")
			 {
				 for (int i = 0; i < 20; i++)
					 ui->tableWidget_ME_4->setItem(i, 1, new QTableWidgetItem(""));
			 }



	ui->tableWidget->viewport()->update();
	ui->tableWidget_ME_1->viewport()->update();
	ui->tableWidget_ME_2->viewport()->update();
	ui->tableWidget_ME_3->viewport()->update();
	ui->tableWidget_ME_4->viewport()->update();


	return true;
}



void Widget::paintEvent(QPaintEvent * event)
{
	Q_UNUSED(event);

	if (m_realTimeFlag)
	{

		ui->CameraView->setPixmap(m_pixRgbImage);
		ui->CameraView->setAlignment(Qt::AlignCenter);
		ui->CameraView->setScaledContents(true);
	}
	else
	{
		ui->CameraView->setPixmap(m_pixStaticRgbImage);
		ui->CameraView->setAlignment(Qt::AlignCenter);
		ui->CameraView->setScaledContents(true);
		
		if (m_isVideoPlay)
		{
			setFrameUI(m_frameIndex);
			
		}
	}
}



void Widget::slotUpdateCANData(const ME_DeviceData & canData)
{
	QString str_time_indicator = "";
	QString str_obstacle_Type = "";

	switch (canData.generalInfo.time_indicator)
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
	ui->tableWidget->setItem(0, 1, new QTableWidgetItem(str_time_indicator));
	QString boolText = canData.generalInfo.failSafe ? "true" : "false";
	ui->tableWidget->setItem(1, 1, new QTableWidgetItem(boolText));
	QString str_Fail_safe = "";
	switch (canData.obstacleStatus.failSafe)
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
	ui->tableWidget->setItem(2, 1, new QTableWidgetItem(str_Fail_safe));
	boolText = canData.generalInfo.Tamper_Alert ? "true" : "false";
	ui->tableWidget->setItem(3, 1, new QTableWidgetItem(boolText));
	boolText = canData.generalInfo.headway_valid ? "true" : "false";
	ui->tableWidget->setItem(4, 1, new QTableWidgetItem(boolText));
	ui->tableWidget->setItem(5, 1, new QTableWidgetItem(QString::number(canData.generalInfo.HW_warning_level)));
	ui->tableWidget->setItem(6, 1, new QTableWidgetItem(QString::number(canData.generalInfo.headway_mesurement, 10, 1)));
	ui->tableWidget->setItem(7, 1, new QTableWidgetItem(QString::number(canData.generalInfo.TSR_warning_level)));
	ui->tableWidget->setItem(8, 1, new QTableWidgetItem(QString::number(canData.selfSpeed)));
	boolText = canData.generalInfo.FCW_on ? "true" : "false";
	ui->tableWidget->setItem(9, 1, new QTableWidgetItem(boolText));
	boolText = canData.generalInfo.PCW_PedDZ ? "true" : "false";
	ui->tableWidget->setItem(10, 1, new QTableWidgetItem(boolText));
	if (canData.obstacleStatus.numberOfObstacles !=0)
	{
		ui->tableWidget->setItem(11, 1, new QTableWidgetItem(QString::number(canData.obstacleStatus.numberOfObstacles)));
	}
	boolText = canData.obstacleStatus.LeftCloseRangCutIn ? "true" : "false";
	ui->tableWidget->setItem(12, 1, new QTableWidgetItem(boolText));
	boolText = canData.obstacleStatus.RightCloseRangCutIn ? "true" : "false";
	ui->tableWidget->setItem(13, 1, new QTableWidgetItem(boolText));
	boolText = canData.obstacleStatus.closeCar ? "true" : "false";
	ui->tableWidget->setItem(14, 1, new QTableWidgetItem(boolText));
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[0].obstacleID != 0)
	{
		ui->tableWidget_ME_1->setItem(0, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[0].obstacleID)));
	}

		QString str_obstacleLane = "";
		switch (canData.mapObstacleDataB[0].obstacleLane)
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
		if (!canData.mapObstacleDataB.isEmpty() && str_obstacleLane != "")
		{
			ui->tableWidget_ME_1->setItem(1, 1, new QTableWidgetItem(str_obstacleLane));
			str_obstacleLane = "";
		}
		boolText = canData.mapObstacleDataB[0].CIPVFlags ? "CIPV" : "Not CIPV";
		ui->tableWidget_ME_1->setItem(2, 1, new QTableWidgetItem(boolText));
		boolText = "";//
		QString str_cutInAndOut="";
		switch (canData.mapObstacleDataA[0].cutInAndOut)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_cutInAndOut != "")
		{
			ui->tableWidget_ME_1->setItem(3, 1, new QTableWidgetItem(str_cutInAndOut));
			str_cutInAndOut = "";
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[0].obstacleLength != 0.0)
		{
			ui->tableWidget_ME_1->setItem(4, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[0].obstacleLength, 10, 1)));
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[0].obstacleWidth != 0.0)
		{
			ui->tableWidget_ME_1->setItem(5, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[0].obstacleWidth, 10, 1)));
		}
		
		switch (canData.mapObstacleDataA[0].obstacle_Type)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacle_Type != "")
		{
			ui->tableWidget_ME_1->setItem(6, 1, new QTableWidgetItem(str_obstacle_Type));
			str_obstacle_Type = "";
		}
		QString str_obstacleStatus;
		switch (canData.mapObstacleDataA[0].obstacleStatus)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacleStatus != "")
		{
			ui->tableWidget_ME_1->setItem(7, 1, new QTableWidgetItem(str_obstacleStatus));
			str_obstacleStatus = "";
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[0].obstaclePosition.position_x != 0.0)
		{
			ui->tableWidget_ME_1->setItem(8, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[0].obstaclePosition.position_x, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[0].obstaclePosition.position_y != 0.0)
		{
			ui->tableWidget_ME_1->setItem(9, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[0].obstaclePosition.position_y, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[0].obstacleRelvel_X != 0.0)
		{
			ui->tableWidget_ME_1->setItem(10, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[0].obstacleRelvel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[0].objectAccel_X != 0.0)
		{
			ui->tableWidget_ME_1->setItem(11, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[0].objectAccel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[0].obstacleScaleChange != 0.0)
		{
			ui->tableWidget_ME_1->setItem(12, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[0].obstacleScaleChange, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[0].obstacleAngleRate != 0.0)
		{
			ui->tableWidget_ME_1->setItem(13, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[0].obstacleAngleRate, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[0].obstacleAngle != 0.0)
		{
			ui->tableWidget_ME_1->setItem(14, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[0].obstacleAngle, 10, 1)));
		}
		
		boolText = canData.mapObstacleDataA[0].obstacleBrakeLights ? "true" : "false";
		ui->tableWidget_ME_1->setItem(15, 1, new QTableWidgetItem(boolText));
		boolText = "";//
		QString str_blinkerInfo = "";
		switch (canData.mapObstacleDataA[0].blinkerInfo)
		{
		case 0:
			str_blinkerInfo = "unavailable";
			break;
		case 1:
			str_blinkerInfo = "off";
			break;
		case 2:
			str_blinkerInfo = "left";
			break;
		case 3:
			str_blinkerInfo = "right";
			break;
		case 4:
			str_blinkerInfo = "both";
			break;
		}
		if (!canData.mapObstacleDataA.isEmpty() && str_blinkerInfo != "")
		{
			ui->tableWidget_ME_1->setItem(16, 1, new QTableWidgetItem(str_blinkerInfo));
			str_blinkerInfo = "";
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[1].obstacleID != 0)
		{
			ui->tableWidget_ME_2->setItem(0, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[1].obstacleID)));
		}
		switch (canData.mapObstacleDataB[1].obstacleLane)
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
		if (!canData.mapObstacleDataB.isEmpty() && str_obstacleLane != "")
		{
			ui->tableWidget_ME_2->setItem(1, 1, new QTableWidgetItem(str_obstacleLane));
			str_obstacleLane = "";
		}
		boolText = canData.mapObstacleDataB[1].CIPVFlags ? "CIPV" : "Not CIPV";
		ui->tableWidget_ME_2->setItem(2, 1, new QTableWidgetItem(boolText));
		boolText = "";//
		switch (canData.mapObstacleDataA[1].cutInAndOut)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_cutInAndOut != "")
		{
			ui->tableWidget_ME_2->setItem(3, 1, new QTableWidgetItem(str_cutInAndOut));
			str_cutInAndOut = "";
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[1].obstacleLength != 0.0)
		{
			ui->tableWidget_ME_2->setItem(4, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[1].obstacleLength, 10, 1)));
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[1].obstacleWidth != 0.0)
		{
			ui->tableWidget_ME_2->setItem(5, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[1].obstacleWidth, 10, 1)));
		}

		switch (canData.mapObstacleDataA[1].obstacle_Type)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacle_Type != "")
		{
			ui->tableWidget_ME_2->setItem(6, 1, new QTableWidgetItem(str_obstacle_Type));
			str_obstacle_Type = "";
		}
		switch (canData.mapObstacleDataA[1].obstacleStatus)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacleStatus != "")
		{
			ui->tableWidget_ME_2->setItem(7, 1, new QTableWidgetItem(str_obstacleStatus));
			str_obstacleStatus = "";
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[1].obstaclePosition.position_x != 0.0)
		{
			ui->tableWidget_ME_2->setItem(8, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[1].obstaclePosition.position_x, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[1].obstaclePosition.position_y != 0.0)
		{
			ui->tableWidget_ME_2->setItem(9, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[1].obstaclePosition.position_y, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[1].obstacleRelvel_X != 0.0)
		{
			ui->tableWidget_ME_2->setItem(10, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[1].obstacleRelvel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[1].objectAccel_X != 0.0)
		{
			ui->tableWidget_ME_2->setItem(11, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[1].objectAccel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[1].obstacleScaleChange != 0.0)
		{
			ui->tableWidget_ME_2->setItem(12, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[1].obstacleScaleChange, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[1].obstacleAngleRate != 0.0)
		{
			ui->tableWidget_ME_2->setItem(13, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[1].obstacleAngleRate, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[1].obstacleAngle != 0.0)
		{
			ui->tableWidget_ME_2->setItem(14, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[1].obstacleAngle, 10, 1)));
		}

		boolText = canData.mapObstacleDataA[1].obstacleBrakeLights ? "true" : "false";
		ui->tableWidget_ME_2->setItem(15, 1, new QTableWidgetItem(boolText));
		boolText = "";
		switch (canData.mapObstacleDataA[1].blinkerInfo)
		{
		case 0:
			str_blinkerInfo = "unavailable";
			break;
		case 1:
			str_blinkerInfo = "off";
			break;
		case 2:
			str_blinkerInfo = "left";
			break;
		case 3:
			str_blinkerInfo = "right";
			break;
		case 4:
			str_blinkerInfo = "both";
			break;
		}
		if (!canData.mapObstacleDataA.isEmpty() && str_blinkerInfo != "")
		{
			ui->tableWidget_ME_2->setItem(16, 1, new QTableWidgetItem(str_blinkerInfo));
			str_blinkerInfo = "";
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[2].obstacleID != 0)
		{
			ui->tableWidget_ME_3->setItem(0, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[2].obstacleID)));
		}
		switch (canData.mapObstacleDataB[2].obstacleLane)
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
		if (!canData.mapObstacleDataB.isEmpty() && str_obstacleLane != "")
		{
			ui->tableWidget_ME_3->setItem(1, 1, new QTableWidgetItem(str_obstacleLane));
			str_obstacleLane = "";
		}
		boolText = canData.mapObstacleDataB[2].CIPVFlags ? "CIPV" : "Not CIPV";
		ui->tableWidget_ME_3->setItem(2, 1, new QTableWidgetItem(boolText));
		switch (canData.mapObstacleDataA[2].cutInAndOut)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_cutInAndOut != "")
		{
			ui->tableWidget_ME_3->setItem(3, 1, new QTableWidgetItem(str_cutInAndOut));
			str_cutInAndOut = "";
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[2].obstacleLength != 0.0)
		{
			ui->tableWidget_ME_3->setItem(4, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[2].obstacleLength, 10, 1)));
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[2].obstacleWidth != 0.0)
		{
			ui->tableWidget_ME_3->setItem(5, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[2].obstacleWidth, 10, 1)));
		}

		switch (canData.mapObstacleDataA[2].obstacle_Type)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacle_Type != "")
		{
			ui->tableWidget_ME_3->setItem(6, 1, new QTableWidgetItem(str_obstacle_Type));
			str_obstacle_Type = "";
		}
		switch (canData.mapObstacleDataA[2].obstacleStatus)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacleStatus != "")
		{
			ui->tableWidget_ME_3->setItem(7, 1, new QTableWidgetItem(str_obstacleStatus));
			str_obstacleStatus = "";
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[2].obstaclePosition.position_x != 0.0)
		{
			ui->tableWidget_ME_3->setItem(8, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[2].obstaclePosition.position_x, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[2].obstaclePosition.position_y != 0.0)
		{
			ui->tableWidget_ME_3->setItem(9, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[2].obstaclePosition.position_y, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[2].obstacleRelvel_X != 0.0)
		{
			ui->tableWidget_ME_3->setItem(10, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[2].obstacleRelvel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[2].objectAccel_X != 0.0)
		{
			ui->tableWidget_ME_3->setItem(11, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[2].objectAccel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[2].obstacleScaleChange != 0.0)
		{
			ui->tableWidget_ME_3->setItem(12, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[2].obstacleScaleChange, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[2].obstacleAngleRate != 0.0)
		{
			ui->tableWidget_ME_3->setItem(13, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[2].obstacleAngleRate, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[2].obstacleAngle != 0.0)
		{
			ui->tableWidget_ME_3->setItem(14, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[2].obstacleAngle, 10, 1)));
		}

		boolText = canData.mapObstacleDataA[2].obstacleBrakeLights ? "true" : "false";
		ui->tableWidget_ME_3->setItem(15, 1, new QTableWidgetItem(boolText));
		switch (canData.mapObstacleDataA[2].blinkerInfo)
		{
		case 0:
			str_blinkerInfo = "unavailable";
			break;
		case 1:
			str_blinkerInfo = "off";
			break;
		case 2:
			str_blinkerInfo = "left";
			break;
		case 3:
			str_blinkerInfo = "right";
			break;
		case 4:
			str_blinkerInfo = "both";
			break;
		}
		if (!canData.mapObstacleDataA.isEmpty() && str_blinkerInfo != "")
		{
			ui->tableWidget_ME_3->setItem(16, 1, new QTableWidgetItem(str_blinkerInfo));
			str_blinkerInfo = "";
		}


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[3].obstacleID != 0)
		{
			ui->tableWidget_ME_4->setItem(0, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[3].obstacleID)));
		}

		switch (canData.mapObstacleDataB[3].obstacleLane)
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
		if (!canData.mapObstacleDataB.isEmpty() && str_obstacleLane != "")
		{
			ui->tableWidget_ME_4->setItem(1, 1, new QTableWidgetItem(str_obstacleLane));
			str_obstacleLane = "";
		}
		boolText = canData.mapObstacleDataB[3].CIPVFlags ? "CIPV" : "Not CIPV";
		ui->tableWidget_ME_4->setItem(2, 1, new QTableWidgetItem(boolText));
		switch (canData.mapObstacleDataA[3].cutInAndOut)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_cutInAndOut != "")
		{
			ui->tableWidget_ME_4->setItem(3, 1, new QTableWidgetItem(str_cutInAndOut));
			str_cutInAndOut = "";
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[3].obstacleLength != 0.0)
		{
			ui->tableWidget_ME_4->setItem(4, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[3].obstacleLength, 10, 1)));
		}
		if (!canData.mapObstacleDataB.isEmpty() && canData.mapObstacleDataB[3].obstacleWidth != 0.0)
		{
			ui->tableWidget_ME_4->setItem(5, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataB[3].obstacleWidth, 10, 1)));
		}

		switch (canData.mapObstacleDataA[3].obstacle_Type)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacle_Type != "")
		{
			ui->tableWidget_ME_4->setItem(6, 1, new QTableWidgetItem(str_obstacle_Type));
			str_obstacle_Type = "";
		}
		switch (canData.mapObstacleDataA[3].obstacleStatus)
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
		if (!canData.mapObstacleDataA.isEmpty() && str_obstacleStatus != "")
		{
			ui->tableWidget_ME_4->setItem(7, 1, new QTableWidgetItem(str_obstacleStatus));
			str_obstacleStatus = "";
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[3].obstaclePosition.position_x != 0.0)
		{
			ui->tableWidget_ME_4->setItem(8, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[3].obstaclePosition.position_x, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[3].obstaclePosition.position_y != 0.0)
		{
			ui->tableWidget_ME_4->setItem(9, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[3].obstaclePosition.position_y, 10, 1)));
		}
		if (!canData.mapObstacleDataA.isEmpty() && canData.mapObstacleDataA[3].obstacleRelvel_X != 0.0)
		{
			ui->tableWidget_ME_4->setItem(10, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataA[3].obstacleRelvel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[3].objectAccel_X != 0.0)
		{
			ui->tableWidget_ME_4->setItem(11, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[3].objectAccel_X, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[3].obstacleScaleChange != 0.0)
		{
			ui->tableWidget_ME_4->setItem(12, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[3].obstacleScaleChange, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[3].obstacleAngleRate != 0.0)
		{
			ui->tableWidget_ME_4->setItem(13, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[3].obstacleAngleRate, 10, 1)));
		}
		if (!canData.mapObstacleDataC.isEmpty() && canData.mapObstacleDataC[3].obstacleAngle != 0.0)
		{
			ui->tableWidget_ME_4->setItem(14, 1, new QTableWidgetItem(QString::number(canData.mapObstacleDataC[3].obstacleAngle, 10, 1)));
		}

		boolText = canData.mapObstacleDataA[3].obstacleBrakeLights ? "true" : "false";
		ui->tableWidget_ME_4->setItem(15, 1, new QTableWidgetItem(boolText));

		switch (canData.mapObstacleDataA[3].blinkerInfo)
		{
		case 0:
			str_blinkerInfo = "unavailable";
			break;
		case 1:
			str_blinkerInfo = "off";
			break;
		case 2:
			str_blinkerInfo = "left";
			break;
		case 3:
			str_blinkerInfo = "right";
			break;
		case 4:
			str_blinkerInfo = "both";
			break;
		}
		if (!canData.mapObstacleDataA.isEmpty() && str_blinkerInfo != "")
		{
			ui->tableWidget_ME_4->setItem(16, 1, new QTableWidgetItem(str_blinkerInfo));
			str_blinkerInfo = "";
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/*if (canData.mapObstacleDataA[0].obstacleID == 0 && canData.mapObstacleDataA[0].obstacle_Type == 6)
		{
			for (int i = 0; i < 20; i++)
				ui->tableWidget_ME_1->setItem(i, 1, new QTableWidgetItem(""));
		}
		 if (canData.mapObstacleDataA[1].obstacleID == 0 && canData.mapObstacleDataA[1].obstacle_Type == 6)
		{
			for (int i = 0; i < 20; i++)
				ui->tableWidget_ME_2->setItem(i, 1, new QTableWidgetItem(""));
		}
		if (canData.mapObstacleDataA[2].obstacleID == 0 && canData.mapObstacleDataA[2].obstacle_Type == 6)
		{
			for (int i = 0; i < 20; i++)
				ui->tableWidget_ME_3->setItem(i, 1, new QTableWidgetItem(""));

		}
		if (canData.mapObstacleDataA[3].obstacleID == 0 && canData.mapObstacleDataA[3].obstacle_Type == 6)
		{
			for (int i = 0; i < 20; i++)
				ui->tableWidget_ME_4->setItem(i, 1, new QTableWidgetItem(""));
		}
*/


}

void Widget::operationCamera()
{
	if (ui->btn_openCamera->text() == "开启摄像头")
	{
		openCamera();
	}
	else if (ui->btn_openCamera->text() == "关闭摄像头")
	{
		closeCamera();
	}

	if (m_isOpenCamera)
	{
		ui->btn_openCamera->setText("关闭摄像头");

		std::thread threadCamera(&Widget::cameraView, this);
		threadCamera.detach();
	}
	else
	{
		ui->btn_openCamera->setText("开启摄像头");
	}
}

void Widget::openrationCAN()
{
	if (ui->btn_StartCAN->text() == "启动")
	{
		int canDevIndex = 0;
		int canChn = 0;
		int canBitRateIndex = 500;
		int canDevType = 4;
		QString retMsg;

		if (!m_CANParser->openCan(canDevType, canDevIndex, canChn, canBitRateIndex, retMsg))
		{
			ui->btn_StartCAN->setEnabled(true);
			ui->label_CanStatus->setText("设备未连接");
			ui->label_CanStatus->setStyleSheet("QLabel {background-color: rgb(255, 0, 0);}");
			ui->btn_analyzeFrameText->setEnabled(true);

			QMessageBox::warning(this, "错误", retMsg);

		}
		else
		{
			ui->btn_StartCAN->setEnabled(false);
			ui->label_CanStatus->setText("设备已连接");
			ui->label_CanStatus->setStyleSheet("QLabel {background-color: rgb(0, 255, 0);}");
			ui->btn_analyzeFrameText->setEnabled(false);

			ui->btn_StartCAN->setText("断开");
			this->setWindowTitle(this->windowTitle() + retMsg);
		}
	}
	else
	{
		if (m_CANParser->closeCan())
		{
			ui->btn_StartCAN->setEnabled(true);
			ui->label_CanStatus->setText("设备未连接");
			ui->label_CanStatus->setStyleSheet("QLabel {background-color: rgb(255, 0, 0);}");
			ui->btn_analyzeFrameText->setEnabled(true);
			ui->btn_StartCAN->setText("启动");
		}
	}
}


void Widget::operationRecord()
{
	if (ui->btn_startRecord->text() == "开始录制")
	{
		if (m_isOpenCamera && (ui->lE_videoSavePath->text() != ""))
		{
			if (ui->lE_videoSavePath->text().isEmpty() || ui->lE_CANSavePath->text().isEmpty())
			{
				QMessageBox::about(NULL, "提示", "请先设置视频和CAN的保存路径!");
				return;
			}

			QString currentTime = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
			QString videoSavePath = ui->lE_videoSavePath->text() + "/" + currentTime + ".avi";
			if (!m_camera->initVideoWriter(videoSavePath.toStdString()))
			{
				QMessageBox::about(NULL, "提示", "初始化录制失败, 请检查视频本地保存路径是否正确!");
				return;
			}

			QString CANSavePath = ui->lE_CANSavePath->text() + "/" + currentTime + ".json";
			if (!m_CANParser->initCANWriter(CANSavePath))
			{
				QMessageBox::about(NULL, "提示", "初始化录制失败, 请检查CAN数据本地保存路径是否正确!");
				return;
			}

			ui->btn_startRecord->setText("停止录制");
			
			//开启视频录制
			m_camera->saveVideoEnable(true);
			//开启CAN录制
			m_CANParser->saveCANEnable(true);
			//开启录制计时
			m_saveTimer->start();
		}
		else 
		{
			QMessageBox::about(NULL, "提示", "请先开启摄像头或选择视频保存路径！");
		}
	}
	else if (ui->btn_startRecord->text() == "停止录制")
	{
		ui->btn_startRecord->setText("开始录制");
		
		//停止视频录制
		m_camera->saveVideoEnable(false);
		//停止CAN录制
		m_CANParser->saveCANEnable(false);
		//停止录制计时
		m_saveTimer->stop();

		ui->label_recordTime->setText(QTime::fromString("00:00:00").toString("hh:mm:ss"));
	}
}


void Widget::timerEvent(QTimerEvent *event)
{
	while (m_saveTimer->isActive())
	{
		if (event->timerId() == m_frameTimer)
		{
			QString currentTime = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
			qDebug() << currentTime;

			ME_DeviceData objData;

		}
	}
}



void Widget::operationPlayVideo()
{
	if (ui->lE_videoFilePath->text() != "")
	{
		std::string filePath = ui->lE_videoFilePath->text().toStdString();
		if (ui->btn_play->text() == "开始播放")
		{
			ui->btn_play->setText("暂停播放");
			m_isVideoPlay = true;
		}
		else if(ui->btn_play->text() == "暂停播放")
		{
			ui->btn_play->setText("开始播放");
			m_isVideoPlay = false;
		}

		if (m_isVideoPlay)
		{
			int totalFrameNum = m_video->getVideoFrameTotalNum(filePath);
			if (m_frameIndex == totalFrameNum - 1)
			{
				m_frameIndex = 0;
			}

			gotoFrame(m_frameIndex);
			gotoFrameCan(m_frameIndex);
			std::thread threadVideo([this, totalFrameNum]() {videoView(totalFrameNum);});
			threadVideo.detach();
		}
	}
	else
	{
		QMessageBox::about(NULL, "提示", "请先选择视频文件!");
	}
}

void Widget::openFrameFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Can Frame"), ".", tr("txt Files (*.txt)"));
	qDebug() << fileName;

	if (!fileName.isEmpty())
	{
		m_CANParser->analyzeFrameTxt(fileName);

		ui->btn_analyzeFrameText->setEnabled(false);
		ui->btn_StartCAN->setEnabled(false);
	}
	else
	{
		QMessageBox::warning(this, "错误", "未选择文件");
	}
}

void Widget::openVideoFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("选择视频文件"), ".", tr("avi Files (*.avi)"));
	ui->lE_videoFilePath->setText(fileName);
	m_isVideoPlay = false;
	if (!gotoFrame(0))
	{
		ui->lE_videoFilePath->clear();
		QMessageBox::about(NULL, "提示", "视频文件打开失败!");
	}

	int totalFrameNum = m_video->getVideoFrameTotalNum(fileName.toStdString());
	ui->videoSlider->setRange(0, totalFrameNum - 1);
}




void Widget::openCANFile()
{

	Json::Reader reader;
	Json::Value root;
	Json::Value root_frame;

	

	QString filedata = QFileDialog::getOpenFileName(this, tr("Open Can Frame"), ".", tr("txt Files (*.json)"));
	ui->lE_CANFilePath->setText(filedata);
	//m_isCANRecord = false;
	std::string filePathS = ui->lE_CANFilePath->text().toStdString();


	QString filePath = QString::fromStdString(filePathS);
	QFile file(filePath.toLocal8Bit().data());
	std::string temp_str;
	std::string obj;
	
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		temp_str = file.readAll();
	}

	temp_str.pop_back();
	m_strJson = "{\"frame\":[" + temp_str + "]}";
	int count;
	if (reader.parse(m_strJson, root))
	{
	 count = root["frame"].size();
	}

	obstacleID.resize(count);
	obstacleLane.resize(count);
	CIPVFlags.resize(count);
	cutInAndOut.resize(count);
	obstacleLength.resize(count);
	obstacleWidth.resize(count);
	obstacle_Type.resize(count);
	obstacleStatus.resize(count);
	obstaclePositionX.resize(count);
	obstaclePositionY.resize(count);
	obstacleRelvel_X.resize(count);
	objectAccel_X.resize(count);
	obstacleScaleChange.resize(count);
	obstacleAngleRate.resize(count);
	obstacleAngle.resize(count);
	obstacleBrakeLights.resize(count);
	blinkerInfo.resize(count);

	for (int i = 0; i < count; i++)
	{
		obstacleID[i].resize(4);
		obstacleLane[i].resize(4);
		CIPVFlags[i].resize(4);
		cutInAndOut[i].resize(4);
		obstacleLength[i].resize(4);
		obstacleWidth[i].resize(4);
		obstacle_Type[i].resize(4);
		obstacleStatus[i].resize(4);
		obstaclePositionX[i].resize(4);
		obstaclePositionY[i].resize(4);
		obstacleRelvel_X[i].resize(4);
		objectAccel_X[i].resize(4);
		obstacleScaleChange[i].resize(4);
		obstacleAngleRate[i].resize(4);
		obstacleAngle[i].resize(4);
		obstacleBrakeLights[i].resize(4);
		blinkerInfo[i].resize(4);
	}


	if (reader.parse(m_strJson, root))
	{
		for (int nIndex = 0; nIndex < count; nIndex++)
		{
			FCW_on.push_back(root["frame"][nIndex]["info"]["FCW_on"].asBool());
			FailSafe.push_back(root["frame"][nIndex]["info"]["FailSafe"].asBool());
			Fail_safe.push_back(root["frame"][nIndex]["info"]["Fail_safe"].asString());
			Tamper_Alert.push_back(root["frame"][nIndex]["info"]["Tamper_Alert"].asBool());
			HW_waring_level.push_back(root["frame"][nIndex]["info"]["HW_waring_level"].asString());
			LeftCloseRangCutIn.push_back(root["frame"][nIndex]["info"]["LeftCloseRangCutIn"].asBool());
			PCW_PedDZ.push_back(root["frame"][nIndex]["info"]["PCW_PedDZ"].asString());
			RightCloseRangCutIn.push_back(root["frame"][nIndex]["info"]["RightCloseRangCutIn"].asBool());
			TSR_warning_level.push_back(root["frame"][nIndex]["info"]["TSR_warning_level"].asString());
			closeCar.push_back(root["frame"][nIndex]["info"]["closeCar"].asBool());
			headway_mesurement.push_back(root["frame"][nIndex]["info"]["headway_mesurement"].asDouble());
			headway_valid.push_back(root["frame"][nIndex]["info"]["headway_valid"].asBool());
			numberOfObstacles.push_back(root["frame"][nIndex]["info"]["numberOfObstacles"].asInt());
			selfSpeed.push_back(root["frame"][nIndex]["info"]["selfSpeed"].asInt());
			time_indicator.push_back(root["frame"][nIndex]["info"]["time_indicator"].asString());

			for (int i = 0; i < 4; i++)
			{
				obj = "obj_" + std::to_string(i);
				int a = root["frame"][nIndex][obj]["obstacleID"].asInt();
				obstacleID[nIndex][i]=root["frame"][nIndex][obj]["obstacleID"].asInt();
				obstacleLane[nIndex][i]=root["frame"][nIndex][obj]["obstacleLane"].asString();
				CIPVFlags[nIndex][i]=root["frame"][nIndex][obj]["CIPVFlags"].asBool();
				cutInAndOut[nIndex][i]=root["frame"][nIndex][obj]["cutInAndOut"].asString();
				obstacleLength[nIndex][i]=root["frame"][nIndex][obj]["obstacleLength"].asDouble();
				obstacleWidth[nIndex][i]=root["frame"][nIndex][obj]["obstacleWidth"].asDouble();
				obstacle_Type[nIndex][i]=root["frame"][nIndex][obj]["obstacle_Type"].asString();
				obstacleStatus[nIndex][i]=root["frame"][nIndex][obj]["obstacleStatus"].asString();
				obstaclePositionX[nIndex][i]=root["frame"][nIndex][obj]["obstaclePositionX"].asDouble();
				obstaclePositionY[nIndex][i]=root["frame"][nIndex][obj]["obstaclePositionY"].asDouble();
				obstacleRelvel_X[nIndex][i] = root["frame"][nIndex][obj]["obstacleRelvel_X"].asDouble();
				objectAccel_X[nIndex][i]=root["frame"][nIndex][obj]["objectAccel_X"].asDouble();
				obstacleScaleChange[nIndex][i]=root["frame"][nIndex][obj]["obstacleScaleChange"].asDouble();
				obstacleAngleRate[nIndex][i]=root["frame"][nIndex][obj]["obstacleAngleRate"].asDouble();
				obstacleAngle[nIndex][i]=root["frame"][nIndex][obj]["obstacleAngle"].asDouble();
				obstacleBrakeLights[nIndex][i]=root["frame"][nIndex][obj]["obstacleBrakeLights"].asBool();
				blinkerInfo[nIndex][i]=root["frame"][nIndex]["info"][obj].asInt();
			}


			//bool FCW_on = root["frame"][nIndex]["info"]["FCW_on"].asBool();
			//bool FailSafe = root["frame"][nIndex]["info"]["FailSafe"].asBool();
			//std::string Fail_safe = root["frame"][nIndex]["info"]["Fail_safe"].asString();
			//bool Tamper_Alert = root["frame"][nIndex]["info"]["Tamper_Alert"].asBool();
			//std::string HW_waring_level = root["frame"][nIndex]["info"]["HW_waring_level"].asString();
			//bool LeftCloseRangCutIn = root["frame"][nIndex]["info"]["LeftCloseRangCutIn"].asBool();
			//std::string	PCW_PedDZ = root["frame"][nIndex]["info"]["PCW_PedDZ"].asString();
			//bool RightCloseRangCutIn = root["frame"][nIndex]["info"]["RightCloseRangCutIn"].asBool();
			//std::string TSR_warning_level = root["frame"][nIndex]["info"]["TSR_warning_level"].asString();
			//bool closeCar = root["frame"][nIndex]["info"]["closeCar"].asBool();
			//double	headway_mesurement = root["frame"][nIndex]["info"]["headway_mesurement"].asDouble();
			//bool headway_valid = root["frame"][nIndex]["info"]["headway_valid"].asBool();
			//int numberOfObstacles = root["frame"][nIndex]["info"]["numberOfObstacles"].asInt();
			//int selfSpeed = root["frame"][nIndex]["info"]["selfSpeed"].asInt();
			//std::string	time_indicator = root["frame"][nIndex]["info"]["time_indicator"].asString();


			//int obstacleID = root["frame"][nIndex][obj]["obstacleID"].asInt();
			//std::string obstacleLane = root["frame"][nIndex][obj]["obstacleLane"].asString();
			//bool CIPVFlags = root["frame"][nIndex][obj]["CIPVFlags"].asBool();
			//std::string cutInAndOut = root["frame"][nIndex][obj]["cutInAndOut"].asString();
			//double obstacleLength = root["frame"][nIndex][obj]["obstacleLength"].asDouble();
			//double	obstacleWidth = root["frame"][nIndex][obj]["obstacleWidth"].asDouble();
			//std::string obstacle_Type = root["frame"][nIndex][obj]["obstacle_Type"].asString();
			//std::string obstacleStatus = root["frame"][nIndex][obj]["obstacleStatus"].asString();
			//double obstaclePositionX = root["frame"][nIndex][obj]["obstaclePositionX"].asDouble();
			//double obstaclePositionY = root["frame"][nIndex][obj]["obstaclePositionY"].asDouble();
			//double	obstacleRelvel_X = root["frame"][nIndex][obj]["obstacleRelvel_X"].asDouble();
			//double objectAccel_X = root["frame"][nIndex][obj]["objectAccel_X"].asDouble();
			//double obstacleScaleChange = root["frame"][nIndex][obj]["obstacleScaleChange"].asDouble();
			//double obstacleAngleRate = root["frame"][nIndex][obj]["obstacleAngleRate"].asDouble();
			//double	obstacleAngle = root["frame"][nIndex][obj]["obstacleAngle"].asDouble();
			//bool	obstacleBrakeLights = root["frame"][nIndex][obj]["obstacleBrakeLights"].asBool();
			//int	blinkerInfo = root["frame"][nIndex]["info"][obj].asInt();
		}

	}

	if (!gotoFrameCan(0))
	{
		ui->lE_CANFilePath->clear();
		QMessageBox::about(NULL, "提示", "CAN文件打开失败!");
	}	
}

void Widget::onButtonClicked(QAbstractButton * btn)
{
	QList<QAbstractButton*> list = m_pButtonGroup->buttons();
	for (QAbstractButton *pButton : list)
	{
		if (pButton->isChecked())
		{
			if (pButton->text() == "实时播放")
			{
				m_realTimeFlag = true;
				setRealtimePlayIconEnable(true);
				setVideoPlayIconEnable(false);
			}
			else if (pButton->text() == "回放")
			{
				m_realTimeFlag = false;
				setRealtimePlayIconEnable(false);
				setVideoPlayIconEnable(true);
			}

			recoveryStatus();
		}
	}
}

void Widget::slotUpdateDisplayMessage(const QList<DisplayAndWarningMsg>& displayMsgs)
{
    for (int i = 0 ; i < displayMsgs.size(); ++i)
    {
        qDebug() << displayMsgs.at(i).signalName << displayMsgs.at(i).value.trimmed() << displayMsgs.at(i).unit;

        auto iterCarStatus = std::find_if(carStatusObjs.begin(), carStatusObjs.end(), [=](const CarStatusObj& obj)
        {
            return obj.typeName == displayMsgs.at(i).signalName;
        });

        if(iterCarStatus != carStatusObjs.end())
        {
            QString value  = displayMsgs.at(i).value.trimmed();
            if(iterCarStatus->typeName == "PCW")
            {
                int levelValue = value.toInt();
                QString strValue;
                switch (levelValue)
                {
                case 0:
                    strValue = "无预警";
                    break;
                case 1:
                    strValue = "行人一级碰撞预警";
                    break;
                case 2:
                    strValue = "行人二级碰撞预警";
                    break;
                case 3:
                    strValue = "行人紧急制动";
                    break;
                }
                iterCarStatus->valueItem->setText(strValue);
                //iterCarStatus->valueItem->setBackgroundColor(Qt::red);
            }
            else if(iterCarStatus->typeName == "Vehicle_Detection_Switch")
            {
                int levelValue = value.toInt();
                QString strValue;
                switch (levelValue)
                {
                case 0:
                    strValue = "关闭";
                    break;
                case 1:
                    strValue = "开启";
                    break;
                }
                iterCarStatus->valueItem->setText(strValue);
            }
            else if(iterCarStatus->typeName == "FCW_Level")
            {
                int levelValue = value.toInt();
                QString strValue;
                switch (levelValue)
                {
                case 0:
                    strValue = "无预警";
                    break;
                case 1:
                    strValue = "预碰撞预警";
                    break;
                case 2:
                    strValue = "碰撞预警";
                    break;
                }
                iterCarStatus->valueItem->setText(strValue);
            }
            else if(iterCarStatus->typeName == "Vehicle_Distance_Monitoring")
            {
                int levelValue = value.toInt();
                QString strValue;
                QColor color;
                switch (levelValue)
                {
                case 0:
                    strValue = "未检测到前车";
                    color = QColor::fromRgb(255,255,255);
                    break;
                case 1:
                    strValue = "检测到前车，无预警";
                    color = QColor::fromRgb(255,255,255);
                    break;
                case 2:
                    strValue = "检测到前车，产生预警";
                    color = QColor::fromRgb(255,0,0);
                    break;
                }
                iterCarStatus->valueItem->setBackgroundColor(color);
                iterCarStatus->valueItem->setText(strValue);
            }
            else
            {
                iterCarStatus->valueItem->setText(displayMsgs.at(i).value.trimmed() + displayMsgs.at(i).unit);
            }
        }

        auto iterFaultCode = std::find_if(faultCodeObjs.begin(),faultCodeObjs.end(),[=](const FaultCodeObj& obj)
        {
            return obj.typeName == displayMsgs.at(i).signalName;
        });

        if(iterFaultCode != faultCodeObjs.end())
        {
            int value = displayMsgs.at(i).value.trimmed().toInt();
            if(value == 0)
            {
//                iterFaultCode->valueLabel->setStyleSheet("QLabel {background-color: rgb(0, 255, 0);}");
            }
            else
            {
                iterFaultCode->valueLabel->setStyleSheet("QLabel {background-color: rgb(255, 0, 0);}");
            }
        }
    }
}
