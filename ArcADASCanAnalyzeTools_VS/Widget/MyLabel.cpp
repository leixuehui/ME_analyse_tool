#include "MyLabel.h"
#include "TipsLabel.h"

#include <QDebug>
#include <QPainter>
#include <QTime>

MyLabel::MyLabel(QWidget *parent):
    QLabel(parent)
{

}

MyLabel::~MyLabel()
{

}
//
//void MyLabel::genObstacleInfo(QString &obsInfo, const ObjInfo &obj)
//{
//    QTextStream stream(&obsInfo);
//    stream << QString("ID:") << obj.ID<<","
//           << TipsLabel::getObjNameByType(obj.type)
//           << QString(", X:") << QString::number(obj.PosX, 'f', 3) << QString("米")
//           << QString(", Y:") << QString::number(obj.PosY, 'f', 3) << QString("米")
//           << QString(", 宽度:") << QString::number(obj.Width, 'f', 3) << QString("米")
//           << QString(", 纵向加速度:") << QString::number(obj.RelValY, 'f', 3) << QString("米/秒平方");
//
//    stream << "\r\n";
//    stream.flush();
//}


void MyLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    paintCoordinateSystem(&painter);

    for(int i = 0; i< drawObjData_.objs.size();++i)
    {
        drawObject( &painter, &drawObjData_.objs.at(i), drawObjData_.mapObstacleDataB[i]);
    }

#if 0
    {
        QString obsInfo("");

        struct ObjInfo obj;
        obj.ID = 50;
        obj.type = 0x0;
        obj.PosX = 23;
        obj.PosY = 0;
        drawObject(&painter, &obj);
        genObstacleInfo(obsInfo, obj);

        obj.ID = 51;
        obj.type = 0x1;
        obj.PosX = 35;
        obj.PosY = 10;
        drawObject(&painter,&obj);
        genObstacleInfo(obsInfo, obj);

        obj.ID = 52;
        obj.type = 0x2;
        obj.PosX = -12.5;
        obj.PosY = 20;
        drawObject(&painter,&obj);
        genObstacleInfo(obsInfo, obj);

        obj.ID = 53;
        obj.type = 0x3;
        obj.PosX = -10;
        obj.PosY = 30;
        drawObject(&painter,&obj);
        genObstacleInfo(obsInfo, obj);

        obj.ID = 54;
        obj.type = 0x4;
        obj.PosX = 10;
        obj.PosY = 40;
        drawObject(&painter,&obj);
        genObstacleInfo(obsInfo, obj);

    }
#endif
}

