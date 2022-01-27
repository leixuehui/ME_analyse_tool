/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <Widget/MyLabel.h>
#include <Widget/TipsLabel.h>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *gB_CAN;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_StartCAN;
    QLabel *label_CanStatus;
    QPushButton *btn_analyzeFrameText;
    QGroupBox *gB_camera;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_18;
    QRadioButton *radio_camera;
    QSpacerItem *horizontalSpacer;
    QLabel *label_10;
    QComboBox *comboBox;
    QPushButton *btn_openCamera;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_19;
    QLineEdit *lE_videoSavePath;
    QPushButton *btn_videoSavePath;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_20;
    QLineEdit *lE_CANSavePath;
    QPushButton *btn_CANSavePath;
    QHBoxLayout *horizontalLayout_27;
    QPushButton *btn_startRecord;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_8;
    QLabel *label_recordTime;
    QRadioButton *radio_video;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_12;
    QLineEdit *lE_videoFilePath;
    QPushButton *btn_openVideoFile;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_13;
    QLineEdit *lE_CANFilePath;
    QPushButton *btn_openCANFile;
    QTableWidget *tableWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *CameraView;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_play;
    QSlider *videoSlider;
    QHBoxLayout *horizontalLayout_12;
    QLineEdit *lE_gotoFrame;
    QPushButton *btn_goto;
    QHBoxLayout *horizontalLayout_13;
    QTableWidget *tableWidget_ME_1;
    QTableWidget *tableWidget_ME_2;
    QTableWidget *tableWidget_ME_4;
    QTableWidget *tableWidget_ME_3;
    QVBoxLayout *verticalLayout_3;
    MyLabel *label_ObjectDisplay;
    QHBoxLayout *horizontalLayout_17;
    QHBoxLayout *horizontalLayout_16;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QComboBox *cB_X_Range;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QComboBox *cB_Y_Range;
    TipsLabel *label_tips;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1711, 867);
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gB_CAN = new QGroupBox(Widget);
        gB_CAN->setObjectName(QString::fromUtf8("gB_CAN"));
        verticalLayout_2 = new QVBoxLayout(gB_CAN);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btn_StartCAN = new QPushButton(gB_CAN);
        btn_StartCAN->setObjectName(QString::fromUtf8("btn_StartCAN"));

        horizontalLayout_2->addWidget(btn_StartCAN);

        label_CanStatus = new QLabel(gB_CAN);
        label_CanStatus->setObjectName(QString::fromUtf8("label_CanStatus"));
        label_CanStatus->setMinimumSize(QSize(75, 23));
        label_CanStatus->setMaximumSize(QSize(75, 23));
        label_CanStatus->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        label_CanStatus->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_CanStatus);

        btn_analyzeFrameText = new QPushButton(gB_CAN);
        btn_analyzeFrameText->setObjectName(QString::fromUtf8("btn_analyzeFrameText"));

        horizontalLayout_2->addWidget(btn_analyzeFrameText);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_7->addWidget(gB_CAN);

        gB_camera = new QGroupBox(Widget);
        gB_camera->setObjectName(QString::fromUtf8("gB_camera"));
        verticalLayout_5 = new QVBoxLayout(gB_camera);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        radio_camera = new QRadioButton(gB_camera);
        radio_camera->setObjectName(QString::fromUtf8("radio_camera"));

        horizontalLayout_18->addWidget(radio_camera);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer);

        label_10 = new QLabel(gB_camera);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_18->addWidget(label_10);

        comboBox = new QComboBox(gB_camera);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_18->addWidget(comboBox);


        verticalLayout_5->addLayout(horizontalLayout_18);

        btn_openCamera = new QPushButton(gB_camera);
        btn_openCamera->setObjectName(QString::fromUtf8("btn_openCamera"));

        verticalLayout_5->addWidget(btn_openCamera);

        groupBox_2 = new QGroupBox(gB_camera);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        lE_videoSavePath = new QLineEdit(groupBox_2);
        lE_videoSavePath->setObjectName(QString::fromUtf8("lE_videoSavePath"));

        horizontalLayout_19->addWidget(lE_videoSavePath);

        btn_videoSavePath = new QPushButton(groupBox_2);
        btn_videoSavePath->setObjectName(QString::fromUtf8("btn_videoSavePath"));

        horizontalLayout_19->addWidget(btn_videoSavePath);


        gridLayout->addLayout(horizontalLayout_19, 1, 0, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 2, 0, 1, 1);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        lE_CANSavePath = new QLineEdit(groupBox_2);
        lE_CANSavePath->setObjectName(QString::fromUtf8("lE_CANSavePath"));

        horizontalLayout_20->addWidget(lE_CANSavePath);

        btn_CANSavePath = new QPushButton(groupBox_2);
        btn_CANSavePath->setObjectName(QString::fromUtf8("btn_CANSavePath"));

        horizontalLayout_20->addWidget(btn_CANSavePath);


        gridLayout->addLayout(horizontalLayout_20, 3, 0, 1, 1);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(20);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        btn_startRecord = new QPushButton(groupBox_2);
        btn_startRecord->setObjectName(QString::fromUtf8("btn_startRecord"));

        horizontalLayout_27->addWidget(btn_startRecord);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(20);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_15->addWidget(label_8);

        label_recordTime = new QLabel(groupBox_2);
        label_recordTime->setObjectName(QString::fromUtf8("label_recordTime"));

        horizontalLayout_15->addWidget(label_recordTime);

        horizontalLayout_15->setStretch(0, 1);
        horizontalLayout_15->setStretch(1, 3);

        horizontalLayout_27->addLayout(horizontalLayout_15);


        gridLayout->addLayout(horizontalLayout_27, 4, 0, 1, 1);


        verticalLayout_5->addWidget(groupBox_2);

        radio_video = new QRadioButton(gB_camera);
        radio_video->setObjectName(QString::fromUtf8("radio_video"));

        verticalLayout_5->addWidget(radio_video);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_12 = new QLabel(gB_camera);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_11->addWidget(label_12);

        lE_videoFilePath = new QLineEdit(gB_camera);
        lE_videoFilePath->setObjectName(QString::fromUtf8("lE_videoFilePath"));

        horizontalLayout_11->addWidget(lE_videoFilePath);

        btn_openVideoFile = new QPushButton(gB_camera);
        btn_openVideoFile->setObjectName(QString::fromUtf8("btn_openVideoFile"));

        horizontalLayout_11->addWidget(btn_openVideoFile);


        verticalLayout_5->addLayout(horizontalLayout_11);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(-1, 0, -1, -1);
        label_13 = new QLabel(gB_camera);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_28->addWidget(label_13);

        lE_CANFilePath = new QLineEdit(gB_camera);
        lE_CANFilePath->setObjectName(QString::fromUtf8("lE_CANFilePath"));

        horizontalLayout_28->addWidget(lE_CANFilePath);

        btn_openCANFile = new QPushButton(gB_camera);
        btn_openCANFile->setObjectName(QString::fromUtf8("btn_openCANFile"));

        horizontalLayout_28->addWidget(btn_openCANFile);


        verticalLayout_5->addLayout(horizontalLayout_28);


        verticalLayout_7->addWidget(gB_camera);

        tableWidget = new QTableWidget(Widget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 17)
            tableWidget->setRowCount(17);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(10, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(11, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(12, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(13, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(14, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(15, __qtablewidgetitem17);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8(""));
        tableWidget->setRowCount(17);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(150);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(10);
        tableWidget->verticalHeader()->setDefaultSectionSize(25);

        verticalLayout_7->addWidget(tableWidget);

        verticalLayout_7->setStretch(1, 1);
        verticalLayout_7->setStretch(2, 3);

        horizontalLayout_14->addLayout(verticalLayout_7);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        CameraView = new QLabel(Widget);
        CameraView->setObjectName(QString::fromUtf8("CameraView"));
        CameraView->setEnabled(true);
        CameraView->setMinimumSize(QSize(640, 360));
        CameraView->setMaximumSize(QSize(640, 360));

        verticalLayout_4->addWidget(CameraView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btn_play = new QPushButton(Widget);
        btn_play->setObjectName(QString::fromUtf8("btn_play"));

        horizontalLayout->addWidget(btn_play);

        videoSlider = new QSlider(Widget);
        videoSlider->setObjectName(QString::fromUtf8("videoSlider"));
        videoSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(videoSlider);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        lE_gotoFrame = new QLineEdit(Widget);
        lE_gotoFrame->setObjectName(QString::fromUtf8("lE_gotoFrame"));

        horizontalLayout_12->addWidget(lE_gotoFrame);

        btn_goto = new QPushButton(Widget);
        btn_goto->setObjectName(QString::fromUtf8("btn_goto"));

        horizontalLayout_12->addWidget(btn_goto);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 1);

        horizontalLayout->addLayout(horizontalLayout_12);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 15);
        horizontalLayout->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout->addLayout(verticalLayout_4);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        tableWidget_ME_1 = new QTableWidget(Widget);
        if (tableWidget_ME_1->columnCount() < 2)
            tableWidget_ME_1->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setBackground(QColor(245, 245, 245));
        tableWidget_ME_1->setHorizontalHeaderItem(0, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setBackground(QColor(245, 245, 245));
        tableWidget_ME_1->setHorizontalHeaderItem(1, __qtablewidgetitem19);
        if (tableWidget_ME_1->rowCount() < 19)
            tableWidget_ME_1->setRowCount(19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(4, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(5, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(6, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(7, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(8, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(9, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(10, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(11, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(12, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(13, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(14, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(15, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(16, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(17, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_ME_1->setVerticalHeaderItem(18, __qtablewidgetitem38);
        tableWidget_ME_1->setObjectName(QString::fromUtf8("tableWidget_ME_1"));
        tableWidget_ME_1->horizontalHeader()->setVisible(false);
        tableWidget_ME_1->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_ME_1->horizontalHeader()->setMinimumSectionSize(30);
        tableWidget_ME_1->horizontalHeader()->setDefaultSectionSize(119);
        tableWidget_ME_1->verticalHeader()->setVisible(true);
        tableWidget_ME_1->verticalHeader()->setMinimumSectionSize(15);
        tableWidget_ME_1->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout_13->addWidget(tableWidget_ME_1);

        tableWidget_ME_2 = new QTableWidget(Widget);
        if (tableWidget_ME_2->columnCount() < 2)
            tableWidget_ME_2->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        __qtablewidgetitem39->setBackground(QColor(245, 245, 245));
        tableWidget_ME_2->setHorizontalHeaderItem(0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        __qtablewidgetitem40->setBackground(QColor(245, 245, 245));
        tableWidget_ME_2->setHorizontalHeaderItem(1, __qtablewidgetitem40);
        if (tableWidget_ME_2->rowCount() < 19)
            tableWidget_ME_2->setRowCount(19);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(0, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(1, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(2, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(3, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(4, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(5, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(6, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(7, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(8, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(9, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(10, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(11, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(12, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(13, __qtablewidgetitem54);
        QTableWidgetItem *__qtablewidgetitem55 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(14, __qtablewidgetitem55);
        QTableWidgetItem *__qtablewidgetitem56 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(15, __qtablewidgetitem56);
        QTableWidgetItem *__qtablewidgetitem57 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(16, __qtablewidgetitem57);
        QTableWidgetItem *__qtablewidgetitem58 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(17, __qtablewidgetitem58);
        QTableWidgetItem *__qtablewidgetitem59 = new QTableWidgetItem();
        tableWidget_ME_2->setVerticalHeaderItem(18, __qtablewidgetitem59);
        tableWidget_ME_2->setObjectName(QString::fromUtf8("tableWidget_ME_2"));
        tableWidget_ME_2->horizontalHeader()->setVisible(false);
        tableWidget_ME_2->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_ME_2->horizontalHeader()->setMinimumSectionSize(30);
        tableWidget_ME_2->horizontalHeader()->setDefaultSectionSize(119);
        tableWidget_ME_2->verticalHeader()->setMinimumSectionSize(15);
        tableWidget_ME_2->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout_13->addWidget(tableWidget_ME_2);

        tableWidget_ME_4 = new QTableWidget(Widget);
        if (tableWidget_ME_4->columnCount() < 2)
            tableWidget_ME_4->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem60 = new QTableWidgetItem();
        __qtablewidgetitem60->setBackground(QColor(245, 245, 245));
        tableWidget_ME_4->setHorizontalHeaderItem(0, __qtablewidgetitem60);
        QTableWidgetItem *__qtablewidgetitem61 = new QTableWidgetItem();
        __qtablewidgetitem61->setBackground(QColor(245, 245, 245));
        tableWidget_ME_4->setHorizontalHeaderItem(1, __qtablewidgetitem61);
        if (tableWidget_ME_4->rowCount() < 19)
            tableWidget_ME_4->setRowCount(19);
        QTableWidgetItem *__qtablewidgetitem62 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(0, __qtablewidgetitem62);
        QTableWidgetItem *__qtablewidgetitem63 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(1, __qtablewidgetitem63);
        QTableWidgetItem *__qtablewidgetitem64 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(2, __qtablewidgetitem64);
        QTableWidgetItem *__qtablewidgetitem65 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(3, __qtablewidgetitem65);
        QTableWidgetItem *__qtablewidgetitem66 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(4, __qtablewidgetitem66);
        QTableWidgetItem *__qtablewidgetitem67 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(5, __qtablewidgetitem67);
        QTableWidgetItem *__qtablewidgetitem68 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(6, __qtablewidgetitem68);
        QTableWidgetItem *__qtablewidgetitem69 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(7, __qtablewidgetitem69);
        QTableWidgetItem *__qtablewidgetitem70 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(8, __qtablewidgetitem70);
        QTableWidgetItem *__qtablewidgetitem71 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(9, __qtablewidgetitem71);
        QTableWidgetItem *__qtablewidgetitem72 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(10, __qtablewidgetitem72);
        QTableWidgetItem *__qtablewidgetitem73 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(11, __qtablewidgetitem73);
        QTableWidgetItem *__qtablewidgetitem74 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(12, __qtablewidgetitem74);
        QTableWidgetItem *__qtablewidgetitem75 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(13, __qtablewidgetitem75);
        QTableWidgetItem *__qtablewidgetitem76 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(14, __qtablewidgetitem76);
        QTableWidgetItem *__qtablewidgetitem77 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(15, __qtablewidgetitem77);
        QTableWidgetItem *__qtablewidgetitem78 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(16, __qtablewidgetitem78);
        QTableWidgetItem *__qtablewidgetitem79 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(17, __qtablewidgetitem79);
        QTableWidgetItem *__qtablewidgetitem80 = new QTableWidgetItem();
        tableWidget_ME_4->setVerticalHeaderItem(18, __qtablewidgetitem80);
        tableWidget_ME_4->setObjectName(QString::fromUtf8("tableWidget_ME_4"));
        tableWidget_ME_4->horizontalHeader()->setVisible(false);
        tableWidget_ME_4->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_ME_4->horizontalHeader()->setMinimumSectionSize(30);
        tableWidget_ME_4->horizontalHeader()->setDefaultSectionSize(119);
        tableWidget_ME_4->verticalHeader()->setMinimumSectionSize(15);
        tableWidget_ME_4->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout_13->addWidget(tableWidget_ME_4);

        tableWidget_ME_3 = new QTableWidget(Widget);
        if (tableWidget_ME_3->columnCount() < 2)
            tableWidget_ME_3->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem81 = new QTableWidgetItem();
        __qtablewidgetitem81->setBackground(QColor(245, 245, 245));
        tableWidget_ME_3->setHorizontalHeaderItem(0, __qtablewidgetitem81);
        QTableWidgetItem *__qtablewidgetitem82 = new QTableWidgetItem();
        __qtablewidgetitem82->setBackground(QColor(245, 245, 245));
        tableWidget_ME_3->setHorizontalHeaderItem(1, __qtablewidgetitem82);
        if (tableWidget_ME_3->rowCount() < 19)
            tableWidget_ME_3->setRowCount(19);
        QTableWidgetItem *__qtablewidgetitem83 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(0, __qtablewidgetitem83);
        QTableWidgetItem *__qtablewidgetitem84 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(1, __qtablewidgetitem84);
        QTableWidgetItem *__qtablewidgetitem85 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(2, __qtablewidgetitem85);
        QTableWidgetItem *__qtablewidgetitem86 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(3, __qtablewidgetitem86);
        QTableWidgetItem *__qtablewidgetitem87 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(4, __qtablewidgetitem87);
        QTableWidgetItem *__qtablewidgetitem88 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(5, __qtablewidgetitem88);
        QTableWidgetItem *__qtablewidgetitem89 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(6, __qtablewidgetitem89);
        QTableWidgetItem *__qtablewidgetitem90 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(7, __qtablewidgetitem90);
        QTableWidgetItem *__qtablewidgetitem91 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(8, __qtablewidgetitem91);
        QTableWidgetItem *__qtablewidgetitem92 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(9, __qtablewidgetitem92);
        QTableWidgetItem *__qtablewidgetitem93 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(10, __qtablewidgetitem93);
        QTableWidgetItem *__qtablewidgetitem94 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(11, __qtablewidgetitem94);
        QTableWidgetItem *__qtablewidgetitem95 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(12, __qtablewidgetitem95);
        QTableWidgetItem *__qtablewidgetitem96 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(13, __qtablewidgetitem96);
        QTableWidgetItem *__qtablewidgetitem97 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(14, __qtablewidgetitem97);
        QTableWidgetItem *__qtablewidgetitem98 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(15, __qtablewidgetitem98);
        QTableWidgetItem *__qtablewidgetitem99 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(16, __qtablewidgetitem99);
        QTableWidgetItem *__qtablewidgetitem100 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(17, __qtablewidgetitem100);
        QTableWidgetItem *__qtablewidgetitem101 = new QTableWidgetItem();
        tableWidget_ME_3->setVerticalHeaderItem(18, __qtablewidgetitem101);
        tableWidget_ME_3->setObjectName(QString::fromUtf8("tableWidget_ME_3"));
        tableWidget_ME_3->horizontalHeader()->setVisible(false);
        tableWidget_ME_3->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget_ME_3->horizontalHeader()->setMinimumSectionSize(30);
        tableWidget_ME_3->horizontalHeader()->setDefaultSectionSize(119);
        tableWidget_ME_3->verticalHeader()->setMinimumSectionSize(15);
        tableWidget_ME_3->verticalHeader()->setDefaultSectionSize(20);

        horizontalLayout_13->addWidget(tableWidget_ME_3);


        verticalLayout->addLayout(horizontalLayout_13);

        verticalLayout->setStretch(0, 2);

        horizontalLayout_14->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_ObjectDisplay = new MyLabel(Widget);
        label_ObjectDisplay->setObjectName(QString::fromUtf8("label_ObjectDisplay"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_ObjectDisplay->sizePolicy().hasHeightForWidth());
        label_ObjectDisplay->setSizePolicy(sizePolicy);
        label_ObjectDisplay->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_3->addWidget(label_ObjectDisplay);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_9->addWidget(label_5);

        cB_X_Range = new QComboBox(Widget);
        cB_X_Range->setObjectName(QString::fromUtf8("cB_X_Range"));

        horizontalLayout_9->addWidget(cB_X_Range);


        horizontalLayout_16->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_7 = new QLabel(Widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_10->addWidget(label_7);

        cB_Y_Range = new QComboBox(Widget);
        cB_Y_Range->setObjectName(QString::fromUtf8("cB_Y_Range"));

        horizontalLayout_10->addWidget(cB_Y_Range);


        horizontalLayout_16->addLayout(horizontalLayout_10);


        horizontalLayout_17->addLayout(horizontalLayout_16);

        label_tips = new TipsLabel(Widget);
        label_tips->setObjectName(QString::fromUtf8("label_tips"));
        label_tips->setMinimumSize(QSize(0, 0));

        horizontalLayout_17->addWidget(label_tips);

        horizontalLayout_17->setStretch(0, 1);
        horizontalLayout_17->setStretch(1, 6);

        verticalLayout_3->addLayout(horizontalLayout_17);

        verticalLayout_3->setStretch(0, 15);
        verticalLayout_3->setStretch(1, 1);

        horizontalLayout_14->addLayout(verticalLayout_3);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 4);
        horizontalLayout_14->setStretch(2, 2);

        gridLayout_2->addLayout(horizontalLayout_14, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "ArcADASCanAnalyzeTools", nullptr));
        gB_CAN->setTitle(QApplication::translate("Widget", "CAN", nullptr));
        btn_StartCAN->setText(QApplication::translate("Widget", "\345\220\257\345\212\250", nullptr));
        label_CanStatus->setText(QApplication::translate("Widget", "\350\256\276\345\244\207\346\234\252\350\277\236\346\216\245", nullptr));
        btn_analyzeFrameText->setText(QApplication::translate("Widget", "\350\247\243\346\236\220\346\226\207\346\234\254", nullptr));
        gB_camera->setTitle(QApplication::translate("Widget", "\350\247\206\351\242\221", nullptr));
        radio_camera->setText(QApplication::translate("Widget", "\345\256\236\346\227\266\346\222\255\346\224\276", nullptr));
        label_10->setText(QApplication::translate("Widget", "\346\221\204\345\203\217\345\244\264\357\274\232", nullptr));
        comboBox->setItemText(0, QApplication::translate("Widget", "0", nullptr));
        comboBox->setItemText(1, QApplication::translate("Widget", "1", nullptr));

        btn_openCamera->setText(QApplication::translate("Widget", "\345\274\200\345\220\257\346\221\204\345\203\217\345\244\264", nullptr));
        groupBox_2->setTitle(QApplication::translate("Widget", "\346\223\215\344\275\234\346\240\217", nullptr));
        label_6->setText(QApplication::translate("Widget", "\350\247\206\351\242\221\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", nullptr));
        btn_videoSavePath->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        label_9->setText(QApplication::translate("Widget", "CAN\346\225\260\346\215\256\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", nullptr));
        btn_CANSavePath->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        btn_startRecord->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\345\275\225\345\210\266", nullptr));
        label_8->setText(QApplication::translate("Widget", "\345\275\225\345\210\266\346\227\266\351\225\277\357\274\232", nullptr));
        label_recordTime->setText(QApplication::translate("Widget", "00\357\274\23200\357\274\23200", nullptr));
        radio_video->setText(QApplication::translate("Widget", "\345\233\236\346\224\276", nullptr));
        label_12->setText(QApplication::translate("Widget", "\350\247\206\351\242\221\357\274\232", nullptr));
        btn_openVideoFile->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        label_13->setText(QApplication::translate("Widget", "CAN\357\274\232", nullptr));
        btn_openCANFile->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "\345\217\202\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Widget", "\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("Widget", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("Widget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("Widget", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("Widget", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("Widget", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem7->setText(QApplication::translate("Widget", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem8->setText(QApplication::translate("Widget", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem9->setText(QApplication::translate("Widget", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem10->setText(QApplication::translate("Widget", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem11->setText(QApplication::translate("Widget", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(10);
        ___qtablewidgetitem12->setText(QApplication::translate("Widget", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(11);
        ___qtablewidgetitem13->setText(QApplication::translate("Widget", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(12);
        ___qtablewidgetitem14->setText(QApplication::translate("Widget", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(13);
        ___qtablewidgetitem15->setText(QApplication::translate("Widget", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->verticalHeaderItem(14);
        ___qtablewidgetitem16->setText(QApplication::translate("Widget", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->verticalHeaderItem(15);
        ___qtablewidgetitem17->setText(QApplication::translate("Widget", "15", nullptr));
        CameraView->setText(QString());
        btn_play->setText(QApplication::translate("Widget", "\345\274\200\345\247\213\346\222\255\346\224\276", nullptr));
        btn_goto->setText(QApplication::translate("Widget", "\350\267\263\350\275\254", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget_ME_1->horizontalHeaderItem(0);
        ___qtablewidgetitem18->setText(QApplication::translate("Widget", "\345\217\202\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget_ME_1->horizontalHeaderItem(1);
        ___qtablewidgetitem19->setText(QApplication::translate("Widget", "\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget_ME_1->verticalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("Widget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget_ME_1->verticalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("Widget", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget_ME_1->verticalHeaderItem(2);
        ___qtablewidgetitem22->setText(QApplication::translate("Widget", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget_ME_1->verticalHeaderItem(3);
        ___qtablewidgetitem23->setText(QApplication::translate("Widget", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget_ME_1->verticalHeaderItem(4);
        ___qtablewidgetitem24->setText(QApplication::translate("Widget", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget_ME_1->verticalHeaderItem(5);
        ___qtablewidgetitem25->setText(QApplication::translate("Widget", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget_ME_1->verticalHeaderItem(6);
        ___qtablewidgetitem26->setText(QApplication::translate("Widget", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget_ME_1->verticalHeaderItem(7);
        ___qtablewidgetitem27->setText(QApplication::translate("Widget", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget_ME_1->verticalHeaderItem(8);
        ___qtablewidgetitem28->setText(QApplication::translate("Widget", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget_ME_1->verticalHeaderItem(9);
        ___qtablewidgetitem29->setText(QApplication::translate("Widget", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget_ME_1->verticalHeaderItem(10);
        ___qtablewidgetitem30->setText(QApplication::translate("Widget", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget_ME_1->verticalHeaderItem(11);
        ___qtablewidgetitem31->setText(QApplication::translate("Widget", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget_ME_1->verticalHeaderItem(12);
        ___qtablewidgetitem32->setText(QApplication::translate("Widget", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget_ME_1->verticalHeaderItem(13);
        ___qtablewidgetitem33->setText(QApplication::translate("Widget", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_ME_1->verticalHeaderItem(14);
        ___qtablewidgetitem34->setText(QApplication::translate("Widget", "15", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_ME_1->verticalHeaderItem(15);
        ___qtablewidgetitem35->setText(QApplication::translate("Widget", "16", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_ME_1->verticalHeaderItem(16);
        ___qtablewidgetitem36->setText(QApplication::translate("Widget", "17", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_ME_1->verticalHeaderItem(17);
        ___qtablewidgetitem37->setText(QApplication::translate("Widget", "18", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_ME_1->verticalHeaderItem(18);
        ___qtablewidgetitem38->setText(QApplication::translate("Widget", "19", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_ME_2->horizontalHeaderItem(0);
        ___qtablewidgetitem39->setText(QApplication::translate("Widget", "\345\217\202\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_ME_2->horizontalHeaderItem(1);
        ___qtablewidgetitem40->setText(QApplication::translate("Widget", "\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_ME_2->verticalHeaderItem(0);
        ___qtablewidgetitem41->setText(QApplication::translate("Widget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_ME_2->verticalHeaderItem(1);
        ___qtablewidgetitem42->setText(QApplication::translate("Widget", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_ME_2->verticalHeaderItem(2);
        ___qtablewidgetitem43->setText(QApplication::translate("Widget", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_ME_2->verticalHeaderItem(3);
        ___qtablewidgetitem44->setText(QApplication::translate("Widget", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_ME_2->verticalHeaderItem(4);
        ___qtablewidgetitem45->setText(QApplication::translate("Widget", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_ME_2->verticalHeaderItem(5);
        ___qtablewidgetitem46->setText(QApplication::translate("Widget", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget_ME_2->verticalHeaderItem(6);
        ___qtablewidgetitem47->setText(QApplication::translate("Widget", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget_ME_2->verticalHeaderItem(7);
        ___qtablewidgetitem48->setText(QApplication::translate("Widget", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget_ME_2->verticalHeaderItem(8);
        ___qtablewidgetitem49->setText(QApplication::translate("Widget", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget_ME_2->verticalHeaderItem(9);
        ___qtablewidgetitem50->setText(QApplication::translate("Widget", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget_ME_2->verticalHeaderItem(10);
        ___qtablewidgetitem51->setText(QApplication::translate("Widget", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget_ME_2->verticalHeaderItem(11);
        ___qtablewidgetitem52->setText(QApplication::translate("Widget", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget_ME_2->verticalHeaderItem(12);
        ___qtablewidgetitem53->setText(QApplication::translate("Widget", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget_ME_2->verticalHeaderItem(13);
        ___qtablewidgetitem54->setText(QApplication::translate("Widget", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem55 = tableWidget_ME_2->verticalHeaderItem(14);
        ___qtablewidgetitem55->setText(QApplication::translate("Widget", "15", nullptr));
        QTableWidgetItem *___qtablewidgetitem56 = tableWidget_ME_2->verticalHeaderItem(15);
        ___qtablewidgetitem56->setText(QApplication::translate("Widget", "16", nullptr));
        QTableWidgetItem *___qtablewidgetitem57 = tableWidget_ME_2->verticalHeaderItem(16);
        ___qtablewidgetitem57->setText(QApplication::translate("Widget", "17", nullptr));
        QTableWidgetItem *___qtablewidgetitem58 = tableWidget_ME_2->verticalHeaderItem(17);
        ___qtablewidgetitem58->setText(QApplication::translate("Widget", "18", nullptr));
        QTableWidgetItem *___qtablewidgetitem59 = tableWidget_ME_2->verticalHeaderItem(18);
        ___qtablewidgetitem59->setText(QApplication::translate("Widget", "19", nullptr));
        QTableWidgetItem *___qtablewidgetitem60 = tableWidget_ME_4->horizontalHeaderItem(0);
        ___qtablewidgetitem60->setText(QApplication::translate("Widget", "\345\217\202\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem61 = tableWidget_ME_4->horizontalHeaderItem(1);
        ___qtablewidgetitem61->setText(QApplication::translate("Widget", "\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem62 = tableWidget_ME_4->verticalHeaderItem(0);
        ___qtablewidgetitem62->setText(QApplication::translate("Widget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem63 = tableWidget_ME_4->verticalHeaderItem(1);
        ___qtablewidgetitem63->setText(QApplication::translate("Widget", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem64 = tableWidget_ME_4->verticalHeaderItem(2);
        ___qtablewidgetitem64->setText(QApplication::translate("Widget", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem65 = tableWidget_ME_4->verticalHeaderItem(3);
        ___qtablewidgetitem65->setText(QApplication::translate("Widget", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem66 = tableWidget_ME_4->verticalHeaderItem(4);
        ___qtablewidgetitem66->setText(QApplication::translate("Widget", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem67 = tableWidget_ME_4->verticalHeaderItem(5);
        ___qtablewidgetitem67->setText(QApplication::translate("Widget", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem68 = tableWidget_ME_4->verticalHeaderItem(6);
        ___qtablewidgetitem68->setText(QApplication::translate("Widget", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem69 = tableWidget_ME_4->verticalHeaderItem(7);
        ___qtablewidgetitem69->setText(QApplication::translate("Widget", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem70 = tableWidget_ME_4->verticalHeaderItem(8);
        ___qtablewidgetitem70->setText(QApplication::translate("Widget", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem71 = tableWidget_ME_4->verticalHeaderItem(9);
        ___qtablewidgetitem71->setText(QApplication::translate("Widget", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem72 = tableWidget_ME_4->verticalHeaderItem(10);
        ___qtablewidgetitem72->setText(QApplication::translate("Widget", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem73 = tableWidget_ME_4->verticalHeaderItem(11);
        ___qtablewidgetitem73->setText(QApplication::translate("Widget", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem74 = tableWidget_ME_4->verticalHeaderItem(12);
        ___qtablewidgetitem74->setText(QApplication::translate("Widget", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem75 = tableWidget_ME_4->verticalHeaderItem(13);
        ___qtablewidgetitem75->setText(QApplication::translate("Widget", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem76 = tableWidget_ME_4->verticalHeaderItem(14);
        ___qtablewidgetitem76->setText(QApplication::translate("Widget", "15", nullptr));
        QTableWidgetItem *___qtablewidgetitem77 = tableWidget_ME_4->verticalHeaderItem(15);
        ___qtablewidgetitem77->setText(QApplication::translate("Widget", "16", nullptr));
        QTableWidgetItem *___qtablewidgetitem78 = tableWidget_ME_4->verticalHeaderItem(16);
        ___qtablewidgetitem78->setText(QApplication::translate("Widget", "17", nullptr));
        QTableWidgetItem *___qtablewidgetitem79 = tableWidget_ME_4->verticalHeaderItem(17);
        ___qtablewidgetitem79->setText(QApplication::translate("Widget", "18", nullptr));
        QTableWidgetItem *___qtablewidgetitem80 = tableWidget_ME_4->verticalHeaderItem(18);
        ___qtablewidgetitem80->setText(QApplication::translate("Widget", "19", nullptr));
        QTableWidgetItem *___qtablewidgetitem81 = tableWidget_ME_3->horizontalHeaderItem(0);
        ___qtablewidgetitem81->setText(QApplication::translate("Widget", "\345\217\202\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem82 = tableWidget_ME_3->horizontalHeaderItem(1);
        ___qtablewidgetitem82->setText(QApplication::translate("Widget", "\345\200\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem83 = tableWidget_ME_3->verticalHeaderItem(0);
        ___qtablewidgetitem83->setText(QApplication::translate("Widget", "1", nullptr));
        QTableWidgetItem *___qtablewidgetitem84 = tableWidget_ME_3->verticalHeaderItem(1);
        ___qtablewidgetitem84->setText(QApplication::translate("Widget", "2", nullptr));
        QTableWidgetItem *___qtablewidgetitem85 = tableWidget_ME_3->verticalHeaderItem(2);
        ___qtablewidgetitem85->setText(QApplication::translate("Widget", "3", nullptr));
        QTableWidgetItem *___qtablewidgetitem86 = tableWidget_ME_3->verticalHeaderItem(3);
        ___qtablewidgetitem86->setText(QApplication::translate("Widget", "4", nullptr));
        QTableWidgetItem *___qtablewidgetitem87 = tableWidget_ME_3->verticalHeaderItem(4);
        ___qtablewidgetitem87->setText(QApplication::translate("Widget", "5", nullptr));
        QTableWidgetItem *___qtablewidgetitem88 = tableWidget_ME_3->verticalHeaderItem(5);
        ___qtablewidgetitem88->setText(QApplication::translate("Widget", "6", nullptr));
        QTableWidgetItem *___qtablewidgetitem89 = tableWidget_ME_3->verticalHeaderItem(6);
        ___qtablewidgetitem89->setText(QApplication::translate("Widget", "7", nullptr));
        QTableWidgetItem *___qtablewidgetitem90 = tableWidget_ME_3->verticalHeaderItem(7);
        ___qtablewidgetitem90->setText(QApplication::translate("Widget", "8", nullptr));
        QTableWidgetItem *___qtablewidgetitem91 = tableWidget_ME_3->verticalHeaderItem(8);
        ___qtablewidgetitem91->setText(QApplication::translate("Widget", "9", nullptr));
        QTableWidgetItem *___qtablewidgetitem92 = tableWidget_ME_3->verticalHeaderItem(9);
        ___qtablewidgetitem92->setText(QApplication::translate("Widget", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem93 = tableWidget_ME_3->verticalHeaderItem(10);
        ___qtablewidgetitem93->setText(QApplication::translate("Widget", "11", nullptr));
        QTableWidgetItem *___qtablewidgetitem94 = tableWidget_ME_3->verticalHeaderItem(11);
        ___qtablewidgetitem94->setText(QApplication::translate("Widget", "12", nullptr));
        QTableWidgetItem *___qtablewidgetitem95 = tableWidget_ME_3->verticalHeaderItem(12);
        ___qtablewidgetitem95->setText(QApplication::translate("Widget", "13", nullptr));
        QTableWidgetItem *___qtablewidgetitem96 = tableWidget_ME_3->verticalHeaderItem(13);
        ___qtablewidgetitem96->setText(QApplication::translate("Widget", "14", nullptr));
        QTableWidgetItem *___qtablewidgetitem97 = tableWidget_ME_3->verticalHeaderItem(14);
        ___qtablewidgetitem97->setText(QApplication::translate("Widget", "15", nullptr));
        QTableWidgetItem *___qtablewidgetitem98 = tableWidget_ME_3->verticalHeaderItem(15);
        ___qtablewidgetitem98->setText(QApplication::translate("Widget", "16", nullptr));
        QTableWidgetItem *___qtablewidgetitem99 = tableWidget_ME_3->verticalHeaderItem(16);
        ___qtablewidgetitem99->setText(QApplication::translate("Widget", "17", nullptr));
        QTableWidgetItem *___qtablewidgetitem100 = tableWidget_ME_3->verticalHeaderItem(17);
        ___qtablewidgetitem100->setText(QApplication::translate("Widget", "18", nullptr));
        QTableWidgetItem *___qtablewidgetitem101 = tableWidget_ME_3->verticalHeaderItem(18);
        ___qtablewidgetitem101->setText(QApplication::translate("Widget", "19", nullptr));
        label_ObjectDisplay->setText(QString());
        label_5->setText(QApplication::translate("Widget", "X\350\214\203\345\233\264\357\274\232", nullptr));
        label_7->setText(QApplication::translate("Widget", "Y\350\214\203\345\233\264\357\274\232", nullptr));
        label_tips->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
