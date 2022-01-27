#include "TipsLabel.h"
#include <QDebug>
#include <QPainter>

QList<ObjType> TipsLabel::objTypes;

TipsLabel::TipsLabel(QWidget *parent):
    QLabel(parent)
{
    objTypes.append({Qt::red,"CIPV",0});
	objTypes.append({ Qt::green,"others",1 });
    objTypes.append({Qt::green,"others",2});
    objTypes.append({Qt::green,"others",3});
    //objTypes.append({Qt::blue,"unused",0x5});
}

QString TipsLabel::getObjNameByType(int typeId)
{
    for(int i = 0; i < objTypes.size(); ++i)
    {
        if(objTypes.at(i).typeId == typeId)
        {
            return objTypes.at(i).typeName;
        }
    }

    return "unused";
}

QColor TipsLabel::getColorByType(int typeId)
{
    for(int i = 0; i < objTypes.size(); ++i)
    {
        if(objTypes.at(i).typeId == typeId)
        {
            return objTypes.at(i).color;
        }
    }

    return Qt::red;
}

/*
 * 颜色区分Obstacle的类型
 * Vehicle  蓝色
 * Truck    黄色
 * Bike     紫色
 * Ped      红色
 * Bicycle  绿色
 */
void TipsLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int textWidth  = 150;
    int textHeight = 30;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for(int i = 0;i < 2;++i)
    {
        int r = 10;
        int ObjImageX = 30 + (textWidth + r) * i;
        int ObjImageY = 15;

        QRadialGradient radialGradient(ObjImageX, ObjImageY, r, ObjImageX, ObjImageY);
        painter.setPen(Qt::NoPen);
        radialGradient.setColorAt(0.0, objTypes[i].color);
        radialGradient.setColorAt(0.8, Qt::white);
        radialGradient.setColorAt(1.0, Qt::black);
        painter.setBrush(QBrush(radialGradient));
        painter.drawEllipse(ObjImageX - r, ObjImageY - r, 2 * r, 2 * r);

        QPen pen(objTypes[i].color);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        QFont font = painter.font();
        QString fontFamily("Consolas");
        font.setFamily(fontFamily);
        font.setPixelSize(12);
        painter.setFont(font);
        const QRect rectangle = QRect(ObjImageX + r, 0, textWidth, textHeight);
        QRect boundingRect;
        painter.drawText(rectangle, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, objTypes[i].typeName, &boundingRect);
    }
}