void MyLabel::tranferDrawObjData(const ME_DeviceData & drawObjData, QString& obsInfo,QString& otherInfo)
{
    obsInfo += "共 " +QString::number(drawObjData.obstacleStatus.numberOfObstacles) + " 个障碍物 ";





 
    /*switch (drawObjData.statuInfo.driverStatus)
    {
    case 0:
        obsInfo += "未变道,";
        break;
    case 1:
        obsInfo += "左变道,";
        break;
    case 2:
        obsInfo += "右变道,";
        break;
    }*/

   /* switch (drawObjData.statuInfo.leftLaneStatus)
    {
    case 0:
        obsInfo += "无左车道线,";
        break;
    case 1:
        obsInfo += "检测到左车道线" + QString::number(drawObjData.statuInfo.leftLaneLength) + " m,";
        break;
    }*/

   /* switch (drawObjData.statuInfo.rightLaneStatus)
    {
    case 0:
        obsInfo += "无右车道线,";
        break;
    case 1:
        obsInfo += "检测到右车道线"+ QString::number(drawObjData.statuInfo.rightLaneLength) + " m,";
        break;
    }

    obsInfo += "计数器 " + QString::number(drawObjData.statuInfo.measCounter) + "\n";


    if(drawObjData.leftLaneAInfo.valid == 1)
    {
        QString leftLaneAInfoStr = "左车道线A ";
        switch (drawObjData.leftLaneAInfo.quality)
        {
        case 0:
        case 1:
            leftLaneAInfoStr += "低质量 ";
            break;
        case 2:
        case 3:
            leftLaneAInfoStr += "高质量 ";
            break;
        }

        switch (drawObjData.leftLaneAInfo.laneType)
        {
        case 0:
            leftLaneAInfoStr += "虚线 ";
            break;
        case 1:
            leftLaneAInfoStr += "实线 ";
            break;
        }

        leftLaneAInfoStr += "WidthMarking " + QString::number(drawObjData.leftLaneAInfo.widthMarking) + " ";
        leftLaneAInfoStr += "C0 " + QString::number(drawObjData.leftLaneAInfo.c0) + " ";
        leftLaneAInfoStr += "C1 " + QString::number(drawObjData.leftLaneAInfo.c1) + " ";

        otherInfo += leftLaneAInfoStr + "\n";
    }

    if(drawObjData.rightLaneAInfo.valid == 1)
    {
        QString rightLaneAInfoStr = "右车道线A ";
        switch (drawObjData.rightLaneAInfo.quality)
        {
        case 0:
        case 1:
            rightLaneAInfoStr += "低质量 ";
            break;
        case 2:
        case 3:
            rightLaneAInfoStr += "高质量 ";
            break;
        }

        switch (drawObjData.rightLaneAInfo.laneType)
        {
        case 0:
            rightLaneAInfoStr += "虚线 ";
            break;
        case 1:
            rightLaneAInfoStr += "实线 ";
            break;
        }

        rightLaneAInfoStr += "WidthMarking " + QString::number(drawObjData.rightLaneAInfo.widthMarking) + " ";
        rightLaneAInfoStr += "C0 " + QString::number(drawObjData.rightLaneAInfo.c0) + " ";
        rightLaneAInfoStr += "C1 " + QString::number(drawObjData.rightLaneAInfo.c1) + " ";

        otherInfo += rightLaneAInfoStr + "\n";
    }

    if(drawObjData.leftLaneBInfo.valid == 1)
    {
        QString leftLaneBInfoStr = "左车道线B ";

        leftLaneBInfoStr += "C2 " + QString::number(drawObjData.leftLaneBInfo.c2) + " ";
        leftLaneBInfoStr += "ViewRange " + QString::number(drawObjData.leftLaneBInfo.viewRange) + " ";

        switch (drawObjData.leftLaneBInfo.viewRangeValid)
        {
        case 0:
            leftLaneBInfoStr += "无效 ";
            break;
        case 1:
            leftLaneBInfoStr += "有效 ";
            break;
        }

        otherInfo += leftLaneBInfoStr + "\n";
    }

    if(drawObjData.rightLaneBInfo.valid == 1)
    {
        QString rightLaneBInfoStr = "右车道线B ";

        rightLaneBInfoStr += "C2 " + QString::number(drawObjData.rightLaneBInfo.c2) + " ";
        rightLaneBInfoStr += "ViewRange " + QString::number(drawObjData.rightLaneBInfo.viewRange) + " ";

        switch (drawObjData.rightLaneBInfo.viewRangeValid)
        {
        case 0:
            rightLaneBInfoStr += "无效 ";
            break;
        case 1:
            rightLaneBInfoStr += "有效 ";
            break;
        }

        otherInfo += rightLaneBInfoStr + "\n";
    }

    switch (drawObjData.speedlimitSign)
    {
    case 0:
        otherInfo += "未识别到限速牌 " ;
        break;
    case 1:
        otherInfo += "识别到限速牌 "+ QString::number(drawObjData.speed) + " km/h ";
        break;
    case 2:
        otherInfo += "识别到解除限速牌 "+ QString::number(drawObjData.speed) + " km/h ";
        break;
    }

    otherInfo += "\n";*/

   /* if(drawObjData.deviceInfoObj.valid)
    {
        QString deviceInfoStr =  "时间段:";
        switch (drawObjData.deviceInfoObj.timeInterval)
        {
        case 0:

            deviceInfoStr += "未知 " ;
            break;
        case 1:
            deviceInfoStr += "白天 " ;
            break;
        case 2:
            deviceInfoStr += "晚上 " ;
            break;
        default:
            deviceInfoStr += "保留 " ;
            break;
        }

        deviceInfoStr += "标定百分比:" + QString::number(drawObjData.deviceInfoObj.calibPercentage)+" ";
        switch (drawObjData.deviceInfoObj.calibStatus)
        {
        case 0:
            deviceInfoStr += "未标定";
            break;
        case 1:
            deviceInfoStr += "标定成功";
            break;
        case 2:
            deviceInfoStr += "标定中";
            break;
        case 3:
            deviceInfoStr += "标定失败";
            break;
        }

        switch (drawObjData.deviceInfoObj.sightlineShelter)
        {
        case 0:
            deviceInfoStr += "未遮挡 " ;
            break;
        case 1:
            deviceInfoStr += "遮挡 " ;
            break;
        default:
            deviceInfoStr += "保留 " ;
            break;
        }

        deviceInfoStr += " 版本号 " + QString::number(drawObjData.deviceInfoObj.versionMain)
                +" " + QString::number(drawObjData.deviceInfoObj.versionMinor)
                +" " + QString::number(drawObjData.deviceInfoObj.versionPatch);

        otherInfo += deviceInfoStr +"\n";
    }*/

}

void MyLabel::paintCoordinateSystem(QPainter* painter)
{
    /*
     * X方向和Y方向都只画3条线
     */

    int x0 = 0;
    int y0 = 0;
    int w = this->geometry().width();
    int h = this->geometry().height() - 20; /* 坐标原点上移20像素 */
    int x_step = w / 4;
    int y_step = h / 4;

    QPen pen(QColor(0, 0, 0));
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    QBrush brush(Qt::white);
    painter->setBrush(brush);
    painter->drawRect(0, 0, w, h);

    /* X方向 */
    {
        QVector<QLineF> lines;
        lines.append(QLineF(x0 + 1 * x_step, y0, x0 + 1 * x_step, y0 + h + 20));
        lines.append(QLineF(x0 + 2 * x_step, y0, x0 + 2 * x_step, y0 + h + 20));
        lines.append(QLineF(x0 + 3 * x_step, y0, x0 + 3 * x_step, y0 + h + 20));
		lines.append(QLineF(x0 + 4 * x_step, y0, x0 + 4 * x_step, y0 + h + 20));
		lines.append(QLineF(x0 + 5 * x_step, y0, x0 + 5 * x_step, y0 + h + 20));
        painter->drawLines(lines);
    }

    /* Y方向 */
    {
        QVector<QLineF> lines;
        lines.append(QLineF(x0, y0 + 1 * y_step, x0 + w, y0 + 1 * y_step));
        lines.append(QLineF(x0, y0 + 2 * y_step, x0 + w, y0 + 2 * y_step));
        lines.append(QLineF(x0, y0 + 3 * y_step, x0 + w, y0 + 3 * y_step));
		lines.append(QLineF(x0, y0 + 4 * y_step, x0 + w, y0 + 4 * y_step));
		lines.append(QLineF(x0, y0 + 5 * y_step, x0 + w, y0 + 5 * y_step));
        painter->drawLines(lines);
    }

    /* 坐标轴 */
    QPen pen2(Qt::cyan);
    pen2.setStyle(Qt::DotLine);
    pen2.setWidth(3);
    painter->setPen(pen2);
    painter->drawLine(QLineF(x0, y0 + h, x0 + w, y0 + h));
    painter->drawLine(QLineF(x0 + 2 * x_step, y0, x0 + 2 * x_step, y0 + h));

    /* 刻度值 */
    QPen pen3(Qt::black);
    pen3.setStyle(Qt::SolidLine);
    pen3.setWidth(3);
    painter->setPen(pen3);
    QFont font = painter->font();
    QString fontFamily("Consolas");
    font.setFamily(fontFamily);
    font.setPixelSize(12);
    painter->setFont(font);

    QString msg0("");
    QString msg1("");
    QString msg2("");
    QString msg3("");
    QString msg4("");

    switch (yRangeIndex)
    {
    case 0://10m
        msg0 = QString("0.0米");
        msg1 = QString("2.5米");
        msg2 = QString("5.0米");
        msg3 = QString("7.5米");
        msg4 = QString("10.0米");
        break;
    case 1://20m
        msg0 = QString("0.0米");
        msg1 = QString("5.0米");
        msg2 = QString("10.0米");
        msg3 = QString("15.5米");
        msg4 = QString("20.0米");
        break;
    case 2://30m
        msg0 = QString("0.0米");
        msg1 = QString("7.5米");
        msg2 = QString("15.0米");
        msg3 = QString("22.5米");
        msg4 = QString("30.0米");
        break;
    case 3://50m
        msg0 = QString("0.0米");
        msg1 = QString("12.5米");
        msg2 = QString("25.0米");
        msg3 = QString("37.5米");
        msg4 = QString("50.0米");
        break;
    case 4://100m
        msg0 = QString("0.0米");
        msg1 = QString("25.0米");
        msg2 = QString("50.0米");
        msg3 = QString("75.0米");
        msg4 = QString("100.0米");
        break;
    case 5://150m
        msg0 = QString("0.0米");
        msg1 = QString("37.5米");
        msg2 = QString("75.0米");
        msg3 = QString("112.5米");
        msg4 = QString("150.0米");
        break;
    case 6://200m
        msg0 = QString("0.0米");
        msg1 = QString("50.0米");
        msg2 = QString("100.0米");
        msg3 = QString("150.0米");
        msg4 = QString("200.0米");
        break;
    case 7://250m
        msg0 = QString("0.0米");
        msg1 = QString("62.5米");
        msg2 = QString("125.0米");
        msg3 = QString("187.5米");
        msg4 = QString("250.0米");
        break;
    case 8://300m
        msg0 = QString("0.0米");
        msg1 = QString("75.0米");
        msg2 = QString("150.0米");
        msg3 = QString("225.0米");
        msg4 = QString("300.0米");
        break;
    default:
        break;
    }

    {
        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0, y0 + h - 20, 80, 20);
            painter->drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, msg0, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0, y0 + y_step * 3 - 20, 80, 20);
            painter->drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, msg1, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0, y0 + y_step * 2 - 20, 80, 20);
            painter->drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, msg2, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0, y0 + y_step * 1 - 20, 80, 20);
            painter->drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, msg3, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0, y0 + y_step * 0, 80, 20);
            painter->drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, msg4, &boundingRect);
        }
    }

    switch (xRangeIndex) {
    case 0://10m
        msg0 = QString("-5.0米");
        msg1 = QString("-2.5米");
        msg2 = QString("0.0米");
        msg3 = QString("2.5米");
        msg4 = QString("5.0米");
        break;
    case 1://20m
        msg0 = QString("-10.0米");
        msg1 = QString("-5.0米");
        msg2 = QString("0.0米");
        msg3 = QString("5.0米");
        msg4 = QString("10.0米");
        break;
    case 2://30m
        msg0 = QString("-15.0米");
        msg1 = QString("-7.5米");
        msg2 = QString("0.0米");
        msg3 = QString("7.5米");
        msg4 = QString("15.0米");
        break;
    case 3://50m
        msg0 = QString("-25.0米");
        msg1 = QString("-12.5米");
        msg2 = QString("0.0米");
        msg3 = QString("12.5米");
        msg4 = QString("25.0米");
        break;
    case 4://100m
        msg0 = QString("-50.0米");
        msg1 = QString("-25.0米");
        msg2 = QString("0.0米");
        msg3 = QString("25.0米");
        msg4 = QString("50.0米");
        break;
    default:
        msg0 = QString("");
        msg1 = QString("");
        msg2 = QString("");
        msg3 = QString("");
        msg4 = QString("");
        break;
    }

    {
        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0 + x_step * 0, y0 + h, 80, 20);
            painter->drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, msg0, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0 + x_step * 1 - 40, y0 + h, 80, 20);
            painter->drawText(rectangle, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, msg1, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0 + x_step * 2 - 40, y0 + h, 80, 20);
            painter->drawText(rectangle, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, msg2, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0 + x_step * 3 - 40, y0 + h, 80, 20);
            painter->drawText(rectangle, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, msg3, &boundingRect);
        }

        {
            QRect boundingRect;
            const QRect rectangle = QRect(x0 + w - 80, y0 + h, 80, 20);
            painter->drawText(rectangle, Qt::AlignRight | Qt::AlignVCenter | Qt::TextSingleLine, msg4, &boundingRect);
        }
    }

}

void MyLabel::slotDisplayObj(const ME_DeviceData & drawObjData)
{
    drawObjData_ = drawObjData;
    QString obsInfo;
    QString otherInfo;
    tranferDrawObjData(drawObjData, obsInfo,otherInfo);

    emit signalObstacleInfoChanged(obsInfo,otherInfo);

    update();
}

void MyLabel::slotCoordinateChanged(int xIndex, int yIndex)
{
    xRangeIndex = xIndex;
    yRangeIndex = yIndex;
    update();
}

void MyLabel::drawObject(QPainter* painter,const Position *info,  ObstacleData_B mapObstacleData)
{
    int objDrawPosX = 0;
    int objDrawPosY = 0;
    float x_range_meter = 0.0;
    float y_range_meter = 0.0;
    float x_scale = 0.0; /* 米/每像素 */
    float y_scale = 0.0; /* 米/每像素 */

    switch (yRangeIndex) {
    case 0://10m
        y_range_meter = 10.0;
        break;
    case 1://20m
        y_range_meter = 20.0;
        break;
    case 2://30m
        y_range_meter = 30.0;
        break;
    case 3://50m
        y_range_meter = 50.0;
        break;
    case 4://100m
        y_range_meter = 100.0;
        break;
    case 5://150m
        y_range_meter = 150.0;
        break;
    case 6://200m
        y_range_meter = 200.0;
        break;
    case 7://250m
        y_range_meter = 250.0;
        break;
    case 8://300m
        y_range_meter = 300.0;
        break;
    default:
        break;
    }

    y_scale = y_range_meter / ( this->geometry().height() - 20);

    switch (xRangeIndex) {
    case 0://10m
        x_range_meter = 10.0;
        break;
    case 1://20m
        x_range_meter = 20.0;
        break;
    case 2://30m
        x_range_meter = 30.0;
        break;
    case 3://50m
        x_range_meter = 50.0;
        break;
    case 4://100
        x_range_meter = 100.0;
        break;
    default:
        break;
    }

    x_scale = x_range_meter / this->geometry().width();
	int a = this->geometry().height();
	/*if (info->position_x == NULL)
	{
		return;
	}*/
    objDrawPosY = (this->geometry().height() - 20 - info->position_x / y_scale);
    objDrawPosX =  this->geometry().width() / 2 + info->position_y / x_scale;


    int r = 5;
    painter->setRenderHint(QPainter::Antialiasing);
    QRadialGradient radialGradient(objDrawPosX, objDrawPosY, r, objDrawPosX, objDrawPosY);
    painter->setPen(Qt::NoPen);
	radialGradient.setColorAt(0.0, TipsLabel::getColorByType(1));
    radialGradient.setColorAt(0.8, Qt::white);
    radialGradient.setColorAt(1.0, Qt::black);
    painter->setBrush(QBrush(radialGradient));
    painter->drawEllipse(objDrawPosX - r, objDrawPosY - r, 2 * r, 2 * r);
	if (mapObstacleData.CIPVFlags == 1)
	{
		r = 10;
		QRadialGradient radialGradient(objDrawPosX, objDrawPosY, r, objDrawPosX, objDrawPosY);
		radialGradient.setColorAt(0.0, TipsLabel::getColorByType(0));
		radialGradient.setColorAt(0.8, Qt::white);
		radialGradient.setColorAt(1.0, Qt::black);
		painter->setBrush(QBrush(radialGradient));
		painter->drawEllipse(objDrawPosX - r, objDrawPosY - r, 2 * r, 2 * r);
	}



    //QPen pen(Qt::black);
    //pen.setStyle(Qt::SolidLine);
    //painter->setPen(pen);
    //QFont font = painter->font();
    //QString fontFamily("Consolas");
    //font.setFamily(fontFamily);
    //font.setPixelSize(14);
    //painter->setFont(font);
    //int textWidth = 4 * r;
    //int textHeight = 4 * r;
    //const QRect rectangle = QRect(objDrawPosX - 2 * r, objDrawPosY - 4 * r, textWidth, textHeight);
    //QRect boundingRect;
    ////painter->drawText(rectangle, Qt::AlignHCenter | Qt::AlignVCenter | Qt::TextSingleLine, QString::number(info->ID, 10), &boundingRect);

}
